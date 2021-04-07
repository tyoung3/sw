/** @file SWPROJECT.C 
		  Generate a  script to create FBP project files from the network model.

 @@TODO:  Fix http link in swgraph 
 
 todo Generate project examples
	
	
	@todo Structure in module/modele package.  Pass struct instead of integers.
	@todo Restore poc test
	@todo Document more functions 
	@todo Allow git.hub, etc. imports.  Simplify .sw file requirements.
	@todo  Wait on multiple inputs for example and deadlock prevention in ...test_.go files. -> or <- to diffferentiate.
		@toto negative nimports and noutports in swgen.sh to prioritize ports and reduce n goroutines.
	@todo Generate man doc(s) from Doxygen
	@todo Fix generated graph HTMLs
	@todo Generate Init function w/commentary
	@todo Fix swgen arguments w/default generation. Generate in config file
	@todo Process command arguments.
	@todo Update .yaml file instead of replacing it.  Do not erase prev config. 
	
 DONE: 
	@done Avoid duplicates in YAML config file.
	@done If component involved in a cycle, then subtask all sends and receives
	@done Subtask channel send/receive when more than two ports,  for deadlock prevention.
	@done Fix swgo [poc]
	
 SHELVED:
	@shelved Avoid using .sw file name as module:  use it for program name only. 
	@shelved Blue/Gold code generation for deadlock prevention	
	@shelved output Buffer > 0  filtercode generation for deadlock prevention
 	
 Method:  Build project model in memory 
          Traverse model to generate project file
          Generate code tree from project file and go templates
          
Approach: Prototype code tree generation          
 
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


#if 0
static String Timestamp()
{
    time_t ltime;		/* calendar time */
    ltime = time(NULL);		/* get current cal time */
    return (asctime(localtime(&ltime)));
}

static String Plural(int n) {
	if(n==1) 
		return "";
	return "s";
}

static Port findPort(Process p, int id)
{
    Port pt = p->port;
    Port pt0 = pt;


    do {
	if (pt->id == id) {
	    return pt;
	}
	pt = pt->next;
    } while (pt != pt0);

    sprintf(fbfr, "Process %s Port %i mismatch\n", p->name, id);
    FAIL(findPort, fbfr);
}

static void showArgs(Process p)
{ 
    int i = 1;

    if (!p->arg)
	return;

    while (p->arg[i] != NULL) {
	printf(" \"%s\"", p->arg[i]);
	i++;
    }
}

static void showSink(Process p, int id)
{

    printf("(%s %s.%s ", p->name, p->comp->path, p->comp->name);

    showArgs(p);


    printf(")");
    if (id > 0)
	printf("%d", id);
    printf(" ");
}

static void showSource(Process p, int id, int bfsz)
{

    if (bfsz == defaultBufferSize) {
	printf("\t\t<- %d(%s %s.%s",
	       id, p->name, p->comp->path, p->comp->name);
    } else {
	printf("\t\t<%d- ", bfsz);
	if (id > 0)
	    printf("%d", id);
	printf("(%s %s.%s", p->name, p->comp->path, p->comp->name);
    }

    showArgs(p);
    printf(");\t\n");
}

static int assign_channel(int ch, Stream f)
{

    findPort(f->source, f->source_id)->channel = ch;
    findPort(f->sink, f->sink_id)->channel = ch;
    return ch;
}

static void assignChannels(Model m)
{  
    int ch = m->nstreams - 1;
    Stream f = m->stream;

    /* if (ch<1) { 
		ch=1;
    } */

    while (f) {
	switch (f->type) {
	   case IS_SUB:
	   case IS_ORPHAN:
		break;
	   case IS_NET:
		assign_channel(ch--, f);
	    	break;
	}
	f = f->next;
    }
}

static void ConnectProcess(Process p, int partn) {
	Port pt;

	if(p->partn==partn)
		return;

	p->partn=partn;
	pt=p->port;
	if(pt) {
		do {
		   if(pt->match) {
			if(pt->match->stream->source!=p) 
				ConnectProcess(pt->match->stream->source,partn);
			if(pt->match->stream->sink!=p)
				ConnectProcess(pt->match->stream->sink,partn);
		   }
		   pt=pt->next;
		} while(pt!=p->port);
	}	
}

/** For every disconnected process; 
    increment partn and
    set partn in every connected process;	
*/
static int ComputeNpartitions(Model m) {
	Process p;
	int nparts=0;

	p=m->proc;
	while(p) {
		p->partn=0;
		p=p->next;
	}

	p=m->proc;
	while(p) {
		if(p->partn==0) {
			nparts++;
			ConnectProcess(p,nparts);
		}
		p=p->next;
	}

	return nparts;
}


static void ShowOrphan(Process p) {
    printf("%s %s.%s", p->name, p->comp->path, p->comp->name);
    showArgs(p);
    printf(";\n");
}

/** Show Network definition */
static void showND(Model m)
{
    Stream f;
    int nparts, ncycles;			/* Number of partitions */

    //* Generate commented Reconstructed Network Definition */
    printf
	("NetDef() {\n\tcat <<- EOF \n***********   Expanded %s Network Definition   **********   \n",
	 m->name);
    f = m->stream;
    assignChannels(m);

    while (f) {
	switch (f->source->kind) {
		case IS_SUB:

			break;
		case IS_NET:
	    		showSink(f->sink, f->sink_id);
	    		showSource(f->source, f->source_id, f->bufsz);
			break;
		case IS_ORPHAN:
			ShowOrphan(f->source);
	} 
	f = f->next;
    }

    nparts=ComputeNpartitions(m);

    ncycles=m->nstreams - m->nprocs + nparts;  
    printf("# %d stream%s, %d processes, %d component%s, %d partition%s, %d cycle%s.\n",
		m->nstreams,  Plural(m->nstreams), 
		m->nprocs,
		m->ncomponents, Plural(m->ncomponents),
		nparts, Plural(nparts), 
		ncycles, Plural(ncycles));
    printf("*********************************************/\nEOF\n}\n\n");
}

/** Generate Prefix code */
static void genPrefix(Model m)
{
    // int nstreams = m->nstreams;
    // int bfrtbl[m->nstreams + 10];
    // int i;
    //Stream f = m->stream;

    C(# StreamWork project generated by sw/swproject.c);
    printf("-%s %s\n", version, Timestamp());
    printf("# Configuration file: %s\n\n\n",configfile);
    printf("# Purpose:  create GoLang code from an .SW file.\n");
    printf("# 	Generate a GoLang source and test file for every component.\n");
    printf("# 	Build the project and run it.\n\n");
    showND(m);			/* Show commented Net Definition */
    printf("\nNetDef\n");
      
    
    //	echo package $1 > ../$1/${2}.go
    //	echo package $1 > ../$1/${2}_test.go  
      
    printf("\nGenComp() {\necho package $1 > ../$1/${2}.go\necho package $1 > ../$1/${2}_test.go\n" );
    printf("}\n");
}

#endif

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
	
	c=m->comp;
	module=Prefix(m->name);   // Strip off suffix: .sw
	
	while(c!=NULL) {
		getPorts(m, c, &inp,&outp);   
		printf("swgen.sh gs %s %s %s %d %d %s \"arg1\" \"val1\" %c \n",
			module ,c->path, getConfType(c->path), inp, outp, c->name, amp );
		amp='&'; 
		c=c->next;
	}
}


/***************   End of SWPROJECT.C   ********************/
