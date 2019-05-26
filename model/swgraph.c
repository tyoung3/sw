/* SWGRAPH.C 
		  Generate Graphviz input 
		  
TODO:   
*/
#include <stdio.h>
#include <stdlib.h>
#include "model.h"

#define P(s) printf("%s\n",(#s));
#define C(s) printf("%s,\n",(#s));


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
static int assign_channel(int ch, Flow f) {
		
		findPort(f->source->port,f->source_id)->channel=ch;
		findPort(f->sink->port,  f->sink_id) ->channel=ch;
		return ch;
}
	
static void assignChannels(Model m) {
	int ch=m->nflows-1;
	Flow f=m->flow;
	
	while(f) {
		assign_channel(ch--,f);	
		f=f->next;
	}	
}

/////////////////////////////////////////////////

static void genSuffix() {

	 
	printf("}\n");
}

static void genPrefix(int nflows) {


	printf("#Prefix here. %d flows\n",nflows);
	P(digraph g {);
	P(graph [);
		C(	name="Streamwork: Collate Example Graph" );
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
               C(     edge [ color=green);
              C(              style=bold);
            C(                fontsize="18");
              C(              fontcolor=black);
               P(     ]);

}

#ifdef OLDSTUFF
static void genEdit() {
    P(        "EDIT" );
    C(                [ shape=record);
    C(                  color="black");
    C(                  URL="EDIT.shtml");
    C(                  host="nogales");
    P(  label="{<P> EDIT);|swedit}|<0> 0|<7 > 7 |<6> 6|<5 > 5 "];);
   
}
#endif

static void genPort(int n) {
  		printf("<%i> %i  ", n, n);
}  	

static void genArgs(char **a) {
		int i=1;
		
		while(a[i] != NULL) {
			printf(" \\\"%s\\\"", a[i++]);
		}
}

	/* EXAMPLE: label="{<P> G1 Gen1 \"xyz\" |{<0> 0 |<1> 1 } }"  */
static void genProc(char *name, char *comp, char *host, char **args) {

     printf("       \"%s\" ", name );
     C(                   [ shape=record);
     C(                  color="black" );
     printf("  URL=\".%s.shtml\"\n",name);
     printf(" host=\"%s\" \n", host);
     printf("label=\"{<P> %s %s",name,comp);
     genArgs(args);
  
}  	    
 

static void endProc() {
    printf("\"\n"); 
    printf("];\n"); // End proc 
}

     
static void genCluster1(char *name) { 
               
  printf("subgraph \"cluster%s\" {\n",name );
	printf("label = \"%s\"; name=\"%s\";\n",name,name);
	printf("URL=\"%s.shtml\";\n\n",name);

     
}
    
#ifdef OLDSTUF    
static void genSAVE() {
    P(        "SAVE" );
    C(                     [ shape=record);
    C(                       URL="SAVE.shtml");
    C(                       color="black" );
    C(                       host="taos");
    P(                       label="{<P> SAVE|WriteFile }|<in> in"];);
}

static void genTaos() {        
    P(subgraph "clustertaos" { );
     P(        label = "taos"; name="taos";);
    P(        URL="taos.html";);
		genSAVE();
    P(        });
 }   
#endif 
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
	Flow f;
	Process src,snk;
	int channel=7;
	
	f=m->flow;
	while(f) {
		src=f->source;
		snk=f->sink;
			channel=findChannel(src->port,f->source_id); 
			if(f->bufsz<2) { 
				printf("\"%s\":%i -> \"%s\":%i [label=\"%i\"];\n",
					src->name, f->source_id, 
					snk->name,
					f->sink_id,
					channel); 		
			} else {
				printf("\"%s\":%i -> \"%s\":%i [label=\"%i[%i]\"];\n",
					src->name, f->source_id, 
					snk->name,
					f->sink_id,
					channel,
					f->bufsz
					); 		
			}		
		f=f->next;
	}

#ifdef GENOLD_STUFF	
    P({ "PANEL":1  -> "EDIT":0;  headurl="pe10.shtml";});
    P("EDIT":7  -> "SAVE":in;);
    P("EDIT":5  -> "PANEL":0;);
#endif
    
}


	
static void genProcs(Process p) {
	Port pt;	
    
	while(p) {
			printf("#(%s %s.%s) %d ports\n",
				p->name, 			
				p->comp->path,
				p->comp->name,
				p->nportsIn + p->nportsOut
			);
 
		genProc(p->name,p->comp->name,"taos_", p->arg);
			pt = p->port;
			printf("|{");
			do {
				genPort(pt->id);
				pt=pt->next;
				if(pt != p->port ) {
					printf("|");
				}
			} while(pt != p->port);
        printf(" }}");
		endProc(); 
		
		p=p->next;
	}	
	
		
	printf("\n");
}	



void genGraph(Model model) {
	Flow f;
	Process p;
	
	
	
	if (!model) {
			fprintf(stderr,"swgo/FAIL: Missing model\n");
			exit(1);
	}
	
	assignChannels(model);
		
			//* Generate commented Reconstructed Network Definition */
	printf("#########   Expanded Network Definition   ######### \n");
	f=model->flow;

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
	genPrefix(model->nflows);
	
	
	genCluster1("COLLATING NODE");
		
		p=model->proc;  /* Get first process */
		genProcs(p); 
    P(        });    /* End Cluster1 */	

#ifdef GENOLD_STUFF	
	genCluster1("OLDhost");
		genProc("PANEL", "Pcomp","PnlHost");
			genPort(0);
			genPort(2);
			genPort(1);
		endProc(); 
		genEdit();
		genSAVE();
    P(        });    /* End Cluster1 */	
#endif
    
	genLinks(model); 
	genSuffix();	   //* Generate Suffix code */
}

/*    End of SWGRAPH.C  */

#ifdef EXAMPLE_GRAPH
digraph g {
	graph [
		name="Collate Example Graph",
 		style=bold,
 		color=green,
 		margin="2",
   		rankdir="TB",
#   		rankdir="LR",
 		ranksep=0.75,
 		nodesep=0.75,
 		size="8,11",
 		center=1,
 		fontsize="24",
  		fontcolor=green,
 		fontname="Helvetica"
		URL="/home/tyoung3/vdfd/bin/html/g.html"
 	   ]
 		node [  shape=record,
 			fontsize="18",
 	        	fontcolor=green,
 		       	fontname="Helvetica",
			color=green,
         		fillcolor=tan,
         		style=filled,
 	        	height=.2
     		 ];
 		edge [ color=green,
         		style=bold,
 			fontsize="18",
 	        	fontcolor=green,
      		]
 	


  subgraph "clustertaos" { 
	 label = "taos"; name="taos";
	URL="taos.html";
	"PANEL" 
					[ shape=record,
					color="green", 
					URL="./PANEL.shtml",
 					host="taos",
					label="{<P> PANEL|GC.tcl }|<1 > 1 |<0> 0"];
	}

  subgraph "clusternogales" { 
	 label = "nogales"; name="nogales";
	URL="nogales.shtml";

	"EDIT" 
					[ shape=record,
					color="green", 
					URL="EDIT.shtml",
 					host="nogales",
					label="{<P> EDIT|swedit}|<0> 0|<7 > 7 |<6> 6|<5 > 5 "];
	"SAVE" 
					[ shape=record,
					URL="SAVE.shtml",
					color="green", 
 					host="nogales",
					label="{<P> SAVE|WriteFile }|<in> in"];
					
	"/dev/null" [  
					shape=record,
 					host="nogales",
					URL="_dev_null.shtml",
					label="<F> /dev/null", 
					fillcolor=limegreen ];
  }
{ "PANEL":1  -> "EDIT":0;  headurl="pe10.shtml";}
"EDIT":7  -> "SAVE":in;
"EDIT":6 -> "/dev/null";
"EDIT":5  -> "PANEL":0;
}
#endif 
