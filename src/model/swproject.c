/** @file swproject.c
		  Generate a  script to create FBP project files from the network model.
**/
 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "swsym.h"
#include "model.h"
#include "sw.h"

#include <assert.h>

/** Print string */
#define P(s) printf("%s\n",(#s));
#define PE(s) {};			/**<Print empty string*/
#define C(s) printf("%s",(#s));		/**<Print String  */

/** Return prefix(aaa) of aaa.bbb  */
static char *getPrefix(char *s) {
	char *s0;
	char *s1;

	s0=malloc(sizeof(s)+1);
	s1=s0;
	
	while (*s != 0) {
 		if( *s == '.') {     
			*s1=0;
			return s0;
		} else {
		   *s1++ = *s++;
		}
	}
	
	return s;
}

/** Return component arguments. */
static char **getArgs( Model m, Component c) {
	Stream s;
	Process p;
	static char *noargs[1];

	noargs[0] = 0x0;

	s=m->stream;
	
	while ( s != NULL ) {
	    if( ( s->source != NULL) && ( s->sink != NULL) ) { 
		p=s->source;
		if ((p->comp == c) & (p->arg[1] !=NULL)) {
			return p->arg;	
		}
		p=s->sink;
		if ((p->comp == c) & (p->arg[1] != NULL)) {
			return p->arg;	
		}
	    }	
		s = s->next;
	}
	
	return noargs;
}

/** Find number of input and output ports for component **/
static Process getPorts(Model m, Component c,  int *inp, int *outp) {
	Stream s;
	Process p;
	
	s=m->stream;
	
	while ( s != NULL ) {
	    if(  (s->source !=NULL) && (s->sink !=NULL ) ) {
		p=s->source;
		if ( p->comp == c ) {
			*inp=p->nportsIn;
			*outp=p->nportsOut;
			return p;	
		}
		p=s->sink;
		if (p->comp == c) {
			*inp=p->nportsIn;
			*outp=p->nportsOut;
			return p;	
		}
	    }	
		s = s->next;
	}
	
	*inp=0;
	*outp=0;
	return NULL;
}

/** Return true if pkg is an existing SW package: 
	sw or swutility, or ? */
int isaSwPkg(char *pkg) {

	if(strncmp(pkg,"sw",6) == 0) return 1;	
	if(strncmp(pkg,"swutility",9) == 0) return 1;
	if(strncmp(pkg,"sw_",3) == 0) return 1;
	return 0;   
}

#if 0
static Process findProcForComp(Model m,Component c) {
	Stream s;
	
	s=m->stream; 
	while(s) {
		if(c == s->source->comp) 
			return s->source; 
		if(c == s->sink->comp) 
			return s->sink; 
		s=s->next;
	}
	FAIL(findProcForComp, "Cannot find process");
}
#endif

static char setIO(Component c, Port pt, Process p) {
    Process src;

    src=pt->stream->source;  // component can be both source and sink 
    if(src==p) {             //   so check if this process 
	    if(src->comp == c)   //   is souce or not.
		    return 'o';
	}
		    
	return 'i';	
}

static void printTypes(Process p, Component c) {
	Port pt;
	char io;
	
	c=p->comp;
	pt=p->port;
	do {
	  char *typ="_";
		io=setIO(c,pt,p);
		if( pt->stream->iptype != NULL && pt->stream->iptype[0] != 0)
			typ=pt->stream->iptype;
		printf(" -%c %s", io, typ);
		pt=pt->next;
	} while(pt!=p->port); 
}

/** Generate a project from the network model. */
void genProject(Model m) {
	Component c;
	Process p;
	int inp=0;	// Number of input ports 	
	int outp=0;	// Number of output ports
	char *module; 	// Go Module (and executable name)  
	char **args;  // Process arguments
	int i=0;
	
	c=m->comp;
	module=getPrefix(m->name);   // Strip off suffix: .sw
	
	while(c!=NULL) {
		p=getPorts(m, c, &inp,&outp); 
		args=getArgs(m, c);  
		if((c->path[0] != '{') & (c->path[0] != '/')) {
			if(!isaSwPkg(c->path))  {			 
				printf("swgen.sh gs %s %s %s %s",
					module ,c->path, getConfType(c->path), c->name);
				printTypes(p,c);
				i=0;	
				while( args[i] !=NULL  ) 	
				 	printf(" %s", args[i++]);		  
				printf("\n" );
		  	}	
		}	
		c=c->next;
	}
}


/***************   End of SWPROJECT.C   ********************/
