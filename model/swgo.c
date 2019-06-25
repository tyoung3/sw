/* SWGO.C 
		  Greate StreamWork Go program 
		  
TODO: 
*/
#include <stdio.h>
#include <stdlib.h>
#include "swsym.h"
#include "model.h"
#include "sw.h"

#define P(s) printf("%s\n",(#s));
#define C(s) printf("%s",(#s));

//* Generate Suffix code */
void genSuffix() {

	P(wg.Wait());
	printf("}\n");
}

static void genPath(char *s) {
	char *importPath={"github.com/tyoung3/streamwork"};	

	if(s==NULL) {
		printf("import \"%s/fbp\"\n",importPath);
	} else {	
		printf("import \"%s/%s\"\n",importPath,s);
	}

}

int newPath(char *p) {

	if(getPath(p) ==1) 
		return 1;
		
	return 0;	
}
	
static void genPaths(Model m) {
	Process p;
		
	// P(import "fmt");
	P(import "sync");
	
	genPath(NULL);

	p=m->proc;
	while (p) {
		if( newPath(p->comp->path) ) {
			genPath(p->comp->path);
		}	
		p=p->next;
 	} ;

	printf("\n\n");
}	



static Port findPort(Process p, int id) {
	Port pt=p->port;
	Port pt0=pt;
	
	
	do  {
		if(pt->id == id) {					
			return pt;
		}	
		pt=pt->next;
	} 	while(pt != pt0);
	 
	sprintf(fbfr,"Process %s Port %i mismatch\n",
		p->name, id);
	FAIL(findPort,fbfr);
}

static void showArgs(Process p) {
	int i=1;
	
	if(!p->arg) 
			return;
			
	while(p->arg[i] != NULL) {
		printf(" \"%s\"",p->arg[i]);
		i++;
	}	

	
}
static void showSink(Process p, int id) {	
		
			printf("(%s %s.%s ",
				p->name,
				p->comp->path,
				p->comp->name
				);
				
			showArgs(p);	
			
			
			printf(")%d ",id);
}			

static void showSource(Process p, int id, int bfsz) {		
		
		if(bfsz == cfg.defBufferSize) {
			printf("\t\t<- %d(%s %s.%s", 
				id, 
				p->name,
				p->comp->path,
				p->comp->name
			);
		} else {
			printf("\t\t<%d- %d(%s %s.%s",
				bfsz, 
				id, 
				p->name,
				p->comp->path,
				p->comp->name
			);
		}
			
			showArgs(p);
			printf(");\t\n");
}			

static int assign_channel(int ch, Stream f) {
		
		findPort(f->source,f->source_id)->channel=ch;
		findPort(f->sink,  f->sink_id) ->channel=ch;
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
static void showND(Model m) {	
	Stream f;
				
			//* Generate commented Reconstructed Network Definition */
	printf("/***********   Expanded Network Definition   **********   \n");
	f=m->stream;
	assignChannels(m);
	
	while(f) {
		if( f->source->kind==IS_NET) {
			showSink(f->sink, f->sink_id);	
			showSource(f->source,f->source_id,f->bufsz);
		}	
		f=f->next;
	}
	
	printf(
	  "# %d streams, %d processes, %d components, %d partitions.\n",
			m->nstreams, 
			m->nprocs, 
			m->ncomponents,
			m->nprocs - m->nstreams);
	printf(
	"*********************************************/\n");
}	
//* Generate Prefix code */
void genPrefix(Model m) {
	int nstreams=m->nstreams;
	int bfrtbl[m->nstreams + 10];	
	int i;
	Stream f=m->stream; 

	P(package main);
	printf("\n/");
	C(* StreamWork Go code.  Generated by swgo.c)
 	 
 	printf("-%s\n*/\n",version); 
	printf("\n");
	showND(m);  			/* Show commented ND */
	printf("\n");

	genPaths(m);

	P(func main() {);
		printf("	var cs []chan interface{}\n	");
		P(	var wg sync.WaitGroup);
	printf("\n");
	
	f=m->stream;
	i=0;
	while(f) {
		bfrtbl[nstreams - i++ - 1 ] = f->bufsz;
		f=f->next;
	}	
	i=0;
	f=m->stream;  
	while(i<nstreams) {
		if(bfrtbl[i]>0) {
			printf("cs = append(cs,make(chan interface{},%i))\n",
					bfrtbl[i]);
		} else {
			printf("cs = append(cs,make(chan interface{}))\n");
		}		
		i++;
	}		
	printf("\n");
}

static int needaSlice(Port pt) {
	Port pt0=pt;
	int  ch; 
	
	ch = pt->channel;
	pt = pt->next;
	
	do {
		if(pt->channel!=++ch) {
			return 1;
		}
		pt=pt->next;
	} while (pt != pt0);
	return 0;
}

	/* Generate a slice of channels for this process */			
static void makeChSlice(Process p, int nstreams) {			
	char *name;
	Port pt;
	
	name=p->name;
	printf("\n\tvar cs_%s []chan interface{}\n",name);
	printf(  "\tfor i:=0; i<%i; i++ {\n\t\t", nstreams); 
	printf("cs_%s=append(cs_%s, make(chan interface{},2))",
				name,name
				);
	printf("\n\t}\n");
	
	pt=p->port;
	do		{
		printf("\tcs_%s[%i] = cs[%i]\n",
			name,pt->id,pt->channel);
		pt=pt->next;
	} while (pt != p->port);
}			

static void	genLaunch1(Process p) {
	int i=1;
	
				printf("fbp.Launch(&wg,");
				printf("[]string{\"%s\"",p->name); 
				
				if(p->arg) {
					while(p->arg[i]) {
						printf(",\"%s\"",p->arg[i]);
						i++;
					}
				}
				printf("},\t%9s.%s, ",		
					p->comp->path,
					p->comp->name);
								
}					

static void genLaunches(Process p) {	
	int ch;   /* Assigned channel */
	int nstreams;
    int ch0;  /* initial channel index */
    
	while(p) {
   		nstreams=p->nportsIn + p->nportsOut;
		if( nstreams > 1 ) {
			if(needaSlice(p->port))  { 
				makeChSlice(p, nstreams);
				genLaunch1(p);
				printf("cs_%s[0:%i])\n",
					p->name,	
					nstreams
				);		
			} else {
				genLaunch1(p);
				ch0=p->port->channel;
				printf("cs[%i:%i])\n",
					ch0,
					ch0+nstreams
				);				
			}		
		} else {
			ch = p->port->channel;	
			genLaunch1(p);
			printf("cs[%i:%i])\n",
				ch,ch+1	
			);		
		}		
		p=p->next;
	}	
	
	printf("\n");
}	

		
void genGo(Model model) {
	Process p;
		
	
	genPrefix(model);  		    /* Generate Prefix code */
	p=model->proc;  			/* Get first process    */
	genLaunches(p); 			/* Expand processes     */ 
	genSuffix();				/* Generate Suffix code */
}

/* Generate Expanded Network Definition */
void genND(Model mod) {
	Stream f;
	
				//* Generate Prefix code */
	printf("StreamWork Network Definition.  Generated by sw-%s. \n",version);				
				
	f=mod->stream;
	while(f) {
		if ( f->sink->port->id )
			printf("(%s)%d<-%d(%s); \n", f->sink->name,f->sink->port->id, f->source->port->id, f->source->name);
		else 
			printf(" (%s)%d<-(%s); \n", f->sink->name, f->source->port->id, f->source->name);		
				
		f=f->next;
	}
				
}

/***************   End of SWGO.C   ********************/
#ifdef GO_EXAMPLE 
package  main

/* /home/tyoung3/go/mod/fbp/comp2/comp2_test.go
 *		 Streamworks  	 
 *		generated by fbpgo.sh-v0.0.1  on Wed May  8 15:47:11 EDT 2019
*******************************************************/

import "fmt"
import "sync"
import "github.com/tyoung3/streamwork/fbp"
import "github.com/tyoung3/streamwork/poc"


func main() {
	var cs []chan interface{}
	var wg sync.WaitGroup
	
	fmt.Println("Testgo Start")
	cs = append(cs, make(chan interface{}))

	fbp.Launch(&wg, []string{"Testgo"}, poc.Print1, cs)
	fbp.Launch(&wg, []string{"Comp1","11"}, pod.Gen1, cs)
	wg.Wait()
	fmt.Println("Testgo end")
}
#endif
