/** @file swmain.c

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sw.h"
#include "swgo.h"
#include "swgofbp.h"
#include "swsym.h"
#include "swgraph.h"
#include "swconfig.h"

typedef enum
    { GOMODE = 0, ASTMODE, GENTREE, GRAPHMODE, JAVAFBP, PROJECT, CMODE =
   7, GENGOFBP
} MODE;

char fbfr[BUFFSIZE + 1]; /**<File name buffer.*/

char *version = { "0.15.0" };

String configfile = { "sw.cfg" };		/**<SW configuration file> */

static MODE mode = GOMODE;			    /** Outut mode*/
char *fname = { "stdin" };		/**<Input file name or Standard input.> */

ValidSW pValidSW(FILE * inp);  /**<True if valid input> */

//CCIDE_INLINE_CODE:

char *FixVersion()
{
	char bfr[100];

	sprintf(bfr, "%d.%d.%d", MAJOR, MINOR, SLEVEL);
	version = strdup(bfr);
}

char *mystrncat(char *d, char *s, size_t n)
{
	if (sizeof(d) + sizeof(s) >= (n - 1)) {
		abort();
	}
	return strcat(d, s);
}

/** True if process structure misconfigured. */
static int badProc(Process p)
{
	int i;
	Port port;

	if (!p)
		return 0;

	if (!p->comp) {
		snprintf(fbfr, BUFFSIZE, "missing component for process: (%s)",
			 p->name);
		FAIL(badProc, fbfr);
		return 1;
	}

	port = p->port;
	i = 0;

	if (port && ( p->kind == IS_NET || p->kind == IS_STRUCT) ) {
		if (port->id < 0) {
			port->id = 0;	// Expand missing port number 
		}
		for (; i < (p->nportsIn + p->nportsOut); i++) {
			if (!port->stream) {
				snprintf(fbfr, BUFFSIZE,
					 "(%s) port[%i] is disconnected(has no ->stream).\n",
					 p->name, i);
				FAIL(badProc, fbfr);
			}
			if (port->id > i) {
				snprintf(fbfr, BUFFSIZE,
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

/** True is strings are equal */
int eqs(char *s1, char *s2)
{

	if (strncmp(s1, s2, 40) == 0)
		return 1;

	return 0;
}

static int nameFail(char *psnkname, char *nsnk, char *nsrc, char *psrcname)
{

	snprintf(fbfr, BUFFSIZE, "(%s)%s <- %s(%s)", psnkname, nsnk, nsrc,
		 psrcname);
	FAIL(nameFail, fbfr);
}

static int NameMisMatch(Process src, int source_id, Process snk, int sink_id)
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
		if (s->source->nportsIn > 0)
			FixComp(s->source, defaultFilterComp, defaultPath);
		else
			FixComp(s->source, defaultSourceComp, defaultPath);
	}

	if (s->type == IS_ORPHAN)
		return;
	if (!s->sink->comp) {
		if (s->sink->nportsOut > 0)
			FixComp(s->sink, defaultFilterComp, defaultPath);
		else
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
		case IS_STRUCT:
		case IS_NET:
			FixComps(f);
			if (f->sink->name == NULL) {
				snprintf(fbfr, BUFFSIZE,
					 "Sink process has no name. Source is %s.",
					 f->source->name);
				FAIL(verifyOK, fbfr);
			}
			if (f->source->name == NULL) {
				snprintf(fbfr, BUFFSIZE,
					 "Source process has no name. Sink is %s.",
					 f->sink->name);
				FAIL(verifyOK, fbfr);
			}
			if (badProc(f->sink) || badProc(f->source)) {
				return 0;
			}
			if (NameMisMatch
			    (f->source, f->source_id, f->sink, f->sink_id))
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

/** sw progam help.*/
static void Usage()
{
	fprintf(stderr,
		"\nUsage:\tsw [-m MODE] [-cfg CONFIGURATION_FILE] [-d DEFAULT_PATH] [ SW_FILE ]\n");
	fprintf(stderr, "\tsw -v\n");
	fprintf(stderr, "\tsw --help\n");
	fprintf(stderr,
		"\n\tMODE={0-GOMODE|1-ASTMODE|2-GENTREE|3-GRAPHMODE|4-JAVAFBP|5-PROJECT|7-CMODE|8-GENGOFBP,}\n");
	fprintf(stderr,
		"\tIf SW_FILE Is omitted sw will read from stdin. \n\n");
}

FILE *input;				/**<Input SW file name */
static FILE *openFile(char *fname)
{
	input = fopen(fname, "r");
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


static void CheckInput(FILE *s) {

	if (input == NULL) {
		snprintf(fbfr,
		BUFFSIZE,
		"Error opening input file: %s.",
		fname);
		
		FAIL(openFile,fbfr);
	}
}

String  yamlOption="YAML";  /* YAML | NONE */   

static int BadArg(int argc, char **argv)
{
    int i = 1;
    yamlOption="YAML";
    
    while (i < argc) {
/*DECISION_TABLE:*/
/*   Y  -  -  -  -  -  -  -  -  N  -  - | strncmp(argv[i], "-yaml", 30) == 0*/
/*   -  -  -  -  -  -  -  -  Y  N  -  - | strncmp(argv[i], "--help",7) == 0 */
/*   -  -  -  -  -  -  Y  Y  -  N  -  - | strncmp(argv[i], "-cfg", 6) == 0  */
/*   -  -  -  Y  Y  -  -  -  -  N  -  - | strncmp(argv[i], "-d", 30) == 0	*/
/*   -  Y  Y  -  -  -  -  -  -  N  -  - | strncmp(argv[i], "-m", 30) == 0	*/
/*   -  -  -  -  -  Y  -  -  -  N  -  - | strncmp(argv[i], "-v", 4) == 0 	*/
/*   -  N  Y  N  Y  -  N  Y  -  -  -  - | i >= argc - 1 			*/
/*   -  -  -  -  -  -  -  -  -  -  Y  N | i < argc 				*/
/*  ____________________________________|      */
/*   X  -  -  -  -  -  -  -  -  -  -  - | yamlOption=argv[++i];	*/
/*   -  X  -  -  -  -  -  -  -  -  -  - | mode = atoi(argv[++i]);	*/
/*   -  -  -  X  -  -  -  -  -  -  -  - | defaultPath = argv[++i];	*/
/*   -  -  -  -  X  X  -  -  -  -  -  - | printf("StreamWork/sw-%s\n", version);*/
/*   -  -  -  -  -  -  X  -  -  -  -  - | configfile = argv[++i];*/
/*   -  -  -  -  -  -  -  -  X  -  -  - | Usage();*/
/*   -  -  -  -  -  -  -  -  -  X  -  - | fname = argv[i];*/
/*   -  -  -  -  -  -  -  -  -  X  -  - | input = openFile(fname);*/
/*   -  -  -  -  -  -  -  -  -  X  -  - | CheckInput(input);*/
/*   -  -  -  -  -  -  -  -  -  -  X  - | fprintf(stderr,"CONFIG/WARNING/BadArg:%s\n",argv[i]); */
/*   X  X  -  X  -  -  -  -  -  X  X  - | i++; 		*/
/*   -  -  -  -  -  X  -  -  X  -  -  X | exit(EXIT_SUCCESS);*/
/*   -  -  X  -  X  -  X  X  X  -  -  - | exit(EXIT_FAILURE);;*/
/*END_TABLE:*/
/*GENERATED_CODE: FOR TABLE_1.*/
/*	12 Rules, 8 conditions, and 12 actions.*/
/*	Table 1 rule order = 10 7 8 4 5 2 3 1 9 6 11 12 */
 {	unsigned long CCIDE_table1_yes[12]={   0UL,   4UL,  68UL,   8UL,  72UL,  16UL,  80UL,   1UL,   2UL,  32UL,   0UL, 128UL};
	unsigned long CCIDE_table1_no[12]= {  63UL,  64UL,   0UL,  64UL,   0UL,  64UL,   0UL,   0UL,   0UL,   0UL, 128UL,   0UL};


	switch(CCIDEFindRule(12,
		  (strncmp(argv[i], "-yaml", 30) == 0)
		| (strncmp(argv[i], "--help",7) == 0)<<1
		| (strncmp(argv[i], "-cfg", 6) == 0)<<2
		| (strncmp(argv[i], "-d", 30) == 0)<<3
		| (strncmp(argv[i], "-m", 30) == 0)<<4
		| (strncmp(argv[i], "-v", 4) == 0)<<5
		| (i >= argc - 1)<<6
		| (i < argc)<<7
		  ,CCIDE_table1_yes, CCIDE_table1_no)) {
	case  8:	/*	Rule  9 */
	    Usage();
	    exit(EXIT_SUCCESS);
	    goto CCIDE_case1_6;
	case  1:	/*	Rule  7 */
	    configfile = argv[++i];
	    goto CCIDE_case1_6;
	case  4:	/*	Rule  5 */
	    printf("StreamWork/sw-%s\n", version);
	case  2:	/*	Rule  8 */
	CCIDE_case1_6: case  6:	/*	Rule  3 */
	    exit(EXIT_FAILURE);;
	    break;
	case  9:	/*	Rule  6 */
	    printf("StreamWork/sw-%s\n", version);
	case 10:	/*	Rule 11 */
	    exit(EXIT_SUCCESS);
	    break;
	case  0:	/*	Rule 10 */
	    fname = argv[i];
	    input = openFile(fname);
	    CheckInput(input);
	    goto CCIDE_case1_11;
	case  3:	/*	Rule  4 */
	    defaultPath = argv[++i];
	    goto CCIDE_case1_11;
	case  5:	/*	Rule  2 */
	    mode = atoi(argv[++i]);
	    goto CCIDE_case1_11;
	case  7:	/*	Rule  1 */
	    yamlOption=argv[++i];
	CCIDE_case1_11: case 11:	/*	Rule 12 */
	    i++;
	    break;
	} /* End Switch*/	
/*END_GENERATED_CODE: FOR TABLE_1, by ccide-0.6.6-1 Tue 29 Mar 2022 06:39:50 PM EDT */


   } 	  /* End While */

	
	return 0;
}

ValidSW IncludeFile(char *fname)
{
	ValidSW parse_tree = NULL;

	fclose(input);
	input = openFile(fname);
	if (input == NULL) {
		perror(fname);
		//      #include <errno.h>
		FAIL(Cannot open, fname);
	}
	parse_tree = pValidSW(input);
	if (parse_tree == NULL) {
		FAIL(Cannot parse, fname);
	}
	return parse_tree;
}

static void output(Model model, ValidSW parse_tree)
{
	switch (mode) {
	case ASTMODE:		// Abstract Syntax                  
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
		genGo(model);	// Generate Go MAIN.GO
		break;
	case GENGOFBP:
		genGoFBP(model);	// Generate gofbp MAIN.GO
		break;
	case CMODE:
		genC(model);	// Generate C source  [TBI]
		break;
	case PROJECT:
		genProject(model);	// Generate project files in current directory  [TBI]
		break;
	default:
		Usage();
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv)
{
	version = FixVersion();
	ValidSW parse_tree = NULL;
	Model model = NULL;	/* Network Model */

	input = stdin;

	if (BadArg(argc, argv)) {
		Usage();
		exit(EXIT_FAILURE);
	}

	if (ConfigError(configfile)) {
		FAIL(swmain / main, "Configuration file parse error");
	}

	parse_tree = pValidSW(input);	/** Parse network definition */

	if (parse_tree) {
		tabinit();
			/** set symbol table */
		model = MakeModel(NULL);
		visitValidSW(model, parse_tree);/** Build model */
		model->name = baseOf(fname);
		model->filename = fname;
		if (verifyOK(model)) {
			if (!model->proc) {
				FAIL(swmain/main, "No processes found.");
			} else {
				output(model, parse_tree);
			}
		} else {
			FAIL(VerfyOK, "Verify failed!");
			return EXIT_FAILURE;
		}
	} else {
		FAIL(SWMAIN, "Parse failed!");
	}

	return EXIT_SUCCESS;
    // return 0;
}
