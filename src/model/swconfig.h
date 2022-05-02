/** \file swconfig.h 

 ** Streamwork configuration includes

 */
 
#ifndef _SWCONFIG_H
#define _SWCONFIG_H

#include "sw.h"
#include <string.h>

#define htmldir		  cfg.HTMLdir
#define defaultPath 	  cfg.DefaultPath
#define defaultTypePath    cfg.DefaultTypePath
#define defaultSourceComp  cfg.DefaultSourceComp
#define defaultSinkComp    cfg.DefaultSinkComp
#define defaultFilterComp  cfg.DefaultFilterComp
#define defaultOrphanComp  cfg.DefaultOrphanComp
#define defaultChannelType cfg.DefaultChannelType
#define defaultBufferSize   cfg.DefaultBufferSize
#define defaultLibrary	  cfg.DefaultLibrary
#define includePath	  cfg.IncludePath
#define maxbfsz		  cfg.Maxbfsz
#define maxdepth	          cfg.MaxDepth       	// Maximum subnet depth
#define TABLESIZE 	  cfg.Tablesize

#define badkind(S) { 						\
   fprintf(stderr,						\
	"Error: bad kind field when visiting %s!\n",(#S));	\
   exit(EXIT_FAILURE); 							\
}

			/** Configure structure */
struct cfg_ {
	int   Maxbfsz;			/**<Maximum buffer size */
	int   MaxDepth;			/**<Maximum subnet depth*/
	int   Tablesize;		/**<Symbol table size*/
	int   DefaultBufferSize;	/**<Default buffer size */
	char *DefaultPath;		    /**<Default package path*/
	char *DefaultTypePath;		/**<Default type path(package)*/
	char *DefaultSourceComp;	/**<Default source component*/
	char *DefaultSinkComp;		/**<Default sink component*/
	char *DefaultFilterComp;	/**<Default filter component*/
	char *DefaultOrphanComp;	/**<Default orphan component*/
	char *DefaultLibrary;		/**<Default module library: github.com/... for instance.*/
	char *IncludePath;		/**<colon separated list of paths to search for INCLUDEd files */		
	// Not implemented char *DefaultIPtype;		/**< Type of data in the stream */
	char *HTMLdir;			/**<Directory for html tooltips in network graph*/
	char *DefaultChannelType;   /** interface{} OR typeT */
} ;	

#define SetV(S) if (strcmp(key,(#S))==0) { cfg.S = val; }
#define SetS(S) if (strcmp(key,Filter(#S))==0) { cfg.S = val; }
#define visitDate(X) 

#define CheckString(S,N)  					\
  if(!match((S),"([a-zA-Z0-9_.]+)$")) {				\
	fprintf(stderr,						\
		"\033[31m%s is not a valid %s.\033[39m\n",	\
		(S),#N);					\
	exit(EXIT_FAILURE);						\
  }

extern String  yamlOption;
	
	/* swconfig.c prototypes */
String 	visitSymval(Symval _p_);
int 	ConfigError(String s);  /* Process configuration file */
void 	visitValidConfig(ValidConfig p);
Ident 	visitIdent1(Ident i);
int   	visitInteger1(Integer i);
String  visitModPath(ModPath p);
String 	visitString1(String s);

#endif  //  _SWCONFIG_H

