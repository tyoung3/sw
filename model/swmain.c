/* SWMAIN.C 

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sw.h"
#include "swgo.h"
#include "swsym.h"
#include "swgraph.h"  

char *version={VERSION};  

ValidSW pValidSW(FILE *inp);

typedef enum{ GOMODE=0, ASTMODE, GENTREE, GRAPHMODE, JAVAFBP, CMODE=7 }   MODE;

static int badProc(Process p) {
			int i;
			Port port;
			
			if(!p->comp) {
				fprintf(stderr,
				  "SW/badProc/FAIL: missing component for process: (%s)\n", 
						p->name
				);
				return 1;
			}
			
			port = p->port; 
			i=0;
			if(port->id < 0) { 
				port->id = 0;   // Expand missing port number 
				port=port->next;
				i=1;
			}	
			for(;i < (p->nportsIn + p->nportsOut); i++) {
				if( port->id != i ) {
					fprintf(stderr,
						"SWMAIN/badProc/FAIL: (%s) port[%i] is %i, should be = %i\n", 
						p->name, 
						i, 
						port->id,
						i); 
					fprintf(stderr,"\t port numbers for (%s)  need to be 0,1,2,... \n",p->name);	
					return 1;
				}
				port = port->next;
			}
			
			
			return 0;
}


static Port findPrt(Process p, int id) {
	Port pt;	

	pt = p->port;
	do {
		if( pt->id == id )
			return pt;
		pt=pt->next;
	} while(pt != p->port); 
				
	return p->port;
}

static int eqs(char *s1, char *s2) {

	if(strncmp(s1,s2,40) == 0) 
		return 1;

	return 0;	
}

static int nameFail(char *psnkname, char *nsnk, char *nsrc, char *psrcname) {    	    	
				
				fprintf(stderr,"SWMAIN/NameMisMatch/FAIL: (%s)%s <- %s(%s) \n",
						psnkname,
						nsnk,
						nsrc,
						psrcname
				);
    			exit(1);
}    			

static int NameMisMatch(Process src, int source_id, Process snk, int sink_id) {
	Port psrc, psnk;
	char *nsrc, *nsnk;
	
	psrc = findPrt(src,source_id);	
	nsrc=psrc->name;
		 
	psnk = findPrt(snk,sink_id);	
	nsnk=psnk->name;
	
    if( eqs(nsnk,"IN") 		&&  eqs(nsrc,"OUT")  )  {
    	return 0; 
	}
    	
    if( eqs(nsnk,"in") 		&&  eqs(nsrc,"out")  ) 	{
    	return 0; 
	}

    if( eqs(nsnk,"SOCKET") 	&&  eqs(nsrc,"PLUG")  ) {
    	return 0; 
	}

    if( eqs(nsnk,"SLOT")	 &&  eqs(nsrc,"TAB")  ) {
    	return 0; 
	}
    	
    	if( eqs(nsrc,"IN") || 
    	    eqs(nsrc,"in")  ||
    	    eqs(nsrc,"PLUG")||
    	    eqs(nsrc,"SLOT")
    	    )  return nameFail(snk->name,nsnk,nsrc,src->name);
    				
    	if( eqs(nsnk,"OUT")   || 
    	    eqs(nsnk,"out")   ||
    	    eqs(nsnk,"SOCKET")||
    	    eqs(nsnk,"TAB")  	   
    	    )  return nameFail(snk->name,nsnk,nsrc,src->name);
	
	if(strcmp(nsnk,nsrc) == 0 ) 	
		return 0;

	if(eqs(nsrc,"")) 
			return 0;
	if(eqs(nsnk,"")) {
			return 0;
	}
	
    return nameFail(snk->name,nsnk,nsrc,src->name);
    	    
}

static int verifyOK(Model model) { 						/*expand and check model*/
	Stream f;
	
	if(!model) {
		fprintf(stderr,"SWMAIN/verifyOK/FAIL: network model is missing!");
		return(0);
	}	

#ifdef VERIFY_VERBOSE	
	fprintf(stderr,
		"SWMAIN/VerifyOK/model: %d/%d/%d Stream/procs/components.\n", 
			model->nstreams, 
			model->nprocs, 
			model->ncomponents
	);
#endif	
	
	f=model->stream;
	while(f) {
		if( badProc(f->sink) || badProc(f->source) ) {
			fprintf(stderr,"SW/verify: failed.");
			exit(1);
		}	
		if(NameMisMatch(f->source,f->source_id,f->sink,f->sink_id))	
				return 1;
		f=f->next;
	}
	return 1;			
	
};  		


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
      fprintf(stderr, "SW/openFile/FAIL Error opening input file: %s.\n", fname);
      exit(1);
    } 
    return input;
}

	/* Point to character past the last '/' */
char *baseOf(char *s) {
		char *sr=s;
		
		while(*s != 0) {
			if(*s == '/') {
				sr = s+1;
			}
			s++;
		}
		return sr;
}

int main(int argc, char ** argv)
{
  ValidSW parse_tree;
  Model model;    /* Network Model */
  MODE mode=GOMODE;
  char *fname={"stdin"};
  
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
  			fname=argv[3];
  		} 
  	}	else {
  			if( strncmp(argv[1],"-v",4) == 0) {
  				printf("StreamWork/sw-%s\n", version);
  				exit(0);
  			} else {
  				input=openFile(argv[1]);
  			}	
  	}			
  }
  	
  parse_tree = pValidSW(input);
  
  if (parse_tree)   {  
    model=visitValidSW(parse_tree);
    model->name = baseOf(fname) ;
    if(verifyOK(model)) {
		if(!model->proc) {
			fprintf(stderr,"SWMAIN/FAIL: No processes found\n");
			exit(1);
		}
    	switch (mode) {
	    	case GRAPHMODE:       
    			genGraph(model);  	// Generate GraphViz .DOT file
    			break;
    		case JAVAFBP:
    			genJavaFBP(model); 	// Generate JavaFBP 
    			break;
	    	case ASTMODE:       // Abstract Syntax 			
    			printf("%s\n\n", showValidSW(parse_tree));  //Print abstract syntax tree
    			break;
    		case GENTREE:
    			printf("[Linearized Tree]\n");
   				printf("%s\n\n", printValidSW(parse_tree)); //Print expanded network definition 
    			break;	
    		case GOMODE: 
	    	    genGo(model);	// Generate Go MAIN.GO
    			break;	
    		case CMODE: 
	    	    genC(model);    // Generate C source
    			break;	
    		default:
    			Usage();
	    	    break;	
	    } 	    	
    } else {
    	fprintf(stderr,"SW/VerfyOK/FAIL:  failed.\n");
    	exit(1);
    }	
    return 0;
  }
  return 1;
}
