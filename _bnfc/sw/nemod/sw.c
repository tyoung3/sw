/* SW.c

*/

#include <stdlib.h>
#include <stdio.h>
#include "sw.h"
	
Model visitValidSW(ValidSW _p_) {   /* Parse visit root */
	
    return visitListStm(_p_->u.valid_.liststm_);
}

Model visitStm(Stm _p_) 
{	
					//m=MakeModel(visitStm(liststm->stm_));
	return MakeModel(visitFlw(_p_->u.sflow_.flw_));
}

Model visitListStm(ListStm liststm)
{
	Model m;
	m = visitStm(liststm->stm_);
	liststm = liststm->liststm_;
	
  while(liststm != 0)
  {
  	Model m2;
    m2 = visitStm(liststm->stm_);
  	m->nflows++;
  	m2->flow->next=m->flow;
  	m->flow=m2->flow;
    liststm = liststm->liststm_;
  }
  return m;
}

Flow visitFlw(Flw _p_)
{
    return MakeFlow(
    	visitSnk(_p_->u.flowx_.snk_),
    	visitSrce(_p_->u.flowx_.srce_)  
    	); 
}

Process visitSrce(Srce _p_)
{
	Process p;
	Port pt;
    p = visitProc(_p_->u.sourcex_.proc_);
    pt = visitPrt(_p_->u.sourcex_.prt_);
    p->port = pt; /* ? Multiple ports FIX later*/ 
    return p;
}

Process visitSnk(Snk _p_)
{
	Process p;
	Port pt;
    pt=visitPrt(_p_->u.sinkx_.prt_);
    p=visitProc(_p_->u.sinkx_.proc_);
    p->port = pt;/* ? Multiple ports FIX later*/ 
    return p;
}

Process visitProc(Proc _p_)
{
  switch(_p_->kind)
  {
  case is_Processx:
    return MakeProcess(
    	visitIdent(_p_->u.processx_.ident_), 
    	visitComp(_p_->u.processx_.comp_)
    );
    /*
    visitIdent(_p_->u.processx_.ident_);
    visitComp(_p_->u.processx_.comp_);
    visitListArgument(_p_->u.processx_.listargument_);
    */
    break;  
  case is_Processy:   
    return MakeProcess(
    	visitIdent(_p_->u.processy_.ident_), NULL
    	// visitListArgument(_p_->u.processy_.listargument_)
    	// visitListArgument(_p_->u.processy_.listargument_)
    );
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
     return MakeComponent(visitIdent(_p_->u.compx_.ident_), NULL);
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

