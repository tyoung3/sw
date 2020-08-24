/** @file model.h 
	StreamWork Structures and includes
*/

#ifndef MODEL_H
#define MODEL_H

#include "../bnfc/Absyn.h"
#include "../bnfc/Parser.h"
#include "../bnfc/Printer.h"

/*          Network  Model

               |<-------------------------------- 
               |                         ^      ^ 
               v                         |      |
	 Model > Stream > Source_Process > Port > Port 
	 			 	Sink_Process     > Port > Port
	                Process          > Component
				    Process          > Process


               |<--------------------------------
               |                         ^      ^ 
               v                         |      |
	 Model > Stream > SinkPort   -> SinkProcess    -> Component
                        > SourcePort -> SourceProcess  -> Component

	 Process->port->port....
*/

/*    MODEL  Structures   */

typedef enum {IS_NET, IS_SUB, IS_ORPHAN} STATE;   /* Type of Stream */

/** Component structure */
struct Component_ {
		String name;   // First letter Upper Case. No slashes    
		String path;   // Ex. github/tyoung3/streamwork/std 
} Component_;
typedef struct Component_ *Component;


/** Port structure */
struct Port_ {
	int id; 
	int channel;  /* Assigned Go Channel Number */	
	String name;
	struct Port_ *match;
	struct Stream_ *stream;
	struct Port_ *next;
	struct Port_ *prev;
} Port_;
typedef struct Port_ *Port;
	
/** Process structure */
struct Process_ {
		String name;
		Component comp;    		  
		Port  port; 	      /* Port list */
		int  nportsIn;
		int  nportsOut;
		int  ch;			/* Low channel number */
		int  depth;			/* Subnet depth */
		struct Process_ *next;
		char **arg;		  /* An array of strings. */
		STATE kind;	  /* In subnet or net */
} Process_; 
typedef struct Process_ *Process;

/** Stream structure */
struct Stream_ {
	Process source;
	Process sink;      
	Port  SourcePort; 
	Port  SinkPort; 		      
	int source_id; 	
	int sink_id; 	
	int bufsz; 
	STATE  state;    /* Type of Stream IS_SUB or IS_NET */
	struct Stream_ *next;
} Stream_;
typedef struct Stream_ *Stream;

typedef enum {SINK,SOURCE} PortType;

/** Extport structure */
struct Extport_ {
	PortType type;
	Process source;
	Process sink;
	String  name;   /* Port name */
	int source_id; 	
	int sink_id; 
	int bufsz;	
	struct Extport_ *next;
} Extport_;
typedef struct Extport_ *Extport;

/** Subnetm structure */
struct Subnetm_ {     /*  Subnetm: a list of external ports and streams*/
	char *name;
	Stream  stream;		/* First SN stream in this subnet */
	Extport extport;
	struct Subnetm_ *next;
} Subnetm_;
typedef struct Subnetm_ *Subnetm;

/** Model structure */
struct Model_ {
	int nstreams;
	int ncomponents;
	int nprocs; 		/* number of processes */
	Stream stream;		/* pointer to first stream*/
	Subnetm subnetm;     	/* Pointer to first subnet */
	Process proc;		/* Pointer to First Process */
	char *name;		/* Model Name */
} Model_;
typedef struct Model_ *Model;

/*   End of MODEL  Structures   */

#endif  // MODEL_H
