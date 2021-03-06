/** \file swconfig.c 

 ** Streamwork Configuration

*/
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <sys/types.h>

#include "../bnfc/Parser.h"
#include "sw.h"
#include "swconfig.h"

struct cfg_ cfg = { 0, 10000, 10000, 1000, 
	"def", "Gen", "Print", "Filter", "defaultLib", "/home/tyoung3/go/src/github.com/tyoung3/sw/lib", "/home/tyoung3/go/src/github.com/tyoung3/sw/swbase/html/",NULL };

void visitEntry(Entry _p_);

static String Filter(String s) {

	return s;
}

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
	SetS(IncludePath);
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

String visitKeyName(KeyName p)
{
  switch(p->kind)
  {
  case is_KeynameS:
    return visitSymval(p->u.keynames_.symval_);
  case is_KeynameM:
    return makeModPath(
    	visitModPath(p->u.keynamem_.modpath_),
         visitSymval(p->u.keynamem_.symval_));   
  default:
    badkind(KeyName);
  }
}


void visitKeyVal(KeyVal p)
{
  switch(p->kind)
  {
  case is_CfgKeyvalint:
    CfgInt(	
    visitKeyName(p->u.cfgkeyvalint_.keyname_),
    visitInteger1(p->u.cfgkeyvalint_.integer_));
    break;  
  case is_CfgKeyvalstr:
    CfgString(	visitKeyName(p->u.cfgkeyvalstr_.keyname_),
    visitString1(p->u.cfgkeyvalstr_.string_));
    break;  
  case is_CfgKeyDate:
    /* Code for CfgKeyDate Goes Here */
    badkind(KeyVal_date);
    visitKeyName(p->u.cfgkeydate_.keyname_);
    visitDate(p->u.cfgkeydate_.date_);
    break;
  default:
    badkind(KeyVal_default);
  }
}

#ifdef SAVE_IN_CASE_CF_CHANGE
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
#endif

    
void visitEntry(Entry p)
{
  switch(p->kind) {
  case is_CfgEntrya:
    visitKeyVal(p->u.cfgentrya_.keyval_);
    break;
  case is_CfgEntryb:
    visitKeyName(p->u.cfgentryb_.keyname_);
    break;
  default:
    badkind(Entry);
   } 
}

void visitListEntry(ListEntry listentry)
{
  while(listentry != 0)
  {
    visitEntry(listentry->entry_);
    listentry = listentry->listentry_;
  }
}
void visitValidConfig(ValidConfig _p_)
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


/** Parse config file, validate, and set cfg struct */
int ConfigError(String s) {
  ValidConfig parse_tree;
  FILE *file;

  file = fopen(s, "rb");
  if(!file) {
	fprintf(stderr,"WARNING: missing config file -- %s.\n",s);
	return 0;  /** Missing config file is OK */
  }
  
  parse_tree = pValidConfig(file);
  if (parse_tree) { 
	visitValidConfig(parse_tree);
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
