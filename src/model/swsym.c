/** \file swsym.c 

 ** Symbol Table Functions

 */


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include <string.h>
#include "swsym.h"
#include "sw.h"
#include "swconfig.h"

/** Variable key/value structure. */
struct bucket {
    union {
	Stream stream;   	/**<??*/
	Process proc;		/**<??*/
	Component comp;		/**<??*/
	String  string;		/**<??*/
	String  type;        	/**<Config type: YAML or NONE */
    } u;  /**<Union of return values */
    char *tag;			/**<??*/	
    int nrefs;			/**<Number of references to symbol */
    int serno;			/** object serial number */
    struct bucket *link;	/**<??*/
    struct bucket *next;	/**<??*/
} bucket;  /**<Variable key/value structure.*/
typedef struct bucket *Bucketp;	/**<Pointer to bucket*/

Bucketp *symtable;		/**<Array of bucket pointers */
 
#define FREE(x)      free((char *) (x))					/**<Free storage*/
#define NEW(t)      ((t *) alloca((unsigned) sizeof(t)))		/**<Allocate a new table entry*/
#define NEW2(n, t) ((t *) alloca((unsigned) ((n) * sizeof(t*))))	/**<Allocate multiple table entries.*/

#ifndef REGISTER
#define REGISTER register		/**<??*/
#endif

#define COUNT_SYMS 1			/**< Number of table entries stored.*/

#if COUNT_SYMS
int nsyms;				/**<Number of Symbols */
#endif

static Bucketp firstsymbol;	/**<??*/
static Bucketp lastsymbol;	/**<??*/

void tabinit()
{
    int i;

    symtable = (Bucketp *) malloc(TABLESIZE * sizeof(Bucketp));

    if (symtable == NULL) {
	FAIL(tabinit, "Too many variables for memory.");
    }

    /* Set all symtable pointers to NULL 
       [REPLACED by loop, below, to eliminate Valgrind errors.]
       symtable[0] = NULL;
       i = sizeof(*symtable);
       i *= TABLESIZE - 1;
       memmove(&symtable[1], &symtable[0], i);
     */


    for (i = 0; i < TABLESIZE; i++) {
	symtable[i] = NULL;
    };

    firstsymbol = NULL;
    lastsymbol = NULL;

}

/** Find symbol table entry for key.*/
static int hash(char *key)
{
    register int k;

    k = 0;
    while (*key)
	k = ((k << 1) ^ (*key++)) & 0x3fff;

    return (k % TABLESIZE);
}

/** Find table entry for key.  Create new entry if no existing entry */
static Bucketp lookup(char *key)
{
    register int hashval;
    register Bucketp bp;
    register int found;

    hashval = hash(key) % TABLESIZE;

    bp = symtable[hashval];

    found = 0;
    while (bp != NULL && found == 0) {
	if (strcmp(key, bp->tag) == 0)
	    found = 1;
	else
	    bp = bp->link;
    }

    if (found == 0) {
	nsyms++;
	if (nsyms > TABLESIZE) {
	    snprintf(fbfr, BUFFSIZE, 
		    "%i variables exceeds symtable size.\n", TABLESIZE);
	    FAIL(lookup, fbfr);
	}
	bp = (Bucketp) malloc(sizeof(bucket));
	bp->link = symtable[hashval];
	bp->next = NULL;
	bp->tag = strdup(key);
	bp->u.comp = NULL;
	bp->nrefs = 0;
	if (firstsymbol == NULL) {
	    firstsymbol = bp;
	    lastsymbol = bp;
	} else {
	    lastsymbol->next = bp;
	    lastsymbol = bp;
	}

	symtable[hashval] = bp;
    }

    return (bp);
}

/** Delete symbol table when done. */
void free_symtab()
{
    register int i;
    register Bucketp bp, bptmp;	/* JF don't use ptr after free */

    for (i = 0; i < TABLESIZE; i++) {
	bp = symtable[i];
	while (bp) {
	    bptmp = bp->link;
	    FREE(bp);
	    bp = bptmp;
	}
    }
}

/** Find string for key.*/
String getSymVar(String name) {
    Bucketp b;

    b = lookup(name);
    if(b->u.string==NULL)
	return name;
    return(b->u.string);
}

/** Find string value for key.*/
String getStringVar(String name) {
    Bucketp b;

    b = lookup(name);
    if(b->u.string==NULL)
	return name;
    return b->u.string;
}

/** Add new string value to table. */
String addStringVar(String name, String val) {
    Bucketp b;

    b = lookup((char*)name);
    b->u.string = strdup(val);
    return val;
}

/** Add new value for symbol variable to table */
String addSymVar(String name, String val) {
    Bucketp b;

    b = lookup(name);
    b->u.string = val;
    return val;
}
 
/** Add new component pointer to table */
Component addComponent(char *name, char *path, Component c)
{
    Bucketp b;
    char key[BUFFSIZE+1];

    key[0] = '^';
    key[1] = 0;
    strncat(key, path, BUFFSIZE);
    strncat(key, ".", BUFFSIZE);
    strncat(key, name, BUFFSIZE);
    b = lookup(key);
    b->u.comp = c;
    return b->u.comp;
}

/** Find component in table */
Component getComponent(char *name, char *path)
{
    Bucketp b;
    char key[BUFFSIZE+1];

    key[0] = '^';
    key[1] = 0;
    strncat(key, path, BUFFSIZE);
    strncat(key, ".", BUFFSIZE);
    strncat(key, name, BUFFSIZE);
    b = lookup(key);
    return b->u.comp;
}

/** Add new process to table */
Process addProc(char *key, Process p)
{
    Bucketp b;

    b = lookup(key);
    b->u.proc = p;
    return b->u.proc;
}

/** Find process in table */
Process getProc(char *key)
{
    Bucketp b;

    b = lookup(key);
    return b->u.proc;
}

/** Get Conf Type */
String getConfType(char *path)
{
   Bucketp b;
    char key[BUFFSIZE+1];

    key[0] = '#';
    key[1] = 0;
    strncat(key, path, BUFFSIZE);


    b = lookup(key);
    if( b->u.type == NULL ) {
    	b->u.type=yamlOption;
    	return yamlOption;
    }
    
    return b->u.type;
}

int getPathColor(char *p) {
    Bucketp b;
    char key[BUFFSIZE+1]; key[0] = '<';
    static int color_i=0; 
    
    key[1] = 0;
    strncat(key, p, BUFFSIZE);

    b = lookup(key);
    
    if(b->nrefs==0) {
    	b->serno=color_i++;
    	if(color_i >= ncolors) 
    		color_i=0;
    } 
    
    b->nrefs++;
    return b->serno;
}

/** Find path for key */
int getPath(char *name)
{
    Bucketp b;
    char key[BUFFSIZE+1];

    key[0] = '<';
    key[1] = 0;
    strncat(key, name, BUFFSIZE);

    b = lookup(key);
    b->nrefs++;
    return b->nrefs;
}

#ifdef TEST_MAIN
/** Unit test symbol table lookup */
int main()
{
    struct bucket b1, b2;
    struct Process_ p1 = { "C1_x" }, p2 = {
    "C2_x"};
    tabinit();

#define ASSOCP(k,w) lookup( #k )->proc = (w)
#define SSHOWP(k) fprintf( stderr, "%s == %s\n", #k, lookup( #k )->proc->name)

    ASSOCP(P1, &p1);
    ASSOCP(P2, &p2);

    SSHOWP(P1);
    SSHOWP(P2);
}
#endif

/* End of SWSYM.C )} */
