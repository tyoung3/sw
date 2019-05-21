/* SW.c

*/

#include <stdlib.h>
#include <stdio.h>
#include "sw.h"
#include "swsym.h"

static String default_path={"strings"};   /* ?? arg later */
	
Model visitValidSW(ValidSW _p_) {   /* Parse visit root */
	
    return visitListStm(_p_->u.valid_.liststm_);
}

Model visitStm(Stm _p_) 
{	
	Model m;
					//m=MakeModel(visitStm(liststm->stm_));
	
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
	
    return MakeFlow(snk, src);
    
}

Process visitSrce(Srce _p_)
{
	Process p;
	Port pt;
    p = visitProc(_p_->u.sourcex_.proc_);
    pt = visitPrt(_p_->u.sourcex_.prt_);
    pt->next = p->port;
    p->port  = pt; 
    p->nportsOut++;
    return p;
}

Process visitSnk(Snk _p_)
{
	Process p;
	Port pt;
    pt=visitPrt(_p_->u.sinkx_.prt_);
    p=visitProc(_p_->u.sinkx_.proc_);
    pt->next = p->port;
    p->port = pt; 
    p->nportsIn++;  
    return p;
}

Process visitProc(Proc _p_)
{
  switch(_p_->kind) {
  
  case is_Processx:  
    visitListArgument(_p_->u.processx_.listargument_);
    return MakeProcess(
    	visitIdent(_p_->u.processx_.ident_), 
    	visitComp(_p_->u.processx_.comp_)
    );   
    break;
      
  case is_Processy:   
    visitListArgument(_p_->u.processy_.listargument_);
    return MakeProcess(
    	visitIdent(_p_->u.processy_.ident_), NULL);
    	
     
    break;
  default:
    fprintf(stderr, "Error: bad kind field when printing Proc!\n");
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

  return listargument;
  
  while(listargument != 0)
  {
    visitArgument(listargument->argument_);
    listargument = listargument->listargument_;
  }
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

