/** @file sw.c
    Create network model from parse tree 

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sw.h"
#include "swconfig.h"
#include "swsym.h"
#include "model.h"
#include <assert.h>       
#include <sys/stat.h>


#define DEBUGGING

static char *iptype_save="";  		/* latest visited IP type */  
static  Process fl = NULL;		/** List of processes to free	*/

/** Place to store latest visited source port. */
Port LatestSrcPort = NULL;  

/** Current network type. */
TYPE type = IS_NET;

int bs = 1;			/**<  Buffer size */
Model net_model = NULL;		/**<  Network model anchor point. */

#ifdef DEBUGGING
static int VerifyStream(Stream s)
{				/* Check proper Stream connections */
    Process src, snk;
    Port psrc, psnk;

    assert(s);
    src = s->source;
    snk = s->sink;
    assert(src && snk);
    psrc = s->SourcePort;
    psnk = s->SinkPort;

    assert(psrc && psnk);
    assert(psrc->id == s->source_id);
    assert(psnk->id == s->sink_id);
    assert(psrc->stream == s);
    assert(psnk->stream == s);
    assert(s->SourcePort->stream->SourcePort == s->SourcePort);
    assert(s->SinkPort->stream->SinkPort == s->SinkPort);

    if (src->kind == IS_NET) {
	assert(psnk->match == psrc);
	assert(psrc->match == psnk);
    }

    return 1;
}
#else
#define VerifyStream(S)
#define checkSource(S)
#endif

static Subnetm linkSubnet(Model m, char *name)
{
    Subnetm sn2;

    sn2 = m->subnetm;
    if (!sn2) {
	sn2 = (Subnetm) malloc(sizeof(Subnetm_));
	sn2->name = name;
	sn2->stream = NULL;
	sn2->extport = NULL;
	sn2->next = NULL;
	m->subnetm = sn2;
	return sn2;
    }

    while (sn2) {
	if (strncmp(name, sn2->name, 100) == 0) {
	    return sn2;
	}
	sn2 = sn2->next;
    }
    sn2 = (Subnetm) malloc(sizeof(Subnetm_));
    sn2->name = name;
    sn2->stream = NULL;
    sn2->extport = NULL;
    sn2->next = m->subnetm;
    m->subnetm = sn2;
    return sn2;
}

static void linkExt(Subnetm sn, Extport pt)
{
    Extport pt2;

    pt2 = sn->extport;
    if (!pt2) {
	sn->extport = pt;
	return;
    }
    pt->next = pt2;
    sn->extport = pt;
}

/** Make subnet definition */
Subnetm MakeSubnetm(Ident name, Stream s, Extport in, Extport out)
{
    Subnetm sn;

    sn = linkSubnet(net_model, name);

    if (s) {
	s->next = sn->stream;
	sn->stream = s;
    }

    if (in) {
	linkExt(sn, in);
    } else {
	if (out) {
	    linkExt(sn, out);
	}
    }

    return sn;
};

/** Make Model structure */
Model MakeModel(Stream f)
{
    Model m;

    m = (Model) malloc(sizeof(Model_));

    if (!m) {
	FAIL(MakeModel, "Out of memory when allocating Process!\n");
    }

    m->nstreams = 0;
    m->ncomponents = 0;
    m->nprocs = 0;
    m->level  = 0;
    m->stream = f;
    m->proc = NULL;
    m->subnetm = NULL;
    m->comp=NULL;
    m->name = "SW";
    return m;

}

static char **MakeArg(ListArgument la, char *name)
{
    char **arg;			/* Pointer to array of string pointers. */
    int i = 1, narg = 1;
    ListArgument la2 = la;

    while (la2) {
	narg++;
	la2 = la2->listargument_;
    }

    arg = (char **) malloc((narg + 1) * sizeof(char *));
    arg[0] = name;
    arg[narg] = NULL;

    i = narg - 1;
    while (la) {
	arg[i--] = visitStringval(la->argument_->u.argumentx_.stringval_);
	la = la->listargument_;
    }

    return arg;
}

static char *fixName(char *name)
{
    char bfr[101];
    static int nanon = 1;	/* Number of anonymous processes */

    if (name[0] == '_') {	// Anonymous process Q
	sprintf(bfr, "_%i", nanon++);
	return strndup(bfr, 100);
    }
    return name;
}

static Process
MakeProcess(Model model, Ident name, Component comp, char **arg)
{
    Process p;


    if (name[0] == '_' && name[1] == 0)
	name = fixName(name);
    p = getProc(name);

    if (p == NULL) {
	p = (Process) malloc(sizeof(Process_));
	if (!p) {
	    FAIL(MakeProcess, "Out of memory when allocating Process!\n");
	}
	p->comp = NULL;
	if (comp)
	    p->comp = comp;
	p->name = name;
	p->nportsIn = 0;
	p->nportsOut = 0;
	p->port = NULL;
	p->kind = type;
	p->depth = 0;
	if (type == IS_NET) {
	    p->next = model->proc;
	    model->proc = p;
	    model->nprocs++;
	} else {
	    p->next = NULL;
	}
	p->arg = arg;
	p->arg[0] = name;
	addProc(name, p);
    } else {
	if (comp) {
	    p->comp = comp;
	}
    }

    return p;

}

static int fixId(int i)
{
    if (i < 0)
	return 0;
    return i;
}

/** Make Port structure */
Port MakePort(int n, Ident id)
{
    Port p;

    p = (Port) malloc(sizeof(Port_));
    if (!p) {
	fprintf(stderr, "Error: out of memory when allocating Port!\n");
	exit(1);
    }

    if (id) {
	p->name = id;
    } else {
	p->name = "";
    }
    p->id = n;
    p->channel = -1;
    p->match = NULL;
    p->stream = NULL;
    p->next = p;
    p->prev = p;
    p->match = NULL;
    return p;
}

/** Make Component structure */
//  @BUG Lookup existing component first
Component MakeComponent(Ident name, String path)
{
    Component c;

    c = getComponent(name, path);

    if (c == NULL) {
	c = (Component) malloc(sizeof(Component_));
	if (path[0] != '_') {    /* subnet? */
	    net_model->ncomponents++;
	    c->next=net_model->comp;   /* Link component to list */
	    net_model->comp=c;
	}
    }
    if (!c) {
	fprintf(stderr,
		"Error: out of memory when allocating Component!\n");
	exit(1);
    }

    addComponent(name, path, c);	/* Add to symbol table */
    c->name = name;
    c->path = path;
    return c;
}


/** Make Stream structure */
static Stream MakeStream(TYPE type, Process src, Process snk, int bs, Model m,
	   Port SourcePort, Port SinkPort, char *iptype)
{
    Stream f;

    if (!src) {
	FAIL(MakeStream, "No source for stream. Hermit maybe.\n");
	exit(0);
    }

    f = (Stream) malloc(sizeof(Stream_));

    if (!f) {
	FAIL(MakeStream, "Out of memory when allocating Stream!\n");
    }
    f->SourcePort = SourcePort;
    f->SinkPort = SinkPort;
    f->source = src;
    f->sink = snk;
    f->next = NULL;
    f->type = type;		
    f->next = m->stream;
    m->stream = f;
    if (bs < 0)
	bs = 0;
    if (bs > maxbfsz)
	bs = maxbfsz;
    f->bufsz = bs;
    f->iptype = iptype;    /* From visiting arrows */	

    switch (type) {
    	case IS_NET:
		m->nstreams++;
		__attribute__ ((fallthrough));
   	case IS_SUB:
    		f->source_id = fixId(SourcePort->id);
   	 	f->sink_id   = fixId(SinkPort->id);
		break;
    	case IS_ORPHAN:
		break;
		badkind(MakeStream);
    }
	
    return f;
}

/** Subnet port id */
Ident visitSubId(SubId p)
{
  return p;
}

/** Numeric variable */
Numvar visitNumvar(Numvar p)
{
    return p;
}

/** String variable */
String visitStringvar(Stringvar p) {
	   return p;
}

/** Environment variable */
String visitEnvar(Envar p)
{
  return p;
}

/** Get Environment variable */
String getEnvVar(String s) {
	String s1,s2;

	s1=s+2;
	s2=getenv(s1);
	return s2;
	return(getenv("BROWSER"));
}

String visitStringval(Stringval _p_) {   /**<Get String value*/

    switch (_p_->kind) {
    case is_StringVals:
	return visitString(_p_->u.stringvals_.string_);
    case is_StringValv:
	return getStringVar(_p_->u.stringvalv_.stringvar_);
    case is_StringVale:
    	return(getEnvVar(visitEnvar(_p_->u.stringvale_.envar_)));
    default:
	badkind(Stringval);
    }
}

/** Get Numeric value */
Integer visitNumval(Numval _p_)		
{
    switch (_p_->kind) {
    case is_NumVali:
	return (visitInteger(_p_->u.numvali_.integer_));
    case is_NumValv:
	visitNumvar(_p_->u.numvalv_.numvar_);
	return 0;
    default:
	badkind(Numval);
    }
}

/** Assign value to numeric variable. */
void visitNumassgn(Numassgn _p_)   
{
    switch (_p_->kind) {
    case is_NumAssgnv:
	visitNumvar(_p_->u.numassgnv_.numvar_);
	visitNumval(_p_->u.numassgnv_.numval_);
	break;
    default:
	badkind(Numassgn);
    }
}

#if 1
/** Get Id */
#define visitId(i) (String) i
#else
/** Get Id */
String visitId(Id i)
{
    return i;
}
#endif

/** Get Symbol value */
String visitSymval(Symval _p_)		 /**<Get symbol value.*/
{
    switch (_p_->kind) {
    case is_Symvalv:
	return getSymVar(_p_->u.symvalv_.symvar_);

    case is_Symvali:
	return (visitId(_p_->u.symvali_.id_)); 

    default:
	badkind(Symval);
    }
}

/** Assign value to symbol*/
String visitSymAssgn(SymAssgn _p_)		 
{
    return addSymVar(_p_->u.symassgni_.symvar_,
    	visitSymval(_p_->u.symassgni_.symval_));
}

/** Assign value to String variable */
void visitStrassgn(Strassgn _p_)
{
	addStringVar( 
    		visitStringvar(_p_->u.strassgnv_.stringvar_),
    		visitSymval(_p_->u.strassgnv_.symval_)
	);
}

/** Get buffer size */
Integer visitBuffsize(Buffsize _p_)
{
    switch (_p_->kind) {
    case is_Bufszi:
	return (visitNumval(_p_->u.bufszi_.numval_));
    case is_Bufsze:
	return defaultBufferSize;   
    default:
	badkind(Buffsize);
    }
}


String visitSymvalu(Symvalu p)
{
  switch(p->kind)
  {
  case is_Symvaluv:
    return visitSymval(p->u.symvaluv_.symval_);
  case is_Symvaluu:
    return "_";
  default:
    badkind(Symvalu);
  }
}

String visitTypeDef(TypeDef p)
{
  switch(p->kind)
  {
  case is_Typedefa:
    return visitSymvalu(p->u.typedefa_.symvalu_);
  case is_Typedefnull:
    return "";
  default:  
	  badkind(TypgDef);
  }
}

/** Get left arrow bufferize */
Integer visitLarrow(Larrow _p_)
{
    iptype_save=visitTypeDef(_p_->u.arrowx_.typedef_);
    return visitBuffsize(_p_->u.arrowx_.buffsize_);
}

/** Get right arrow buffersize */
Integer visitRarrow(Rarrow _p_)
{
    iptype_save=visitTypeDef(_p_->u.arrowr_.typedef_);
    return visitBuffsize(_p_->u.arrowr_.buffsize_);
}

/** Add port,p to port list at P->port in order by port id*/
static void linkPort(Process P, Port p)
{
    Port p2;

    if (!P->port) {
	P->port = p;
	p->next = p;
	p->prev = p;
	return;
    }

    p2 = P->port;

    do {
	if (p->id < p2->id) {
	    p->next = p2;
	    p->prev = p2->prev;
	    if (P->port == p2) {
		P->port = p;
	    }
	    p->prev->next = p;
	    p->next->prev = p;
	    return;
	}
	p2 = p2->next;
    }
    while (p2 != P->port);

    p->next = P->port;
    p->prev = p2->prev;
    p->next->prev = p;
    p->prev->next = p;

}

/** Set stream pointer in port structure */
static void setStream(Port pt, Stream s)
{
    while (pt->stream) {
	pt = pt->next;
    }
    pt->stream = s;
}

/** Set number of out ports in source process */
static void SetSource(Process p)
{

    p->nportsOut++;
}

/** Set number of input ports in sink process */
static void SetSink(Process p)
{

    p->nportsIn++;
}

static Process lastProc=NULL;
 
/** Get stream structure */
Stream visitdataflow(DataFlow _p_)
{
    Process snk, src;
    Port pt, src_pt, snk_pt;
    Stream s, s2;
    int bs;

    switch (_p_->kind) {
    case is_Streamx:
	bs = visitLarrow(_p_->u.streamx_.larrow_);
	lastProc = src = visitProc(_p_->u.streamx_.proc_2);
	snk = visitProc(_p_->u.streamx_.proc_1);
	src_pt = visitPrt(_p_->u.streamx_.prt_2);
	snk_pt = visitPrt(_p_->u.streamx_.prt_1);
	linkPort(snk, snk_pt);
	SetSink(snk);
	SetSource(src);
	linkPort(src, src_pt);
	s = MakeStream(type, src, snk, bs, net_model, src_pt, snk_pt, iptype_save);
	iptype_save="";
	s->SourcePort = src_pt;
	s->SinkPort = snk_pt;
	s->SourcePort->stream = s->SinkPort->stream = s;
	s->sink_id = snk_pt->id = fixId(snk_pt->id);
	s->source_id = src_pt->id = fixId(src_pt->id);
	s->SinkPort->match = s->SourcePort;
	s->SourcePort->match = s->SinkPort;
	VerifyStream(s);
	return s;
    case is_Streamrx:
	src = visitProc(_p_->u.streamrx_.proc_1);
	LatestSrcPort = visitPrt(_p_->u.streamrx_.prt_1);
	linkPort(src, LatestSrcPort);
	SetSource(src);
	lastProc = snk = visitProc(_p_->u.streamrx_.proc_2);
	pt = visitPrt(_p_->u.streamrx_.prt_2);
	linkPort(snk, pt);
	SetSink(snk);
	bs = visitRarrow(_p_->u.streamrx_.rarrow_);
	s = MakeStream(type, src, snk, bs, net_model, LatestSrcPort,
		       pt, iptype_save);
	iptype_save="";
	setStream(LatestSrcPort, s);
	setStream(pt, s);
	s->sink_id = pt->id = fixId(pt->id);
	s->source_id = LatestSrcPort->id = fixId(LatestSrcPort->id);
	s->SinkPort->match = s->SourcePort;
	s->SourcePort->match = s->SinkPort;
	VerifyStream(s);
	return s;

    case is_Streamy:
	visitdataflow(_p_->u.streamy_.dataflow_);
	snk = lastProc;
	pt = visitPrt(_p_->u.streamy_.prt_1);
	bs = visitLarrow(_p_->u.streamy_.larrow_);
	LatestSrcPort = visitPrt(_p_->u.streamy_.prt_2);
	lastProc = src = visitProc(_p_->u.streamy_.proc_);
	linkPort(src, LatestSrcPort);
	SetSource(src);
	linkPort(snk, pt);
	SetSink(snk);
	s2 = MakeStream(type, src, snk, bs, net_model, LatestSrcPort,
			pt, iptype_save);
	iptype_save="";
	s2->SourcePort->stream = s2->SinkPort->stream = s2;
	s2->SourcePort = LatestSrcPort;
	s2->SinkPort = pt;
	s2->SourcePort->stream = s2->SinkPort->stream = s2;
	s2->sink_id = pt->id = fixId(pt->id);
	s2->source_id = LatestSrcPort->id = fixId(LatestSrcPort->id);
	s2->SinkPort->match = s2->SourcePort;
	s2->SourcePort->match = s2->SinkPort;
	VerifyStream(s2);
	return s2;
    case is_Streamry:
	 visitdataflow(_p_->u.streamry_.dataflow_);
	src 	 = lastProc;
	lastProc = snk = visitProc(_p_->u.streamry_.proc_);
	bs 	 = visitRarrow(_p_->u.streamry_.rarrow_);
	src_pt 	 = visitPrt(_p_->u.streamry_.prt_1);	/* Source Port */
	src_pt->id = fixId(src_pt->id);
	linkPort(src, src_pt);
	SetSource(src);
	pt 	 = visitPrt(_p_->u.streamry_.prt_2);	/* Sink Port */
	pt->id 	 = fixId(pt->id);
	linkPort(snk, pt);
	SetSink(snk);
	s2 		= MakeStream(type, src, snk, bs, net_model, src_pt, pt, iptype_save);
	iptype_save   	= "";
	s2->SinkPort = pt;
	setStream(src_pt, s2);
	setStream(pt, s2);
	s2->sink_id 	= pt->id;
	s2->source_id 	= src_pt->id;
	s2->SinkPort->match   = s2->SourcePort;
	s2->SourcePort->match = s2->SinkPort;
	VerifyStream(s2);
	return s2;

    default:
	badkind(dataflow);
    }
}

static String saves = NULL;   /**<Save name ?? */
/** Create an external port structure. */
Extport MakeExtport(PortType type, Process p, Port prt, int bs, int id)
{
    Extport ep;

    ep 		= (Extport) malloc(sizeof(Extport_));
    ep->type 	= type;
    linkPort(p, prt);
    ep->name 	= prt->name = saves;
    saves 	= NULL;
    
    if (type == SINK) {
	ep->sink = p;
	ep->source = NULL;
	ep->sink_id = fixId(prt->id);
	ep->source_id = id;
	SetSink(p);
    } else {
	ep->source = p;
	ep->sink = NULL;
	ep->source_id = fixId(prt->id);
	ep->sink_id = id;
	SetSource(p);
    }

    ep->bufsz  = bs;
    ep->iptype = NULL;
    ep->next   = NULL;
    return ep;
}

/** Get tab */
Integer visitTab(Tab _p_)
{
    switch (_p_->kind) {
    case is_Tabn:
	return visitNumval(_p_->u.tabn_.numval_);
    case is_Tabs:
	saves = visitSymval(_p_->u.tabs_.symval_);	 
	return -2;
    default:
	badkind(Tab);
    }
}

/** Get external input port */
Extport visitExtPortIn(ExtPortIn _p_)
{
    Extport ep; 
    switch (_p_->kind) {
    case is_Extin:
	ep = MakeExtport(SINK,
			   visitProc(_p_->u.extin_.proc_),
			   visitPrt(_p_->u.extin_.prt_),
			   visitLarrow(_p_->u.extin_.larrow_),
			   visitTab(_p_->u.extin_.tab_));
	ep->iptype = strdup(iptype_save);
	iptype_save="";
        return ep;
    case is_ExtinR:
	ep = MakeExtport(SINK,
			   visitProc(_p_->u.extinr_.proc_),
			   visitPrt(_p_->u.extinr_.prt_),
			   visitRarrow(_p_->u.extinr_.rarrow_),
			   visitTab(_p_->u.extinr_.tab_));
	ep->iptype = strdup(iptype_save);
	iptype_save="";
        return ep;
    default:
	badkind(ExtPortIn);
    }

}

/** Get external output port. */
Extport visitExtPortOut(ExtPortOut _p_)
{
    Extport ep;
    switch (_p_->kind) {
    case is_Extout:
	ep = MakeExtport(SOURCE,
			   visitProc(_p_->u.extout_.proc_),
			   visitPrt(_p_->u.extout_.prt_),
			   visitLarrow(_p_->u.extout_.larrow_),
			   visitTab(_p_->u.extout_.tab_));
	ep->iptype = strdup(iptype_save);
	iptype_save="";
	return ep;		   
    case is_Extoutr:
	return MakeExtport(SOURCE,
			   visitProc(_p_->u.extoutr_.proc_),
			   visitPrt(_p_->u.extoutr_.prt_),
			   visitRarrow(_p_->u.extoutr_.rarrow_),
			   visitTab(_p_->u.extoutr_.tab_));
	ep->iptype = strdup(iptype_save);
	iptype_save="";
	return ep;
    default:
	badkind(ExtPortOut);
    }
}

/** Get hermit structure */
Process visitHermt(Hermt _p_)
{
    char *name;
    Process p;
    type = IS_NET;
    switch (_p_->kind) {
    case is_Hermtx:
	name = visitSymvalu(_p_->u.hermtx_.symvalu_);
	p = MakeProcess(net_model,
			name,
			visitComp(_p_->u.hermtx_.comp_),
			MakeArg(visitListArgument
				(_p_->u.hermtx_.listargument_), name));
	return p;
    case is_Hermty:
	p = MakeProcess(net_model,
			visitSymvalu(_p_->u.hermty_.symvalu_), NULL,
			MakeArg(visitListArgument
				(_p_->u.hermty_.listargument_), NULL));

	return p;
    default:
	badkind(Hermt);
    }
}

/** Get underscore ?? */
static Ident UnderScore( Ident id) {
	Ident uid;

	uid = id;  // ?? add underscore later. Just refactor now.
	return uid;
}

/** Get subnet */
Subnetm visitSubnet(Subnet _p_, Ident id)
{
    Stream s = NULL;
    Extport eport = NULL;
    Process p;

    switch (_p_->kind) {
    case is_Sneth:
	p = visitHermt(_p_->u.sneth_.hermt_);
	if (!p->comp)
	    p->comp = MakeComponent(p->name, defaultPath);
	return MakeSubnetm(id, NULL, eport, eport);
    case is_Snets:
	s = visitdataflow(_p_->u.snets_.dataflow_);
	return MakeSubnetm(id, s, eport, eport);
    case is_Snetin:
	return MakeSubnetm(id, s,
			   visitExtPortIn(_p_->u.snetin_.extportin_),
			   eport);
    case is_Snetout:
	return MakeSubnetm(id, s,
			   visitExtPortOut(_p_->u.snetout_.extportout_),
			   eport);
    default:
	badkind(Subnet);
    }
}

/** Get subnet list */
static void visitListSubnet(ListSubnet listsubnet, Ident id)
{
    while (listsubnet != 0) {
	(visitSubnet(listsubnet->subnet_, UnderScore(id)));
	listsubnet = listsubnet->listsubnet_;
    }
}

/** Get subnet definition */
void visitSubdef(Subdef _p_)
{	
    visitListSubnet(_p_->u.snet_.listsubnet_,
	visitSubId(_p_->u.snet_.subid_));
    //visitListSubnet(_p_->u.snet_.listsubnet_,
	//		    visitSymval(_p_->u.snet_.symval_));
}

#define BUFFSIZE 1000
static char *Exists(char *s) {
	struct stat sb;
	char bfr[BUFFSIZE+1];
	
	if(lstat(s, &sb) == 0)
		return s; 
	
	if(includePath==NULL) 
		return NULL;
		
	strncpy(bfr,includePath,BUFFSIZE);
	if( lstat( strncat(bfr,s,BUFFSIZE), &sb ) == 0 ) 
		return strdup(bfr);
			
	return NULL;		
}

static char *findFile(char *s) {
	char *s2;
	
	s2=Exists(s);
	
	if(s2 != NULL )
		return s2;
		
        FAIL(Cannot locate, s);
}

/** Get network statement. */
void visitStm(Stm _p_)
{
    Process p;     
    ValidSW pt;
    type = IS_NET;
    
    switch (_p_->kind) {
    case is_Stminc:
         pt = IncludeFile(visitString(findFile(_p_->u.stminc_.string_)));  
         visitListStm(pt->u.valid_.liststm_);
         return;
    case is_Stmx:
	visitdataflow(_p_->u.stmx_.dataflow_);
	return;
    case is_Stmn:
	visitNumassgn(_p_->u.stmn_.numassgn_);
	return;
    case is_Stms:
	visitStrassgn(_p_->u.stms_.strassgn_);
	return;  
    case is_Stmb:
    	visitSymAssgn(_p_->u.stmb_.symassgn_);
	break;
    case is_Stmnet:
	type = IS_SUB;
	visitSubdef(_p_->u.stmnet_.subdef_);
	break;
    case is_Stmh:
	p = visitHermt(_p_->u.stmh_.hermt_);
	if (!p->comp)
	    p->comp = MakeComponent(p->name, defaultPath);
	break;
    default:
	badkind(Stm);
    }
}

/** Get network statement list */
void visitListStm(ListStm liststm)
{

    while (liststm != NULL) {
	visitStm(liststm->stm_);
	liststm = liststm->liststm_;
    }
}


/** Get process */
Process visitProc(Proc _p_) {

    switch (_p_->kind) {

    case is_Processx:
	return MakeProcess(net_model,
			   visitSymvalu(_p_->u.processx_.symvalu_),
			   visitComp(_p_->u.processx_.comp_),
			   MakeArg(visitListArgument
				   (_p_->u.processx_.listargument_),
				   visitSymvalu(_p_->u.processx_.symvalu_)));

    case is_Processy:
	return MakeProcess(net_model,
			   visitSymvalu(_p_->u.processy_.symvalu_),
			   NULL,
			   MakeArg(visitListArgument
				   (_p_->u.processy_.listargument_),
				   NULL));
    default:
	badkind(Proc);
    }
}

/** Get port */
Port visitPrt(Prt _p_)
{
    switch (_p_->kind) {
    case is_Portx:

	return (MakePort(visitNumval(_p_->u.portx_.numval_), NULL));
    case is_Portni:
	return MakePort(visitNumval(_p_->u.portni_.numval_),
			visitSymval(_p_->u.portni_.symval_));
    case is_Portin:
	return MakePort(visitNumval(_p_->u.portin_.numval_),
			visitSymval(_p_->u.portin_.symval_));
    case is_Portn:
	return MakePort(-1, visitSymval(_p_->u.portn_.symval_));
    case is_Porte:
	return MakePort(-1, NULL);
    default:
	badkind(Prt);
    }
}


/** Create module path ( also used in swconfig.c ) */
char *makeModPath(char *pn, char *nn)
{
    char bfr[100];

    strncpy(bfr, pn, 100);
    strncat(bfr, "/", 99);
    strncat(bfr, nn, 100);
    return (strdup(bfr));
}

String prepend(char *pp, char *ap) {
	char bfr[300];
	strncpy(bfr, pp, 300);
    	strncat(bfr, ap, 300-strlen(bfr) );
    	return (strdup(bfr));
}

/** Get module path */
String visitModPath(ModPath p)
{
  switch(p->kind)
  {
  case is_Modpa:
    return prepend("/", visitSymval(p->u.modpa_.symval_));
  case is_Modpx:
    return(visitSymval(p->u.modpx_.symval_));
  case is_Modpy:
    return( makeModPath(	
    	visitModPath(p->u.modpy_.modpath_),
    	visitSymval(p->u.modpy_.symval_)));
  default:
  	badkind(ModPath);
  }
}

String  visitValidImport(ValidImport s0) { 
	return s0;
}   

Component visitRemPath(RemPath p)
{
    return  MakeComponent(
    	visitSymval(p->u.rempatha_.symval_), 
    	visitValidImport(p->u.rempatha_.validimport_)); 
}

/** Get component */
Component visitComp(Comp _p_)
{
    switch (_p_->kind) {
    case is_Compa:
    	return  visitRemPath(_p_->u.compa_.rempath_);
    case is_Compx:
	return MakeComponent(visitSymval(_p_->u.compx_.symval_),
			     defaultPath);
    case is_Compn:
	return MakeComponent(visitSubId(_p_->u.compn_.subid_),"_");
    case is_Compz:
    	return MakeComponent(	
    		visitSymval(_p_->u.compz_.symval_),
    		visitModPath(_p_->u.compz_.modpath_));
    default:		
	badkind(Comp);
    }
}

/** Get process argument */
Argument visitArgument(Argument _p_)
{
    Argument arg;

	//visitStringval(_p_->u.argumentx_.stringval_);
	arg=make_Argumentx(make_StringVals
		       (visitStringval(_p_->u.argumentx_.stringval_)));
    return arg;
	//make_Argumentx(
	//	       (visitStringval(_p_->u.argumentx_.stringval_));
}

/** Get list of arguments.*/
ListArgument visitListArgument(ListArgument listargument)
{
    ListArgument l = NULL;

    while (listargument != 0) {
	l = make_ListArgument(visitArgument(listargument->argument_), l);
	listargument = listargument->listargument_;
    }

    return l;

}

/** Get Integer */
Integer visitInteger(Integer i)
{
    return i;
}

/** Get String */
String visitString(String s)
{
    return s;
}

/** Create a name string */
static char *makeName(char *pn, char *nn)
{
    char bfr[1000];

    strncpy(bfr, pn, 500);
    strncat(bfr, "_", 501);
    strncat(bfr, nn, 1000);
    return (strdup(bfr));
}


/** Check depth of subnet expansion.   Subnets may invoke subnets up to maxdepth depth. */
static int CheckDepth(int d)
{
    if (d > maxdepth) {
	sprintf(fbfr,
		"Exceeded maximum subnet expansion depth, %d. Loop maybe.\n",
		maxdepth);
	FAIL(CheckDepth, fbfr);
    }
    return d + 1;
}

static int typeOK( char *s1, char *s2) { 
	if( s1 == NULL || *s1 == 0) 
		return 1;
	if( s2 == NULL || *s2 == 0) 
		return 1;
	if(strcmp(s1,s2) == 0 ) 
		return 1;	
	
	return 0;
}

static void checkIPtype(char *msg, char *srcType, char *snkType, char *srcName, char *snkName) {
    
    if(! typeOK(srcType, snkType)) {
	sprintf(fbfr,
		"%s: Type Mismatch for (%s) -%s>  and (%s) -%s>\n",
		msg,
		srcName, 
		srcType,
		snkName,
		snkType);
    	FAIL(msg, fbfr);
    }
}

/** Expand a subnet*/
static void Expand2(Model m, Process p, Stream s)
{
    char *srcname, *snkname;	// Concatenated process names 
    Process src, snk;
    Port psrc, psnk;
    Stream ns;			/* New Stream */
    type = IS_NET;

    srcname = makeName(p->name, s->source->name);
    snkname = makeName(p->name, s->sink->name);
    src = MakeProcess(m, srcname, s->source->comp, MakeArg(NULL, NULL));
    src->arg = s->source->arg;
    snk = MakeProcess(m, snkname, s->sink->comp, MakeArg(NULL, NULL));
    snk->arg = s->sink->arg;
    psrc = MakePort(s->source_id, s->source->port->name);
    psnk = MakePort(s->sink_id, s->sink->port->name);
    linkPort(src, psrc);
    linkPort(snk, psnk);
    src->nportsOut++;
    snk->nportsIn++;
    bs = s->bufsz;
    ns = MakeStream(type, src, snk, bs, m, psrc, psnk, s->iptype);
    ns->sink_id = s->sink_id;
    ns->source_id = s->source_id;
    ns->bufsz = s->bufsz;
    ns->type = type;
    psrc->stream = psnk->stream = ns;
    ns->source->depth = ns->sink->depth = CheckDepth(p->depth);
    ns->SinkPort->match = ns->SourcePort;
    ns->SourcePort->match = ns->SinkPort;
    VerifyStream(ns);
    VerifyStream(s);

}

/** Copy port structure */
static Port copyPort(Port p0)
{
    Port p1;
    p1 = MakePort(p0->id, p0->name);
    *p1 = *p0;
    return p1;
}


static Extport extprtList = NULL;   /**<Anchor for external port list */
/**  Add external port to list of unmatched external ports.
     Match ports later
*/
static int findAmatchingPort(Model m, Process p, Extport ep)
{
    Extport ep2 = NULL;
    Port pt;
    Process p2;
    // Component c=NULL;
    char *srcname;
    char *snkname;

    type = IS_ORPHAN;

    if (ep->type == SOURCE) {
	srcname = makeName(p->name, fixName(ep->source->name));
	p2 = getProc(srcname);
	if (!p2) {
	    p2 = MakeProcess(m, srcname, ep->source->comp, ep->source->arg);
	}
	
	pt = MakePort(ep->source_id, ep->name);
    } else {
	snkname = makeName(p->name, fixName(ep->sink->name));
	p2 = getProc(snkname);
	if (!p2) {
	    p2 = MakeProcess(m, snkname, ep->sink->comp, ep->sink->arg);
	}
	pt = MakePort(ep->sink_id, ep->name);
    }
    p2->depth = p->depth + 1;
    ep2 = MakeExtport(ep->type, p2, pt, ep->bufsz, -1);
    ep2->iptype = ep->iptype;
    ep2->next = extprtList;
    ep2->source_id = ep->source_id;
    ep2->sink_id = ep->sink_id;
    ep2->name = ep->name;
    extprtList = ep2;
    return 1;
}

/** Expand process,p, subnet component.  
      Match ep to a port,pt in p.
      Update existing stream,s, in pt */
static void Expand3(Model m, Process p, Extport ep)
{

    Port pt = NULL, ptc = NULL;
    Stream s;
    Process pnew;
    char *srcname;
    char *snkname;

    if (ep->type == SOURCE) {
	pt = p->port;		/** Find matching sink port  */
	if (pt) {
	    do {
		pt->id = fixId(pt->id);
		if (pt->id == ep->sink_id) {
		    s = pt->stream;
		    VerifyStream(s);
		    assert(s && pt == s->SourcePort);
		    srcname = makeName(p->name, fixName(ep->source->name));
		    pnew = MakeProcess(m,
				       srcname, ep->source->comp,
				       ep->source->arg);
		    s->source = pnew;
		    if (ep->bufsz > s->bufsz)
			s->bufsz = ep->bufsz;
		    checkIPtype("Expand3A", ep->iptype, s->iptype,s->source->name,ep->name); 	
		    if( ( ep->iptype && ep->iptype[0]) != 0 )	
			    s->iptype = ep->iptype;	
		    pnew->nportsOut++;
		    pnew->depth = p->depth + 1;
		    ptc = copyPort(pt);
		    ptc->stream = s;
		    ptc->id = s->source_id = ep->source_id;
		    linkPort(pnew, ptc);
		    s->SourcePort = ptc;
		    s->SinkPort->match = s->SourcePort;
		    s->SourcePort->match = s->SinkPort;
		    VerifyStream(s);
		    return;
		}
		pt = pt->next;
	    }
	    while (pt != p->port);
	}
    } else {			/* type is SINK */

	pt = p->port;
	if (pt) {
	    do {
		pt->id = fixId(pt->id);
		if (pt->id == ep->source_id) {	/* Find matching source port for ep */
		    s = pt->stream;
		    assert(s && pt == s->SinkPort);
		    snkname = makeName(p->name, fixName(ep->sink->name));
		    pnew =
			MakeProcess(m, snkname, ep->sink->comp,
				    ep->sink->arg);
		    s->sink = pnew;
		    if (ep->bufsz > s->bufsz)
			s->bufsz = ep->bufsz;
		    checkIPtype("Expand3B",s->iptype, ep->iptype,s->source->name,ep->name); 	
		    if( (ep->iptype && ep->iptype[0]) != 0 )	
		     	s->iptype = ep->iptype;	
		    pnew->nportsIn++;
		    ptc = copyPort(pt);
		    ptc->stream = s;
		    ptc->id = s->sink_id = ep->sink_id;
		    linkPort(pnew, ptc);
		    pnew->depth = p->depth + 1;
		    if (s->sink->comp == NULL) {
			s->sink->comp = MakeComponent(defaultSinkComp, defaultPath);
		    }
		    if (s->source->comp == NULL) {
			s->source->comp =
			    MakeComponent(defaultSourceComp, defaultPath);
		    }
		    s->SinkPort = ptc;
		    s->SinkPort->match   = s->SourcePort;
		    s->SourcePort->match = s->SinkPort;
		    VerifyStream(s);
		    return;
		}
		pt = pt->next;
	    }
	    while (pt != p->port);
	}
    }

    findAmatchingPort(m, p, ep);

}

	/** Expand the model for each external port and stream in the subnet */
static void Expand(Model m, Process p, Subnetm sn)
{
    Stream s;
    Extport ep;

    ep = sn->extport;
    while (ep) {
	Expand3(m, p, ep);
	ep = ep->next;
    }

    s = sn->stream;
    while (s) {
	Expand2(m, p, s);
	s = s->next;
    }

}

	/** Expand a subnet process, i.e. replace this process
	   with its subnet */
static void expandSub(Model m, Process p)
{
    Subnetm sn;

    sn = m->subnetm;
    while (sn) {		// find the subnet for p
	if (strncmp(sn->name, p->comp->name, 100) == 0) {
	    Expand(m, p, sn);
	    return;
	}
	sn = sn->next;
    }

    sprintf(fbfr,
	    "Cannot find subnet %s for process %s\n", p->comp->name,
	    p->name);
    FAIL(expandSub, fbfr);
}

/** Add process to list to be freed.  */
static void FreeLater(Process *fl, Process p)
{
    p->next = *fl;
    *fl = p;
}

/** Free discarded process structure memory. */
static void FreeExpandedProcesses(Process *fl)
{
    Process pn;

    while (*fl != NULL) {
	pn = (*fl)->next;
	free(*fl);
	*fl = pn;
    }
    *fl = NULL;
}
    
	/** While some process contains a subnet component, 
	   expand that component subnet. */
static void expandSubnets(Model m)
{
    Process p, pp, ps;
    int more;			/** 1=could be more subnets  	*/
    int level=0;		/** subnet level 	 	*/ 

    do {
	p = m->proc;
	pp = NULL;
	more = 0; 
	while (p) {
	    if (p->comp) {
		if (p->comp->path[0] == '_') {	/* Is a subnet */
		    more = 1; 
		    m->nprocs--;
		    ps = p;
		    if (pp)	// delink p from process chain.     
			pp->next = p->next;
		    else {
			m->proc = p->next;
		    }
		    expandSub(m, ps);
		    FreeLater(&fl, ps);	/* Pointers to ps still exist. */
		    break;
		}
	    }
	    level += more;
	    pp = p;
	    p = p->next;
	}
    }
    while (more);
    
    if(level > m->level) 
    	m->level = level;
}


		/** Fix  port stream pointers for this stream */
static void fixStream(Stream s2)
{
    Process p;
    Port pt;

    p = s2->source;
    pt = p->port;

    do {
	pt->id = fixId(pt->id);
	if (pt->id == s2->source_id) {
	    pt->stream = s2;
	    return;
	}
	pt = pt->next;

    }
    while (pt != p->port);

    /*  Fix Sink port for this stream */
    p = s2->sink;
    pt = p->port;

    do {
	pt->id = fixId(pt->id);
	if (pt->id == s2->sink_id) {
	    pt->stream = s2;
	    return;
	}
	pt = pt->next;

    }
    while (pt != p->port);


}
			/** Fix Fan in */
static void fixFan2(Model m, Process p, Port pt0, Port pt)
{
    Process j;			// New anonymous join process 
    Component c;
    Port pt1, pt2, ptn;
    Stream s0, s1, s2;

    /*              BEFORE 
       (A)id <- x(B);    [ s0 pt0 psnk0]
       (A)id <- y(C);    [ s1 pt  psnk1]  */
       
    /*              AFTER
       (A)id <- 2(_ sw.Join);  [ s0 pt0 ptn]  
       (j)1  <- x(B);          [ s2 pt2   ]  
       (j)0  <- y(C);          [ s1 pt1   ] 
    */
       
    c = MakeComponent("Join", "stdPackage");
    j = MakeProcess(m, "_", c, MakeArg(NULL, NULL));
    j->depth = p->depth + 1;

    pt1 = MakePort(0, "");
    pt2 = MakePort(1, "");
    ptn = MakePort(2, "");	/*Join output */

    s1 = pt->stream;
    s0 = pt0->stream;

    checkIPtype("FixFan2", s0->iptype, s1->iptype, s0->source->name, s1->source->name );     
    
    if(s0->iptype == NULL || s0->iptype[0] == 0)
    	s0->iptype = s1->iptype;
    	
    if(s1->iptype == NULL || s1->iptype[0] == 0) 
       s1->iptype = s0->iptype;	

    s2 = MakeStream(IS_NET, pt0->stream->source, j,
		    pt0->stream->bufsz, m, pt0, pt, pt0->stream->iptype);
    s2->SourcePort = s0->SourcePort;

    s0->source = j;
    s0->SourcePort = ptn;
    s0->SourcePort->stream = s0;
    s0->source_id = ptn->id;
    ptn->stream = s0;

    s2->sink_id = 1;
    assert(s0->SinkPort->stream == s0);
    s2->source_id = s2->SourcePort->id;
    s2->SinkPort = pt2;
    s2->SourcePort->stream = s2;
    pt2->stream = s2;

    s1->sink = j;
    s1->sink_id = 0;
    assert(s2->SourcePort->stream == s2);


    pt->next->prev = pt0;	// Delink pt
    pt0->next = pt->next;
    p->nportsIn--;


    /* Fix j ports */
    ptn->id = 2;
    ptn->name = "";
    
    j->port = pt1;
    pt1->next = pt2;
    pt2->next = ptn;
    ptn->next = pt1;
    
    pt2->next->prev = pt2;
    pt1->next->prev = pt1;
    ptn->next->prev = ptn;
    
    pt1->stream = s1;
    pt2->stream = s2;
    s1->SinkPort = pt1;
    j->nportsIn = 2;
    j->nportsOut = 1;
    fixStream(s2);
    fixStream(s1);

    s0->SinkPort->match = s0->SourcePort;
    s0->SourcePort->match = s0->SinkPort;
    s1->SinkPort->match = s1->SourcePort;
    s1->SourcePort->match = s1->SinkPort;
    s2->SinkPort->match = s2->SourcePort;
    s2->SourcePort->match = s2->SinkPort;
    VerifyStream(s0);
    VerifyStream(s1);
    VerifyStream(s2);
}

/** Create anonymous Split process if output port directed to more than one process.*/
static void fixFanOut(Model m, Process p, Port pt0, Port pt)
{
    Process j;			// New anonymous split process 
    Component c;
    Port pt1, pt2;
    Stream s0, s1, s2;

    /*              BEFORE 
       (B)x <- id(A);  [ s0 pt0]
       (C)y <- id(A);  [ s1 pt ]  */
    /*              AFTER
       (B)x <-  1(j);  [ s0 pt0]  
       (C)y <-  2(j;   [ s1    ] 
       (j)0 <- id(A);  [ s2    ]  */

    c = MakeComponent("Split", stdPackage);
    j = MakeProcess(m, "_", c, MakeArg(NULL, NULL));
    j->depth = p->depth + 1;

    pt1 = MakePort(1, "");
    pt2 = MakePort(2, "");
    s0 = pt0->stream;
    s1 = pt->stream;

    checkIPtype("fixFanOut", s0->iptype, s1->iptype, s0->source->name, s1->sink->name); 
     
    if(s0->iptype == NULL || s0->iptype[0] == 0) 
    	s0->iptype = s1->iptype;
    	 
    s2 = MakeStream(IS_NET, pt0->stream->source, j,
		    pt0->stream->bufsz, m, pt0, pt, pt0->stream->iptype );
		    
    s0->iptype = s1->iptype = s2->iptype ;		    

    s2->sink_id = 0;
    s2->source_id = pt0->id;

    s1->SourcePort = pt2;
    s1->source = j;
    s1->source_id = 2;

    s0->source = j;
    s0->source_id = 1;
    s0->SourcePort = pt1;
    s0->SinkPort->match = s0->SourcePort;
    s0->SourcePort->match = s0->SinkPort;

    pt->next->prev = pt0;	// Delink pt
    pt0->next = pt->next;
    p->nportsOut--;


    /* Fix j ports */
    j->port = pt;
    pt->id = 0;
    pt->stream = s2;
    pt->name = "";
    pt->next = pt1;
    pt1->next = pt2;
    pt2->next = pt;
    pt2->prev = pt1;
    pt1->prev = pt;
    pt->prev = pt2;
    pt1->stream = s0;
    pt2->stream = s1;
    j->nportsIn = 1;
    j->nportsOut = 2;
    s0->SourcePort->stream = s0;
    s1->SourcePort->stream = s1;
    s2->SourcePort->stream = s2;
    s0->SinkPort->stream = s0;
    s1->SinkPort->stream = s1;
    s2->SinkPort->stream = s2;
    assert(s1->SourcePort != s2->SinkPort);
    s0->source_id = s0->SourcePort->id;
    s1->source_id = s1->SourcePort->id;
    s2->source_id = s2->SourcePort->id;
    s0->SinkPort->match = s0->SourcePort;
    s0->SourcePort->match = s0->SinkPort;
    s1->SinkPort->match = s1->SourcePort;
    s1->SourcePort->match = s1->SinkPort;
    s2->SinkPort->match = s2->SourcePort;
    s2->SourcePort->match = s2->SinkPort;
    VerifyStream(s0);
    VerifyStream(s1);
    VerifyStream(s2);

}

/** Search for fanin/fanout conditions */
static void fixFan(Model m, Process p)
{
    Port pt, pt0;
    int id = -999;

    pt = p->port;		/* pt may be = 0 */

    if (pt != 0) {
	do {
	    pt->id = fixId(pt->id);
	    if (pt->id == id) {
		if (pt0->stream->sink == p && pt->stream->sink == p) {
		    fixFan2(m, p, pt0, pt);
		    pt = p->port;	/* Go back to first port */
		} else {
		    if (pt0->stream->source == p
			&& pt->stream->source == p) {
			fixFanOut(m, p, pt0, pt);
			pt = p->port;	/* Go back to first port */
		    }
		}
	    }
	    id = pt->id;
	    pt0 = pt;
	    pt = pt->next;
	}
	while (pt != p->port);
    }
}

/** For all processes(p) Fix fan in and fan out. 
   * Insert sw.Join  process wherever fanin occurs.
   * Insert sw.Split process wherever fanout occurs. 
*/
static void fixFanInOut(Model m)
{
    Process p;

    p = m->proc;

    while (p) {			
	fixFan(m, p);
	p = p->next;
    }
}

/** Add process to model.*/
static void linkProc(Model m, Process p)
{
    Process p2;

    p->kind = IS_NET;
    p2 = m->proc;
    while (p2) {
	if (strcmp(p2->name, p->name) == 0) {
	    return;
	}
	p2 = p2->next;
    };


    p->next = m->proc;
    m->proc = p;
    m->nprocs++;

}

/** MAX(A,B) returns highest of A or B */
#define MAX(A,B) ( (A>B)? A: B)

/** Slow, bubble sort to put ports for process p in order by port ID */
static void SortPorts(Process p)
{
    Port pt0, pt1, pt2, ptw;
    int more = 1;

    pt0 = p->port;
    if (!pt0->next)
	return;

    while (more) {
	pt1 = pt0;
	pt2 = pt0->next;
	more = 0;
	while (pt2 != pt0) {
	    if (pt1->id > pt2->id) {
		more = 1;
		if (p->port == pt1) {
		    pt1->next = pt2;
		    pt1->prev->next = pt2;
		    pt2->prev = pt1;
		    pt2->next = pt1;
		    pt1->prev = pt2;
		    ptw = pt1;
		    pt1 = pt2;
		    pt2 = ptw;
		    pt0 = p->port = pt1;
		} else {
		    pt1->next = pt2->next;
		    pt1->prev->next = pt2;
		    pt2->prev = pt1->prev;
		    pt2->next = pt1;
		    pt1->prev = pt2;
		    ptw = pt1;
		   //pt1 = pt2;
		    pt2 = ptw;
		}
	    }
	    pt1 = pt2;
	    pt2 = pt1->next;
	}
    }
}

/** Create a new stream structure. */
static void createStream(Model m, Extport ep, Extport ep2)
{
    Stream s;
    Port snkpt, srcpt, pt;

    srcpt = ep->source->port;


    pt = ep2->sink->port;
    while (pt->id != ep2->sink_id) {
	pt = pt->next;
	if (pt == ep2->sink->port) {
	   FAIL(creatStream,"No matching external sink port");
	}
    }
    snkpt = pt;

    while (srcpt->id != ep->source_id) {
	srcpt = srcpt->next;
	if (srcpt == ep->source->port) {
	    FAIL(creatStream,"No matching external source port");
	}
    }

    checkIPtype("createStream", ep->iptype, ep2->iptype, ep->name, ep2->name); 
    
    s = MakeStream(IS_NET, ep->source, ep2->sink,
		   MAX(ep->bufsz, ep2->bufsz), m, srcpt, snkpt, ep2->iptype);
	
    linkProc(m, ep->source);
    linkProc(m, ep2->sink);
	
    s->SourcePort->match = s->SinkPort;
    s->SinkPort->match = s->SourcePort;
    s->SourcePort->stream = s;
    s->SinkPort->stream = s;
    s->SourcePort->id = s->source_id = fixId(ep->source_id);
    s->SinkPort->id = s->sink_id = fixId(ep2->sink_id);

    SortPorts(s->source);
    SortPorts(s->sink);
    VerifyStream(s);
}

/** MATCH(SRC,SNK) is true if port names match. ?? */
#define MATCH(SRC,SNK) if(eqs(srcn,#SRC)) {	\
			  if(eqs(snkn,#SNK)) {	\
				return 1;	\
			  } else {		\
				return 0;	\
			  }			\
		       }

/** Return true if names match.*/
static int MatchName(String srcn, String snkn)
{

    if(srcn==NULL) 
	return 0;
    MATCH(OUT, IN);
    MATCH(TAB, SLOT);
    MATCH(PLUG, SOCKET);
    MATCH(out, in);
    MATCH(tab, slot);
    MATCH(plug, socket);

    if (eqs(srcn, snkn))
	return 1;

    return 0;
}

/** return true if external port is matched.*/
static int Matched(Extport ep2) {
	Port pt;
	int  id;

	id=ep2->sink_id;
	pt=ep2->sink->port;
	do {
		if(pt->id==id) {
			if(pt->match==NULL) {
				return 0;
			}
			return 1;
		}
		pt=pt->next;
	} while ( pt!=ep2->sink->port );
	return 0;
}

/** match external ports: ep2 is sink port*/
static int isaMatch(Extport ep2, Extport ep)
{

    if(Matched(ep2) )  /** Create a new stream if external port is matched.*/ 
		return 0;


    if(ep->name) {
   	 if (ep2->source_id < 0) {
		if (MatchName(ep->name, ep2->name))
	  		  return 1;
   	 }
	 return 0;
    }

	
    if (ep->sink_id == ep2->source_id)
	return 1;

    if (ep->name == NULL)
	return 0;
    return 0;
}

/** Create a new stream if external port is matched.*/ 
static void findSink(Model m, Extport ep)
{
    Extport ep2;		/* sink port */
    Process p;

    ep2 = extprtList;
    while (ep2) {
	if (ep2->type == SINK) {
	    p = ep2->sink;
	    if (p != ep->source) {
		if (isaMatch(ep2, ep)) {
		    createStream(m, ep, ep2);
		    return;
		}
	    }
	}
	ep2 = ep2->next;
    }
}

	/** Match source ports to appropriate sink ports 
	    then identify and mark any leftover orphan processes, creating orphan streams 
	 */
static void autolink(Model m)
{
    Extport ep;
    Process p;

    ep = extprtList;
    type = IS_NET;
    while (ep) {
	if (ep->type == SOURCE) {
	    findSink(m, ep);          /** Create a new stream if external port is matched.*/ 
	}
	ep = ep->next;
    }

    p=m->proc;

    while(p) {
	if(p->nportsIn + p->nportsOut == 0) {
		p->kind=IS_ORPHAN;	
		MakeStream(IS_ORPHAN,  p, NULL, -1, m, NULL, NULL,"");
	}
	p=p->next;
    }	
}

static void removeDeadStreams(Model m) {
	Stream s, sp;
	
	s=m->stream;
	while(s != NULL) {
	     if(s->source->comp != NULL) {
		if(  s->source->comp->path[0] == '_' ) {  /* if subnet, remove stream */
			if(s==m->stream) {
				m->stream=s->next;
			} else {
				sp->next = s->next;
				s=sp;
			} 
			//free(s);
		}
	     }	
	     sp=s; s=s->next;
	}
}

/** Convert the parse tree into a SW network model. */
Model visitValidSW(Model model, ValidSW _p_)  {
   
    net_model = model;
    visitListStm(_p_->u.valid_.liststm_);	/* Visit the root of the parse tree to begin.    */

      
      
    fixFanInOut(net_model);			/* Insert Join and Split processes as necessary. */
    expandSubnets(net_model);   
    fixFanInOut(net_model);  
    autolink(net_model);			/* Connect orphan ports.  			 */
    removeDeadStreams(net_model);	        /* Some streams could have all subnet components.*/
    FreeExpandedProcesses(&fl);                 /* Need to remove dead streams first. 		 */
    return net_model;
}
