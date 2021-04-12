/** \file swconfig.c 

 ** Streamwork Configuration

*/
 
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
	"def", "Gen1", "Print1", "Filter1", "defaultLib", "/home/tyoung3/go/mod/sw/html/",NULL };

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
	SetS(DefaultOrphanComp);
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

#if 0
void visitModPath(ModPath p)
{
  switch(p->kind)
  {
  case is_Modpx:
    /* Code for Modpx Goes Here */
    visitSymval(p->u.modpx_.symval_);
    break;
  case is_Modpy:
    /* Code for Modpy Goes Here */
    visitModPath(p->u.modpy_.modpath_);
    visitSymval(p->u.modpy_.symval_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing ModPath!\n");
    exit(1);
  }
}
#endif

/** @todo implemement visitKeyName QQ */
String visitKeyName(KeyName p)
{
  switch(p->kind)
  {
  case is_KeynameS:
    /* Code for KeynameS Goes Here */
    visitSymval(p->u.keynames_.symval_);
    break;
  case is_KeynameM:
    /* Code for KeynameM Goes Here */
    visitModPath(p->u.keynamem_.modpath_);
    visitSymval(p->u.keynamem_.symval_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing KeyName!\n");
    exit(1);
  }
  // return "Not implemented";
}

#if 1 
#define visitDate(X) 
#else
void visitDate(Date p)
{
  /* Code for Date Goes Here */
}
#endif

void visitKeyVal(KeyVal p)
{
  switch(p->kind)
  {
  case is_CfgKeyvalint:
    CfgInt(	
    visitKeyName(p->u.cfgkeyvalint_.keyname_),
    visitInteger1(p->u.cfgkeyvalint_.integer_));
    break;  
  case is_CfgKeyDate:
    /* Code for CfgKeyDate Goes Here */
    visitKeyName(p->u.cfgkeydate_.keyname_);
    visitDate(p->u.cfgkeydate_.date_);
    break;
  case is_CfgKeyvalstr:
    CfgString(	visitKeyName(p->u.cfgkeyvalstr_.keyname_),
    visitString1(p->u.cfgkeyvalstr_.string_));
    break;  
  case is_CfgKeyvalent:
    visitEntry(p->u.cfgkeyvalent_.entry_);
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

String visitHeading(Heading p)
{
   return visitKeyName(p->u.cfgheading_.keyname_);
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


/** Parse config file, validate, and set cfg struct */
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
	fprintf(stderr,"Config file: \'%s\'  parse error.\n", s);
	return 1;
  }

  fclose(file);

  if(!match(htmldir,"(/[a-zA-Z0-9_.-]+)/$")) {
	fprintf(stderr,
		"\033[31mConfigError%s is not a valid directory path.\033[39m\n", 
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
  CheckString(defaultOrphanComp,component);
	
  return 0;

}
