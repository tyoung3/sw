#ifndef MODEL_H
#define MODEL_H

#include "../bnfc/Absyn.h"
#include "../bnfc/Parser.h"
#include "../bnfc/Printer.h"

/*          Network  Model
 
	 Model > Stream > Source_Process > Port > Port 
	 			 	Sink_Process   > Port > Port
	                Process        > Component
				    Process        > Process
*/

/*    MODEL  Structures   */

typedef enum {IS_NET, IS_SUB} STATE;
typedef enum {NONE,GOIP,SUBNET,OTHER} KINDOF;

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
		STATE kind;	  /* In subnet or net */
} Process_; 
typedef struct Process_ *Process;

struct Stream_ {
	Process source;
	Process sink;
	int source_id; 	
	int sink_id; 	
	int bufsz; 
	STATE  state;    /* Type of Stream GOIP, SUBNET,  etc*/
	struct Stream_ *next;
	struct Stream_ *prev;
} Stream_;
typedef struct Stream_ *Stream;

typedef enum {SINK,SOURCE} PortType;
struct Extport_ {
	PortType type;
	Process souce;
	Process sink;
	int source_id; 	
	int sink_id; 	
	struct Extport_ *next;
} Extport_;
typedef struct Extport_ *Extport;


struct MSubnet_ {     /* Model Subnet */
	char *name;
	Stream  stream;	
	Extport extport;
	struct MSubnet_ *next;
};
typedef struct MSubnet_ *MSubnet;

struct Model_ {
	int nstreams;
	int ncomponents;
	int nprocs; 		/* number of processes */
	Stream stream;			/* pointer to first stream*/
	Process proc;		/* First Process */
	char *name;			/* Model Name */
} Model_;
typedef struct Model_ *Model;

/*   End of MODEL  Structures   */

#endif  // MODEL_H
