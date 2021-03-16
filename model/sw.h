#ifndef SW_H_
#define SW_H_
/* You might want to change the above name. */

#include "swmain.h"
#include "model.h"
#include "swconfig.h"

extern char *version;  /* In swmain.c from Makefile $VERSION */

#define FAIL1(S) { 					\
	fprintf(stderr,"\033[31mFAIL: SW/%s\033[39m\n",(#S));	\
	exit(1);					\
	}

		/* Abort message */
#define FAIL(F,S) { 						\
	fprintf(stderr,							\
		"\033[31mSW/%s/FAIL: %s\033[39m\n",	\
		(#F),								\
		(S)   );							\
		exit(1);							\
	}	
	
/* sw.c  */
void 	expandSubnets(Model model);
void 	visitDouble(Double d);
void 	visitChar(Char c);
void	visitStm(Stm p);
void 	visitListStm(ListStm p);
Stream	visitS_tream(S_tream p);
//Process visitPrtProc(PrtProc p);
//Process visitProcPrt(ProcPrt p);
Process visitProc(Proc p);
Port    visitPrt(Prt p);
Component visitComp(Comp p);
Argument visitArgument(Argument p);
ListArgument visitListArgument(ListArgument p);
Model 	visitValidSW(ValidSW p);

Ident visitIdent(Ident i);
Integer visitInteger(Integer i);
String visitString(String s);
String visitStringval(Stringval p);
Component MakeComponent(Ident name, String path);

	/* swjafafbp.c */
void genJavaFBP(Model model);

	/* swc.c       */
void genC(Model model); 

	/* swmain.c */
extern String configfile;
extern struct cfg_ cfg;
extern char fbfr[]; 	
#endif   // SW_H_

