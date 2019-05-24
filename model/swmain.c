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
#include <string.h>

char *version={VERSION};


ValidSW pValidSW(FILE *inp);

typedef enum{ GOMODE=0, ASTMODE, GENTREE, GRAPHMODE, JAVAFBP, CMODE=7 }   MODE;

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

static int verifyOK(Model model) { 						/*expand and check model*/
	Flow f;
	
	if(!model) {
		fprintf(stderr,"SW/verify: model not built!");
		return(0);
	}	

#ifdef VERIFY_VERBOSE	
	fprintf(stderr,
		"SW/verify/model: %d/%d/%d flows/procs/components.\n", 
			model->nflows, 
			model->nprocs, 
			model->ncomponents
	);
#endif	
	
	f=model->flow;
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
		arg[i--] = la->argument_->u.argumentx_.string_;
		la       = la->listargument_;
	}
	
	return arg;
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

Process MakeProcess(Ident name, Component comp, ListArgument la) {
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


static void Usage() {
    fprintf(stderr,"Usage:\tsw [-m MODE [ SW_FILE ]\n");
    fprintf(stderr,"\tsw -v\n");
    fprintf(stderr,"\t\tMODE={0-GOMODE|1-ASTMODE|2-GENTREE|3-GRAPHMODE|4-JAVAFBP|7-CMODE,}\n");
    fprintf(stderr,"\t\t[with no arguments, sw will read from stdin. \n");
}
 	
  
FILE *input;
static FILE *openFile(char *fname) {
    input = fopen(fname, "r");
    if (!input)   {
      fprintf(stderr, "Error opening input file: %s.\n", fname);
      exit(1);
    } 
    return input;
}

int main(int argc, char ** argv)
{
  ValidSW parse_tree;
  Model model;    /* Network Model */
  MODE mode=GOMODE;
  
  input = stdin;
  
  if (argc > 1)  {
  	if(argc>2) {
  		if(strncmp(argv[1],"-m",30) == 0) {  
  			mode=atoi(argv[2]);
  		} else {
  			Usage(); 
  			exit(1);
  		}	
  		if(argc>4) {
  			Usage();
  			exit(1);
  		} 
  		if(argc>3) {
  			input=openFile(argv[3]);
  		} 
  	}	else {
  			if( strncmp(argv[1],"-v",4) == 0) {
  				printf("Streamwork/sw-%s\n", version);
  				exit(0);
  			} else {
  				input=openFile(argv[1]);
  			}	
  	}			
  }
  	
  parse_tree = pValidSW(input);
  
  if (parse_tree)   {  
    model=visitValidSW(parse_tree);
    // @TODO Free Parse tree storage
    if(verifyOK(model)) {
    	switch (mode) {
	    	case GRAPHMODE:      
    			genGraph(model);
    			break;
    		case JAVAFBP:
    			genJavaFBP(model);
    			break;
	    	case ASTMODE:       // Abstract Syntax 			
    			printf("%s\n\n", showValidSW(parse_tree));
    			break;
    		case GENTREE:
    			printf("[Linearized Tree]\n");
   				printf("%s\n\n", printValidSW(parse_tree));
    			break;	
    		case GOMODE: 
	    	    genGo(model);
    			break;	
    		case CMODE: 
	    	    genC(model);
    			break;	
    		default:
    			Usage();
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
