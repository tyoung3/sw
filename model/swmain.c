/** @file SWMAIN.C 

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sw.h"
#include "swgo.h"
#include "swsym.h"
#include "swgraph.h"

/** 
	@todo Implement Process name expansion. 
	Ex. "_MONITOR;" launches system monitor
	@todo Create Man page w/Doxygen
	@todo Generate project examples

*/

typedef enum
    { GOMODE = 0, ASTMODE, GENTREE, GRAPHMODE, JAVAFBP, CMODE = 7 } MODE;

char fbfr[100];
char *version = { VERSION };

String configfile={"/home/tyoung3/projects/docker/goland/sw/sw.cfg"};

static MODE mode = GOMODE;
static char *fname = { "stdin" };

ValidSW pValidSW(FILE * inp);

static int badProc(Process p)
{
    int i;
    Port port;

    if(!p)
	return 0;

    if (!p->comp) {
	sprintf(fbfr, "missing component for process: (%s)", p->name);
	FAIL(badProc, fbfr);
	return 1;
    }

    port = p->port;
    i = 0;

    if (port && p->kind == IS_NET) {
	if (port->id < 0) {
	    port->id = 0;	// Expand missing port number 
	}
	for (; i < (p->nportsIn + p->nportsOut); i++) {
	    if (!port->stream) {
		sprintf(fbfr,
			"(%s) port[%i] is disconnected(has no ->stream).\n",
			p->name, i);
		FAIL(badProc, fbfr);
	    }
	    if (port->id != i) {
		sprintf(fbfr,
			"(%s) port[%i] is %i, should be = %i.\n",
			p->name, i, port->id, i);
		FAIL(badProc, fbfr);
	    }
	    port = port->next;
	}

    }

    return 0;
}


static Port findPrt(Process p, int id)
{
    Port pt;

    pt = p->port;
    do {
	if (pt->id == id)
	    return pt;
	pt = pt->next;
    }
    while (pt != p->port);

    return p->port;
}

int eqs(char *s1, char *s2)
{

    if (strncmp(s1, s2, 40) == 0)
	return 1;

    return 0;
}

static int nameFail(char *psnkname, char *nsnk, char *nsrc, char *psrcname)
{

    sprintf(fbfr, "(%s)%s <- %s(%s)", psnkname, nsnk, nsrc, psrcname);
    FAIL(nameFail, fbfr);
}

static int
NameMisMatch(Process src, int source_id, Process snk, int sink_id)
{
    Port psrc, psnk;
    char *nsrc, *nsnk;

    psrc = findPrt(src, source_id);
    nsrc = psrc->name;

    psnk = findPrt(snk, sink_id);
    nsnk = psnk->name;

    if (!nsnk || !nsrc) {
	return 0;
    }

    if (eqs(nsnk, "IN") && eqs(nsrc, "OUT")) {
	return 0;
    }

    if (eqs(nsnk, "in") && eqs(nsrc, "out")) {
	return 0;
    }

    if (eqs(nsnk, "SOCKET") && eqs(nsrc, "PLUG")) {
	return 0;
    }

    if (eqs(nsnk, "SLOT") && eqs(nsrc, "TAB")) {
	return 0;
    }

    if (eqs(nsrc, "IN") ||
	eqs(nsrc, "in") || eqs(nsrc, "PLUG") || eqs(nsrc, "SLOT"))
	return nameFail(snk->name, nsnk, nsrc, src->name);

    if (eqs(nsnk, "OUT") ||
	eqs(nsnk, "out") || eqs(nsnk, "SOCKET") || eqs(nsnk, "TAB"))
	return nameFail(snk->name, nsnk, nsrc, src->name);

    if (strcmp(nsnk, nsrc) == 0)
	return 0;

    if (eqs(nsrc, ""))
	return 0;
    if (eqs(nsnk, "")) {
	return 0;
    }

    return nameFail(snk->name, nsnk, nsrc, src->name);

}

static void FixComp(Process p, char *cn, char *path)
{


    p->comp = MakeComponent(cn, path);
}

/** Insert default components if necessary. */
static void FixComps(Stream s)
{
    if (!s->source->comp) {
	FixComp(s->source, defaultSourceComp, defaultPath);
    }
    
    if(s->type==IS_ORPHAN) 
	return;
    if (!s->sink->comp) {
	FixComp(s->sink, defaultSinkComp, defaultPath);
    }
}

/** verifyOK will expand and check model*/
static int verifyOK(Model model)
{
    Stream f;
    Process p;

    if (!model) {
	FAIL(verifyOK, "network model is missing!");
    }

    f = model->stream;
    while (f) {
       switch (f->type) {
	 case IS_ORPHAN:
		break;
	 case IS_SUB:
		break;
	 case IS_NET:
		FixComps(f);
		if(f->sink->name==NULL) {
			sprintf(fbfr, 
				"Sink process has no name. Source is %s.", 
				f->source->name);
			FAIL(verifyOK, fbfr);
		}
		if(f->source->name==NULL) {
			sprintf(fbfr, 
				"Source process has no name. Sink is %s.", 
				f->sink->name);
			FAIL(verifyOK, fbfr);
		}
		if (badProc(f->sink) || badProc(f->source)) {
	    		return 0;
		}
		if (NameMisMatch(f->source, f->source_id, f->sink, f->sink_id))
	    		return 0;
       }		
       f = f->next;
    }

    p = model->proc;
    while (p) {
	if (badProc(p)) {
	    FAIL(verifyOK,
		 "bad process definition. Missing component maybe.");
	}
	p = p->next;
    }

    return 1;

};

static void Usage()
{
    fprintf(stderr, "\nUsage:\tsw [-m MODE [ SW_FILE ]\n");
    fprintf(stderr, "\tsw -v\n");
    fprintf(stderr,
	    "\t\tMODE={0-GOMODE|1-ASTMODE|2-GENTREE|3-GRAPHMODE|4-JAVAFBP|7-CMODE,}\n");
    fprintf(stderr, "\t\t[with no arguments, sw will read from stdin. \n");
}


FILE *input;
static FILE *openFile(char *fname)
{
    input = fopen(fname, "r");
#if 0
    if (!input) {
	sprintf(fbfr, "Error opening input file: %s.", fname);
	FAIL(openFile, fbfr);
    }
#endif
    return input;
}

	/** Point to character past the last '/' */
char *baseOf(char *s)
{
    char *sr = s;

    while (*s != 0) {
	if (*s == '/') {
	    sr = s + 1;
	}
	s++;
    }
    return sr;
}

static int BadArg(int argc, char **argv)
{
    int i = 1;

    while (i < argc) {
	if (strncmp(argv[i], "-m", 30) == 0) {
	    if (i == argc - 1)
		return 1;
	    mode = atoi(argv[++i]);
	} else {
	    if (strncmp(argv[i], "-d", 30) == 0) {
		if (i == argc - 1)
		    return 1;
		defaultPath = argv[++i];
	    } else {
		if (strncmp(argv[i], "-v", 4) == 0) {
		    printf("StreamWork/sw-%s\n", version);
		    exit(0);
		} else {
		    if (strncmp(argv[i], "-cfg", 6) == 0) {	
			configfile=argv[++i];
		    } else {
			if (strncmp(argv[i], "--help", 7) == 0){
				Usage();
			} else {
		   	 	fname = argv[i];
		   	 	input = openFile(fname);
		   	 	if(input==NULL) {
					sprintf(fbfr, 
					   "Error opening input file: %s.", fname);
					FAIL(openFile, fbfr);
				}
			}
		    }
		}
	    }
	}
	i++;
    }
    return 0;
}

int main(int argc, char **argv)
{
    ValidSW parse_tree = NULL;
    Model model = NULL;		/* Network Model */

    input = stdin;

    if (BadArg(argc, argv)) {
	Usage();
	exit(1);
    }

    if(ConfigError(configfile)) {
	FAIL(swmain / main, "Configuration file parse error");	
    }

    parse_tree = pValidSW(input);	/** Parse network definition */

    if (parse_tree) {
	tabinit();	/** set symbol table */
	model = visitValidSW(parse_tree);	/** Build model */
	model->name = baseOf(fname);
	if (verifyOK(model)) {
	    if (!model->proc) {
		FAIL(swmain / main, "No processes found.");
		exit(1);
	    }
	    switch (mode) {
	    case ASTMODE:	// Abstract Syntax                  
		printf("%s\n\n", showValidSW(parse_tree));	//Print abstract syntax tree
		break;
	    case GENTREE:
		printf("#          [Linearized Tree]\n");
		printf("%s\n\n", printValidSW(parse_tree));	//Print expanded network
		break;
	    case GRAPHMODE:
		genGraph(model);	// Generate .DOT file
		break;
	    case JAVAFBP:
		genJavaFBP(model);	// Generate JavaFBP [TBI]
		break;
	    case GOMODE:
		genGo(model);		// Generate Go MAIN.GO
		break;
	    case CMODE:
		genC(model);		// Generate C source  [TBI]
		break;
	    default:
		Usage();
	    }
	} else {
	    FAIL(VerfyOK, "Verify failed!");
	}
	return 0;
    }
    return 1;
}
