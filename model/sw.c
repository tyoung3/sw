/* SW.c

*/

#include <stdlib.h>
#include <stdio.h>
#include "sw.h"
#include "swsym.h"

#define NOBUFFERS

static String default_path={"strings"};   /* ?? arg later */
int bs,maxbfsz=1;		              /*  Buffer size */
	
Model visitValidSW(ValidSW _p_) {   /* Parse visit root */
	
    return visitListStm(_p_->u.valid_.liststm_);
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
    visitStringvar(_p_->u.stringvalv_.stringvar_);
    return NULL;
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
    fprintf(stderr, "Error: bad kind field when printing Strassgn!\n");
    exit(1);
  }
}

Model visitStm(Stm _p_) 
{	
	Model m;  // ?? m=MakeModel(visitStm(liststm->stm_));
	
	switch(_p_->kind)
  {
  case is_Stmx:
	m=MakeModel(visitS_tream(_p_->u.stmx_.s_tream_));
	return m;
    break;  
  case is_Stmn:
    /* Code for Stmn Goes Here */
    visitNumassgn(_p_->u.stmn_.numassgn_);
    return NULL;
  case is_Stms:
    /* Code for Stms Goes Here */
    visitStrassgn(_p_->u.stms_.strassgn_);
    return NULL;
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

Model visitListStm(ListStm liststm)
{
	if(!liststm) {
		fprintf(stderr,"SW/WARNING: no valid streams\n"); 
		exit(0);
	}

	Model m;
	m = visitStm(liststm->stm_);
	m->proc = m->stream->source;
  	m->proc->next = m->stream->sink;
  	m->stream->sink->next = NULL;
	liststm = liststm->liststm_;
	
  while(liststm != 0)
  {
  	Model m2;
    m2 = visitStm(liststm->stm_);
  	m->nstreams++;
  	m2->stream->next=m->stream;
  	m->stream=m2->stream;
  	
  	if( notListed(m2->stream->source, m)) {
  		m2->stream->source->next = m->proc;
  		m->proc = m2->stream->source;
  	} 
  	if( notListed(m2->stream->sink, m)) {
  		m->stream->sink->next = m->proc;
  		m->proc = m2->stream->sink;
  	} 
  	
    liststm = liststm->liststm_;
  }
  return m;
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

 
Stream visitS_tream(S_tream _p_)
{
	Process snk,src;

    snk=visitSnk(_p_->u.streamx_.snk_);
    bs=visitBuffsize(_p_->u.streamx_.buffsize_);
    if(bs<1) bs=1;   
    if(bs>MAX_BUFFER)    
    	bs=MAX_BUFFER;
    if( bs > maxbfsz) 
    		maxbfsz=bs;	
    src=visitSrce(_p_->u.streamx_.srce_);
    return MakeStream(src, snk, bs);
    
}


/* Add port,p to port list at P->port */
static void linkPort(Process P, Port p) {  
	Port p2;   
	
	if(P->port == NULL) {
   		P->port = p;
    	p->next = p;
    	p->prev = p;
		return;
	}
	  
	p2 = P->port;
	while(p2!=P->port) {
		if(p->id < p2->id) {         
			p->next = p2;
			p->prev = p2->prev;
			p->prev->next = p;
			p->next->prev = p;
			return;
		}
		p2 = p2->next;
	}
	
    p->next = P->port;      //    p=9  p2=1
    p->prev = P->port->prev;
    p->next->prev = p;
	p->prev->next = p;
}    

Process visitSrce(Srce _p_)
{
	Process p;
	Port pt;
    p  = visitProc(_p_->u.sourcex_.proc_);
    pt = visitPrt (_p_->u.sourcex_.prt_);  
    p->source_id = pt->id; 
    p->nportsOut++;
    linkPort(p,pt);
    return p;
}
    
Process visitSnk(Snk _p_)
{
	Process p;
	Port pt;
	
    pt=visitPrt (_p_->u.sinkx_.prt_);
    p =visitProc(_p_->u.sinkx_.proc_);
    p->sink_id = pt->id;
    p->nportsIn++;  
    linkPort(p,pt);
    return p;
}

Process visitProc(Proc _p_)
{
  switch(_p_->kind) {
  
  case is_Processx:  
    return MakeProcess(
    	visitIdent(_p_->u.processx_.ident_), 
    	visitComp(_p_->u.processx_.comp_),
    	visitListArgument(_p_->u.processx_.listargument_)
    );   
      
  case is_Processy:   
    return MakeProcess(
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
    /* Code For ListArgument Goes Here */
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

