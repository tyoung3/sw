/* SWMAIN.C 

*/
#include <stdio.h>
#include <stdlib.h>

#include "Parser.h"
#include "Printer.h"
#include "Absyn.h"
#include "sw.h"
#include "swgo.h"
#include "swsym.h"
#include "swgraph.h"

ValidSW pValidSW(FILE *inp);

	
static int badProc(Process p) {
			int i;
			Port port;
			
			if(!p->comp) {
				fprintf(stderr,
				  "SW/verify: missing component for process: (%s)\n", 
						p->name
				);
				return 1;
			}
			
			
			port = p->port; 
			for(i=0;i < (p->nportsIn + p->nportsOut); i++) {
				if( port->id != i ) {
					fprintf(stderr,
						"SW/verify: (%s) %ith port is %i, not = %i\n", 
						p->name, 
						i, 
						port->id,
						i); 
					return 1;
				}
				port = port->next;
			}
			
			
			return 0;
}

static int verifyOK(Model nemod) { 						/*expand and check nemod*/
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
		if( badProc(f->sink) || badProc(f->source) ) {
			fprintf(stderr,"SW/verify: failed.");
			exit(1);
		}	
		f=f->next;
	}
	return 1;
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
    
Flow MakeFlow(Process src, Process snk) {
	Flow f;
	
	f=(Flow)malloc(sizeof(Flow_)); 
    if (!f)
    {
        fprintf(stderr, "Error: out of memory when allocating Flow!\n");
        exit(1);
    }
    
	f->source    = src;
	f->sink      = snk;
	f->source_id = src->source_id; 
	f->sink_id   = snk->sink_id;
	f->next      = NULL;
	f->prev      = NULL;
	f->type		 = GOGO;  /* Defined w/ '<-'  */
	return f;
} 


Process MakeProcess(Ident name, Component comp) {
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
    	    fprintf(stderr, "Error: out of memory when allocating Process!\n");
    	    exit(1);
    	}
    	
		p->comp = comp;
		p->name = name;
		p->nportsIn =0;
		p->nportsOut=0;
		p->port	= NULL;
		p->next = NULL;
		p->prev = NULL;
    	addProc(name,p);
    }	
    
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
	m->proc = NULL;
	//p->next = NULL;
	//p->prev = NULL;
	return m;
	
} 

typedef enum{ GOMODE, GRAPHMODE, CMODE, ASTMODE}   MODE;
 	
int main(int argc, char ** argv)
{
  FILE *input;
  Model nemod;    /* Network Model */
  MODE mode=GOMODE;
  
  if(argc>2) {
  		mode=atoi(argv[2]);
  }
  
  ValidSW parse_tree;
  if (argc > 1)   {
    input = fopen(argv[1], "r");
    if (!input)   {
      fprintf(stderr, "Error opening input file.\n");
      exit(1);
    } 
  }
  else input = stdin;
  
  parse_tree = pValidSW(input);
  if (parse_tree)   {
    // printf("\nParse Succesful!\n");
    // printf("\n[Abstract Syntax]\n");
    // printf("[Linearized Tree]\n");
    // printf("%s\n\n", printValidSW(parse_tree));
    
    nemod=visitValidSW(parse_tree);
    if(verifyOK(nemod)) {
    	switch (mode) {
	    	case GRAPHMODE:      
    			genGraph(nemod);
    			break;
	    	case ASTMODE:       // Abstract Syntax 			
    			printf("%s\n\n", showValidSW(parse_tree));
    			break;
    		case GOMODE: 
    		default:
	    	    genGo(nemod);
	    	    break;	
	    } 	    	
    } else {
    	fprintf(stderr,"SW/FAIL: Verify failed.\n");
    	exit(1);
    }	
    return 0;
  }
  return 1;
}
