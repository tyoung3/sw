/* SWGRAPH.C 
		  Generate Graphviz input 
		  
TODO:   
	* Title 
	* head,taillabels
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"

#define P(s) printf("%s\n",(#s));
#define C(s) printf("%s,\n",(#s));

// Define to remove process ports
#define NO_PORTS
// Define COMP_TIPS to move COMP info into tooltips for svg/html 
#define COMP_TIPS 
// Define NO_COMP_LABEL to hide component info
#define NO_COMP_LABELS
#define EDGE_LABELS
/////////////////  Dupes code in swgo.c  //////////////////////////////
static Port findPort(Port pt, int id) {
	
	while(pt) {
		if(pt->id == id) {					
			return pt;
		}	
		pt=pt->next;
	}
	return NULL;
}
static int assign_channel(int ch, Stream f) {
		
		findPort(f->source->port,f->source_id)->channel=ch;
		findPort(f->sink->port,  f->sink_id) ->channel=ch;
		return ch;
}
	
static void assignChannels(Model m) {
	int ch=m->nstreams-1;
	Stream f=m->stream;
	
	while(f) {
		assign_channel(ch--,f);	
		f=f->next;
	}	
}

/////////////////////////////////////////////////

static void genSuffix() {

	 
	printf("}\n");
}

static void genPrefix(char *gname, int nstreams) {


	printf("#Prefix here. %d streams\n",nstreams);
	printf("digraph \"%s\" {",gname);
	 
	P(graph [);
		C(	name="Streamwork/swgraph: " );
        C(	fontcolor=black);
        P(	fontname="Helvetica");           
    P(]);

    C(node [  shape=record);
                   C( fontsize="18");
                      C(      fontcolor=black);
                       C(    fontname="Helvetica");
                    C(        color=black);
                   C(         fillcolor=powderblue);
                  C(          style=filled);
                    P(        height=.2);
                  P(   ];);
               C(     edge [ color=blue);
              C(              style=bold);
          // NG in dot.    C(              len=0.1);
            C(                fontsize="18");
              C(              labelfontcolor=black);
              C(              fontcolor=blue);
               P(     ]);

}
#ifndef NO_PORTS
static void genPort(int n) {
  		printf("<%i> %i  ", n, n);
}  	
#endif

static void genArgs(char **a) {
		int i=1;
		
		while(a[i] != NULL) {
			printf(" \\\"%s\\\"", a[i++]);
		}
}


static char *makeURL(char *comp) {
		char bfr[100]; 
		
		snprintf(bfr, sizeof(bfr) -1,
		"/home/tyoung3/go/mod/sw/html/%s.html",comp);
		return strndup(bfr,sizeof(bfr) -1);
}


	/* EXAMPLE: label="{<P> G1 Gen1 \"xyz\" |{<0> 0 |<1> 1 } }"  */
static void genProc(char *name, char *comp, char *path,  char *host, char **args) {


     printf("       \"%s\" ", name );
     C(                   [ shape=record);
     C(                  color="black" );
     printf("  URL=\"%s\"\n",makeURL(comp));
     printf(" host=\"%s\" \n", host);
     printf(" tooltip=\"%s.%s ",path,comp);
     genArgs(args);
     printf("\"\n");
     // ? Generate args for tip
#ifdef NO_COMP_LABELS
     printf("label=\"{<P> %s ",name);
#else
     printf("label=\"{<P> %s %s",name,comp);
     genArgs(args); 
#endif 

}  	 

static void endProc() {
    printf("\"\n"); 
    printf("];\n"); // End proc 
}

     
static void genCluster1(char *name) { 
               
  printf("subgraph \"cluster%s\" {\n",name );
	printf("label = \"%s\"; name=\"%s\";\n",name,name);
	printf("URL=\"%s.html\";\n\n",name);

     
}
   
static int findChannel(Port p, int id) {
	Port p0;	
	
	p0 = p;
	do {
		if(p->id == id) {
				return p->channel;
		}		
		p=p->next;
	} while(p != p0);
	
	return -1;
}

static void genLinks(Model m) {   // [label="C Miss"];
	Stream f;
	Process src,snk;
	int channel=7;
	
	f=m->stream;
	while(f) {
		src=f->source;
		snk=f->sink;
			channel=findChannel(src->port,f->source_id); 
			if(f->bufsz<2) { 
#ifndef NO_PORTS			
				printf("\"%s\":%i -> \"%s\":%i [label=\"%i\",headlabel=\"%i\",taillabel=\"%i\",tooltip=\"%i\"];\n",
#else
				printf("\"%s\"  -> \"%s\"  [label=\"%i\",headlabel=\"%i\",taillabel=\"%i\",tooltip=\"%i\"];\n",
#endif				
					src->name,  
					snk->name,
					channel,
					f->sink_id,
					f->source_id,
					channel
					); 		
			} else {
#ifndef NO_PORTS			
				printf("\"%s\":%i -> \"%s\":%i [label=\"%i\"]\",headlabel=\"%i\",taillabel=\"%i\"", tooltip=\"%i[%i]\"];\n",
#else
				printf("\"%s\" -> \"%s\" [label=\"%i\",headlabel=\"%i\",taillabel=\"%i\",	tooltip=\"%i[%i]\"];\n",
#endif				
					src->name,  
					snk->name,
					channel,
					f->sink_id,
					f->source_id,
					channel, f->bufsz); 		
			}		
		f=f->next;
	}
}
	
static void genProcs(Process p) {
    
	while(p) {
			printf("#(%s %s.%s) %d ports\n",
				p->name, 			
				p->comp->path,
				p->comp->name,
				p->nportsIn + p->nportsOut
			);
 
		genProc(p->name,p->comp->name,p->comp->path,"taos_", p->arg);
#ifndef NO_PORTS	
	Port pt;			
	    pt = p->port;
			printf("|{");
			do {
				genPort(pt->id);
				pt=pt->next;
				if(pt != p->port ) {
					printf("|");
				}
			} while(pt != p->port);
        printf(" }");
#endif        
        printf(" }");
		endProc(); 
		
		p=p->next;
	}	
	
		
	printf("\n");
}	

void genGraph(Model model) {
	Stream f;
	Process p;
	
	
	
	if (!model) {
			fprintf(stderr,"swgo/FAIL: Missing model\n");
			exit(1);
	}
	
	assignChannels(model);
		
			//* Generate commented Reconstructed Network Definition */
	printf("#########   Expanded Network Definition   ######### \n");
	f=model->stream;

	while(f) {
			printf("# (%s %s.%s)%d <- %d(%s %s.%s) \n", 
				f->sink->name,
				f->sink->comp->path,
				f->sink->comp->name,
				f->sink_id, 
				f->source_id, 
				f->source->name,
				f->source->comp->path,
				f->source->comp->name
			);
				
		f=f->next;
	}
	
	printf("\n");	
	
				//* Generate Prefix code */
	genPrefix(model->name, model->nstreams);
	
	
	genCluster1( model->name );
		
		p=model->proc;  /* Get first process */
		genProcs(p); 
    P(        });    /* End Cluster1 */	

    
	genLinks(model); 
	genSuffix();	   //* Generate Suffix code */
}

/*    End of SWGRAPH.C  */

