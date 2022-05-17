/** @file sw.c
    Create StreamWork network model from parse tree 
    Then call specified output function.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include "sw.h"
#include "swconfig.h"
#include "swsym.h"
#include "model.h"

#define MAX_INCLUDE_LEVEL 100

#define FailKind(S, K) {          \
    fprintf(stderr,               \
        "SW/Error: bad kind field, %d, while visiting %s!\n", \
        K, #S);                   \
    exit(1);                      \
}

/******************   Function Prototypes   *****************/
static void expandSubnet(Model m, Process p, Subnetm sn);
static void expandSub(Model m, Process p); 
int         VerifyStream(Stream s);
char        *makeName(char *pn, char *nn);
char        *fixName(char *name);
Extport     MakeExtport(PortType type, Process p, Port prt, Arrow a, int id);

/******************   Local  Variables   *****************/
static int        bs = 1;			/**<  Buffer size */
static char      *savedPrefix = "";
static Port       LatestSrcPort = NULL;/** Latest visited source port. */
static streamType stype = IS_NET;   /** Current network type. */
static Model      net_model = NULL; /** Network model anchor point. */
static String     saves = NULL;     /**<Save name ?? */

/******************   Local Functions   *****************/

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
Subnetm MakeSubnetm(Ident name, Stream s, 
                    Extport in, Extport out,
                    Process p)
{
	Subnetm sn;
	Extport orphan;

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
	    } else {        /* Must be an orphan */
	        if(p) {
	            orphan=MakeExtport(ORPHAN,p, NULL, NULL, -99); 
	            linkExt(sn,orphan);  
	        }
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

	m->nstreams = m->nStructStreams = m->nIntStreams = m->nStringStreams =
	    0;
	m->ncomponents = 0;
	m->nprocs = 0;
	m->level = 0;
	m->stream = f;
	m->proc = NULL;
	m->subnetm = NULL;
	m->comp = NULL;
	m->name = "SW";
	m->maxexpands = -1;	/* Allow unlimited subnet expansion to start */
	return m;

}

char **MakeArg(ListArgument la, char *name)
{
	char **arg;		/* Pointer to array of string pointers. */
	int i = 1, narg = 1;
	ListArgument la2 = la;

	while (la2) {
		narg++;
		la2 = la2->listargument_;
	}

	arg = (char **)malloc((narg + 1) * sizeof(char *));
	arg[0] = name;
	arg[narg] = NULL;

	i = narg - 1;
	while (la) {
		arg[i--] =
		    visitStringval(la->argument_->u.argumentx_.stringval_);
		la = la->listargument_;
	}

	return arg;
}

/** Numeric variable */
Numvar visitNumvar(Numvar p)
{
	return p;
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

Attribute MakeAttr(ListAttr la)
{
	Attribute attr, lattr;
	ListAttr la2 = la;

	if (!la2)
		return NULL;
	lattr = NULL;

	while (la2) {
		attr = (Attribute) malloc(sizeof(Attribute_));
		switch (la2->attr_->kind) {
		case is_Attrs:
			attr->val.s =
			    visitStringval(la2->attr_->u.attrs_.stringval_);
			attr->key = visitSymval(la2->attr_->u.attrs_.symval_);
			attr->type = STRING;
			break;
		case is_Attrn:
			attr->key = visitSymval(la2->attr_->u.attrn_.symval_);
			attr->val.i = visitNumval(la2->attr_->u.attrn_.numval_);
			attr->type = INT;
		}
		attr->next = lattr;
		la2 = la2->listattr_;
		lattr = attr;
	}

	return attr;
}

enum PREFIX_MODE { SET, GET };
static char *savePrefix(int m, char *s)
{
	switch (m) {
	case SET:
		savedPrefix = s;
		break;
	case GET:
		return savedPrefix;
	}

	return "";
}


Process MakeProcess(Model model, Ident name, Component comp, char **arg, Attribute attr)
{
	Process p;

	// if (name[0] == '_' && name[1] == 0)
	name = fixName(name);
	p = getProc(name);

	if (p == NULL) {
		p = (Process) malloc(sizeof(Process_));
		if (!p) {
			FAIL(MakeProcess,
			     "Out of memory when allocating Process!\n");
		}
		p->comp = NULL;
		if (comp)
			p->comp = comp;
		p->name = name;
		p->nportsIn = 0;
		p->nportsOut = 0;
		p->port = NULL;
		p->kind = stype;
		p->depth = 0;
		p->attr = attr;
		if (stype == IS_NET || stype == IS_STRUCT) {
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

int fixId(int i)
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
		exit(EXIT_FAILURE);
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
		if (path[0] != '_') {	/* subnet? */
			net_model->ncomponents++;
			c->next = net_model->comp;	/* Link component to list */
			net_model->comp = c;
		}
	}
	if (!c) {
		fprintf(stderr,
			"Error: out of memory when allocating Component!\n");
		exit(EXIT_FAILURE);
	}

	addComponent(name, path, c);	/* Add to symbol table */
	c->name = name;
	c->path = path;
	return c;
}

/** Make Stream structure */
Stream
MakeStream(streamType stype, Process src, Process snk, int bs, Model m,
	   Port SourcePort, Port SinkPort, char *iptype)
{
	Stream f;

	if (!src) {
		FAIL(MakeStream, "No source for stream. Hermit maybe.\n");
		exit(EXIT_FAILURE);
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
	f->type = stype;
	f->next = m->stream;
	m->stream = f;
	if (bs < 0)
		bs = 0;
	if (bs > maxbfsz)
		bs = maxbfsz;
	f->bufsz = bs;
	f->iptype = iptype;	/* From visiting arrows */

	switch (stype) {
	case IS_STRUCT:
		m->nstreams--;
		m->nStructStreams++;
	case IS_NET:
		m->nstreams++;
		__attribute__((fallthrough));
	case IS_SUB:
		f->source_id = fixId(SourcePort->id);
		f->sink_id = fixId(SinkPort->id);
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

/** String variable */
String visitStringvar(Stringvar p)
{
	return p;
}

/** Environment variable */
String visitEnvar(Envar p)
{
	return p;
}

/** Get Environment variable */
String getEnvVar(String s)
{
	String s1, s2;

	s1 = s + 2;
	s2 = getenv(s1);
	return s2;
	return (getenv("BROWSER"));
}

String visitStringval(Stringval _p_)
{					 /**<Get String value*/

	switch (_p_->kind) {
	case is_StringVals:
		return visitString(_p_->u.stringvals_.string_);
	case is_StringValv:
		return getStringVar(_p_->u.stringvalv_.stringvar_);
	case is_StringVale:
		return (getEnvVar(visitEnvar(_p_->u.stringvale_.envar_)));
	default:
		badkind(Stringval);
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
#endif

/** Get Symbol value */
String visitSymval(Symval _p_)
{
/**<Get symbol value.*/
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
	addStringVar(visitStringvar(_p_->u.strassgnv_.stringvar_),
		     visitStringval(_p_->u.strassgnv_.stringval_));
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
	switch (p->kind) {
	case is_Symvaluv:
		return visitSymval(p->u.symvaluv_.symval_);
	case is_Symvaluu:
		return "_";
	default:
		badkind(Symvalu);
	}
}

static int builtinType(char *t)
{
	char c = t[0];
	if (c == '_')
		return 1;	// Short for interface{} 
	if (c >= 'a' && c <= 'z')
		return 1;
	return 0;

/*        
      char *b[] = {
            "int", "int8",   int16",  "int32",  "int64",  
                  "uint8", "uint16", "uint32", "uint64",  
            "float", "float32", "float64", "complex64", "complex128",
             "", "", 
            NULL};
      int i=0;
      
      do {
            if( strncmp(t,b[i],100) == 0 ) 
                return 1;
            i++;
      } while ( b[i] != NULL ); 
      
      return 0;
*/
}

String visitTypeDef(TypeDef p)
{
	char bfr[BUFFSIZE + 1];
	char *t;		// Channel type 
	switch (p->kind) {
	case is_TypedefArray:
		/* Code for TypedefArray Goes Here */
		snprintf(bfr, BUFFSIZE, "[%d]%s",
			 visitNumval(p->u.typedefarray_.numval_),
			 visitTypeDef(p->u.typedefarray_.typedef_));
		return strndup(bfr, BUFFSIZE);
	case is_Typedefa:
		t = visitSymvalu(p->u.typedefa_.symvalu_);
		// if( builtinType(t) ) return t;
		// snprintf(bfr,BUFFSIZE,"%s.%s",defaultTypePath,t);
		// return strndup(bfr,BUFFSIZE);
		return t;
	case is_Typedefb:
		snprintf(bfr, BUFFSIZE, "%s.%s",
			 visitTypeDef(p->u.typedefb_.typedef_),
			 visitSymvalu(p->u.typedefb_.symvalu_));
		return strndup(bfr, BUFFSIZE);
	case is_Typedefnull:
		return "";
	case is_Typdefl:
		return visitTypeDef(p->u.typdefl_.typedef_1);
		// ?? visitTypeDef(p->u.typdefl_.typedef_2);
		break;

	default:
		badkind(TypeDef);
	}
}

Arrow makeArrow(char *iptype, int bs)
{
	Arrow a;

	a = (Arrow) malloc(sizeof(Arrow_));
	a->iptype = iptype;
	a->bs = bs;
	return a;
}

/** Get left arrow bufferize */
static Arrow visitLarrow(Larrow _p_)
{
	return makeArrow(visitTypeDef(_p_->u.arrowx_.typedef_),
			 visitBuffsize(_p_->u.arrowx_.buffsize_));
	// iptype_save = visitTypeDef (_p_->u.arrowx_.typedef_);
	//return visitBuffsize (_p_->u.arrowx_.buffsize_);
}

/** Get right arrow buffersize */
static Arrow visitRarrow(Rarrow _p_)
{
	return makeArrow(visitTypeDef(_p_->u.arrowr_.typedef_),
			 visitBuffsize(_p_->u.arrowr_.buffsize_));
}

/** Add port,p to port list at P->port in order by port id*/
void linkPort(Process P, Port p)
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
	
	while (p2 != P->port); /* Point p2 to end of list */

	p->next = P->port;     /* Make p last in list */
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

static Arrow visitLSarrow(LSarrow p)
{
	return makeArrow(visitTypeDef(p->u.arrowsl_.typedef_),
			 visitBuffsize(p->u.arrowsl_.buffsize_));
}

static Arrow visitRSarrow(RSarrow p)
{
	return makeArrow(visitTypeDef(p->u.arrowsr_.typedef_),
			 visitBuffsize(p->u.arrowsr_.buffsize_));
}

/** Set number of input ports in sink process */
static void SetSink(Process p)
{

	p->nportsIn++;
}

Stream df(streamType stype, Arrow a, Process src, Process snk,
   Port src_pt, Port snk_pt)
{
	Stream s;

	linkPort(snk, snk_pt);
	SetSink(snk);
	SetSource(src);
	linkPort(src, src_pt);
	s = MakeStream(stype, src, snk,
		       a->bs, net_model, src_pt, snk_pt, a->iptype);
	//iptype_save = "";
	s->SourcePort = src_pt;
	s->SinkPort = snk_pt;
	s->SourcePort->stream = s->SinkPort->stream = s;
	s->sink_id = snk_pt->id = fixId(snk_pt->id);
	s->source_id = src_pt->id = fixId(src_pt->id);
	s->SinkPort->match = s->SourcePort;
	s->SourcePort->match = s->SinkPort;
	VerifyStream(s);
	return s;
}

/** Get stream structure */
Stream visitDataFlow(DataFlow _p_)
{
	Process snk, src;
	Port pt, src_pt, snk_pt;
	Stream s, s2;
	int bs;

	switch (_p_->kind) {
	case is_Streamx:
		return df(stype,
			  visitLarrow(_p_->u.streamx_.larrow_),
			  visitProc(_p_->u.streamx_.proc_2),
			  visitProc(_p_->u.streamx_.proc_1),
			  visitPrt(_p_->u.streamx_.prt_2),
			  visitPrt(_p_->u.streamx_.prt_1));

	case is_Streamrx:
		return df(stype,
			  visitRarrow(_p_->u.streamrx_.rarrow_),
			  visitProc(_p_->u.streamrx_.proc_1),
			  visitProc(_p_->u.streamrx_.proc_2),
			  visitPrt(_p_->u.streamrx_.prt_1),
			  visitPrt(_p_->u.streamrx_.prt_2));

	case is_Streamls:
		return df(IS_STRUCT,
			  visitLSarrow(_p_->u.streamls_.lsarrow_),
			  visitProc(_p_->u.streamls_.proc_2),
			  visitProc(_p_->u.streamls_.proc_1),
			  visitPrt(_p_->u.streamls_.prt_2),
			  visitPrt(_p_->u.streamls_.prt_1));
	case is_Streamrs:
		return df(IS_STRUCT,
			  visitRSarrow(_p_->u.streamrs_.rsarrow_),
			  visitProc(_p_->u.streamrs_.proc_1),
			  visitProc(_p_->u.streamrs_.proc_2),
			  visitPrt(_p_->u.streamrs_.prt_1),
			  visitPrt(_p_->u.streamrs_.prt_2));
	case is_Streamy:
		return df(stype, visitLarrow(_p_->u.streamy_.larrow_),
			  visitProc(_p_->u.streamy_.proc_),
			  visitDataFlow(_p_->u.streamy_.dataflow_)->source,
			  visitPrt(_p_->u.streamy_.prt_2),
			  visitPrt(_p_->u.streamy_.prt_1));

	case is_Streamry:
		return df(stype, visitRarrow(_p_->u.streamry_.rarrow_),
			  visitDataFlow(_p_->u.streamry_.dataflow_)->sink,
			  visitProc(_p_->u.streamry_.proc_),
			  visitPrt(_p_->u.streamry_.prt_1),
			  visitPrt(_p_->u.streamry_.prt_2));

	case is_Streamlsy:
		return df(IS_STRUCT,
			  visitLSarrow(_p_->u.streamlsy_.lsarrow_),
			  visitProc(_p_->u.streamlsy_.proc_),
			  visitDataFlow(_p_->u.streamlsy_.dataflow_)->sink,
			  visitPrt(_p_->u.streamlsy_.prt_2),
			  visitPrt(_p_->u.streamlsy_.prt_1));
	case is_Streamrsy:
		return df(IS_STRUCT,
			  visitRSarrow(_p_->u.streamrsy_.rsarrow_),
			  visitDataFlow(_p_->u.streamrsy_.dataflow_)->sink,
			  visitProc(_p_->u.streamrsy_.proc_),
			  visitPrt(_p_->u.streamrsy_.prt_2),
			  visitPrt(_p_->u.streamrsy_.prt_1));

	default:
		badkind(dataflow);
	}
}

/** Create an external port structure. */
Extport MakeExtport(PortType stype, Process p, Port prt, Arrow a, int id)
{
	Extport ep;

	ep = (Extport) malloc(sizeof(Extport_));
	ep->type = stype;
	
	if(prt) {
    	linkPort(p, prt);
	    ep->name = prt->name = saves;
	    saves = NULL;
    }
    
	if (stype == SINK) {
		ep->sink = p;
		ep->source = NULL;
		ep->sink_id = fixId(prt->id);
		ep->source_id = id;
		SetSink(p);
	} else  {
	    if(stype == SOURCE) {
    		ep->source = p;
	    	ep->sink = NULL;
	    	ep->source_id = fixId(prt->id);
	    	ep->sink_id = id;
	    	SetSource(p);
	    } else {   // Must be ORPHAN
	        ep->source = p;
	        ep->source_id = id;
	        SetSource(p);
	    
	    }
	}    

    if(a) {
    	ep->bufsz = a->bs;
	    ep->iptype = a->iptype;
	}    
	ep->next = NULL;
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

//static void setIpType(Extport ep) {                   
//      ep->iptype = strdup (iptype_save);
      //if(ep->iptype[0]==0) {
	    //  ep->iptype=ep->name;
      //}             
      //iptype_save = "";
//}

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
		//setIpType(ep);
		return ep;
	case is_ExtinR:
		ep = MakeExtport(SINK,
				 visitProc(_p_->u.extinr_.proc_),
				 visitPrt(_p_->u.extinr_.prt_),
				 visitRarrow(_p_->u.extinr_.rarrow_),
				 visitTab(_p_->u.extinr_.tab_));
		//setIpType(ep);
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
		//setIpType(ep);
		return ep;
	case is_Extoutr:
		return MakeExtport(SOURCE,
				   visitProc(_p_->u.extoutr_.proc_),
				   visitPrt(_p_->u.extoutr_.prt_),
				   visitRarrow(_p_->u.extoutr_.rarrow_),
				   visitTab(_p_->u.extoutr_.tab_));
		//setIpType(ep);
		return ep;
	default:
		badkind(ExtPortOut);
	}
}/** Add process to model.*/

void linkProc(Model m, Process p)
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

/** Get hermit structure */
Process visitHermt(Hermt _p_)
{
	char *name;
	Process p;
	stype = IS_NET;
	switch (_p_->kind) {
	case is_Hermtx:
		name = visitSymvalu(_p_->u.hermtx_.symvalu_);
		p = MakeProcess(net_model,
				name,
				visitComp(_p_->u.hermtx_.comp_),
				MakeArg(visitListArgument
					(_p_->u.hermtx_.listargument_), name),
				NULL);
		return p;
	case is_Hermty:
		p = MakeProcess(net_model,
				visitSymvalu(_p_->u.hermty_.symvalu_), NULL,
				MakeArg(visitListArgument
					(_p_->u.hermty_.listargument_), NULL),
				NULL);
		linkProc(net_model, p);
		return p;
	default:
		badkind(Hermt);
	}
}

/** Get underscore ?? */
static Ident UnderScore(Ident id)
{
	Ident uid;

	uid = id;		// ?? add underscore later. Just refactor now.
	return uid;
}

// Remove p from Model->proc list.
static void Unlink(Process p) {
		Model m;
		Process pm, pp; 
		
		m=net_model;
		
		pm=m->proc;
		
		pp=NULL;
		while(pm) {
				if( p==pm) {
						if(pp) {
							pp->next=p->next;
						} else {
							m->proc=p->next;
						}
						m->nprocs--;
						return;
				}
				pp=pm;
				pm=pm->next;
		}
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
		if(p) 
			Unlink(p);   // Remove p from Model->proc list.
		if (!p->comp)
			p->comp = MakeComponent(p->name, defaultPath);
		return MakeSubnetm(id, NULL, eport, eport, p);
	case is_Snets:
		s = visitDataFlow(_p_->u.snets_.dataflow_);
		return MakeSubnetm(id, s, eport, eport, NULL);
	case is_Snetin:
		return MakeSubnetm(id, s,
				   visitExtPortIn(_p_->u.snetin_.extportin_),
				   eport,NULL);
	case is_Snetout:
		return MakeSubnetm(id, s,
				   visitExtPortOut(_p_->u.snetout_.extportout_),
				   eport,NULL);
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
	//                  visitSymval(_p_->u.snet_.symval_));
}

#if 0
static char *Exists(char *s)
{
	struct stat sb;
	char bfr[BUFFSIZE + 1];

	if (lstat(s, &sb) == 0)
		return s;

	if (includePath == NULL)
		return NULL;

	strncpy(bfr, includePath, BUFFSIZE);
	if (lstat(strncat(bfr, s, BUFFSIZE), &sb) == 0)
		return strdup(bfr);

	return NULL;
}

static char *findFile(char *s)
{
	char *s2;

	s2 = Exists(s);

	if (s2 != NULL)
		return s2;

	FAIL(Cannot locate, s);
}
#endif

void visitStm(Stm _p_)
{
	Process p;
	ValidSW pt;
	static int includeLevel = 0;

	stype = IS_NET;

	switch (_p_->kind) {
		char *s;
	case is_StmPrefix:
		s = visitStringval(_p_->u.stmprefix_.stringval_);
		savePrefix(SET, s);
		return;
	case is_Stminc:
		// pt = IncludeFile(findFile(visitStringval(_p_->u.stminc_.stringval_)));  
		pt = IncludeFile(visitStringval(_p_->u.stminc_.stringval_));
		includeLevel++;
		if (includeLevel > MAX_INCLUDE_LEVEL)
			FAIL(INCLUDE statement recursion,
			     "MAX_INCLUDE_LEVEL exceeded");
		visitListStm(pt->u.valid_.liststm_);
		includeLevel--;
		return;
	case is_Stmx:
		visitDataFlow(_p_->u.stmx_.dataflow_);
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
		stype = IS_SUB;
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

Attribute makeAttribute()
{
	return (Attribute) malloc(sizeof(Attribute_));
}

Attribute visitAttr(Attr p)
{
	Attribute a;
	a = makeAttribute();
	switch (p->kind) {
	case is_Attrs:
		a->key = visitSymval(p->u.attrs_.symval_);
		a->val.s = visitStringval(p->u.attrs_.stringval_);
		a->type = STRING;
		return a;
	case is_Attrn:
		a->key = visitSymval(p->u.attrn_.symval_);
		a->val.i = visitNumval(p->u.attrn_.numval_);
		a->type = INT;
		return a;
	default:
	badkind(Attribute)}
}

ListAttr visitListAttr(ListAttr listattr)
{
	return listattr;
	while (listattr != 0) {
		/* Code For ListAttr Goes Here */
		visitAttr(listattr->attr_);
		listattr = listattr->listattr_;
		// return visitAttr(listattr->listattr_);
	}
}

ListAttr visitAttributes(Attributes p)
{
	switch (p->kind) {
	case is_Attribe:
		return visitListAttr(p->u.attribe_.listattr_);
	case is_Attribs:
		return NULL;
	default:
		FailKind(visitAttributes, p->kind);
	}
}

/** Get process */
Process visitProc(Proc _p_)
{

	switch (_p_->kind) {

	case is_Processx:
		return MakeProcess(net_model,
				   visitSymvalu(_p_->u.processx_.symvalu_),
				   visitComp(_p_->u.processx_.comp_),
				   MakeArg(visitListArgument
					   (_p_->u.processx_.listargument_),
					   visitSymvalu(_p_->u.
							processx_.symvalu_)),
				   MakeAttr(visitAttributes
					    (_p_->u.processx_.attributes_)));
	case is_Processy:
		return MakeProcess(net_model,
				   visitSymvalu(_p_->u.processy_.symvalu_),
				   NULL,
				   MakeArg(NULL, NULL),
				   MakeAttr(visitAttributes
					    (_p_->u.processy_.attributes_)));
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

String prepend(char *pp, char *ap)
{
	char bfr[300];
	strncpy(bfr, pp, 300);
	strncat(bfr, ap, 300 - strlen(bfr));
	return (strdup(bfr));
}

/** Get module path */
String visitModPath(ModPath p)
{
	switch (p->kind) {
	case is_Modpa:
		return prepend("/", visitSymval(p->u.modpa_.symval_));
	case is_Modpx:
		return (visitSymval(p->u.modpx_.symval_));
	case is_Modpy:
		return (makeModPath(visitModPath(p->u.modpy_.modpath_),
				    visitSymval(p->u.modpy_.symval_)));
	case is_Modps:
		/* Code for Modps Goes Here */
		return getStringVar(visitStringvar(p->u.modps_.stringvar_));
		break;

	default:
		badkind(ModPath);
	}
}

String visitValidImport(ValidImport s0)
{
	return s0;
}

Component visitRemPath(RemPath p)
{
	return MakeComponent(visitSymval(p->u.rempatha_.symval_),
			     visitValidImport(p->u.rempatha_.validimport_));
}

/** Get component */
Component visitComp(Comp _p_)
{
	switch (_p_->kind) {
	case is_Compa:
		return visitRemPath(_p_->u.compa_.rempath_);
	case is_Compx:
		return MakeComponent(visitSymval(_p_->u.compx_.symval_),
				     defaultPath);
	case is_Compn:
		return MakeComponent(visitSubId(_p_->u.compn_.subid_), "_");
	case is_Compz:
		return MakeComponent(visitSymval(_p_->u.compz_.symval_),
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
	arg = make_Argumentx(make_StringVals
			     (visitStringval(_p_->u.argumentx_.stringval_)));
	return arg;
	//make_Argumentx(
	//             (visitStringval(_p_->u.argumentx_.stringval_));
}

/** Get list of arguments.*/
ListArgument visitListArgument(ListArgument listargument)
{
	ListArgument l = NULL;

	while (listargument != 0) {
		l = make_ListArgument(visitArgument(listargument->argument_),
				      l);
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
/********************  Global FUnctions   ****************/
char *fixName(char *name)  {
	char bfr[BUFFSIZE + 1];
	static int nanon = 1;	/* Number of anonymous processes */

	if (name[0] == '_') {	// Anonymous process Q
		snprintf(bfr, BUFFSIZE, "%i", nanon++);
		return strndup(bfr, 100);
	}

	if (savePrefix(GET, name) == NULL)
		return name;

	snprintf(bfr, BUFFSIZE, "%s%s", savePrefix(GET, name), name);
	return strndup(bfr, 100);
}

char *makeName(char *pn, char *nn) /** Create a name string */
{
	char bfr[1000];

	strncpy(bfr, pn, 500);
	//  strncat(bfr, "_", 501);
	strncat(bfr, nn, 1000);
	return (strdup(bfr));
}
/** Convert the parse tree into a SW network model. */
Model visitValidSW(Model m, ValidSW _p_) {
	savePrefix(SET, "");
	net_model = m;    /** ? @todo remove global **/
	visitListStm(_p_->u.valid_.liststm_);	/* Visit the root of the parse tree to begin.    */
	return m;
}
