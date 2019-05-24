/* SW.c

*/

#include <stdlib.h>
#include <stdio.h>
#include "sw.h"
#include "swsym.h"

static String default_path={"std"};   /* ?? arg later */
	
Model visitValidSW(ValidSW _p_) {   /* Parse visit root */
	
    return visitListStm(_p_->u.valid_.liststm_);
}

Model visitStm(Stm _p_) 
{	
	Model m;  // ?? m=MakeModel(visitStm(liststm->stm_));
	m=MakeModel(visitFlw(_p_->u.sflow_.flw_));
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
		fprintf(stderr,"SW/FAIL: no valid flows\n"); 
		exit(1);
	}

	Model m;
	m = visitStm(liststm->stm_);
	m->proc = m->flow->source;
  	m->proc->next = m->flow->sink;
  	m->flow->sink->next = NULL;
	liststm = liststm->liststm_;
	
  while(liststm != 0)
  {
  	Model m2;
    m2 = visitStm(liststm->stm_);
  	m->nflows++;
  	m2->flow->next=m->flow;
  	m->flow=m2->flow;
  	
  	if( notListed(m2->flow->source, m)) {
  		m2->flow->source->next = m->proc;
  		m->proc = m2->flow->source;
  	} 
  	if( notListed(m2->flow->sink, m)) {
  		m->flow->sink->next = m->proc;
  		m->proc = m2->flow->sink;
  	} 
  	
    liststm = liststm->liststm_;
  }
  return m;
}

Flow visitFlw(Flw _p_)
{
	Process snk,src;
    	
    snk=visitSnk(_p_->u.flowx_.snk_);
    src=visitSrce(_p_->u.flowx_.srce_);
	
    return MakeFlow(src, snk);
    
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

Port visitPrt(Prt _p_)  {
    return MakePort(visitInteger(_p_->u.portx_.integer_)); 
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
