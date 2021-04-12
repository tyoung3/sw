/** \file swconfig.h 

 ** Streamwork configuration includes

 */
 
#ifndef _SWCONFIG_H
#define _SWCONFIG_H

#define htmldir		  cfg.HTMLdir
#define defaultPath 	  cfg.DefaultPath
#define defaultSourceComp cfg.DefaultSourceComp
#define defaultSinkComp   cfg.DefaultSinkComp
#define defaultFilterComp cfg.DefaultFilterComp
#define defaultOrphanComp cfg.DefaultOrphanComp
#define defaultBufferSize cfg.DefaultBufferSize
#define defaultLibrary	  cfg.DefaultLibrary
#define maxbfsz		  cfg.Maxbfsz
#define maxdepth	  cfg.MaxDepth
#define TABLESIZE 	  cfg.Tablesize

#define badkind(S) { 						\
   fprintf(stderr,						\
	"Error: bad kind field when visiting %s!\n",(#S));	\
   exit(1); 							\
}

String visitSymval(Symval _p_);

int ConfigError(String s);  /* swconfig.c process configuration file */

void visitValidCFG(ValidCFG p);

Ident visitIdent1(Ident i);
int   visitInteger1(Integer i);
//void visitDouble(Double d);
//void visitChar(Char c);
String visitString1(String s);

/** Configure structure */
struct cfg_ {
	int   Maxbfsz;			/**<Maximum buffer size */
	int   MaxDepth;			/**<Maximum subnet depth*/
	int   Tablesize;		/**<Symbol table size*/
	int   DefaultBufferSize;	/**<Default buffer size */
	char *DefaultPath;		/**<Default module path*/
	char *DefaultSourceComp;	/**<Default source component*/
	char *DefaultSinkComp;		/**<Default sink component*/
	char *DefaultFilterComp;	/**<Default filter component*/
	char *DefaultOrphanComp;	/**<Default orphan component*/
	char *DefaultLibrary;		/**<Default module library: github.com/... for instance.*/
	char *HTMLdir;			/**<Directory for html tooltips in network graph*/
} ;	
	
#endif

