#ifndef _SWCONFIG_H
#define _SWCONFIG_H

#define htmldir		  cfg.HTMLdir
#define defaultPath 	  cfg.DefaultPath
#define defaultSourceComp cfg.DefaultSourceComp
#define defaultSinkComp   cfg.DefaultSinkComp
#define defaultFilterComp cfg.DefaultFilterComp
#define defaultBufferSize cfg.DefaultBufferSize
#define maxbfsz		  cfg.Maxbfsz
#define maxdepth	  cfg.MaxDepth
#define TABLESIZE 	  cfg.Tablesize

int ConfigError(String s);  /* swconfig.c process configuration file */

void visitValidCFG(ValidCFG p);
void visitStn(Stn p);
void visitListStn(ListStn p);

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
	char *HTMLdir;
} ;	
	
#endif

