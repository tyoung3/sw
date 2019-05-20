/* SWGO.C 
		  Greate StreamWork Go program 
*/
#include <stdio.h>
#include <stdlib.h>
#include "nemod.h"


void genGo(Model mod) {
	Flow f;
	
	fprintf(stderr,"GenGo: %d flows.\n", mod->nflows);
	
	if (!mod) {
			fprintf(stderr,"swgo/FAIL: Missing model\n");
			exit(1);
	}
	
				//* Generate Prefix code */
				
				//* Generate Flow code */
	f=mod->flow;
	while(f) {
		printf("\n");		
		f=f->next;
	}
				//* Generate Suffix code */
}

