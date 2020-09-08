/*** BNFC-Generated Visitor Traversal Skeleton. ***/
/* This traverses the abstract syntax tree.
   To use, copy Skeleton.h and Skeleton.c to
   new files. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <sys/types.h>

#include "../bnfc/Parser.h"
#include "swconfig.h"

struct cfg_ cfg = { 0, 10000, 20, 1000, 
	"def", "Gen1", "Print1", "Filter1", "/home/tyoung3/go/mod/sw/html/"  };

// static String title={"No title"};

void visitValidCFG(ValidCFG _p_)
{
    visitListStn(_p_->u.validcfg_.liststn_);
}

static String Filter(String s) {
	// String t;

	return s;
}

#define SetV(S) if (strcmp(key,(#S))==0) { cfg.S = val; }
#define SetS(S) if (strcmp(key,Filter(#S))==0) { cfg.S = val; }

static void CfgInt(String key, int val) {
	SetV(DefaultBufferSize);
	SetV(Maxbfsz);
	SetV(MaxDepth);
	SetV(Tablesize);
}

static void CfgString(String key, String val)  {
	SetS(DefaultPath);
	SetS(DefaultSourceComp);
	SetS(DefaultSinkComp);
	SetS(DefaultFilterComp);
	SetS(DefaultLibrary);
	SetS(HTMLdir);
};

void visitStn(Stn _p_)
{
  switch(_p_->kind)
  {
  case is_StmTitle:
    /* Code for StmTitle Goes Here */
    visitString1(_p_->u.stmtitle_.string_);
    break;  
  case is_StmHeading:
     //visitIdent1(_p_->u.stmdefaults_.ident_);
    break;  
  case is_StmKeyvalint:
    CfgInt(	visitSymval(_p_->u.stmkeyvalint_.symval_),
    	 	visitInteger1(_p_->u.stmkeyvalint_.integer_));
    break;  
  case is_StmKeyvalstr:
    CfgString(	visitSymval(_p_->u.stmkeyvalstr_.symval_),
    		visitString1(_p_->u.stmkeyvalstr_.string_));
    break;
  default:
    fprintf(stderr, "Error: bad kind field when printing Stn!\n");
    exit(1);
  }
}

void visitListStn(ListStn liststn)
{
  while(liststn != 0)
  {
    /* Code For ListStn Goes Here */
    visitStn(liststn->stn_);
    liststn = liststn->liststn_;
  }
}

Ident visitIdent1(Ident i)
{
    return i;
}

int visitInteger1(Integer i)
{
  return i;
}

	String visitString1(String s)
{
  return s;
}

int match(const char *string, const char *pattern) 
{ 
    int status;
    regex_t re; 

    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) 
		return 0; 

    status = regexec(&re, string, 0, NULL, 0); 
    regfree(&re); 

    if (status != 0) 
	  return 0; 

    return 1; 
} 

#define CheckString(S,N)  					\
  if(!match((S),"([a-zA-Z0-9_.]+)$")) {				\
	fprintf(stderr,						\
		"\033[31m%s is not a valid %s.\033[39m\n",	\
		(S),#N);					\
	exit(1);						\
  }

int ConfigError(String s) {
  ValidCFG parse_tree;
  FILE *file;

  file = fopen(s, "rb");
  if(!file) {
	fprintf(stderr,"WARNING: missing config file -- %s.\n",s);
	return 0;  /** Missing config file is OK */
  }
  
  parse_tree = pValidCFG(file);
  if (parse_tree) { 
	visitValidCFG(parse_tree);
  } else {
	fprintf(stderr,"Config file parse error.\n");
	return 1;
  }

  fclose(file);

  if(!match(htmldir,"(/[a-zA-Z0-9_.-]+)/$")) {
	fprintf(stderr,
		"\033[31m%s is not a valid directory path.\033[39m\n", 
		htmldir);
	exit(1);
  }

  if(!match(defaultPath,"([a-zA-Z0-9_.-/]+)$")) {
	fprintf(stderr,
		"\033[31m%s is not a valid path.\033[39m\n", 
		defaultPath);
	exit(1);
  }

  CheckString(defaultSourceComp,component);
  CheckString(defaultSinkComp,component);
  CheckString(defaultFilterComp,component);
	
  return 0;

}
