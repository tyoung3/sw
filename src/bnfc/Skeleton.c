/*** BNFC-Generated Visitor Traversal Skeleton. ***/
/* This traverses the abstract syntax tree.
   To use, copy Skeleton.h and Skeleton.c to
   new files. */

#include <stdlib.h>
#include <stdio.h>

#include "Skeleton.h"

void visitValide(Valide p)
{
  switch(p->kind)
  {
  case is_CFGvalid:
    /* Code for CFGvalid Goes Here */
    visitValidConfig(p->u.cfgvalid_.validconfig_);
    break;
  case is_SWvalid:
    /* Code for SWvalid Goes Here */
    visitValidSW(p->u.swvalid_.validsw_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Valide!\n");
    exit(1);
  }
}

void visitValidSW(ValidSW p)
{
  switch(p->kind)
  {
  case is_Valid:
    /* Code for Valid Goes Here */
    visitListStm(p->u.valid_.liststm_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing ValidSW!\n");
    exit(1);
  }
}

void visitStm(Stm p)
{
  switch(p->kind)
  {
  case is_StmPrefix:
    /* Code for StmPrefix Goes Here */
    visitPrefix(p->u.stmprefix_.prefix_);
    visitStringval(p->u.stmprefix_.stringval_);
    break;
  case is_Stminc:
    /* Code for Stminc Goes Here */
    visitInclude(p->u.stminc_.include_);
    visitStringval(p->u.stminc_.stringval_);
    break;
  case is_Stmx:
    /* Code for Stmx Goes Here */
    visitDataFlow(p->u.stmx_.dataflow_);
    break;
  case is_Stmn:
    /* Code for Stmn Goes Here */
    visitNumassgn(p->u.stmn_.numassgn_);
    break;
  case is_Stms:
    /* Code for Stms Goes Here */
    visitStrassgn(p->u.stms_.strassgn_);
    break;
  case is_Stmb:
    /* Code for Stmb Goes Here */
    visitSymAssgn(p->u.stmb_.symassgn_);
    break;
  case is_Stmh:
    /* Code for Stmh Goes Here */
    visitHermt(p->u.stmh_.hermt_);
    break;
  case is_Stmnet:
    /* Code for Stmnet Goes Here */
    visitSubdef(p->u.stmnet_.subdef_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Stm!\n");
    exit(1);
  }
}

void visitListStm(ListStm liststm)
{
  while(liststm  != 0)
  {
    /* Code For ListStm Goes Here */
    visitStm(liststm->stm_);
    liststm = liststm->liststm_;
  }
}

void visitSubdef(Subdef p)
{
  switch(p->kind)
  {
  case is_Snet:
    /* Code for Snet Goes Here */
    visitSubId(p->u.snet_.subid_);
    visitListSubnet(p->u.snet_.listsubnet_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Subdef!\n");
    exit(1);
  }
}

void visitSubnet(Subnet p)
{
  switch(p->kind)
  {
  case is_Sneth:
    /* Code for Sneth Goes Here */
    visitHermt(p->u.sneth_.hermt_);
    break;
  case is_Snets:
    /* Code for Snets Goes Here */
    visitDataFlow(p->u.snets_.dataflow_);
    break;
  case is_Snetin:
    /* Code for Snetin Goes Here */
    visitExtPortIn(p->u.snetin_.extportin_);
    break;
  case is_Snetout:
    /* Code for Snetout Goes Here */
    visitExtPortOut(p->u.snetout_.extportout_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Subnet!\n");
    exit(1);
  }
}

void visitListSubnet(ListSubnet listsubnet)
{
  while(listsubnet  != 0)
  {
    /* Code For ListSubnet Goes Here */
    visitSubnet(listsubnet->subnet_);
    listsubnet = listsubnet->listsubnet_;
  }
}

void visitExtPortIn(ExtPortIn p)
{
  switch(p->kind)
  {
  case is_Extin:
    /* Code for Extin Goes Here */
    visitProc(p->u.extin_.proc_);
    visitPrt(p->u.extin_.prt_);
    visitLarrow(p->u.extin_.larrow_);
    visitTab(p->u.extin_.tab_);
    break;
  case is_ExtinR:
    /* Code for ExtinR Goes Here */
    visitTab(p->u.extinr_.tab_);
    visitRarrow(p->u.extinr_.rarrow_);
    visitPrt(p->u.extinr_.prt_);
    visitProc(p->u.extinr_.proc_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing ExtPortIn!\n");
    exit(1);
  }
}

void visitExtPortOut(ExtPortOut p)
{
  switch(p->kind)
  {
  case is_Extout:
    /* Code for Extout Goes Here */
    visitTab(p->u.extout_.tab_);
    visitLarrow(p->u.extout_.larrow_);
    visitPrt(p->u.extout_.prt_);
    visitProc(p->u.extout_.proc_);
    break;
  case is_Extoutr:
    /* Code for Extoutr Goes Here */
    visitProc(p->u.extoutr_.proc_);
    visitPrt(p->u.extoutr_.prt_);
    visitRarrow(p->u.extoutr_.rarrow_);
    visitTab(p->u.extoutr_.tab_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing ExtPortOut!\n");
    exit(1);
  }
}

void visitTab(Tab p)
{
  switch(p->kind)
  {
  case is_Tabn:
    /* Code for Tabn Goes Here */
    visitNumval(p->u.tabn_.numval_);
    break;
  case is_Tabs:
    /* Code for Tabs Goes Here */
    visitSymval(p->u.tabs_.symval_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Tab!\n");
    exit(1);
  }
}

void visitDataFlow(DataFlow p)
{
  switch(p->kind)
  {
  case is_Streamx:
    /* Code for Streamx Goes Here */
    visitProc(p->u.streamx_.proc_1);
    visitPrt(p->u.streamx_.prt_1);
    visitLarrow(p->u.streamx_.larrow_);
    visitPrt(p->u.streamx_.prt_2);
    visitProc(p->u.streamx_.proc_2);
    break;
  case is_Streamrx:
    /* Code for Streamrx Goes Here */
    visitProc(p->u.streamrx_.proc_1);
    visitPrt(p->u.streamrx_.prt_1);
    visitRarrow(p->u.streamrx_.rarrow_);
    visitPrt(p->u.streamrx_.prt_2);
    visitProc(p->u.streamrx_.proc_2);
    break;
  case is_Streamls:
    /* Code for Streamls Goes Here */
    visitProc(p->u.streamls_.proc_1);
    visitPrt(p->u.streamls_.prt_1);
    visitLSarrow(p->u.streamls_.lsarrow_);
    visitPrt(p->u.streamls_.prt_2);
    visitProc(p->u.streamls_.proc_2);
    break;
  case is_Streamrs:
    /* Code for Streamrs Goes Here */
    visitProc(p->u.streamrs_.proc_1);
    visitPrt(p->u.streamrs_.prt_1);
    visitRSarrow(p->u.streamrs_.rsarrow_);
    visitPrt(p->u.streamrs_.prt_2);
    visitProc(p->u.streamrs_.proc_2);
    break;
  case is_Streamy:
    /* Code for Streamy Goes Here */
    visitDataFlow(p->u.streamy_.dataflow_);
    visitPrt(p->u.streamy_.prt_1);
    visitLarrow(p->u.streamy_.larrow_);
    visitPrt(p->u.streamy_.prt_2);
    visitProc(p->u.streamy_.proc_);
    break;
  case is_Streamry:
    /* Code for Streamry Goes Here */
    visitDataFlow(p->u.streamry_.dataflow_);
    visitPrt(p->u.streamry_.prt_1);
    visitRarrow(p->u.streamry_.rarrow_);
    visitPrt(p->u.streamry_.prt_2);
    visitProc(p->u.streamry_.proc_);
    break;
  case is_Streamlsy:
    /* Code for Streamlsy Goes Here */
    visitDataFlow(p->u.streamlsy_.dataflow_);
    visitPrt(p->u.streamlsy_.prt_1);
    visitLSarrow(p->u.streamlsy_.lsarrow_);
    visitPrt(p->u.streamlsy_.prt_2);
    visitProc(p->u.streamlsy_.proc_);
    break;
  case is_Streamrsy:
    /* Code for Streamrsy Goes Here */
    visitDataFlow(p->u.streamrsy_.dataflow_);
    visitPrt(p->u.streamrsy_.prt_1);
    visitRSarrow(p->u.streamrsy_.rsarrow_);
    visitPrt(p->u.streamrsy_.prt_2);
    visitProc(p->u.streamrsy_.proc_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing DataFlow!\n");
    exit(1);
  }
}

void visitLarrow(Larrow p)
{
  switch(p->kind)
  {
  case is_Arrowx:
    /* Code for Arrowx Goes Here */
    visitTypeDef(p->u.arrowx_.typedef_);
    visitBuffsize(p->u.arrowx_.buffsize_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Larrow!\n");
    exit(1);
  }
}

void visitRarrow(Rarrow p)
{
  switch(p->kind)
  {
  case is_Arrowr:
    /* Code for Arrowr Goes Here */
    visitTypeDef(p->u.arrowr_.typedef_);
    visitBuffsize(p->u.arrowr_.buffsize_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Rarrow!\n");
    exit(1);
  }
}

void visitLSarrow(LSarrow p)
{
  switch(p->kind)
  {
  case is_Arrowsl:
    /* Code for Arrowsl Goes Here */
    visitTypeDef(p->u.arrowsl_.typedef_);
    visitBuffsize(p->u.arrowsl_.buffsize_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing LSarrow!\n");
    exit(1);
  }
}

void visitRSarrow(RSarrow p)
{
  switch(p->kind)
  {
  case is_Arrowsr:
    /* Code for Arrowsr Goes Here */
    visitTypeDef(p->u.arrowsr_.typedef_);
    visitBuffsize(p->u.arrowsr_.buffsize_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing RSarrow!\n");
    exit(1);
  }
}

void visitTypeDef(TypeDef p)
{
  switch(p->kind)
  {
  case is_Typedefa:
    /* Code for Typedefa Goes Here */
    visitSymvalu(p->u.typedefa_.symvalu_);
    break;
  case is_Typedefb:
    /* Code for Typedefb Goes Here */
    visitSymvalu(p->u.typedefb_.symvalu_1);
    visitSymvalu(p->u.typedefb_.symvalu_2);
    break;
  case is_Typedefnull:
    /* Code for Typedefnull Goes Here */
    break;
  case is_Typdefl:
    /* Code for Typdefl Goes Here */
    visitTypeDef(p->u.typdefl_.typedef_1);
    visitTypeDef(p->u.typdefl_.typedef_2);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing TypeDef!\n");
    exit(1);
  }
}

void visitBuffsize(Buffsize p)
{
  switch(p->kind)
  {
  case is_Bufszi:
    /* Code for Bufszi Goes Here */
    visitNumval(p->u.bufszi_.numval_);
    break;
  case is_Bufsze:
    /* Code for Bufsze Goes Here */
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Buffsize!\n");
    exit(1);
  }
}

void visitHermt(Hermt p)
{
  switch(p->kind)
  {
  case is_Hermtx:
    /* Code for Hermtx Goes Here */
    visitSymvalu(p->u.hermtx_.symvalu_);
    visitComp(p->u.hermtx_.comp_);
    visitListArgument(p->u.hermtx_.listargument_);
    break;
  case is_Hermty:
    /* Code for Hermty Goes Here */
    visitSymvalu(p->u.hermty_.symvalu_);
    visitListArgument(p->u.hermty_.listargument_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Hermt!\n");
    exit(1);
  }
}

void visitSymvalu(Symvalu p)
{
  switch(p->kind)
  {
  case is_Symvaluv:
    /* Code for Symvaluv Goes Here */
    visitSymval(p->u.symvaluv_.symval_);
    break;
  case is_Symvaluu:
    /* Code for Symvaluu Goes Here */
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Symvalu!\n");
    exit(1);
  }
}

void visitProc(Proc p)
{
  switch(p->kind)
  {
  case is_Processx:
    /* Code for Processx Goes Here */
    visitSymvalu(p->u.processx_.symvalu_);
    visitComp(p->u.processx_.comp_);
    visitListArgument(p->u.processx_.listargument_);
    visitAttributes(p->u.processx_.attributes_);
    break;
  case is_Processy:
    /* Code for Processy Goes Here */
    visitSymvalu(p->u.processy_.symvalu_);
    visitAttributes(p->u.processy_.attributes_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Proc!\n");
    exit(1);
  }
}

void visitAttributes(Attributes p)
{
  switch(p->kind)
  {
  case is_Attribe:
    /* Code for Attribe Goes Here */
    visitListAttr(p->u.attribe_.listattr_);
    break;
  case is_Attribs:
    /* Code for Attribs Goes Here */
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Attributes!\n");
    exit(1);
  }
}

void visitAttr(Attr p)
{
  switch(p->kind)
  {
  case is_Attrs:
    /* Code for Attrs Goes Here */
    visitSymval(p->u.attrs_.symval_);
    visitStringval(p->u.attrs_.stringval_);
    break;
  case is_Attrn:
    /* Code for Attrn Goes Here */
    visitSymval(p->u.attrn_.symval_);
    visitNumval(p->u.attrn_.numval_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Attr!\n");
    exit(1);
  }
}

void visitListAttr(ListAttr listattr)
{
  while(listattr  != 0)
  {
    /* Code For ListAttr Goes Here */
    visitAttr(listattr->attr_);
    listattr = listattr->listattr_;
  }
}

void visitPrt(Prt p)
{
  switch(p->kind)
  {
  case is_Portx:
    /* Code for Portx Goes Here */
    visitNumval(p->u.portx_.numval_);
    break;
  case is_Portni:
    /* Code for Portni Goes Here */
    visitNumval(p->u.portni_.numval_);
    visitSymval(p->u.portni_.symval_);
    break;
  case is_Portin:
    /* Code for Portin Goes Here */
    visitSymval(p->u.portin_.symval_);
    visitNumval(p->u.portin_.numval_);
    break;
  case is_Portn:
    /* Code for Portn Goes Here */
    visitSymval(p->u.portn_.symval_);
    break;
  case is_Porte:
    /* Code for Porte Goes Here */
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Prt!\n");
    exit(1);
  }
}

void visitComp(Comp p)
{
  switch(p->kind)
  {
  case is_Compx:
    /* Code for Compx Goes Here */
    visitSymval(p->u.compx_.symval_);
    break;
  case is_Compn:
    /* Code for Compn Goes Here */
    visitSubId(p->u.compn_.subid_);
    break;
  case is_Compz:
    /* Code for Compz Goes Here */
    visitModPath(p->u.compz_.modpath_);
    visitSymval(p->u.compz_.symval_);
    break;
  case is_Compa:
    /* Code for Compa Goes Here */
    visitRemPath(p->u.compa_.rempath_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Comp!\n");
    exit(1);
  }
}

void visitModPath(ModPath p)
{
  switch(p->kind)
  {
  case is_Modpa:
    /* Code for Modpa Goes Here */
    visitSymval(p->u.modpa_.symval_);
    break;
  case is_Modpx:
    /* Code for Modpx Goes Here */
    visitSymval(p->u.modpx_.symval_);
    break;
  case is_Modpy:
    /* Code for Modpy Goes Here */
    visitModPath(p->u.modpy_.modpath_);
    visitSymval(p->u.modpy_.symval_);
    break;
  case is_Modps:
    /* Code for Modps Goes Here */
    visitStringvar(p->u.modps_.stringvar_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing ModPath!\n");
    exit(1);
  }
}

void visitRemPath(RemPath p)
{
  switch(p->kind)
  {
  case is_RemPatha:
    /* Code for RemPatha Goes Here */
    visitValidImport(p->u.rempatha_.validimport_);
    visitSymval(p->u.rempatha_.symval_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing RemPath!\n");
    exit(1);
  }
}

void visitArgument(Argument p)
{
  switch(p->kind)
  {
  case is_Argumentx:
    /* Code for Argumentx Goes Here */
    visitStringval(p->u.argumentx_.stringval_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Argument!\n");
    exit(1);
  }
}

void visitListArgument(ListArgument listargument)
{
  while(listargument  != 0)
  {
    /* Code For ListArgument Goes Here */
    visitArgument(listargument->argument_);
    listargument = listargument->listargument_;
  }
}

void visitNumassgn(Numassgn p)
{
  switch(p->kind)
  {
  case is_NumAssgnv:
    /* Code for NumAssgnv Goes Here */
    visitNumvar(p->u.numassgnv_.numvar_);
    visitNumval(p->u.numassgnv_.numval_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Numassgn!\n");
    exit(1);
  }
}

void visitStrassgn(Strassgn p)
{
  switch(p->kind)
  {
  case is_StrAssgnv:
    /* Code for StrAssgnv Goes Here */
    visitStringvar(p->u.strassgnv_.stringvar_);
    visitStringval(p->u.strassgnv_.stringval_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Strassgn!\n");
    exit(1);
  }
}

void visitSymAssgn(SymAssgn p)
{
  switch(p->kind)
  {
  case is_SymAssgni:
    /* Code for SymAssgni Goes Here */
    visitSymvar(p->u.symassgni_.symvar_);
    visitSymval(p->u.symassgni_.symval_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing SymAssgn!\n");
    exit(1);
  }
}

void visitNumval(Numval p)
{
  switch(p->kind)
  {
  case is_NumVali:
    /* Code for NumVali Goes Here */
    visitInteger(p->u.numvali_.integer_);
    break;
  case is_NumValv:
    /* Code for NumValv Goes Here */
    visitNumvar(p->u.numvalv_.numvar_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Numval!\n");
    exit(1);
  }
}

void visitStringval(Stringval p)
{
  switch(p->kind)
  {
  case is_StringVals:
    /* Code for StringVals Goes Here */
    visitString(p->u.stringvals_.string_);
    break;
  case is_StringValv:
    /* Code for StringValv Goes Here */
    visitStringvar(p->u.stringvalv_.stringvar_);
    break;
  case is_StringVale:
    /* Code for StringVale Goes Here */
    visitEnvar(p->u.stringvale_.envar_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Stringval!\n");
    exit(1);
  }
}

void visitSymval(Symval p)
{
  switch(p->kind)
  {
  case is_Symvalv:
    /* Code for Symvalv Goes Here */
    visitSymvar(p->u.symvalv_.symvar_);
    break;
  case is_Symvali:
    /* Code for Symvali Goes Here */
    visitId(p->u.symvali_.id_);
    break;
  case is_SymVale:
    /* Code for SymVale Goes Here */
    visitEnvar(p->u.symvale_.envar_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Symval!\n");
    exit(1);
  }
}

void visitInclude(Include p)
{
  switch(p->kind)
  {
  case is_Inc1:
    /* Code for Inc1 Goes Here */
    break;
  case is_Inc2:
    /* Code for Inc2 Goes Here */
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Include!\n");
    exit(1);
  }
}

void visitPrefix(Prefix p)
{
  switch(p->kind)
  {
  case is_Prefu:
    /* Code for Prefu Goes Here */
    break;
  case is_Prefl:
    /* Code for Prefl Goes Here */
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Prefix!\n");
    exit(1);
  }
}

void visitValidConfig(ValidConfig p)
{
  switch(p->kind)
  {
  case is_Validcfg:
    /* Code for Validcfg Goes Here */
    visitListEntry(p->u.validcfg_.listentry_);
    break;
  case is_Validcfgd:
    /* Code for Validcfgd Goes Here */
    visitListCentry(p->u.validcfgd_.listcentry_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing ValidConfig!\n");
    exit(1);
  }
}

void visitCentry(Centry p)
{
  switch(p->kind)
  {
  case is_CfgcEntrya:
    /* Code for CfgcEntrya Goes Here */
    visitKeyVal(p->u.cfgcentrya_.keyval_);
    break;
  case is_CfgcEntryb:
    /* Code for CfgcEntryb Goes Here */
    visitKeyName(p->u.cfgcentryb_.keyname_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Centry!\n");
    exit(1);
  }
}

void visitListCentry(ListCentry listcentry)
{
  while(listcentry  != 0)
  {
    /* Code For ListCentry Goes Here */
    visitCentry(listcentry->centry_);
    listcentry = listcentry->listcentry_;
  }
}

void visitEntry(Entry p)
{
  switch(p->kind)
  {
  case is_CfgEntrya:
    /* Code for CfgEntrya Goes Here */
    visitKeyVal(p->u.cfgentrya_.keyval_);
    break;
  case is_CfgEntryb:
    /* Code for CfgEntryb Goes Here */
    visitKeyName(p->u.cfgentryb_.keyname_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing Entry!\n");
    exit(1);
  }
}

void visitListEntry(ListEntry listentry)
{
  while(listentry  != 0)
  {
    /* Code For ListEntry Goes Here */
    visitEntry(listentry->entry_);
    listentry = listentry->listentry_;
  }
}

void visitKeyVal(KeyVal p)
{
  switch(p->kind)
  {
  case is_CfgKeyvalint:
    /* Code for CfgKeyvalint Goes Here */
    visitKeyName(p->u.cfgkeyvalint_.keyname_);
    visitInteger(p->u.cfgkeyvalint_.integer_);
    break;
  case is_CfgKeyvalstr:
    /* Code for CfgKeyvalstr Goes Here */
    visitKeyName(p->u.cfgkeyvalstr_.keyname_);
    visitString(p->u.cfgkeyvalstr_.string_);
    break;
  case is_CfgKeyDate:
    /* Code for CfgKeyDate Goes Here */
    visitKeyName(p->u.cfgkeydate_.keyname_);
    visitDate(p->u.cfgkeydate_.date_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when printing KeyVal!\n");
    exit(1);
  }
}

void visitKeyName(KeyName p)
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
}

void visitNumvar(Numvar p)
{
  /* Code for Numvar Goes Here */
}
void visitStringvar(Stringvar p)
{
  /* Code for Stringvar Goes Here */
}
void visitEnvar(Envar p)
{
  /* Code for Envar Goes Here */
}
void visitSymvar(Symvar p)
{
  /* Code for Symvar Goes Here */
}
void visitSubId(SubId p)
{
  /* Code for SubId Goes Here */
}
void visitId(Id p)
{
  /* Code for Id Goes Here */
}
void visitValidImport(ValidImport p)
{
  /* Code for ValidImport Goes Here */
}
void visitDate(Date p)
{
  /* Code for Date Goes Here */
}
void visitIdent(Ident i)
{
  /* Code for Ident Goes Here */
}
void visitInteger(Integer i)
{
  /* Code for Integer Goes Here */
}
void visitDouble(Double d)
{
  /* Code for Double Goes Here */
}
void visitChar(Char c)
{
  /* Code for Char Goes Here */
}
void visitString(String s)
{
  /* Code for String Goes Here */
}

