#ifndef _SWCONFIG_H
#define _SWCONFIG_H

#define defaultPath 	cfg.DefaultPath
#define defaultSourceComp cfg.DefaultSourceComp
#define defaultSinkComp cfg.DefaultSinkComp
#define defBufferSize 	cfg.DefBufferSize
#define maxbfsz		cfg.Maxbfsz
#define maxdepth	cfg.MaxDepth
#define TABLESIZE 	cfg.Tablesize

int ConfigError(String s);  /* swconfig.c process configuration file */

static void visitValidCFG(ValidCFG p);
static void visitStn(Stn p);
static void visitListStn(ListStn p);

static Ident visitIdent1(Ident i);
static int   visitInteger1(Integer i);
//void visitDouble(Double d);
//void visitChar(Char c);
static String visitString1(String s);

/** Configure structure */
struct cfg_ {
	int   DefBufferSize;
	int   Maxbfsz;
	int   MaxDepth;
	int   Tablesize;
	char *DefaultPath;
	char *DefaultSourceComp;
	char *DefaultSinkComp;
	char *DefaultFilterComp;
} ;	
	
#endif

