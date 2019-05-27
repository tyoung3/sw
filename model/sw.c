/* SW.c

*/

#include <stdlib.h>
#include <stdio.h>
#include "sw.h"
#include "swsym.h"

#define NOBUFFERS

static String default_path={"std"};   /* ?? arg later */
	
Model visitValidSW(ValidSW _p_) {   /* Parse visit root */
	
    return visitListStm(_p_->u.valid_.liststm_);
}

Model visitStm(Stm _p_) 
{	
	Model m;  // ?? m=MakeModel(visitStm(liststm->stm_));
	m=MakeModel(visitS_tream(_p_->u.stmx_.s_tream_));
	return m;
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
		fprintf(stderr,"SW/FAIL: no valid streams\n"); 
		exit(1);
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

int visitBuffsize(Buffsize _p_)
{
  switch(_p_->kind)
  {
  case is_Bufszi:
    /* Code for Bufszi Goes Here */
    return visitInteger(_p_->u.bufszi_.integer_);
    break;  case is_Bufsze:
    	return 1;
    /* Code for Bufsze Goes Here */
    break;
  default:
    fprintf(stderr, "Error: bad kind field when printing Buffsize!\n");
    exit(1);
  }
}

int bs,maxbfsz=1;		/*  Buffer size */

Stream visitS_tream(S_tream _p_)
{
	Process snk,src;

#if 0   	
    snk=visitSnk(_p_->u.streamx_.snk_);
    visitBuffsize(_p_->u.streamx_.buffsize_);
    src=visitSrce(_p_->u.streamx_.srce_);
#else
    snk=visitSnk(_p_->u.streamx_.snk_);
    bs=visitBuffsize(_p_->u.streamx_.buffsize_);
    if(bs<1) bs=1;   
    if(bs>1000)   // TODO Config file for max sizes
    	bs=1000;
    if( bs > maxbfsz) 
    		maxbfsz=bs;	
    src=visitSrce(_p_->u.streamx_.srce_);
#endif	
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
    fprintf(stderr, "Error: bad kind field when visiting Proc!\n");
    exit(1);
  }
}

Port visitPrt(Prt _p_)   
{
  switch(_p_->kind)
  {
  case is_Portx:
    	return MakePort(visitInteger(_p_->u.portx_.integer_),NULL); 
    break;  case is_Portni:
    	 return MakePort(visitInteger(_p_->u.portni_.integer_),
         			     visitIdent(_p_->u.portni_.ident_) 
    	 );
    break;  case is_Portin:
         return MakePort(visitInteger(_p_->u.portin_.integer_),
         				 visitIdent(_p_->u.portin_.ident_)
         );
    break;  case is_Portn:
    	return MakePort(-1,visitIdent(_p_->u.portn_.ident_)
    	);
    break;  case is_Porte:
    	return MakePort(-1,NULL);
    break;
  default:
    fprintf(stderr, "Error: bad kind field when printing Prt!\n");
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
	return make_Argumentx(visitString(_p_->u.argumentx_.string_));
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

