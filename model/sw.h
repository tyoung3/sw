#ifndef SW_H_
#define SW_H_
/* You might want to change the above name. */

#include "Absyn.h"
#include "swmain.h"
#include "model.h"

extern char *version;

/* sw.c  */
extern int maxbfsz;

Model visitValidSW(ValidSW p);
Model visitStm(Stm p);
Model visitListStm(ListStm p);
Flow visitFlw(Flw p);
Process visitSrce(Srce p);
Process visitSnk(Snk p);
Process visitProc(Proc p);
Port visitPrt(Prt p);
Component visitComp(Comp p);
Argument visitArgument(Argument p);
ListArgument visitListArgument(ListArgument p);


Ident visitIdent(Ident i);
Integer visitInteger(Integer i);
void visitDouble(Double d);
void visitChar(Char c);
String visitString(String s);

	/* swjafafbp.c */
void genJavaFBP(Model model);

	/* swc.c       */
void genC(Model model); 
#endif   // SW_H_

