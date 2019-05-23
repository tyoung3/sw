/* SWGO.C 
		  Greate StreamWork Go program 
		  
TODO: 
	. fix argument strings
	. Make collate work 		  
*/
#include <stdio.h>
#include <stdlib.h>
#include "swsym.h"
#include "nemod.h"

#define P(s) printf("%s\n",(#s));

//* Generate Suffix code */
void genSuffix() {

	P(wg.Wait());
	printf("}\n");
}

static void genPath(char *s) {
	char *importPath={"github.com/tyoung3/streamwork"};	

	if(s==NULL) {
		printf("import \"%s\"\n",importPath);
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
		
	P(import "fmt");
	P(import "sync");
	
	genPath(NULL);

	p=m->proc;
	do {
		if( newPath(p->comp->path) ) {
			genPath(p->comp->path);
		}	
		p=p->next;
 	} while (p);

	printf("\n\n");
}	

//* Generate Prefix code */
void genPrefix(Model m) {
	int nflows=m->nflows;	 

	P(package main);
	printf("\n/");
	P(*		 	 DO NOT EDIT!!!
 *		generated by sw/swgo.c 
**/);

	printf("\n");

	genPaths(m);

	P(func main() {);
		P(	var cs []chan interface{});
		P(	var wg sync.WaitGroup);
	printf("\n\t");
	
	P(fmt.Println("StreamWork Proof of Concept Example."));
	
	printf("\n\tfor i:=0; i<%i; i++ {\n\t\t", nflows); 
	P(cs = append(cs, make(chan interface{})));
	printf("\t}\n\n");
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
static void makeChSlice(Process p, int nflows) {			
	char *name;
	Port pt;
	
	name=p->name;
	printf("\n\tfor i:=0; i<%i; i++ {\n\t\t", nflows); 
	printf("cs_%s:=append(cs_%s, make(chan interface{}))",
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

void genLaunches(Process p) {	
	int ch;   /* Assigned channel */
	int nflows;
    
	while(p) {
   		nflows=p->nportsIn + p->nportsOut;
		if( nflows > 1 ) {
			if(needaSlice(p->port))  { 
				makeChSlice(p, nflows);
				printf("fbp.Launch(&wg,");
				printf("[]string{\"%s\"}",p->name); 
				printf(",\t%9s.%s, ",		
					p->comp->path,
					p->comp->name);
				printf("\tcs_%s[0:%i])\n",
					p->name,	
					nflows
				);		
			} else {
				printf("fbp.Launch(&wg,");
				printf("[]string{\"%s\"}",p->name); 
				printf(",\t%9s.%s, ",		
					p->comp->path,
					p->comp->name);
				printf("cs[0:%i])\n",
					nflows
				);				
			}		
		} else {
			ch = p->port->channel;	
			printf("fbp.Launch(&wg,");
			printf("[]string{\"%s\"}",p->name); 
			printf(",\t%9s.%s, ",		
				p->comp->path,
				p->comp->name);
			printf("cs[%i:%i])\n",
				ch,ch+1	
			);		
		}		
		p=p->next;
	}	
	
	printf("\n");
}	

#ifdef ALLOCATECH
static void allocateChannels( Model nemod) {
	Process p;
	int cha=0;  // current channel allocation
	
	p= nemod->proc;
	while(p) {
			if(p->nportsOut > 0) {  /* This is nbr source ports */ 
				 p->ch =cha;  
				 cha+=p->nportsOut;	
			}
			p=p->next;
	}
	 
}
#endif 

Port findPort(Port pt, int id) {
	
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
	
static void showND(Model nemod) {	
	Flow f;
	int ch=nemod->nflows-1;
				
			//* Generate commented Reconstructed Network Definition */
	printf("/*       Network Definition  */\n");
	f=nemod->flow;
	while(f) {
			assign_channel(ch--,f);	
			printf("/* (%s %s.%s)%d <- %d(%s %s.%s) */\n", 
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
}	
		
void genGo(Model nemod) {
	Process p;
		
	if (!nemod) {
			fprintf(stderr,"swgo/FAIL: Missing model\n");
			exit(1);
	}
	
	genPrefix(nemod);  	/* Generate Prefix code */
	showND(nemod);  			/* Show commented ND    */	
	p=nemod->proc;  			/* Get first process    */
	genLaunches(p); 			/* Expand processes     */ 
	genSuffix();				/* Generate Suffix code */
}

/* Generate Expanded Network Definition */
void genND(Model mod) {
	Flow f;
	
	//fprintf(stderr,"GenGo: %d flows.\n", mod->nflows);
	
	if (!mod) {
			fprintf(stderr,"swgo/FAIL: Missing model\n");
			exit(1);
	}
	
				//* Generate Prefix code */
	printf("StreamWork Network Definition.  Generated by sw. \n");				
				
				//* Generate  Network Definition */
	f=mod->flow;
	while(f) {
		if ( f->sink->port->id )
			printf("(%s)%d<-%d(%s) \n", f->sink->name,f->sink->port->id, f->source->port->id, f->source->name);
		else 
			printf(" (%s)%d<-(%s) \n", f->sink->name, f->source->port->id, f->source->name);		
				
		f=f->next;
	}
				
}

/***************   End of SWGO.C   ********************/
#ifdef GO_EXAMPLE 
package  main

/* /home/tyoung3/go/mod/fbp/comp2/comp2_test.go
 *		 	 DO NOT EDIT!!!
 *		generated by fbpgo.sh-v0.0.1  on Wed May  8 15:47:11 EDT 2019
**/

import "fmt"
import "sync"
import "github.com/tyoung3/streamwork"
import "github.com/tyoung3/streamwork/std"
import "github.com/tyoung3/streamwork/strings"


func main() {
	var cs []chan interface{}
	var wg sync.WaitGroup
	
	fmt.Println("Testgo Start")
	cs = append(cs, make(chan interface{}))

	fbp.Launch(&wg, []string{"Testgo"}, strings.Print1, cs)
	fbp.Launch(&wg, []string{"Comp1","11"}, strings.Gen1, cs)
	wg.Wait()
	fmt.Println("Testgo end")
}
#endif
