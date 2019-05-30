#ifndef SW_H_
#define SW_H_
/* You might want to change the above name. */

#include "swmain.h"
#include "model.h"

extern char *version;
#define ID_UNKNOWN 9999999
#define MAX_BUFFER  1000000

/* sw.c  */
extern int maxbfsz;

Model 	visitValidSW(ValidSW p);
void	visitStm(Stm p);
void 	visitListStm(ListStm p);
void 	visitS_tream(S_tream p);
Process visitSrce(Srce p);
Process visitSnk(Snk p);
Process visitProc(Proc p);
Port    visitPrt(Prt p);
Component visitComp(Comp p);
Argument visitArgument(Argument p);
ListArgument visitListArgument(ListArgument p);


Ident visitIdent(Ident i);
Integer visitInteger(Integer i);
void visitDouble(Double d);
void visitChar(Char c);
String visitString(String s);
String visitStringval(Stringval p);

	/* swjafafbp.c */
void genJavaFBP(Model model);

	/* swc.c       */
void genC(Model model); 
#endif   // SW_H_

