/** @file SW.c
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

#define badkind(S) { 						\
   fprintf(stderr,						\
	"Error: bad kind field when visiting %s!\n",(#S));	\
   exit(1); 							\
}

Port LatestPort = NULL, LatestSrcPort = NULL;
STATE state = IS_NET;

int bs = 1;			/*  Buffer size */
Model net_model = NULL;

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
    Subnetm sn2 = m->subnetm;

    sn2 = m->subnetm;
    if (!sn2) {
	sn2 = (Subnetm) malloc(sizeof(Subnetm_));
	sn2->name = name;
	sn2->stream = NULL;
	sn2->extport = NULL;
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
    m->stream = f;
    m->proc = NULL;
    m->subnetm = NULL;
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
	p->kind = state;
	p->depth = 0;
	if (state == IS_NET) {
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
	if (path[0] != '\'')
	    net_model->ncomponents++;
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
Stream
MakeStream(STATE state, Process src, Process snk, int bs, Model m,
	   Port SourcePort, Port SinkPort)
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
    f->source_id = fixId(SourcePort->id);
    f->sink_id = fixId(SinkPort->id);
    f->next = NULL;
    f->state = state;		/* Defined w/ '<-'  */
    if (state == IS_NET) {
	m->nstreams++;
    }
    f->next = m->stream;
    m->stream = f;
    if (bs < 0)
	bs = 0;
    if (bs > maxbfsz)
	bs = maxbfsz;
    f->bufsz = bs;
    return f;
}


Numvar visitNumvar(Numvar p)
{
    return p;
}

String visitStringvar(Stringvar p) {
	   return p;
}

String visitEnvar(Envar p)
{
  return p;
}

String getEnvVar(String s) {
	String s1,s2;

	s1=s+2;
	s2=getenv(s1);
	return s2;
	return(getenv("BROWSER"));
}

String visitStringval(Stringval _p_) {

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

String visitSymval(Symval _p_)
{
    switch (_p_->kind) {
    case is_Symvalv:
	return getSymVar(_p_->u.symvalv_.symvar_);

    case is_Symvali:
	return (visitIdent(_p_->u.symvali_.ident_));

    default:
	badkind(Symval);
    }
}

String visitSymAssgn(SymAssgn _p_)
{
  switch(_p_->kind)
  {
  case is_SymAssgni:
    return addSymVar(_p_->u.symassgni_.symvar_,
    	visitSymval(_p_->u.symassgni_.symval_));
    break;  
   case is_SymAssgns:
     return addSymVar(_p_->u.symassgns_.symvar_1,
   	 getSymVar(_p_->u.symassgns_.symvar_2));
  default:
    badkind(SymAssgn);
  }
}
void visitStrassgn(Strassgn _p_)
{
	addStringVar( 
    		visitStringvar(_p_->u.strassgnv_.stringvar_),
    		visitSymval(_p_->u.strassgnv_.symval_)
	);
}

Integer visitBuffsize(Buffsize _p_)
{
    switch (_p_->kind) {
    case is_Bufszi:
	return (visitNumval(_p_->u.bufszi_.numval_));
    case is_Bufsze:
	return defaultBufferSize;  // @todo 
    default:
	badkind(Buffsize);
    }
}

Integer visitLarrow(Larrow _p_)
{
    return visitBuffsize(_p_->u.arrowx_.buffsize_);
}

Integer visitRarrow(Rarrow _p_)
{
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

static void setStream(Port pt, Stream s)
{
    while (pt->stream) {
	pt = pt->next;
    }
    pt->stream = s;
}

static void SetSource(Process p)
{

    p->nportsOut++;
}

static void SetSink(Process p)
{

    p->nportsIn++;
}

Stream visitS_tream(S_tream _p_)
{
    Process snk, src;
    Port pt, src_pt, snk_pt;
    Stream s, s2;
    int bs;

    switch (_p_->kind) {
    case is_Streamx:
	bs = visitLarrow(_p_->u.streamx_.larrow_);
	src = visitProc(_p_->u.streamx_.proc_2);
	snk = visitProc(_p_->u.streamx_.proc_1);
	src_pt = visitPrt(_p_->u.streamx_.prt_2);
	snk_pt = visitPrt(_p_->u.streamx_.prt_1);
	linkPort(snk, snk_pt);
	SetSink(snk);
	SetSource(src);
	linkPort(src, src_pt);
	s = MakeStream(state, src, snk, bs, net_model, src_pt, snk_pt);
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
	snk = visitProc(_p_->u.streamrx_.proc_2);
	LatestPort = visitPrt(_p_->u.streamrx_.prt_2);
	linkPort(snk, LatestPort);
	SetSink(snk);
	bs = visitRarrow(_p_->u.streamrx_.rarrow_);
	s = MakeStream(state, src, snk, bs, net_model, LatestSrcPort,
		       LatestPort);
	setStream(LatestSrcPort, s);
	setStream(LatestPort, s);
	s->sink_id = LatestPort->id = fixId(LatestPort->id);
	s->source_id = LatestSrcPort->id = fixId(LatestSrcPort->id);
	s->SinkPort->match = s->SourcePort;
	s->SourcePort->match = s->SinkPort;
	VerifyStream(s);
	return s;

    case is_Streamy:
	s = visitS_tream(_p_->u.streamy_.s_tream_);
	snk = s->source;
	LatestPort = pt = visitPrt(_p_->u.streamy_.prt_1);
	bs = visitLarrow(_p_->u.streamy_.larrow_);
	LatestSrcPort = visitPrt(_p_->u.streamy_.prt_2);
	src = visitProc(_p_->u.streamy_.proc_);
	linkPort(src, LatestSrcPort);
	SetSource(src);
	linkPort(snk, pt);
	SetSink(snk);
	s2 = MakeStream(state, src, snk, bs, net_model, LatestSrcPort,
			LatestPort);
	s2->SourcePort->stream = s2->SinkPort->stream = s2;
	s2->SourcePort = LatestSrcPort;
	s2->SinkPort = LatestPort;
	s2->SourcePort->stream = s2->SinkPort->stream = s2;
	s2->sink_id = LatestPort->id = fixId(LatestPort->id);
	s2->source_id = LatestSrcPort->id = fixId(LatestSrcPort->id);
	s2->SinkPort->match = s2->SourcePort;
	s2->SourcePort->match = s2->SinkPort;
	VerifyStream(s2);
	return s2;
    case is_Streamry:
	s = visitS_tream(_p_->u.streamry_.s_tream_);
	snk = visitProc(_p_->u.streamry_.proc_);
	bs = visitRarrow(_p_->u.streamry_.rarrow_);
	src = s->sink;
	src_pt = visitPrt(_p_->u.streamry_.prt_1);	/* Source Port */
	linkPort(src, src_pt);
	SetSource(src);
	pt = visitPrt(_p_->u.streamry_.prt_2);	/* Sink Port */
	SetSink(snk);
	s2 = MakeStream(state, src, snk, bs, net_model, src_pt, pt);
	setStream(src_pt, s2);
	setStream(pt, s2);
	s2->sink_id = s->SinkPort->id;
	s2->source_id = src_pt->id;
	s2->SinkPort->match = s2->SourcePort;
	s2->SourcePort->match = s2->SinkPort;
	VerifyStream(s2);
	return s2;

    default:
	badkind(S_tream);
    }
}

String saves = NULL;
Extport MakeExtport(PortType type, Process p, Port prt, int bs, int id)
{

    Extport ep;

    ep = (Extport) malloc(sizeof(Extport_));

    ep->type = type;
    linkPort(p, prt);
    ep->name = prt->name = saves;
    if (type == SINK) {
	ep->sink = p;
	ep->source = NULL;
	ep->sink_id = fixId(prt->id);
	ep->source_id = id;
	ep->bufsz = bs;
	SetSink(p);
    } else {
	ep->source = p;
	ep->sink = NULL;
	ep->source_id = fixId(prt->id);
	ep->sink_id = id;
	SetSource(p);
    }

    saves = NULL;
    ep->bufsz = bs;
    ep->next = NULL;
    return ep;
}

Integer visitTab(Tab _p_)
{
    switch (_p_->kind) {
    case is_Tabn:
	return visitNumval(_p_->u.tabn_.numval_);
    case is_Tabs:
	saves = visitSymval(_p_->u.tabs_.symval_);	/** @todo fix named ports */
	return -2;
    default:
	badkind(Tab);
    }
}

Extport visitExtPortIn(ExtPortIn _p_)
{
    switch (_p_->kind) {
    case is_Extin:
	return MakeExtport(SINK,
			   visitProc(_p_->u.extin_.proc_),
			   visitPrt(_p_->u.extin_.prt_),
			   visitLarrow(_p_->u.extin_.larrow_),
			   visitTab(_p_->u.extin_.tab_));

    case is_ExtinR:
	return MakeExtport(SINK,
			   visitProc(_p_->u.extinr_.proc_),
			   visitPrt(_p_->u.extinr_.prt_),
			   visitRarrow(_p_->u.extinr_.rarrow_),
			   visitTab(_p_->u.extinr_.tab_));
    default:
	badkind(ExtPortIn);
    }

}

Extport visitExtPortOut(ExtPortOut _p_)
{

    switch (_p_->kind) {
    case is_Extout:
	return MakeExtport(SOURCE,
			   visitProc(_p_->u.extout_.proc_),
			   visitPrt(_p_->u.extout_.prt_),
			   visitLarrow(_p_->u.extout_.larrow_),
			   visitTab(_p_->u.extout_.tab_));
    case is_Extoutr:
	return MakeExtport(SOURCE,
			   visitProc(_p_->u.extoutr_.proc_),
			   visitPrt(_p_->u.extoutr_.prt_),
			   visitRarrow(_p_->u.extoutr_.rarrow_),
			   visitTab(_p_->u.extoutr_.tab_));
    default:
	badkind(ExtPortOut);
    }
}


Process visitHermt(Hermt _p_)
{
    char *name;
    Process p;

    state = IS_NET;
    switch (_p_->kind) {
    case is_Hermtx:
	name = visitSymval(_p_->u.hermtx_.symval_);
	p = MakeProcess(net_model,
			name,
			visitComp(_p_->u.hermtx_.comp_),
			MakeArg(visitListArgument
				(_p_->u.hermtx_.listargument_), name));
	return p;
    case is_Hermty:
	p = MakeProcess(net_model,
			visitSymval(_p_->u.hermty_.symval_), NULL,
			MakeArg(visitListArgument
				(_p_->u.hermty_.listargument_), NULL));

	return p;
    case is_Hermtax:
	p = MakeProcess(net_model, "_", visitComp(_p_->u.hermtax_.comp_),
			MakeArg(visitListArgument
				(_p_->u.hermtax_.listargument_), NULL));
	return p;
    case is_Hermtay:
	p = MakeProcess(net_model, "_", NULL,
			MakeArg(visitListArgument
				(_p_->u.hermtay_.listargument_), NULL));
	return p;
    default:
	badkind(Hermt);
    }
}

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
	s = visitS_tream(_p_->u.snets_.s_tream_);
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

static void visitListSubnet(ListSubnet listsubnet, Ident id)
{
    while (listsubnet != 0) {
	(visitSubnet(listsubnet->subnet_, id));
	listsubnet = listsubnet->listsubnet_;
    }
}

void visitSubdef(Subdef _p_)
{
    visitListSubnet(_p_->u.snet_.listsubnet_,
		    visitSymval(_p_->u.snet_.symval_));
}

void visitStm(Stm _p_)
{
    Process p;

    state = IS_NET;
    switch (_p_->kind) {
    case is_Stmx:
	visitS_tream(_p_->u.stmx_.s_tream_);
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
	state = IS_SUB;
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

void visitListStm(ListStm liststm)
{

    while (liststm != 0) {
	visitStm(liststm->stm_);
	liststm = liststm->liststm_;
    }
}

static char *MakeAnon(Component c)
{
    static char bfr[100];

    if (c == NULL)
	return bfr;

    sprintf(bfr, "_%s", c->name);	// @BUG too many dupes
    return strndup(bfr, 99);

};

Process visitProc(Proc _p_)
{
    Component c;
    char *name;

    switch (_p_->kind) {

    case is_Processx:
	return MakeProcess(net_model,
			   visitSymval(_p_->u.processx_.symval_),
			   visitComp(_p_->u.processx_.comp_),
			   MakeArg(visitListArgument
				   (_p_->u.processx_.listargument_),
				   visitSymval(_p_->u.processx_.symval_)));

    case is_Processy:
	return MakeProcess(net_model,
			       visitSymval(_p_->u.processy_.symval_),
			   NULL,
			   MakeArg(visitListArgument
				   (_p_->u.processy_.listargument_),
				   NULL));

    case is_Processax:		/* Anonymous process */
	c = visitComp(_p_->u.processax_.comp_);
	name = MakeAnon(c);
	return MakeProcess(net_model,
			   name,
			   c,
			   MakeArg(visitListArgument
				   (_p_->u.processax_.listargument_),
				   name));
	break;

    case is_Processay:		/* Anonymous process */
	name = MakeAnon(NULL);
	return MakeProcess(net_model,
			   name,
			   NULL,
			   MakeArg(visitListArgument
				   (_p_->u.processay_.listargument_),
				   name));
    default:
	badkind(Proc);
    }
}

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

Component visitComp(Comp _p_)
{
    switch (_p_->kind) {
    case is_Compx:
	return MakeComponent(visitSymval(_p_->u.compx_.symval_),
			     defaultPath);
    case is_Compy:
	return MakeComponent(visitSymval(_p_->u.compy_.symval_2),
			     visitSymval(_p_->u.compy_.symval_1));
    case is_Compn:
	return MakeComponent(visitSymval(_p_->u.compn_.symval_), "'");
    default:
	badkind(Comp);
    }
}

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

ListArgument visitListArgument(ListArgument listargument)
{
    ListArgument l = NULL;

    while (listargument != 0) {
	l = make_ListArgument(visitArgument(listargument->argument_), l);
	listargument = listargument->listargument_;
    }

    return l;

}

Ident visitIdent(Ident i)
{
    return i;
}

Integer visitInteger(Integer i)
{
    return i;
}

String visitString(String s)
{
    return s;
}

static char *makeName(char *pn, char *nn)
{
    char bfr[1000];

    strncpy(bfr, pn, 500);
    strncat(bfr, "_", 501);
    strncat(bfr, nn, 1000);
    return (strdup(bfr));
}

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


static void Expand2(Model m, Process p, Stream s)
{
    char *srcname, *snkname;	// Concatenated process names 
    Process src, snk;
    Port psrc, psnk;
    Stream ns;			/* New Stream */
    state = IS_NET;

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
    ns = MakeStream(state, src, snk, bs, m, psrc, psnk);
    ns->sink_id = s->sink_id;
    ns->source_id = s->source_id;
    ns->bufsz = s->bufsz;
    ns->state = state;
    psrc->stream = psnk->stream = ns;
    ns->source->depth = ns->sink->depth = CheckDepth(p->depth);
    ns->SinkPort->match = ns->SourcePort;
    ns->SourcePort->match = ns->SinkPort;
    VerifyStream(ns);
    VerifyStream(s);

}

static Port copyPort(Port p0)
{
    Port p1;
    p1 = MakePort(p0->id, p0->name);
    *p1 = *p0;
    return p1;
}

/**  Add external port to list of unmatched external ports.
     Match ports later
*/
Extport extprtList = NULL;
static int findAmatchingPort(Model m, Process p, Extport ep)
{
    Extport ep2 = NULL;
    Port pt;
    Process p2;
    // Component c=NULL;
    char *srcname;
    char *snkname;

    state = IS_ORPHAN;

    if (ep->type == SOURCE) {
	srcname = makeName(p->name, fixName(ep->source->name));
	p2 = getProc(srcname);
	if (!p2) {
	    p2 = MakeProcess(m, srcname, ep->source->comp,
			     ep->source->arg);
	}
	pt = MakePort(ep->sink_id, ep->name);
    } else {
	snkname = makeName(p->name, fixName(ep->sink->name));
	p2 = getProc(snkname);
	if (!p2) {
	    p2 = MakeProcess(m, snkname, ep->sink->comp, ep->sink->arg);
	}
	pt = MakePort(ep->source_id, ep->name);
    }
    p2->depth = p->depth + 1;
    ep2 = MakeExtport(ep->type, p2, pt, ep->bufsz, -1);
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
	while (pt) {
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
		    pnew->nportsIn++;
		    ptc = copyPort(pt);
		    ptc->stream = s;
		    ptc->id = s->sink_id = ep->sink_id;
		    linkPort(pnew, ptc);
		    pnew->depth = p->depth + 1;
		    if (s->sink->comp == NULL) {
			s->sink->comp =
			    MakeComponent(defaultSinkComp, defaultPath);
		    }
		    if (s->source->comp == NULL) {
			s->source->comp =
			    MakeComponent(defaultSourceComp, defaultPath);
		    }
		    s->SinkPort = ptc;
		    s->SinkPort->match = s->SourcePort;
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

	/* Expand the model for each external port and stream in the subnet */
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

static void FreeLater(Process * fl, Process p)
{
    p->next = *fl;
    *fl = p;
}

static void FreeExpandedProcesses(Process * fl)
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
	   expand that component subnet. 
	 */
void expandSubnets(Model m)
{
    Process p, pp, ps;
    Process fl = NULL;		/** List of processes to free */

    int more;

    do {
	p = m->proc;
	pp = NULL;
	more = 0;
	while (p) {
	    if (p->comp) {
		if (p->comp->path[0] == '\'') {	/* Is a subnet */
		    more = 1;
		    m->nprocs--;
		    ps = p;
		    if (pp)	// delink p from process chain.     
			pp->next = p->next;
		    else {
			m->proc = p->next;
		    }
		    p = pp;
		    expandSub(m, ps);
		    FreeLater(&fl, ps);	/* Pointers to ps still exist. */
		    break;
		}
	    }
	    pp = p;
	    p = p->next;
	}
	FreeExpandedProcesses(&fl);
    }
    while (more);

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
    c = MakeComponent("Join", "poc");
    j = MakeProcess(m, "_", c, MakeArg(NULL, NULL));
    j->depth = p->depth + 1;
    /*              AFTER
       (A)id <- 0(_ poc.Join);  [ s0 pt0 ptn]  
       (j)1  <- y(C);                [ s1 pt1   ] 
       (j)2  <- x(B);           [ s2 pt2    ]  */

    pt1 = MakePort(1, "");
    pt2 = MakePort(2, "");
    ptn = MakePort(0, "");	/*Join output */

    s1 = pt->stream;
    s0 = pt0->stream;

    s2 = MakeStream(IS_NET, pt0->stream->source, j,
		    pt0->stream->bufsz, m, pt0, pt);
    s2->SourcePort = s0->SourcePort;

    s0->source = j;
    s0->SourcePort = ptn;
    s0->SourcePort->stream = s0;
    s0->source_id = 0;
    ptn->stream = s0;


    s2->sink_id = 2;
    assert(s0->SinkPort->stream == s0);
    s2->source_id = s2->SourcePort->id;
    s2->SinkPort = pt2;
    s2->SourcePort->stream = s2;
    pt2->stream = s2;

    s1->sink = j;
    s1->sink_id = 1;
    assert(s2->SourcePort->stream == s2);


    pt->next->prev = pt0;	// Delink pt
    pt0->next = pt->next;
    p->nportsIn--;


    /* Fix j ports */
    j->port = ptn;
    ptn->id = 0;
    ptn->name = "";
    ptn->next = pt1;
    pt1->next = pt2;
    pt2->next = ptn;
    pt2->prev = pt1;
    pt1->prev = ptn;
    ptn->prev = pt2;
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

static void fixFanOut(Model m, Process p, Port pt0, Port pt)
{
    Process j;			// New anonymous split process 
    Component c;
    Port pt1, pt2;
    Stream s0, s1, s2;

    /*              BEFORE 
       (B)x <- id(A);  [ s0 pt0]
       (C)y <- id(A);  [ s1 pt ]  */
    c = MakeComponent("Split", "poc");
    j = MakeProcess(m, "_", c, MakeArg(NULL, NULL));
    j->depth = p->depth + 1;
    /*              AFTER
       (B)x <-  1(j);  [ s0 pt0]  
       (C)y <-  2(j;        [ s1    ] 
       (j)0 <- id(A);  [ s2    ]  */


    pt1 = MakePort(1, "");
    pt2 = MakePort(2, "");
    s0 = pt0->stream;

    s2 = MakeStream(IS_NET, pt0->stream->source, j,
		    pt0->stream->bufsz, m, pt0, pt);

    s2->sink_id = 0;
    s2->source_id = pt0->id;

    s1 = pt->stream;
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

			/** Insert poc.Join process wherever fanin occurs. */
static void fixFanInOut(Model m)
{
    Process p;

    p = m->proc;

    while (p) {			/* For all processes(p) Fix fan in and fan out. */
	fixFan(m, p);
	p = p->next;
    }

}

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

#define MAX(A,B) ( (A>B)? A: B)

/** Slow, bubble sort */
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
		    pt1 = pt2;
		    pt2 = ptw;
		}
	    }
	    pt1 = pt2;
	    pt2 = pt1->next;
	}
    }
}

static void createStream(Model m, Extport ep, Extport ep2)
{
    Stream s;
    Port snkpt, srcpt, pt;

    srcpt = ep->source->port;

    pt = ep2->sink->port;
    while (pt->id != ep2->source_id) {
	pt = pt->next;
	if (pt == ep2->sink->port) {
	    abort();
	}
    }
    snkpt = pt;

    while (srcpt->id != ep->sink_id) {
	srcpt = srcpt->next;
	if (srcpt == ep->source->port) {
	    abort();
	}
    }

    s = MakeStream(IS_NET, ep->source, ep2->sink,
		   MAX(ep->bufsz, ep2->bufsz), m, srcpt, snkpt);

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

#define MATCH(SRC,SNK) if(eqs(srcn,#SRC)) {	\
			  if(eqs(snkn,#SNK)) {	\
				return 1;	\
			  } else {		\
				return 0;	\
			  }			\
		       }

static int MatchName(String srcn, String snkn)
{

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

/** match external ports: ep2 is sink port*/
static int isaMatch(Extport ep2, Extport ep)
{

    if (ep2->source_id < 0) {
	if (MatchName(ep->name, ep2->name))
	    return 1;
	return 0;
    }

    if (ep->sink_id == ep2->source_id)
	return 1;

    if (ep->name == NULL)
	return 0;

    return 0;
}

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

	/** Match source ports */
static void autolink(Model m)
{
    Extport ep;

    ep = extprtList;
    state = IS_NET;
    while (ep) {
	if (ep->type == SOURCE) {
	    findSink(m, ep);
	}
	ep = ep->next;
    }
}

Model visitValidSW(ValidSW _p_)
{				/* Parse visit root */

    net_model = MakeModel(NULL);
    visitListStm(_p_->u.valid_.liststm_);
    fixFanInOut(net_model);
    expandSubnets(net_model);
    autolink(net_model);
    return net_model;
}
