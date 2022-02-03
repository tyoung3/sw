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
	 Model > Stream > Source_Process > Port >   sink-Port 
	 		   v 	  Sink_Process   > Port > source-Port
	         Stream   Process        > Component
		      ...     Process        > Process ...


               |<-----------
               |           ^            
               v           |            
	 Model > Stream > SinkPort   -> SinkProcess    -> Component
                    > SourcePort -> SourceProcess  -> Component

	 Process->port->port....
*/

/*    MODEL  Structures   */
   
/** Type of Stream: Network, Subnet, or Orphan */
typedef enum {IS_NET, IS_SUB, IS_ORPHAN} TYPE;

/** Port structure */
typedef struct Port_ {
	int id; 	/**<Port number*/
	int channel;  	/**<Assigned Go Channel Number */	
	String name;    /**<Port name*/

	struct Port_ *match;	/**<Pointer to matching port. */
	struct Stream_ *stream; /**<Stream*/

	struct Port_ *next;	/**<Pointer to next port in process.    */
	struct Port_ *prev;	/**<Pointer to previous port in process. */
} Port_;
typedef struct Port_ *Port; /**<Pointer to Port */

/** Port Direction */
typedef enum {SINK,SOURCE} PortType;  

/* Attributes will be used to decorate graphs in order to 
distinquish component attributes, such as language, development state, module path, etc.*/
typedef struct Attribute_ {
        String key;
        union n { 
            int    nval;
            String sval; 
        } n;
        struct Attribute_ *next;  /* Next attribute in process */
} Attribute_;
typedef struct Attribute_ *Attribute;
 
/** Component structure */
typedef struct Component_ {     
		String name;       /**<First letter Upper Case. No slashes */    
		String path;       /**<Ex. github/tyoung3/streamwork/std  */
		Attribute attr;    /* list of arbitrary process attributes. Useful for graphs */ 
	    struct Component_ *next;  /**<Pointer to next component*/
} Component_;

/** Component pointer */
typedef struct Component_ *Component;

/** Process structure */
typedef struct Process_ {
		String name;		/**<Process name */
		Component comp;    	/**<Pointer to component for this process*/	  
		Port  port; 	    /**<Pointer to list of ports for this process*/
		int  nportsIn;		/**<Number of input ports for this process*/
		int  nportsOut;		/**<Number of output ports for this process*/
		int  ch;		    /**<Low channel number */
		int  depth;		    /**<Subnet depth */
		char **arg;		    /**< Pointer to an array of strings. */
		TYPE kind;	  	    /**< In subnet or net or orphan */
		int  partn;		    /**< Partition number.  */
		struct Process_ *next;  /**<Pointer to next process in the network*/
} Process_; 

typedef struct Process_ *Process;       /**<Pointer to Process */
/** Extport structure */
typedef struct Extport_ {
	PortType type;     	/**<Sink or source	*/
	Process source;		/**<Source process 	*/
	Process sink;		/**<Sink Process	*/

	String  name;   	/**<Port name 		*/
	int source_id; 		/**<Source port number 	*/
	int sink_id;    	/**<Sink port number 	*/
	char *iptype;		/**<Type identifier 	*/
	int bufsz;		/**<Buffer size		*/
	struct Extport_ *next;  /**<Pointer to next Extport*/
} Extport_;
typedef struct Extport_ *Extport;  /**<Pointer to Extport */	

/** Stream structure */
typedef struct Stream_ {
	Process source;  	/**<Source or orphan process */
	Process sink;    	/**<Sink process*/   	
	Port  SourcePort; 	/**<Source port*/
	Port  SinkPort;		/**<Sink port*/    
	int source_id; 		/**<Souce port number*/
	int sink_id; 		/**<Sink port number*/
	int bufsz; 		/**<Buffersize */
	TYPE  type;    		/**< Type of Stream IS_SUB or IS_NET or IS_ORPHAN*/
	char *iptype;    	/**< Type of data being sent -- the information packet type*/
	struct Stream_ *next;	/**<Pointer to next Stream*/
} Stream_;
typedef struct Stream_ *Stream;  /**<Pointer to stream */

/** Subnetm structure */
typedef struct Subnetm_ {     /**<  Subnetm: a list of external ports and streams*/
	char *name;		/**<Subnet name*/
	Stream  stream;		/**< First SN stream in this subnet */
	Extport extport;	/**<External port*/
	struct Subnetm_ *next;	/**<Pointer to next Subnet*/
} Subnetm_;
typedef struct Subnetm_ *Subnetm;   /**<Pointer to Subnet structure */

/** Model structure */
typedef struct Model_ {
	int       nstreams;	/**< Number of Streams in this network.*/	
	int       ncomponents;	/**< Number of unique components in the network.*/
	int       nprocs; 	/**< number of processes 	*/
	Stream    stream;	/**< pointer to first stream	*/
	Subnetm   subnetm;     	/**< Pointer to first subnet 	*/
	Process   proc;		/**< Pointer to First Process 	*/
        Component comp;	        /**< Pointer to first Conponent */
	char     *name;		/**< Model Name 		*/
	int	  level;	/**< Subnet depth		*/
	char	 *filename;	/**< Filename or STDIN		*/
} Model_;
typedef struct Model_ *Model;	/**<Pointer to Model */

/*   End of MODEL  Structures   */

#endif  // MODEL_H
