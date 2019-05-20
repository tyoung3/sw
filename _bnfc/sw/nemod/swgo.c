/* SWGO.C 
		  Greate StreamWork Go program 
*/
#include <stdio.h>
#include <stdlib.h>
#include "nemod.h"

#define P(s) printf("%s\n",(#s));
void genSuffix() {

	P(wg.Wait());
	printf("}\n");
}

void genPrefix(int nflows) {

	P(package main);
	printf("\n/");
	P(*		 	 DO NOT EDIT!!!
 *		generated by sw 
**/);

	printf("\n");
	P(import "fmt");
	P(import "sync");
	P(import "github.com/tyoung3/streamwork");
	P(import "github.com/tyoung3/streamwork/strings");
	printf("\n\n");

	P(func main() {);
		P(	var cs []chan interface{});
		P(	var wg sync.WaitGroup);
	printf("\n\t");
	
	P(fmt.Println("StreamWork Proof of Concept Example."));
	
	printf("\tfor i:=0; i<%i; i++ {\n\t\t", nflows); 
	P(cs = append(cs, make(chan interface{})));
	printf("\t}\n\n");
}
	
void genLaunches(Flow f) {	
    int cn=0;   /* Channel number */
    
	while(f) {
			printf("fbp.Launch(&wg,");
			printf(" []string{\"%s\"}",f->sink->name); 
			printf(", %s.%s, cs[%i:%i])\n",			
				f->sink->comp->path,
				f->sink->comp->name,
				cn, cn+1
			);
	
			printf("fbp.Launch(&wg,");
			printf(" []string{\"%s\"}",f->source->name); 
			printf(", %s.%s, cs[%i:%i])\n",
				f->source->comp->path,
				f->source->comp->name, 
				cn, cn+1
			);
			cn++;
		f=f->next;
	}	
	printf("\n");
}	

void genGo(Model nemod) {
	Flow f;
	
				//* Generate Prefix code */
	genPrefix(nemod->nflows);
	
	if (!nemod) {
			fprintf(stderr,"swgo/FAIL: Missing model\n");
			exit(1);
	}
	
				
			//* Generate commented Reconstructed Network Definition */
	f=nemod->flow;
	while(f) {
			printf("/* (%s %s.%s)%d <- %d(%s %s.%s) */\n", 
				f->sink->name,
				f->sink->comp->path,
				f->sink->comp->name,
				f->sink->port->id, 
				f->source->port->id, 
				f->source->name,
				f->source->comp->path,
				f->source->comp->name
			);
				
		f=f->next;
	}
	printf("\n");
	
		
				//* Generate Flow Code */
	f=nemod->flow;
	genLaunches(f); 

	
				//* Generate Suffix code */
	genSuffix();
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
				//* Generate Suffix code */
}

#ifdef GO_EXAMPLE 
package  main

/* /home/tyoung3/go/mod/fbp/comp2/comp2_test.go
 *		 	 DO NOT EDIT!!!
 *		generated by fbpgo.sh-v0.0.1  on Wed May  8 15:47:11 EDT 2019
**/

import "fmt"
import "sync"
import "github.com/tyoung3/streamwork"
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
