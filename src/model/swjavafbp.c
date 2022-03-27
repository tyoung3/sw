/** @file swjavafbp.c Generate Java code NOT IMPLEMENTED

  These @todoS are sw general, not swproject specific: 
  High Priority:
  
    @done localization  mkdocs first
    @done swgrapgh levels.
    @todo Fix defaultTypePath missing in config file.
        @todo fix null type path problem.
    @todo env variable to pass return code?
    @todo create document tree to model component html file hierarchy
    @todo web server component library 
    @todo string/line channel type component library
    @todo math channel type component library [w/plotting -- geogebra?]
    @todo automate github search for components
    @todo use $PATH and/or $GOPATH to find .sw files
    @todo Update project generation
        @todo Generate channel type definitions and stringify
	    @todo Send multiple(N option) IPs in go tests.
        @todo clean code
        @todo remove dead code
        @todo use templates
	    @todo eliminate unneeded go mod tidy commands
	    @todo If .github, do not generate project
        
    @todo Generate drawFBP format
        @todo Convert drawFBP format to SWL format
	    @todo Convert JPM's javaFBP NDs to SW NDs. https://jpaulm.github.io/fbp/jsyntax.htm
	Language changes:    
        @todo Make process parens optional
        @todo Inter-host stream sockets (IHSS component) and mocks.
	
    @todo Update fbp.twyoung.com web pages
	@todo Create Man pages w/Doxygen
 	@todo Create internal/html with module, package, function, and struct pages. Fix swgraph to find the pages.
 	@todo checkpoint restart
 	      IP save/restore; 
 	@todo Test on Windows
	
  Low Priority:	    
    @todo Compare SWL files;  ala git diff 
	@todo Use PACKAGE_NAME { key: value} format for generated .yaml files.
	@todo Add tests for all useful sw modes.
	@todo Verify output from make check & make distcheck
	@todo Security check:
		Protection from buffer overflow (and other malicious input).
		Limited data lifetime (clearing buffers and heap data)
		Protection from ownership conflicts. 
	@todo Plugins:
		https://pkg.go.dev/plugin 
	@todo Process command/config arguments. 
	@todo negative nimports and noutports in swgen.sh to prioritize ports and reduce the number of goroutines.
	@todo Fix swgen arguments w/default generation. Generate in config file
 	@todo Graph .ISW files (prevent 'no processes' message.
 	@todo Implement Process name expansion. Ex. "_MONITOR;" launches system monitor
 	          
 DONE: 
	
    @todo component docs to README
    @done fix sw.twyoung.com
    @done default channel type path.  
    @done README TOC
	@done Synopsis to README.md.in
	@done Document environment variable usage.  DEBUG/USER/HOME
	@done Show full path for .sw and .cfg files in generated commentary. 
    @done Structure streams swgo.c [/usr/local/src/hw example code]
          Added typed channels.  
	@done Design Project logo and publish.
    @done fix logo graph if necessary
    @done fix 'swgraph n1.sw'
    @done Remove obsolete github branches
    @done remove log.Fatal from packages [ no more found ]
        panic or return/log error instead
	@done Make config an option in project generation.
	@done Make JPM's FBPgo (fbpGO?) Check feasability. 
	@done Discuss differences from 'classic' FBP.
		FBP inspired: 	http://www.jpaulmorrison.com/fbp/noflo.html
		Lifetime: 	https://suif.stanford.edu/collective/taint.html
			Q. Does Go clear buffers at close?
		Ownership: 	https://www.egnyte.com/resource-center/governance-guides/data-ownership
    @done Installation w/Autotools
	@done Add PREFIX statement to prefix process names with a string. 
	@done Make generated test_.go's  deadlock safe. Test w/collate.sw
	@done Improve module location.  Standardize on .../sw/MODULE/pkg/.... | Is .../sw
	@done  Restore poc test
	@done  Type names inside arrows(stream direction indicators). 
	@done  Document more functions 
	@done  Allow git.hub, etc. imports.  Simplify .sw file requirements.
	@done Structure in module/modele package.  Pass struct instead of integers.
	@done Avoid duplicates in YAML config file.
	@done If component involved in a cycle, then subtask all sends and receives
	@done Subtask channel send/receive when more than two ports,  for deadlock prevention.
	@done Fix swgo [poc]
	
 SHELVED:
	@shelved Wait on multiple inputs for example and deadlock prevention in ...test_.go files. -> or <- to diffferentiate.
	@shelved Generate Init function w/commentary
	@shelved Update .yaml file instead of replacing it.  Do not erase prev config.
	@shelved Blue/Gold code generation for deadlock prevention	
	@shelved output Buffer > 0  filtercode generation for deadlock prevention
 

Dumped:	
 	@dumped Generate project examples.
	    @dumped Fix swproject.sh/postage type error. [Works now]
        @dumped Make channels uni-directional [Makes no sense]
            
**/
 
#include <stdio.h>
#include <stdlib.h>
#include "sw.h"
#include "model.h"

#ifndef INCORPORATED
void genJavaFBP(Model m) {m=m;}
#else

#define P(s) printf("%s\n",(#s));
#define C(s) printf("%s,\n",(#s));

/** @todo swjavafbp fix todos. */
static void genSuffix() {
	
	printf("\n\n\n");
	 
	printf("\t\t}\n");
  	P(public static void main(String[] argv) throws Exception{ );             
    P(new xxxxxx().go(););
	printf("\t}\n}\n");
	
	printf("\n\n");
}


static void genPrefix(int nstreams) {

	printf("\n\n\n\n");
	
	printf("//     JavaFBP %d datastreams\n",nstreams);   
	printf("//     Generated by Streamwork/sw\n\n"); 
	P(public class xxxxxx extends Network {);
  	P(protected void define() {);
  	printf("\n\n\n");
	
}

#define genPort(X) 
//static void genPort(int n) {
//  		// printf("|<%i> %i", n, n);
//}  	
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
	Stream f;
	Process src;
	
	f=m->stream;
	
	while(f) {
		src=f->source;
		// snk=f->sink;

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
	Stream f;
	Process p;
		
			//* Generate commented Reconstructed Network Definition */
	// printf("#########   Expanded Network Definition   ######### \n");
	f=model->stream;

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
	genPrefix(model->nstreams);
	
	
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
#endif  //  #ifdef INCORPORATED 

#endif 
static void NeededForTodos() {
    printf("Dummy function\n");
}
