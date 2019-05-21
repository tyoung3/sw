/* SWGRAPH.C 
		  Generate Graphviz input 
		  
TODO: 
	. Everything  	  
*/
#include <stdio.h>
#include <stdlib.h>
#include "nemod.h"

#define P(s) printf("%s\n",(#s));
#define C(s) printf("%s,\n",(#s));
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
                   C(         fillcolor=tan);
                  C(          style=filled);
                    P(        height=.2);
                  P(   ];);
               C(     edge [ color=black);
              C(              style=bold);
            C(                fontsize="18");
              C(              fontcolor=black);
               P(     ]);

}


static void genEdit() {
    P(        "EDIT" );
    C(                [ shape=record);
    C(                  color="black");
    C(                  URL="EDIT.shtml");
    C(                  host="nogales");
    P(  label="{<P> EDIT);|swedit}|<0> 0|<7 > 7 |<6> 6|<5 > 5 "];);
   
}

static void genPort(int n) {
  		printf("|<%i> %i", n, n);
}  	

static void genProc(char *name, char *comp, char *host) {

     printf("       \"%s\" ", name );
     C(                   [ shape=record);
     C(                  color="black" );
     printf("  URL=\".%s.shtml\"\n",name);
     printf(" host=\"%s\" \n", host);
     printf("label=\"{<P> %s|%s }",name,comp);
  
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
    
static void genSAVE() {
    P(        "SAVE" );
    C(                     [ shape=record);
    C(                       URL="SAVE.shtml");
    C(                       color="black" );
    C(                       host="taos");
    P(                       label="{<P> SAVE|WriteFile }|<in> in"];);
}

#ifdef GENTAOS
static void genTaos() {        
    P(subgraph "clustertaos" { );
     P(        label = "taos"; name="taos";);
    P(        URL="taos.html";);
		genSAVE();
    P(        });
 }   
#endif 

static void genLinks(Model m) {
	Flow f;
	Process src,snk;
	
	f=m->flow;
	
	while(f) {
		src=f->source;
		snk=f->sink;
			 
			printf("\"%s\":%i -> \"%s\":%i;\n",
					src->name, f->source_id, 
					snk->name,
					f->sink_id);
	 		
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
	
		genProc(p->name,p->comp->name,"taos_");
			pt = p->port;
			do {
				genPort(pt->id);
				pt=pt->next;
			} while(pt != p->port);
		endProc(); 
		
		p=p->next;
	}	
	
		
	printf("\n");
}	



void genGraph(Model nemod) {
	Flow f;
	Process p;
	
	
	
	if (!nemod) {
			fprintf(stderr,"swgo/FAIL: Missing model\n");
			exit(1);
	}
	
		
		
			//* Generate commented Reconstructed Network Definition */
	printf("#########   Expanded Network Definition   ######### \n");
	f=nemod->flow;

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
	genPrefix(nemod->nflows);
	
	
	genCluster1("COLLATING NODE");
		
		p=nemod->proc;  /* Get first process */
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
    
	genLinks(nemod); 
	genSuffix();	   //* Generate Suffix code */
}

/*    End of SWGRAPH.C  */

#ifdef EXAMPLE_GRAPH
digraph g {
	graph [
		name="Collate Example Graph",
 		style=bold,
 		color=black,
 		margin="2",
   		rankdir="TB",
#   		rankdir="LR",
 		ranksep=0.75,
 		nodesep=0.75,
 		size="8,11",
 		center=1,
 		fontsize="24",
  		fontcolor=black,
 		fontname="Helvetica"
		URL="/home/tyoung3/vdfd/bin/html/g.html"
 	   ]
 		node [  shape=record,
 			fontsize="18",
 	        	fontcolor=black,
 		       	fontname="Helvetica",
			color=black,
         		fillcolor=tan,
         		style=filled,
 	        	height=.2
     		 ];
 		edge [ color=black,
         		style=bold,
 			fontsize="18",
 	        	fontcolor=black,
      		]
 	


  subgraph "clustertaos" { 
	 label = "taos"; name="taos";
	URL="taos.html";
	"PANEL" 
					[ shape=record,
					color="black", 
					URL="./PANEL.shtml",
 					host="taos",
					label="{<P> PANEL|GC.tcl }|<1 > 1 |<0> 0"];
	}

  subgraph "clusternogales" { 
	 label = "nogales"; name="nogales";
	URL="nogales.shtml";

	"EDIT" 
					[ shape=record,
					color="black", 
					URL="EDIT.shtml",
 					host="nogales",
					label="{<P> EDIT|swedit}|<0> 0|<7 > 7 |<6> 6|<5 > 5 "];
	"SAVE" 
					[ shape=record,
					URL="SAVE.shtml",
					color="black", 
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
