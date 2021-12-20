/** \file sw.h

 ** Streamwork includes

 */

#ifndef SW_H_
#define SW_H_
/* You might want to change the above name. */

#include "swmain.h"
#include "model.h"
#include "swconfig.h"
#include "string.h"

#ifndef strndup
char *strndup (const char *s, size_t n);
#endif

#define BUFFSIZE 1000

#ifndef String 
typedef char* String;
#endif

#define STDPACKAGE "swbase"
char *strncat(char *dest, const char *src, size_t n);

char *mystrncat(char *d, char *s, size_t n);

extern char *version;  /* In swmain.c from Makefile $VERSION */

/** Terminate with message */
#define FAIL1(S) { 						\
	fprintf(stderr,"\033[31mFAIL: SW/%s\033[39m\n",(#S));	\
	exit(EXIT_FAILURE);					\
	}

		/**  Abort message */
#define FAIL(F,S) { 					\
	fprintf(stderr,					\
		"\033[31mFAIL: SW/%s: %s\033[39m\n",	\
		(#F),					\
		(S)   );				\
		exit(EXIT_FAILURE);			\
	}	



	
/* sw.c  */

void 	visitDouble(Double d);			/**<Get Double ?*/	
void 	visitChar(Char c);			/**<Get a char */
void	visitStm(Stm p);			/**<Get next Statement*/
void 	visitListStm(ListStm p);		/**<Get list of statements*/
Stream	visitDataFlow(DataFlow p);		/**<Get next stream*/
Process visitProc(Proc p);			/**<Get Process*/
Port    visitPrt(Prt p);			/**<Get Port*/
Component visitComp(Comp p);			/**<Get Component*/
Argument visitArgument(Argument p);		/**<Get argument*/
ListArgument visitListArgument(ListArgument p);	/**<Get argument list*/
Model 	visitValidSW(Model, ValidSW p);		/**<Build model from parse tree*/
Model MakeModel(Stream f);
Ident visitIdent(Ident i);		      	/**<Get port number */
Integer visitInteger(Integer i); 		/**<Get integer*/
String visitString(String s);			/**<Get string*/
String visitStringval(Stringval p);		/**<Get String value*/
Component MakeComponent(Ident name, String path);/**<Create component structure*/
char *makeModPath(char *pn, char *nn);

	/** swjafafbp.c */	
void genJavaFBP(Model model);

	/** swproject.c */
void genProject(Model model);

	/* swc.c       */
void genC(Model model); 

	/* swmain.c */
#undef strncat
#define strncat(X,Y,Z) mystrncat(X,Y,Z)  
extern String configfile;
extern struct cfg_ cfg;
extern char fbfr[]; 	
ValidSW IncludeFile( char *fname);

	/* swsym.c */
int getPathColor(String path);
#define  ncolors 10    

	/* swgraph.c */
extern String fcolors[]; 
    
#endif   // SW_H_

