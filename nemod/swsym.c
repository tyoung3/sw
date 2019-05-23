/** \file swsym.c 

 ** Symbol Table Functions

 */


#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <errno.h>
#include "nemod.h"

// #define TEST_MAIN


struct bucket {
	union {
		Flow flow; 
		Process proc; 
	} u;
	char *tag;
	int nrefs;  // Number of references to this symbol
	struct bucket *link;
	struct bucket *next;
} bucket;
typedef struct bucket *bucketp;

bucketp *symtable;  /* Array of bucket pointers */

int TABLESIZE = 100000;

#include <string.h>
#include <assert.h>
#include <stdio.h>

#define FREE(x)      free((char *) (x))
#define NEW(t)      ((t *) alloca((unsigned) sizeof(t)))
#define NEW2(n, t) ((t *) alloca((unsigned) ((n) * sizeof(t*))))

#ifndef REGISTER
#define REGISTER register
#endif

#define COUNT_SYMS 1

#if COUNT_SYMS
int nsyms;
#endif

static bucketp firstsymbol;
static bucketp lastsymbol;


#define PERR1(S) fprintf(stderr,"SWSYM/FAIL: %s\n",(S) );

void tabinit(int nvar) {
	TABLESIZE=nvar;
	int i;

	symtable = (bucketp *) malloc(TABLESIZE * sizeof( bucketp) );

    if (symtable == NULL) {
		PERR1("Too many variables for memory.");
		exit(1);
    }

    /* Set all symtable pointers to NULL */
#define MEMMOVE    
#ifdef MEMMOVE
    symtable[0] = NULL;
    i = sizeof(*symtable);
    i *= TABLESIZE - 1;
    memmove(&symtable[1], &symtable[0], i);
#else
    for (j = 0; j < TABLESIZE;) {
	symtable[j++] = NULL;
    }
#endif

#ifndef MAKESMALL
    assert(symtable[2] == NULL);
    assert(symtable[TABLESIZE - 1] == NULL);
#endif

    /* for( i=0; i < TABLESIZE; i++ ) { symtable[ i ] = NULL; }; */

    firstsymbol = NULL;
    lastsymbol = NULL;

}

static int hash(char *key)
{ 
    register int k;

    k = 0;
    while (*key)
	k = ((k << 1) ^ (*key++)) & 0x3fff;

    return (k % TABLESIZE);
}

static bucketp lookup(char *key)
{
    register int hashval;
    register bucketp bp;
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
	   	 	fprintf(stderr, "%i variables not enough for this job.\n",
		    TABLESIZE);
	    	exit(1);
		}
		bp = (bucketp) malloc(sizeof(bucket));
		bp->link = symtable[hashval];
		bp->next = NULL;
		bp->tag = strdup(key);
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

void free_symtab()
{
    register int i;
    register bucketp bp, bptmp;	/* JF don't use ptr after free */

    for (i = 0; i < TABLESIZE; i++) {
	bp = symtable[i];
	while (bp) {
	    bptmp = bp->link;
	    FREE(bp);
	    bp = bptmp;
	}
    }
}

Process addProc(char *key, Process p) {
	bucketp b;
	
	b=lookup(key);
	b->u.proc = p;
	return b->u.proc;
}

Process getProc(char *key) {
	bucketp b;
		
	b=lookup(key);
	return b->u.proc;
}

int getPath(char *key) {
	bucketp b;
		
	b=lookup(key);
	b->nrefs++;
	return b->nrefs;
}

#ifdef TEST_MAIN

int main()
{
    struct bucket b1, b2;
	struct Process_ p1={"C1_x"},p2={"C2_x"};
    tabinit(100);

#define ASSOCP(k,w) lookup( #k )->proc = (w)
#define SSHOWP(k) fprintf( stderr, "%s == %s\n", #k, lookup( #k )->proc->name)

    ASSOCP(P1, &p1);
    ASSOCP(P2, &p2);

    SSHOWP(P1);
    SSHOWP(P2);
}
#endif

/* End of SWSYM.C )} */
