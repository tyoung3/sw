/** \file sw.h

 ** Streamwork includes

 */

#ifndef SW_H_
#define SW_H_
/* You might want to change the above name. */

#include "swmain.h"
#include "model.h"
#include "swconfig.h"

extern char *version;  /* In swmain.c from Makefile $VERSION */

/** Terminate with message */
#define FAIL1(S) { 					\
	fprintf(stderr,"\033[31mFAIL: SW/%s\033[39m\n",(#S));	\
	exit(1);					\
	}

		/**  Abort message */
#define FAIL(F,S) { 						\
	fprintf(stderr,							\
		"\033[31mSW/%s/FAIL: %s\033[39m\n",	\
		(#F),								\
		(S)   );							\
		exit(1);							\
	}	
	
/* sw.c  */
void 	expandSubnets(Model model);   		/**<Expand Subnets */
void 	visitDouble(Double d);			/**<Get Double ?*/	
void 	visitChar(Char c);			/**<Get a char */
void	visitStm(Stm p);			/**<Get next Statement*/
void 	visitListStm(ListStm p);		/**<Get list of statements*/
Stream	visitS_tream(S_tream p);		/**<Get next stream*/
Process visitProc(Proc p);			/**<Get Process*/
Port    visitPrt(Prt p);			/**<Get Port*/
Component visitComp(Comp p);			/**<Get Component*/
Argument visitArgument(Argument p);		/**<Get argument*/
ListArgument visitListArgument(ListArgument p);	/**<Get argument list*/
Model 	visitValidSW(ValidSW p);		/**<Build model from parse tree*/
Ident visitIdent(Ident i);		      	/**<Get port number */
Integer visitInteger(Integer i); 		/**<Get integer*/
String visitString(String s);			/**<Get string*/
String visitStringval(Stringval p);		/**<Get String value*/
Component MakeComponent(Ident name, String path);/**<Create component structure*/

	/** swjafafbp.c */	
void genJavaFBP(Model model);

	/** swproject.c */
void genProject(Model model);

	/* swc.c       */
void genC(Model model); 

	/* swmain.c */
extern String configfile;
extern struct cfg_ cfg;
extern char fbfr[]; 	
#endif   // SW_H_

