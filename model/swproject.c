/** @file SWPROJECT.C 
		  Generate a  script to create FBP project files from the network model.

 
 	@@todo Generate project examples
	@todo Process command arguments. 
	@todo Restore poc test
	@todo Document more functions 
	@todo Allow git.hub, etc. imports.  Simplify .sw file requirements.
	@todo negative nimports and noutports in swgen.sh to prioritize ports and reduce n goroutines.
	@todo Generate man doc(s) from Doxygen
	@todo Fix generated graph HTMLs
	@todo Fix swgen arguments w/default generation. Generate in config file
	
 DONE: 
	@done Structure in module/modele package.  Pass struct instead of integers.
	@done Avoid duplicates in YAML config file.
	@done If component involved in a cycle, then subtask all sends and receives
	@done Subtask channel send/receive when more than two ports,  for deadlock prevention.
	@done Fix swgo [poc]
	
 SHELVED:
	@shelved  Wait on multiple inputs for example and deadlock prevention in ...test_.go files. -> or <- to diffferentiate.
	@shelved Generate Init function w/commentary
	@shelved Update .yaml file instead of replacing it.  Do not erase prev config.
	@shelved Avoid using .sw file name as module:  use it for program name only. 
	@shelved Blue/Gold code generation for deadlock prevention	
	@shelved output Buffer > 0  filtercode generation for deadlock prevention
 	
 Method:  Build a script from the .SW file model.
 	  Run the script to generate the code at $GOPATH/src/MODULE; 
 	    where MODULE.sw was the .SW file used to build the model.   
 	           
 
*/

/* @@todo Build a web site from github 
	
	OBJECTIVE: Build working web site in Docker
		
	. Prototype web site 
		. Generate   test.twyoung.com.sw

	. Enhance modular access 
		. Upper/lower case component name for remote/local search.
		. Generate   standard web 
		. Move defaults(Gen1,etc.)   

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "swsym.h"
#include "model.h"
#include "sw.h"

#include <assert.h>

#define P(s) printf("%s\n",(#s));
#define PE(s) {};
#define C(s) printf("%s",(#s));

static char *Prefix(char *s) {
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

static char **getArgs( Model m, Component c) {
	Stream s;
	Process p;
	static char *noargs[1];

	noargs[0] = 0x0;

	s=m->stream;
	
	while ( s != NULL ) {
		p=s->source;
		if ((p->comp == c) & (p->arg[1] !=NULL)) {
			return p->arg;	
		}
		p=s->sink;
		if ((p->comp == c) & (p->arg[1] != NULL)) {
			return p->arg;	
		}
		s = s->next;
	}
	
	return noargs;
}

/** Find number of input and output ports for component **/
static void getPorts(Model m, Component c,  int *inp, int *outp) {
	Stream s;
	Process p;
	
	s=m->stream;
	
	while ( s != NULL ) {
		p=s->source;
		if (p->comp == c) {
			*inp=p->nportsIn;
			*outp=p->nportsOut;
			return;	
		}
		p=s->sink;
		if (p->comp == c) {
			*inp=p->nportsIn;
			*outp=p->nportsOut;
			return;	
		}
		s = s->next;
	}
	
	*inp=0;
	*outp=0;
}


void genProject(Model m) {
	Component c;
	int inp=0;	// Number of input ports 	
	int outp=0;	// Number of output ports
	char *module; 	// Go Module (and executable name)  
	char amp=' ';   // Ampersand (or not);
	char **args;  // Process arguments
	
	c=m->comp;
	module=Prefix(m->name);   // Strip off suffix: .sw
	
	while(c!=NULL) {
		getPorts(m, c, &inp,&outp); 
		args=getArgs(m, c);  
		printf("swgen.sh gs %s %s %s %d %d %s",
			module ,c->path, getConfType(c->path), inp, outp, c->name);
		
		int i=0;
		while( args[i] !=NULL  ) 	
			 printf(" %s", args[i++]);
			  
		printf("%c\n", amp );
		amp='&'; 
		c=c->next;
	}
}


/***************   End of SWPROJECT.C   ********************/
