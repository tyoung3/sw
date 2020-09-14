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

struct cfg_ cfg = { 0, 10000, 10000, 1000, 
	"def", "Gen1", "Print1", "Filter1", "defaultLib", "/home/tyoung3/go/mod/sw/html/"  };

void visitEntry(Entry _p_);

static String Filter(String s) {

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

String visitString1(String s)
{
  return s;
}

Ident visitIdent1(Ident i)
{
    return i;
}

int visitInteger1(Integer i)
{
  return i;
}

void visitKeyVal(KeyVal _p_)
{
  switch(_p_->kind)
  {
  case is_CfgKeyvalint:
    CfgInt(	visitSymval(_p_->u.cfgkeyvalint_.symval_),
    		visitInteger1(_p_->u.cfgkeyvalint_.integer_));
    break;  
  case is_CfgKeyvalstr:
    CfgString(	visitSymval(_p_->u.cfgkeyvalstr_.symval_),
    		visitString1(_p_->u.cfgkeyvalstr_.string_));
    break;  
  case is_CfgKeyvalent:
    visitEntry(_p_->u.cfgkeyvalent_.entry_);
    break;
  default:
    badkind(KeyVal);
  }
}

void visitListKeyVal(ListKeyVal listkeyval)
{
  while(listkeyval != 0)
  {
    visitKeyVal(listkeyval->keyval_);
    listkeyval = listkeyval->listkeyval_;
  }
}

String visitHeading(Heading _p_)
{
   return visitSymval(_p_->u.cfgheading_.symval_);
}

void visitEntry(Entry _p_)
{
    visitHeading(_p_->u.cfgentrya_.heading_);
    visitListKeyVal(_p_->u.cfgentrya_.listkeyval_);
}

void visitListEntry(ListEntry listentry)
{
  while(listentry != 0)
  {
    visitEntry(listentry->entry_);
    listentry = listentry->listentry_;
  }
}
void visitValidCFG(ValidCFG _p_)
{
    visitListEntry(_p_->u.validcfg_.listentry_);
}

int match(const char *string, const char *pattern) 
{ 
    int status;
    regex_t re; 

    if(string==NULL) {
		return 0;
    }

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
