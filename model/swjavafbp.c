/* SWjavafbp.C 
		  Generate JavaFBP Network Definition
		  
TODO: 
	. Everything  	  
*/
#include <stdio.h>
#include <stdlib.h>
#include "model.h"

#define P(s) printf("%s\n",(#s));
#define C(s) printf("%s,\n",(#s));

static void genSuffix() {
	
	printf("\n\n\n");
	 
	printf("\t\t}\n");
  	P(public static void main(String[] argv) throws Exception{ );             
    P(new xxxxxx().go(););
	printf("\t}\n}\n");
	
	printf("\n\n");
}


static void genPrefix(int nflows) {

	printf("\n\n\n\n");
	
	printf("//     JavaFBP %d dataflows\n",nflows);   
	printf("//     Generated by Streamwork/sw\n\n"); 
	P(public class xxxxxx extends Network {);
  	P(protected void define() {);
  	printf("\n\n\n");
	
}


static void genPort(int n) {
  		// printf("|<%i> %i", n, n);
}  	

static void genProc(char *name, char *comp, char *host) {

#ifdef GRAPHV
     printf("       \"%s\" ", name );
     C(                   [ shape=record);
     C(                  color="black" );
     printf("  URL=\".%s.shtml\"\n",name);
     printf(" host=\"%s\" \n", host);
     printf("label=\"{<P> %s|%s }",name,comp);
#endif 
 
}  	    

static void endProc() {
#ifdef GRAPHV
    printf("\"\n"); 
    printf("];\n"); // End proc 
    #endif
}

     
static void genCluster1(char *name) { 
 
#ifdef GRAPHV              
  printf("subgraph \"cluster%s\" {\n",name );
	printf("label = \"%s\"; name=\"%s\";\n",name,name);
	printf("URL=\"%s.shtml\";\n\n",name);
#endif
     
}
    

static void genLinks(Model m) {
	Flow f;
	Process src,snk;
	
	f=m->flow;
	
	while(f) {
		src=f->source;
		snk=f->sink;

    	printf("\tconnect(component(\"%s\",",src->comp->name);
    	printf("%s.class),port(\"OUT\"), \n",src->comp->path); 
  	    printf("\t        component(\"Collate\",Collate.class),port(\"IN\",0)); // array port\n\n");  
      
      
#ifdef GRAPHV			 
			printf("\"%s\":%i -> \"%s\":%i;\n",
					src->name, f->source_id, 
					snk->name,
					f->sink_id);
#endif	 		
		f=f->next;
	}

    
}

	
static void genProcs(Process p) {
	Port pt;	
    
	while(p) {
#ifdef GRAPHZ	
			printf("#(%s %s.%s) %d ports\n",
				p->name, 			
				p->comp->path,
				p->comp->name,
				p->nportsIn + p->nportsOut
			);
#endif	
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



void genJavaFBP(Model model) {
	Flow f;
	Process p;
	
	
	
	if (!model) {
			fprintf(stderr,"swgo/FAIL: Missing model\n");
			exit(1);
	}
	
		
			//* Generate commented Reconstructed Network Definition */
	// printf("#########   Expanded Network Definition   ######### \n");
	f=model->flow;

#ifdef CAN_COMMENT
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
#endif	
	
				//* Generate Prefix code */
	genPrefix(model->nflows);
	
	
	genCluster1("COLLATING NODE");
		
		p=model->proc;  /* Get first process */
		genProcs(p); 
    // P(        });    /* End Cluster1 */	

    
	genLinks(model); 
	genSuffix();	   //* Generate Suffix code */
}

/*    End of SWJAVAFBP.C  */

#ifdef EXAMPLE_JAVAFBP_ND 

/** https://www.jpaulmorrison.com/fbp/jsyntax.htm  
*/
public class xxxxxx extends Network {

  protected void define() {
  
    connect(component("Read Masters",Read.class),port("OUT"),
      component("Collate",Collate.class),port("IN",0)); // array port  
      
    connect(component("Read Details",Read.class),port("OUT"),
      component("Collate"),port("IN",1));// array port  
      
    connect(component("Collate"),port("OUT"),
      component("Process Merged Stream",Proc.class),port("IN"));  
      
    connect(component("Process Merged Stream"),port("OUTM"),
      component("Write New Masters",Write.class),port("IN"));  
      
    connect(component("Process Merged Stream"),port("OUTSE"),
      component("Summary & Errors",Report.class),port("IN"));
      
    initialize(new FileReader("c:\\mastfile"),
      component("Read Masters"),
      port("SOURCE"));
      
    initialize(new FileReader("c:\\detlfile"),
      component("Read Details"),
      port("SOURCE"));
      
    initialize(new FileWriter("c:\\newmast"),
      component("Write New Masters"),
      port("DESTINATION"));

    }

  public static void main(String[] argv) throws Exception{   
            
     new xxxxxx().go();
  }
}

#endif 