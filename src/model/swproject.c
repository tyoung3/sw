/** @file swproject.c
		  Generate a  script to create FBP project files from the network model.
**/
 
/** 
	@todo Show full path for .sw and cfg files in generated commentary. 
	@todo Fix swproject.sh/postage type error.
	@todo Use PACKAGE_NAME { key: value} format for generated .yaml files.
	@todo Convert JPM's javaFBP NDs to SW NDs. https://jpaulm.github.io/fbp/jsyntax.htm
	@todo Document environment variable usage.  DEBUG/USER/HOME
	@todo If .github, do not generate project
    @todo Remove obsolete github branches
    @todo Update fbp.twyoung.com web pages
	@todo Synopsis to README
	@todo Create Man pages w/Doxygen
	@todo Add tests for all useful sw modes.
	@todo Verify output from make check & make distcheck
	@todo Security check:
		Protection from buffer overflow (and other malicious input).
		Limited data lifetime (clearing buffers and heap data)
		Protection from ownership conflicts. 
	@todo Plugins:
		https://pkg.go.dev/plugin
	@todo Design Project logo and publish. 
 	@todo Create internal/html with module, package, function, and struct pages. Fix swgraph to find the pages.
	@todo Process command/config arguments. 
	@todo negative nimports and noutports in swgen.sh to prioritize ports and reduce the number of goroutines.
	@todo Fix swgen arguments w/default generation. Generate in config file
	@todo Send multiple(N option) IPs in go tests.
	@todo Make config an option in project generation.poc
 	@todo Generate project examples.
 	@todo Graph .ISW files (prevent 'no processes' message.
 	@todo Implement Process name expansion. Ex. "_MONITOR;" launches system monitor
	
 DONE: 
	@done Make JPM's FBPgo (fbpGO?) Check feasability. 
	@done Discuss differences from 'classic' FBP.
		FBP inspired: 	http://www.jpaulmorrison.com/fbp/noflo.html
		Lifetime: 	https://suif.stanford.edu/collective/taint.html
			Q. Does Go clear buffers at close?
		Ownership: 	https://www.egnyte.com/resource-center/governance-guides/data-ownership
    @done Installation w/Autotools
	@done Add PREFIX statement to prefix process names with a string. 
	@done Make generated test_.go's  deadlock safe. Test w/collate.sw
	@done Improve module location.  Standardize on .../sw/MODULE/pkg/.... | Is .../sw
	@done  Restore poc test
	@done  Type names inside arrows(stream direction indicators). 
	@done  Document more functions 
	@done  Allow git.hub, etc. imports.  Simplify .sw file requirements.
	@done Structure in module/modele package.  Pass struct instead of integers.
	@done Avoid duplicates in YAML config file.
	@done If component involved in a cycle, then subtask all sends and receives
	@done Subtask channel send/receive when more than two ports,  for deadlock prevention.
	@done Fix swgo [poc]
	
 SHELVED:
	@shelved Wait on multiple inputs for example and deadlock prevention in ...test_.go files. -> or <- to diffferentiate.
	@shelved Generate Init function w/commentary
	@shelved Update .yaml file instead of replacing it.  Do not erase prev config.
	@shelved Blue/Gold code generation for deadlock prevention	
	@shelved output Buffer > 0  filtercode generation for deadlock prevention
 
*/

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
static void getPorts(Model m, Component c,  int *inp, int *outp) {
	Stream s;
	Process p;
	
	s=m->stream;
	
	while ( s != NULL ) {
	    if(  (s->source !=NULL) && (s->sink !=NULL ) ) {
		p=s->source;
		if ( p->comp == c ) {
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
	    }	
		s = s->next;
	}
	
	*inp=0;
	*outp=0;
}

/** Return true if pkg is an existing SW package: 
	sw or swutility, or ? */
int isaSwPkg(char *pkg) {

	if(strncmp(pkg,"sw",6) == 0) return 1;	
	if(strncmp(pkg,"swutility",9) == 0) return 1;
	if(strncmp(pkg,"sw_",3) == 0) return 1;
	return 0;   
}

/** Generate a project from the network model. */
void genProject(Model m) {
	Component c;
	int inp=0;	// Number of input ports 	
	int outp=0;	// Number of output ports
	char *module; 	// Go Module (and executable name)  
	char amp=' ';   // Ampersand (or not);
	char **args;  // Process arguments
	
	c=m->comp;
	module=getPrefix(m->name);   // Strip off suffix: .sw
	
	while(c!=NULL) {
		getPorts(m, c, &inp,&outp); 
		args=getArgs(m, c);  
		if((c->path[0] != '{') & (c->path[0] != '/')) {
			if(!isaSwPkg(c->path))  {			 
				printf("swgen.sh gs %s %s %s %d %d %s",
					module ,c->path, getConfType(c->path), inp, outp, c->name);
					int i=0;
				while( args[i] !=NULL  ) 	
				 	printf(" %s", args[i++]);		  
				printf("%c\n", amp );
				amp='&'; 
		  	}	
		}	
		c=c->next;
	}
}


/***************   End of SWPROJECT.C   ********************/
