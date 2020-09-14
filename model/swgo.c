/** @file SWGO.C 
		  Greate StreamWork Go program 

  @bug  A a;  causes launch code w/missing parameter, S.B cs[0,0].
	
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


static void genPath(char *s)
{
    // char *importPath = { "github.com/tyoung3/streamwork" };
    //char *importPath = { defaultPath };
    char *importLib  = { defaultLibrary };
    printf("import \"%s/%s\"\n", importLib,  s);
#if 0
    if (s == NULL) {
	printf("import \"%s/fbp\"\n", importPath);
    } else {
	printf("import \"%s/%s\"\n", importPath, s);
    }
#endif

}

int newPath(char *p)
{

    if (getPath(p) == 1)
	return 1;

    return 0;
}

static void genPaths(Model m)
{
    Process p;

    // P(import "fmt");
    P(import "sync");
    P(import "github.com/tyoung3/streamwork/fbp");

    p = m->proc;
    while (p) {
	if (newPath(p->comp->path)) {
	    genPath(p->comp->path);
	}
	p = p->next;
    };

    printf("\n\n");
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

    while (f) {
	assign_channel(ch--, f);
	f = f->next;
    }
}

#ifdef NBRMULTIPLES
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

// ?? static void ConnectProcess(Process p, int partn);

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


String Plural(int n) {
	if(n==1) 
		return "";
	return "s";
}

/** Show Network definition */
static void showND(Model m)
{
    Stream f;
    char plural[] = "s";
    int nparts, ncycles;			/* Number of partitions */

    //* Generate commented Reconstructed Network Definition */
    printf
	("/***********   Expanded %s Network Definition   **********   \n",
	 m->name);
    f = m->stream;
    assignChannels(m);

    while (f) {
	if (f->source->kind == IS_NET) {
	    showSink(f->sink, f->sink_id);
	    showSource(f->source, f->source_id, f->bufsz);
	}
	f = f->next;
    }

    nparts=ComputeNpartitions(m);

    if (nparts < 2) {
	plural[0] = 0;
    }
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
    Stream f = m->stream;

    P(package main);
    printf("\n/");
    C(*StreamWork Go code. \n  Generated by sw/swgo.c);
    printf("-%s %s", version, Timestamp());
    printf(" Configuration file: %s\n*/\n\n",configfile);
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
	assert(f->sink->comp->path != 0);
	f = f->next;
    }
    i = 0;
    f = m->stream;
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
    printf("\n\tvar cs_%s []chan interface{}\n", name);
    printf("\tfor i:=0; i<%i; i++ {\n\t\t", nstreams);
    printf("cs_%s=append(cs_%s, make(chan interface{},2))", name, name);
    printf("\n\t}\n");

    pt = p->port;
    do {
	printf("\tcs_%s[%i] = cs[%i]\n", name, pt->id, pt->channel);
	pt = pt->next;
    } while (pt != p->port);
}

static void genLaunch1(Process p)
{
    int i = 1;

    printf("fbp.Launch(&wg,");
    printf("[]string{\"%s\"", p->name);

    if (p->arg) {
	while (p->arg[i]) {
	    printf(",\"%s\"", p->arg[i]);
	    i++;
	}
    }
    printf("},\t%9s.%s, ", p->comp->path, p->comp->name);

}

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
		printf("cs_%s[0:%i])\n", p->name, nstreams);
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
		printf("\n");
	    }
	}
	p = p->next;
    }

    printf("\n");
}


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
	if (f->sink->port->id)
	    printf("(%s)%d<-%d(%s); \n", f->sink->name,
		   f->sink->port->id, f->source->port->id,
		   f->source->name);
	else
	    printf(" (%s)%d<-(%s); \n", f->sink->name,
		   f->source->port->id, f->source->name);

	f = f->next;
    }

}

/***************   End of SWGO.C   ********************/
