#ifndef MODEL_H
#define MODEL_H


#include "Absyn.h"

/*          Network  Model
 
	 Model > Stream > Source_Process > Port > Port 
	 			 	Sink_Process   > Port > Port
	                Process        > Component
				    Process        > Process
*/

/*    MODEL  Structures   */

typedef enum {NONE,GOIP,OTHER} STREAMTYPE;
struct Component_ {
		String name;   // First letter Upper Case. No slashes    
		String path;   // Ex. github/tyoung3/streamwork/std 
		int    nports;
		struct Component_ *next;
		struct Component_ *prev;	
} Component_;
typedef struct Component_ *Component;

struct Port_ {
	int id; 
	int channel;  /* Go Channel Number */	
	String name;
	struct Port_ *match;
	struct Port_ *next;
	struct Port_ *prev;
	//Process_ struct *owner;   ?? Circular
} Port_;
typedef struct Port_ *Port;
		
struct Process_ {
		String name;
		Component comp;    		  
		Port  port; 	      /* Port list */
		int  nportsIn;
		int  nportsOut;
		int  ch;			/* Low channel number */
		int  sink_id;
		int  source_id;
		struct Process_ *next;
		struct Process_ *prev;    
		char **arg;		  /* An array of strings. */
} Process_; 
typedef struct Process_ *Process;

struct Stream_ {
	Process source;
	Process sink;
	int source_id; 	
	int sink_id; 	
	int bufsz; 
	STREAMTYPE type;    /* Type of Stream GOGO, ORPHAN, etc*/
	struct Stream_ *next;
	struct Stream_ *prev;
} Stream_;
typedef struct Stream_ *Stream;

struct Model_ {
	int nflows;
	int ncomponents;
	int nprocs; 		/* number of processes */
	Stream flow;			/* pointer to first stream*/
	Process proc;		/* First Process */
} Model_;
typedef struct Model_ *Model;

/*   End of MODEL  Structures   */

#endif  // MODEL_H
