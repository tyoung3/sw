/*** BNFC-Generated Visitor Traversal Skeleton. ***/
/* This traverses the abstract syntax tree.
   To use, copy Skeleton.h and Skeleton.c to
   new files. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Absyn.h"
#include "Parser.h"

#include "swconfig.h"

struct cfg_ cfg = { 0, 10000, 20, 1000, "def", "Gen1", "Print1", "Filter1" };

static String title={"No title"};

void visitValidCFG(ValidCFG _p_)
{
  switch(_p_->kind)
  {
  case is_Valid:
    /* Code for Valid Goes Here */
    visitListStn(_p_->u.valid_.liststn_);
    break;
  default:
    fprintf(stderr, "Error: bad kind field when printing ValidCFG!\n");
    exit(1);
  }
}


#define SetV(S) if (strcmp(key,(#S))==0) { cfg.S = val; }
#define SetS(S) SetV(S)

static void CfgInt(String key, int val) {
	SetV(DefBufferSize);
	SetV(Maxbfsz);
	SetV(MaxDepth);
	SetV(Tablesize);
}

static void CfgString(String key, String val)  {
	SetS(DefaultPath);
	SetS(DefaultSourceComp);
	SetS(DefaultSinkComp);
	SetS(DefaultFilterComp);
};

static void visitStn(Stn _p_)
{
  switch(_p_->kind)
  {
  case is_StmTitle:
    /* Code for StmTitle Goes Here */
    title=visitIdent1(_p_->u.stmtitle_.ident_);
    break;  
  case is_StmDefaults:
    // visitIdent1(_p_->u.stmdefaults_.ident_);
    break;  
  case is_StmKeyvalint:
    CfgInt(	visitIdent1(_p_->u.stmkeyvalint_.ident_),
    	 	visitInteger1(_p_->u.stmkeyvalint_.integer_));
    break;  
  case is_StmKeyvalstr:
    CfgString(	visitIdent1(_p_->u.stmkeyvalstr_.ident_),
    		visitString1(_p_->u.stmkeyvalstr_.string_));
    break;
  default:
    fprintf(stderr, "Error: bad kind field when printing Stn!\n");
    exit(1);
  }
}

static void visitListStn(ListStn liststn)
{
  while(liststn != 0)
  {
    /* Code For ListStn Goes Here */
    visitStn(liststn->stn_);
    liststn = liststn->liststn_;
  }
}

static Ident visitIdent1(Ident i)
{
    return i;
}

static int visitInteger1(Integer i)
{
  return i;
}

static String visitString1(String s)
{
  return s;
}


int ConfigError(String s) {
  ValidCFG parse_tree;

  FILE *file;

  file = fopen(s, "rb");
  if(!file) {
	return 0;  /** Missing config file is OK */
  }
  
  parse_tree = pValidCFG(file);
  if (parse_tree) { 
	visitValidCFG(parse_tree);
  } else {
	fprintf(stderr,"Config file parse error.");
	return 1;
  }

  fclose(file);
	
  return 0;

}
