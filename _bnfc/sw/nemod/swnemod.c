
#include <stdio.h>
#include <stdlib.h>

#include "Parser.h"
#include "Printer.h"
#include "Absyn.h"
#include "sw.h"
#include "swgo.h"

ValidSW pValidSW(FILE *inp);


Model genGraph(Model nemod) { return nemod;};       /*Create Graphviz file */


int verifyOK(Model nemod) { 						/*expand and check nemod*/
	Flow f;
	
	if(!nemod) {
		fprintf(stderr,"SW/verify: Model nemod not built!");
		return(0);
	}	

#ifdef VERIFY_VERBOSE	
	fprintf(stderr,
		"SW/verify/nemod: %d/%d/%d flows/procs/components.\n", 
			nemod->nflows, 
			nemod->nprocs, 
			nemod->ncomponents
	);
#endif	
	
	f=nemod->flow;
	while(f) {
			if(!f->sink->comp) {
				fprintf(stderr,"SW/verify: missing (%s) sink component.\n", 
					f->sink->name
				);
				return 0;
			}
#if 0		
			printf("/* (%s %s.%s)%d<-%d(%s %s) */\n", 
				f->sink->name,
				f->sink->comp->path,
				f->sink->comp->name,
				f->sink->port->id, 
				f->source->port->id, 
				f->source->name,
				f->source->comp->name
			);
#endif				
		f=f->next;
	}
	return 1;
	
};  		

Port MakePort(int n) {
	Port p; 
	
	p=(Port)malloc(sizeof(Port_)); 
    if (!p)
    {
        fprintf(stderr, "Error: out of memory when allocating Port!\n");
        exit(1);
    }
    
	p->id = n;
	p->match = NULL;
	p->next = NULL;
	p->prev = NULL;
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
    
Flow MakeFlow(Process src, Process snk) {
	Flow f;
	
	f=(Flow)malloc(sizeof(Flow_)); 
    if (!f)
    {
        fprintf(stderr, "Error: out of memory when allocating Flow!\n");
        exit(1);
    }
    
	f->source = src;
	f->sink = snk;
	f->next = NULL;
	f->prev = NULL;
	return f;
} 


Process MakeProcess(Ident name, Component comp) {
	Process p;
	
	p=(Process)malloc(sizeof(Process_)); 
    if (!p)
    {
        fprintf(stderr, "Error: out of memory when allocating Process!\n");
        exit(1);
    }
    
	p->comp = comp;
	p->name = name;
	p->port	= NULL;
	p->next = NULL;
	p->prev = NULL;
	return p;
	
} 

Model MakeModel(Flow f) {
	Model m;
	
	m=(Model)malloc(sizeof(Model_)); 
    if (!m)
    {
        fprintf(stderr, "Error: out of memory when allocating Process!\n");
        exit(1);
    }
    
	m->nflows = 1;
	m->ncomponents = 0;
	m->nprocs	= 0;
	m->flow=f;
	//p->next = NULL;
	//p->prev = NULL;
	return m;
	
} 
	
int main(int argc, char ** argv)
{
  FILE *input;
  Model nemod;    /* Network Model */
  
  ValidSW parse_tree;
  if (argc > 1)   {
    input = fopen(argv[1], "r");
    if (!input)   {
      fprintf(stderr, "Error opening input file.\n");
      exit(1);
    } 
  }
  else input = stdin;
  /* The default entry point is used. For other options see Parser.h */
  parse_tree = pValidSW(input);
  if (parse_tree)   {
    // printf("\nParse Succesful!\n");
    // printf("\n[Abstract Syntax]\n");
    // printf("%s\n\n", showValidSW(parse_tree));
    // printf("[Linearized Tree]\n");
    // printf("%s\n\n", printValidSW(parse_tree));
    
    nemod=visitValidSW(parse_tree);
    // fprintf(stderr,"Nice visit!\n");
    if(verifyOK(nemod)) {  
	    genGo(nemod); 
    	genGraph(nemod);
    } else {
    	fprintf(stderr,"SW/FAIL: Verify failed!");
    	exit(1);
    }	
    return 0;
  }
  return 1;
}
