/** @file swgo.c 
		  Greate a Go program from the network model	
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "swsym.h"
#include "model.h"
#include "sw.h"

#include <assert.h> 



/** Print string.*/
#define P(s) printf("%s\n",(#s));	
#define PE(s) {};  			/**<Print empty string */
#define C(s) printf("%s",(#s));		/**<Print defined string*/

/**Get timestamp*/
static String Timestamp()
{
    time_t ltime;		/* calendar time */
    ltime = time(NULL);		/* get current cal time */
    return (asctime(localtime(&ltime)));
}

/** Generate Suffix code */
void genSuffix()
{

    P(wg.Wait());
    printf("}\n");
}

String deleteBrace(char *s0) {
	char *s=s0;
		
	do {
		if(*s == '}') 
			*s=0;
		s++;
	} while(*s !=0);

	return s0; 
}

/** Print generated module path.*/
static void genPath(Component  c)
{
    char *s=c->path;
    char *importLib  = { defaultLibrary };
    
    if( strcmp(s,STDPACKAGE) == 0) 
    	 return;
    if(s[0] == '{') {
    	printf("import \"%s\"\n",  deleteBrace(s+1));
    } else {
    if(s[0] == '/') {
    	printf("import \"%s\"\n",   s);
    } else {
    	printf("import \"%s/%s\"\n", importLib,   s);
    }}	
}

/** Return true if path is new.*/
int newPath(char *p)	
{

    if (getPath(p) == 1)
	return 1;

    return 0;
}

#define StringIt(X) #X

/** Create import paths from process structs.*/
static void genPaths(Model m)
{
    Process p;

    // P(import "fmt");
    P(import "sync");
    printf("import %s \"github.com/tyoung3/sw\"\n", STDPACKAGE);

    p = m->proc;
    while (p) {
	if (newPath(p->comp->path)) {
	    genPath(p->comp);
	}
	p = p->next;
    };

    printf("\n\n");
}


/** Find process port from matching port id */
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

    snprintf(fbfr, BUFFSIZE, "Process %s Port %i mismatch\n", p->name, id);
    FAIL(findPort, fbfr);
}

/** Print arguments for process.*/
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

/** Print Sink process */
static void showSink(Process p, int id)
{

    printf("(%s %s.%s ", p->name, p->comp->path, p->comp->name);

    showArgs(p);


    printf(")");
    if (id > 0)
	printf("%d", id);
    printf(" ");
}

/** Print Source Process */
static void showSource(Process p, int id, int bfsz, char *iptype)
{

    if (bfsz == defaultBufferSize) {
	printf("\t\t<%s-\t%d(%s %s.%s",
	       iptype, id, p->name, p->comp->path, p->comp->name);
    } else {
	printf("\t\t<%s %d-\t", iptype, bfsz);
	if (id > 0)
	    printf("%d", id);
	printf("(%s %s.%s", p->name, p->comp->path, p->comp->name);
    }

    showArgs(p);
    printf(");\t\n");
}

/** Assign channel number to source and sink ports.*/
static int assign_channel(int ch, Stream f)
{

    findPort(f->source, f->source_id)->channel = ch;
    findPort(f->sink, f->sink_id)->channel = ch;
    return ch;
}

/** For each stream; assign the channel to source and sink ports.  Must be done after expansion is complete*/ 
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

#ifdef NBRMULTIPLESrunning
/**  Count number of streams connecting identical nodes */
static int nbrMultiples(Model m)
{
    Stream s, s2;
    Process p1, p2, p3, p4;
    int n = 0;

    s = m->stream;
    while (s) {
	s2 = s->next;
	p1 = s->source;
	p2 = s->sink;
	while (s2) {
	    p3 = s2->source;
	    p4 = s2->sink;
	    if ((p1 == p3 && p2 == p4) || (p1 == p4 && p2 == p3)) {
		n++;
	    }
	    s2 = s2->next;
	}
	s = s->next;
    }

    return n;
};
#endif


/** @todo  Handle unmatched ports by autconnecting to dummy process.  
*/
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

/** Return 's' or blank. */
String Plural(int n) {
	if(n==1) 
		return "";
	return "s";
}

/** Print orphan data */
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
	("/***********   Expanded %s Network Definition   **********   \n",
	 m->name);
    f = m->stream;
    assignChannels(m);

    while (f) {
	switch (f->source->kind) {
		case IS_SUB:
			break;
		case IS_NET:
	    		showSink(f->sink, f->sink_id);
	    		showSource(f->source, f->source_id, f->bufsz, f->iptype);
			break;
		case IS_ORPHAN:
			ShowOrphan(f->source);
	} 
	f = f->next;
    }

    nparts=ComputeNpartitions(m);

    ncycles=m->nstreams - m->nprocs + nparts;  
    printf("# %d stream%s, %d processes, %d component%s, %d partition%s, %d cycle%s.\n",
		m->nstreams, Plural(m->nstreams), 
		 m->nprocs,
		m->ncomponents, Plural(m->ncomponents),
		nparts, Plural(nparts), 
		ncycles, Plural(ncycles));
    printf("*********************************************/\n");
}

/** Generate Prefix code */
void genPrefix(Model m)
{
    int nstreams = m->nstreams;
    int bfrtbl[m->nstreams + 10];
    int i;
    Stream f;

    P(package main);
    printf("\n/");
    C(*StreamWork Go code. \n  Generated by sw/swgo.c);
    printf("-%s %s", version, Timestamp());
//    printf(" Configuration file: %s/%s\n*/\n\n",get_current_dir_name(),configfile);
    printf(" Configuration file: %s/sw/%s\n*/\n\n",getenv("GOPATH"),configfile);
    showND(m);			/* Show commented ND */
    printf("\n");

    genPaths(m);

    P(func main() {
	);
    PE(} Fixes indent);
    printf("	var cs []chan interface{}\n	");
    P(var wg sync.WaitGroup);
    printf("\n");

    f = m->stream;
    i = 0;
    while (f) {
	bfrtbl[nstreams - i++ - 1] = f->bufsz;
	f = f->next;
    }
    i = 0;
    // f = m->stream;
    while (i < nstreams) {
	if (bfrtbl[i] > 0) {
	    printf("cs = append(cs,make(chan interface{},%i))\n",
		   bfrtbl[i]);
	} else {
	    printf("cs = append(cs,make(chan interface{}))\n");
	}
	i++;
    }
    printf("\n");
}

/** Return true if channel numbers not lined up */
static int needaSlice(Port pt)
{
    Port pt0 = pt;
    int ch;

    ch = pt->channel;
    pt = pt->next;

    do {
	if (pt->channel != ++ch) {
	    return 1;
	}
	pt = pt->next;
    } while (pt != pt0);
    return 0;
}

	/** Generate a slice of channels for this process */
static void makeChSlice(Process p, int nstreams)
{
    char *name;
    Port pt;

    name = p->name;
    printf("\n\tvar _cs%s []chan interface{}\n", name);
    printf("\tfor i:=0; i<%i; i++ {\n\t\t", nstreams);
    printf("_cs%s=append(_cs%s, make(chan interface{},2))", name, name);
    printf("\n\t}\n");

    pt = p->port;
    do {
	printf("\t_cs%s[%i] = cs[%i]\n", name, pt->id, pt->channel);
	pt = pt->next;
    } while (pt != p->port);
}

/** Return rightmost path element */
char *stripPath( char *s1 ) {
	char *s;
	char *s2;
	
	s=s2=s1;
	
	while (*s != 0) {
		if (*s == '/') {
			s2=s+1;
		}
		s++;
	}
	return s2;
	
}

/** print launch process code. */
static void genLaunch1(Process p)
{
    int i = 1;
    printf( STDPACKAGE ".Launch(&wg,");
    printf("[]string{\"%s\"", p->name);

    if (p->arg) {
	while (p->arg[i]) {
	    printf(",\"%s\"", p->arg[i]);
	    i++;
	}
    }
    
    printf("},\t%9s.%s, ", stripPath(p->comp->path), p->comp->name);

}

/** Generate startup code */
static void genLaunches(Process p)
{
    int ch;			/* Assigned channel */
    int nstreams;
    int ch0;			/* initial channel index */


    while (p) {
	nstreams = p->nportsIn + p->nportsOut;
	if (nstreams > 1) {
	    if (needaSlice(p->port)) {
		makeChSlice(p, nstreams);
		genLaunch1(p);
		printf("_cs%s[0:%i])\n", p->name, nstreams);
	    } else {
		genLaunch1(p);
		ch0 = p->port->channel;
		printf("cs[%i:%i])\n", ch0, ch0 + nstreams);
	    }
	} else {
	    if (nstreams > 0) {
		ch = p->port->channel;
		genLaunch1(p);
		printf("cs[%i:%i])\n", ch, ch + 1);
	    } else {
		genLaunch1(p);
		printf("cs[0:1])\n");
	    }
	}
	p = p->next;
    }

    printf("\n");
}

/** Generate Go language Main package code from SW network model.*/
void genGo(Model model)
{
    Process p;


    genPrefix(model);		/* Generate Prefix code */
    p = model->proc;		/* Get first process    */
    genLaunches(p);		/* Expand processes     */
    genSuffix();		/* Generate Suffix code */
}

/** Generate Expanded Network Definition */
void genND(Model mod)
{
    Stream f;

				/** Generate Prefix code */
    printf("StreamWork Network Definition.  Generated by sw-%s. \n",
	   version);

    f = mod->stream;
    while (f) {
      if( f->type==IS_NET) {
		if (f->sink->port->id) {
	    		printf("(%s)%d<%s-%d(%s); \n", f->sink->name,
		   		f->sink->port->id,
		   		f->iptype,
		   		f->source->port->id,
		   		f->source->name);
		} else {
	    		printf(" (%s)%d<%s-(%s); \n", f->sink->name,
		   		f->source->port->id, 
		   		f->iptype, f->source->name);
		}
      }  else  {
	 if( f->type==IS_ORPHAN ) {
		printf("%s;\n",f->source->name);
	 }
      }	
      f = f->next;
    }

}

/***************   End of SWGO.C   ********************/
