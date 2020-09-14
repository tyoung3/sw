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
	int   Maxbfsz;
	int   MaxDepth;
	int   Tablesize;
	int   DefaultBufferSize;
	char *DefaultPath;
	char *DefaultSourceComp;
	char *DefaultSinkComp;
	char *DefaultFilterComp;
	char *DefaultOrphanComp;
	char *DefaultLibrary;
	char *HTMLdir;
} ;	
	
#endif

