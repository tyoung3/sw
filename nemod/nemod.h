#ifndef nemod_h_
#define nemod_h_


#include "Absyn.h"

/*          Network  Model
 
	 Model > Flow > Source_Process > Port > Port 
	 			 	Sink_Process   > Port > Port
	                Process        > Component
				    Process        > Process
*/

/*    NEMOD  Structures   */

typedef enum {NONE,GOGO,OTHER} FLOWTYPE;
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
	struct Port_ *match;
	struct Port_ *next;
	struct Port_ *prev;
	//Process_ struct *owner;   ?? Circular
} Port_;
typedef struct Port_ *Port;
		
struct Process_ {
		String name;
		Component comp;    
		// ArgList arg;
		Port   port; 	      /* Port list */
		int  nportsIn;
		int  nportsOut;
		int  ch;			/* Low channel number */
		int  sink_id;
		int  source_id;
		struct Process_ *next;
		struct Process_ *prev;    
} Process_; 
typedef struct Process_ *Process;

struct Flow_ {
	Process source;
	Process sink;
	int source_id; 	
	int sink_id; 	
	FLOWTYPE type;    /* Type of flow GOGO, ORPHAN, etc*/
	struct Flow_ *next;
	struct Flow_ *prev;
} Flow_;
typedef struct Flow_ *Flow;

struct Model_ {
	int nflows;
	int ncomponents;
	int nprocs; 		/* number of processes */
	Flow flow;			/* pointer to first flow */
	Process proc;		/* First Process */
} Model_;
typedef struct Model_ *Model;

/*   End of NEMOD  Structures   */

#endif  // nemod_h_
