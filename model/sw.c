/* SW.c

*/

#include <stdlib.h>
#include <stdio.h>
#include "sw.h"
#include "swsym.h"

#define NOBUFFERS

#define defaultPath       "def"
#define defaultSourceComp "Gen1"
#define defaultSinkComp   "Print1"

static String default_path={"strings"};   /* ?? arg later */
int bs,maxbfsz=1;		              /*  Buffer size */


Model net_model=NULL;  
	
Model visitValidSW(ValidSW _p_) {   /* Parse visit root */
	
	 net_model=MakeModel(NULL);
     visitListStm(_p_->u.valid_.liststm_);
     return net_model;
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
    fprintf(stderr, "Error: bad kind field when printing Stringval!\n");
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
    fprintf(stderr, "Error: bad kind field when printing Numval!\n");
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
    fprintf(stderr, "Error: bad kind field when printing Numassgn!\n");
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
        "Error: bad kind field when printing Strassgn!\n");
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
    fprintf(stderr, "Error: bad kind field when printing Buffsize!\n");
    exit(1);
  }
}

Integer visitArrow(Arrow _p_)
{
    return visitBuffsize(_p_->u.arrowx_.buffsize_);
}

/* Add port,p to port list at P->port */
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
	return MakeStream(GOIP,
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
    return MakeStream(GOIP, src, snk, bs, net_model);
  default:
    fprintf(stderr, "Error: bad kind field when printing S_tream!\n");
    exit(1);
  }
}

void visitExtPortIn(ExtPortIn _p_)
{
  switch(_p_->kind)
  {
  case is_Extin:
    /* Code for Extin Goes Here */
    visitSnk(_p_->u.extin_.snk_);
    visitArrow(_p_->u.extin_.arrow_);
    visitNumval(_p_->u.extin_.numval_);
    break;
  default:
    fprintf(stderr, "Error: bad kind field when printing ExtPortIn!\n");
    exit(1);
  }
}

void visitExtPortOut(ExtPortOut _p_)
{
  switch(_p_->kind)
  {
  case is_Extout:
    /* Code for Extout Goes Here */
    visitNumval(_p_->u.extout_.numval_);
    visitArrow(_p_->u.extout_.arrow_);
    visitSrce(_p_->u.extout_.srce_);
    break;
  default:
    fprintf(stderr, "Error: bad kind field when printing ExtPortOut!\n");
    exit(1);
  }
}
void visitSubnet(Subnet _p_)
{
  switch(_p_->kind)
  {
  case is_Snets:
    /* Code for Snets Goes Here */
    visitS_tream(_p_->u.snets_.s_tream_);
    break;  case is_Snetin:
    /* Code for Snetin Goes Here */
    visitExtPortIn(_p_->u.snetin_.extportin_);
    break;  case is_Snetout:
    /* Code for Snetout Goes Here */
    visitExtPortOut(_p_->u.snetout_.extportout_);
    break;
  default:
    fprintf(stderr, "Error: bad kind field when printing Subnet!\n");
    exit(1);
  }
}

void visitListSubnet(ListSubnet listsubnet)
{
  while(listsubnet != 0)
  {
    /* Code For ListSubnet Goes Here */
    visitSubnet(listsubnet->subnet_);
    listsubnet = listsubnet->listsubnet_;
  }
}

void visitSubdef(Subdef _p_)
{
  switch(_p_->kind)
  {
  case is_Snet:
    /* Code for Snet Goes Here */
    visitIdent(_p_->u.snet_.ident_);
    visitListSubnet(_p_->u.snet_.listsubnet_);
    break;
  default:
    fprintf(stderr, "Error: bad kind field when printing Subdef!\n");
    exit(1);
  }
}

void visitStm(Stm _p_) 
{	
	switch(_p_->kind)
  {
  case is_Stmx:
  	visitS_tream(_p_->u.stmx_.s_tream_);
  	return;
  case is_Stmn:
    /* Code for Stmn Goes Here */
    visitNumassgn(_p_->u.stmn_.numassgn_);
    return ;
  case is_Stms:
    /* Code for Stms Goes Here */
    visitStrassgn(_p_->u.stms_.strassgn_);
    return ; 
  case is_Stmnet:
    /* Code for Stmnet Goes Here */
    visitSubdef(_p_->u.stmnet_.subdef_);
    break;
  default:
    fprintf(stderr, "Error: bad kind field when printing Stm!\n");
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

#ifdef DSAWLKJ 
Model visitListStm(ListStm liststm)
{
	Model m;
    if( ! liststm)  
    	return net_model;
    
    m=net_model;	    
    m->proc = m->stream->source;
  	m->proc->next = m->stream->sink;
  	m->stream->sink->next = NULL;   
	liststm = liststm->liststm_;
	 
 while(liststm != 0) {
  	Model m2;
    m2 = visitStm(liststm->stm_);
    
    if(m2) { 
  		//m2->stream->next=m->stream;
  		//m->stream=m2->stream;
  	
  		if( notListed(m2->stream->source, m)) {
  			m2->stream->source->next = m->proc;
  			m->proc = m2->stream->source;
  		} 
  		if( notListed(m2->stream->sink, m)) {
  			m->stream->sink->next = m->proc;
  			m->proc = m2->stream->sink;
  		} 
 	}  	
    liststm = liststm->liststm_;
  }
  
  return m;
}
#endif
 


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
    fprintf(stderr, "Error: bad kind field when printing Srce!\n");
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
    fprintf(stderr, "Error: bad kind field when printing Snk!\n");
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
    	"Error: bad kind field when printing Prt!\n");
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
    fprintf(stderr, "Error: bad kind field when printing Comp!\n");
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

