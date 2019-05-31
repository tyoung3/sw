/* SW.c
    Create network model from parse tree 
*/

#include <stdlib.h>
#include <stdio.h>
#include "sw.h"
#include "swsym.h"
#include "model.h"

#define NOBUFFERS

#define defaultPath       "def"
#define defaultSourceComp "Gen1"
#define defaultFilterComp "Filter1"
#define defaultSinkComp   "Print1"

/* @TODO  Standardize error messages */

STATE state=IS_NET; 

static String default_path={"strings"};   /* ?? arg later */
int bs,maxbfsz=1;		              /*  Buffer size */

Model net_model=NULL;  
Subnetm MakeSubnetm(Stream s, Extport in, Extport out ) {
	Subnetm sn;   
	
	sn = (Subnetm)malloc(sizeof(Subnetm_));
	sn->name = NULL;
	sn->stream=s;
	sn->extport=in;
	if(in)
		in->next=out;
	return  sn;
}; 

Model MakeModel(Stream f) {
	Model m;
	
	m=(Model)malloc(sizeof(Model_)); 
    if (!m)
    {
        fprintf(stderr, "SW/MakeModel/FAIL: out of memory when allocating Process!\n");
        exit(1);
    }
    
	m->nstreams = 0;
	m->ncomponents = 0;
	m->nprocs	= 0;
	m->stream=f;
	m->proc = NULL;
	//p->next = NULL;
	//p->prev = NULL;
	return m;
	
}	    

Model visitValidSW(ValidSW _p_) {   /* Parse visit root */
	
	 net_model=MakeModel(NULL);
     visitListStm(_p_->u.valid_.liststm_);
     return net_model;
}



static int countArg(char **arg) {
	int i=0;
	
	while(arg[i++] != NULL) {
	}
	
	return i;
}

static char **NewArg(char **arg, char **narg) {    			
		char **a; 
		int i,j,na;
		
		
		na = countArg(arg) + countArg(narg) - 1;
		a = (char**) malloc( na * sizeof(char*));
		
		while ( arg[i]  ) {
			a[i] = arg[i];
			i++;
		}		
		
		j=1;
		
		while ( narg[j] ) {
			a[i] = narg[j];
			i++; j++;
		} 
		
		free(arg);
		free(narg);
		return a;
		
}
static char **MakeArg(ListArgument la, char *name) {
	char **arg;   /* Pointer to array of string pointers. */
	int i=1,narg=1;
	ListArgument la2=la;
	
	while(la2) {
		narg++;
		la2     = la2->listargument_;
	}
	
	arg = (char **) malloc((narg+1)*sizeof(char*)); 
	arg[0] = name;
	arg[narg] = NULL; 

	i=narg-1;
	while(la) {
		arg[i--] = 
		  visitStringval(la->argument_->u.argumentx_.stringval_);
		la       = la->listargument_;
	}
	
	return arg;
}
static Process MakeProcess( Model model,Ident name, Component comp, ListArgument la) {
	Process p;
	static int onone=1;
	
	if(onone) {
		onone=0; 
		tabinit(100000);
	}
	
	p=getProc(name);
	 
	if(p==NULL) {
		p=(Process)malloc(sizeof(Process_)); 
    	if (!p)
    	{
    	    fprintf(stderr, "SW/MakeProcess/FAIL: out of memory when allocating Process!\n");
    	    exit(1);
    	}
    	
		p->comp = comp;
		p->name = name;
		p->nportsIn =0;
		p->nportsOut=0;
		p->port	= NULL;
	    p->kind = state;
		if(state == IS_NET) {
			p->next = model->proc;
			model->proc = p;
			model->nprocs++;
		}	else {
			p->next = NULL;
		}
		p->prev = NULL;
		p->arg  = MakeArg(la,name);
    	addProc(name,p);
    }	else {
    	if(comp) {
    		p->comp = comp;
    	}
    	if(la) {
    		if( p->arg ) { 	
    			p->arg  = NewArg(p->arg,MakeArg(la,name)); 
    		} else {
	    		p->arg  = MakeArg(la,name);
	    	}	
    	}	
    }
    
	return p;
	
} 	

static int fixId(int i) {
	if (i<0) 
		return 0;
	return i;
}
	

Port MakePort(int n, Ident id) {
	Port p; 
	
	p=(Port)malloc(sizeof(Port_)); 
    if (!p)
    {
        fprintf(stderr, "Error: out of memory when allocating Port!\n");
        exit(1);
    }
    
    if(id) {
    	p->name=id;
    } else {
    	p->name="";
    }	
	p->id = n;
	p->match = NULL;
	p->next = p;
	p->prev = p;
	p->match = NULL;
	// p->owner = own;
	return p;
} 
    


Component MakeComponent(Ident name, String path) {
	Component c; 
	
	c=(Component)malloc(sizeof(Component_)); 
    if (!c)
    {
        fprintf(stderr, "Error: out of memory when allocating Component!\n");
        exit(1);
    }
    
	c->name = name;
	c->path = path;
	c->nports = 0;
	c->prev = NULL;
	c->next = NULL;
	return c;
} 


Stream MakeStream(STATE  state, Process src, Process snk, int bs, Model m) {
	Stream f;
	
	f=(Stream)malloc(sizeof(Stream_)); 
    if (!f)
    {
        fprintf(stderr, "SWMAIN/MakeStream/FAIL: out of memory when allocating Stream!\n");
        exit(1);
    }
    
	f->source    = src;
	f->sink      = snk;
	f->source_id = fixId(src->source_id); 
	f->sink_id   = fixId(snk->sink_id);
	f->next      = NULL;
	f->prev      = NULL;
	f->state	 = state;  /* Defined w/ '<-'  */
	if(state==IS_NET) {
 		m->nstreams++;
	}
    f->next = m->stream;	
    m->stream=f;
    if(bs<1) bs=1;   
    if(bs>MAX_BUFFER)    
    	bs=MAX_BUFFER;
    if( bs > maxbfsz) 
    		maxbfsz=bs;	
	f->bufsz	 = bs;
	return f;
} 


Numvar visitNumvar(Numvar p)
{
	return p;
}
String visitStringvar(Stringvar p)
{
	return p;
}
String visitStringval(Stringval _p_)
{
  switch(_p_->kind)
  {
  case is_StringVals:
    return (visitString(_p_->u.stringvals_.string_));
  case is_StringValv:
    return visitStringvar(_p_->u.stringvalv_.stringvar_);
  
  default:
    fprintf(stderr, "Error: bad kind field when visiting Stringval!\n");
    exit(1);
  }
}

Integer visitNumval(Numval _p_)
{
  switch(_p_->kind)
  {
  case is_NumVali:
    /* Code for NumVali Goes Here */
    return (visitInteger(_p_->u.numvali_.integer_));
  case is_NumValv:
    /* Code for NumValv Goes Here */
    visitNumvar(_p_->u.numvalv_.numvar_);
	return 0;
  default:
    fprintf(stderr, "Error: bad kind field when visiting Numval!\n");
    exit(1);
  }
}

void visitNumassgn(Numassgn _p_)
{
  switch(_p_->kind)
  {
  case is_NumAssgnv:
    /* Code for NumAssgnv Goes Here */
    visitNumvar(_p_->u.numassgnv_.numvar_);
    visitNumval(_p_->u.numassgnv_.numval_);
    break;
  default:
    fprintf(stderr, "Error: bad kind field when visiting Numassgn!\n");
    exit(1);
  }
} 

void visitStrassgn(Strassgn _p_)
{
  switch(_p_->kind)
  {
  case is_StrAssgnv:
    /* Code for StrAssgnv Goes Here */
    visitStringvar(_p_->u.strassgnv_.stringvar_);
    visitStringval(_p_->u.strassgnv_.stringval_);
    break;
  default:
    fprintf(stderr, 
        "Error: bad kind field when visiting Strassgn!\n");
    exit(1);
  }
}


Integer visitBuffsize(Buffsize _p_)
{
  switch(_p_->kind)
  {
  case is_Bufszi:
    	return( visitNumval(_p_->u.bufszi_.numval_)) ;
  case is_Bufsze:
    	return 1;
  default:
    fprintf(stderr, "Error: bad kind field when visiting Buffsize!\n");
    exit(1);
  }
}

Integer visitArrow(Arrow _p_)
{
    return visitBuffsize(_p_->u.arrowx_.buffsize_);
}

/* Add port,p to port list at P->port in order by port id*/
static void linkPort(Process P, Port p) {  
	Port p2;   
	
	if(!P->port) {
   		P->port = p;
    	p->next = p;
    	p->prev = p;
		return;
	}
	  
	p2 = P->port;
	
	do {
		if(p->id < p2->id) {  
			p->next = p2; 
			p->prev = p2->prev;
			if(P->port == p2) {
				P->port=p;
			}      
			p->prev->next = p;
			p->next->prev = p;
			return;
		}
		p2 = p2->next;
	} while(p2!=P->port);
	
    p->next = P->port;      
    p->prev = p2->prev;
    p->next->prev = p;
	p->prev->next = p;
}    

Stream visitS_tream(S_tream _p_)
{
	Process snk,src;
	Port pt;
	Stream s;
	
  switch(_p_->kind)
  {
  case is_Streamx:
	return MakeStream(state,
     visitSrce(_p_->u.streamx_.srce_),
     visitSnk(_p_->u.streamx_.snk_),
	 visitArrow(_p_->u.streamx_.arrow_),
     net_model);
  case is_Streamy:    
    s=visitS_tream(_p_->u.streamy_.s_tream_);
    snk=s->source;   
    bs=visitArrow(_p_->u.streamy_.arrow_);
    src=visitSrce(_p_->u.streamy_.srce_);
    pt=visitPrt(_p_->u.streamy_.prt_);
    snk->sink_id   = pt->id;
    snk->nportsIn++;  
    linkPort( snk,pt);
    return MakeStream(state, src, snk, bs, net_model);
  default:
    fprintf(stderr, "Error: bad kind field when visiting S_tream!\n");
    exit(1);
  }
}

Extport visitExtPortIn(ExtPortIn _p_)
{
    /* Code for Extin Goes Here */
    visitSnk(_p_->u.extin_.snk_);
    visitArrow(_p_->u.extin_.arrow_);
    visitNumval(_p_->u.extin_.numval_);
    return (Extport) NULL;
}

Extport visitExtPortOut(ExtPortOut _p_)
{
    visitNumval(_p_->u.extout_.numval_);
    visitArrow(_p_->u.extout_.arrow_);
    visitSrce(_p_->u.extout_.srce_);
    
    return (Extport) NULL;
}


Subnetm visitSubnet(Subnet _p_)
{
	Stream s=NULL;
	Extport eport=NULL;
	
  switch(_p_->kind)
  {
  case is_Snets:
    return MakeSubnetm(
    	visitS_tream(_p_->u.snets_.s_tream_),
    	eport,eport);
  case is_Snetin:
    return MakeSubnetm(s,
    	visitExtPortIn(_p_->u.snetin_.extportin_), eport);
  case is_Snetout:
    return MakeSubnetm(
    	s,eport,visitExtPortOut(_p_->u.snetout_.extportout_));
  default:
    fprintf(stderr, "Error: bad kind field when visiting Subnet!\n");
    exit(1);
  }
}

static void visitListSubnet(ListSubnet listsubnet)
{
  while(listsubnet != 0)
  {
     (visitSubnet(listsubnet->subnet_) );
    listsubnet = listsubnet->listsubnet_;
  }
}

void visitSubdef(Subdef _p_)
{
    visitListSubnet(_p_->u.snet_.listsubnet_);
}

void visitStm(Stm _p_) 
{	
    state=IS_NET;
	switch(_p_->kind)
  {
  case is_Stmx:
  	visitS_tream(_p_->u.stmx_.s_tream_);
  	return;
  case is_Stmn:
    visitNumassgn(_p_->u.stmn_.numassgn_);
    return ;
  case is_Stms:
    visitStrassgn(_p_->u.stms_.strassgn_);
    return ; 
  case is_Stmnet:
    state=IS_SUB;
    visitSubdef(_p_->u.stmnet_.subdef_);
    break;
  default:
    fprintf(stderr, "Error: bad kind field when visiting Stm!\n");
    exit(1);
  }
}

static int notListed(Process p, Model m) {
	Process a;
	
	a=m->proc;
	while(a) {
		if( getProc(p->name) == 
		    getProc(a->name) )
		return 0;
		a=a->next;
	};
		    
	return 1;
}

void visitListStm(ListStm liststm)
{
  
  while(liststm != 0)
  {
    visitStm(liststm->stm_);
    liststm = liststm->liststm_;
  }
}


Process visitSrce(Srce _p_)
{
	Process p;
	Port pt;
	String s;
	Component c;
	
  switch(_p_->kind)
  {
  case is_Sourcex:
    p  = visitProc(_p_->u.sourcex_.proc_);
    pt = visitPrt (_p_->u.sourcex_.prt_);  
    p->source_id = pt->id; 
    p->nportsOut++;
    linkPort(p,pt);
    return p;
  case is_Sourcey:
    s=visitIdent(_p_->u.sourcey_.ident_);
    c=MakeComponent(defaultSourceComp,defaultPath);
    p=MakeProcess(net_model,s,c,NULL);
    pt=MakePort(-2,"");
    p->source_id=-2;
    p->nportsOut++;
    linkPort(p,pt);
    return p;
  default:
    fprintf(stderr, "Error: bad kind field when visiting Srce!\n");
    exit(1);
  }
}
    
Process visitSnk(Snk _p_)
{
	Process p;
	Port pt;
	String s;
	Component c;
	
  switch(_p_->kind)
  {
  case is_Sinkx:
    /* Code for Sinkx Goes Here */
    p =visitProc(_p_->u.sinkx_.proc_);
    pt=visitPrt(_p_->u.sinkx_.prt_);
    p->sink_id = pt->id;
    p->nportsIn++;  
    linkPort(p,pt);
    return p;  
  case is_Sinky:
    /* Code for Sinky Goes Here */
    s=visitIdent(_p_->u.sinky_.ident_);
    c=MakeComponent(defaultSinkComp,defaultPath);
    p=MakeProcess(net_model,s,c,NULL);
    pt=MakePort(-2,"");
    p->sink_id=-2;
    p->nportsIn++;
    linkPort(p,pt);
    return p;
  default:
    fprintf(stderr, "Error: bad kind field when visiting Snk!\n");
    exit(1);
  }
  
}

Process visitProc(Proc _p_)
{
  switch(_p_->kind) {
  
  case is_Processx:  
    return MakeProcess(net_model,
    	visitIdent(_p_->u.processx_.ident_), 
    	visitComp(_p_->u.processx_.comp_),
    	visitListArgument(_p_->u.processx_.listargument_)
    );   
      
  case is_Processy:   
    return MakeProcess(net_model,
    	visitIdent(_p_->u.processy_.ident_), 
    	NULL,
    	visitListArgument(_p_->u.processy_.listargument_) 
    );
  default:
    fprintf(stderr, 
    "Error: bad kind field when visiting Proc!\n");
    exit(1);
  }
}

Port visitPrt(Prt _p_)   
{
  switch(_p_->kind)
  {
  case is_Portx:

  		return(MakePort(visitNumval(_p_->u.portx_.numval_),
  			NULL));
    case is_Portni:   		
    	return MakePort(visitNumval(_p_->u.portni_.numval_),
   		visitIdent(_p_->u.portni_.ident_));
    case is_Portin:
    		return MakePort(visitNumval(_p_->u.portin_.numval_),
    		visitIdent(_p_->u.portin_.ident_));
    case is_Portn:
    	return MakePort(-1,visitIdent(_p_->u.portn_.ident_));
    case is_Porte:
    	return MakePort(-1,NULL);
  default:
    fprintf(stderr, 
    	"Error: bad kind field when visiting Prt!\n");
    exit(1);
  }
}

Component visitComp(Comp _p_)
{
  switch(_p_->kind)
  {
  case is_Compx:
     return MakeComponent(visitIdent(_p_->u.compx_.ident_), default_path);
   case is_Compy:
     return MakeComponent( 
	    visitIdent(_p_->u.compy_.ident_2),
    	visitIdent(_p_->u.compy_.ident_1)
    );
  case is_Compn:
    return MakeComponent( visitIdent(_p_->u.compn_.ident_),"");
  default:
    fprintf(stderr, "Error: bad kind field when visiting Comp!\n");
    exit(1);
  }
}

Argument visitArgument(Argument _p_)
{   
	// OLD: return make_Argumentx(visitString(_p_->u.argumentx_.string_));	
    return make_Argumentx(make_StringValv(visitStringval(_p_->u.argumentx_.stringval_)));
}

ListArgument visitListArgument(ListArgument listargument)
{
	ListArgument l=NULL;
	
	while(listargument != 0)
  {
    l = make_ListArgument(visitArgument(
    	listargument->argument_),
    	l);
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

