/*** BNFC-Generated Pretty Printer and Abstract Syntax Viewer ***/

#include "Printer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INDENT_WIDTH 2

int _n_;
char *buf_;
int cur_;
int buf_size;

/* You may wish to change the renderC functions */
void renderC(Char c)
{
  if (c == '{')
  {
     bufAppendC('\n');
     indent();
     bufAppendC(c);
     _n_ = _n_ + INDENT_WIDTH;
     bufAppendC('\n');
     indent();
  }
  else if (c == '(' || c == '[')
     bufAppendC(c);
  else if (c == ')' || c == ']')
  {
     backup();
     bufAppendC(c);
  }
  else if (c == '}')
  {
     int t;
     _n_ = _n_ - INDENT_WIDTH;
     for(t=0; t<INDENT_WIDTH; t++) {
       backup();
     }
     bufAppendC(c);
     bufAppendC('\n');
     indent();
  }
  else if (c == ',')
  {
     backup();
     bufAppendC(c);
     bufAppendC(' ');
  }
  else if (c == ';')
  {
     backup();
     bufAppendC(c);
     bufAppendC('\n');
     indent();
  }
  else if (c == 0) return;
  else
  {
     bufAppendC(' ');
     bufAppendC(c);
     bufAppendC(' ');
  }
}
void renderS(String s)
{
  if(strlen(s) > 0)
  {
    bufAppendS(s);
    bufAppendC(' ');
  }
}
void indent(void)
{
  int n = _n_;
  while (n > 0)
  {
    bufAppendC(' ');
    n--;
  }
}
void backup(void)
{
  if (buf_[cur_ - 1] == ' ')
  {
    buf_[cur_ - 1] = 0;
    cur_--;
  }
}
char *printValide(Valide p)
{
  _n_ = 0;
  bufReset();
  ppValide(p, 0);
  return buf_;
}
char *printValidSW(ValidSW p)
{
  _n_ = 0;
  bufReset();
  ppValidSW(p, 0);
  return buf_;
}
char *printValidConfig(ValidConfig p)
{
  _n_ = 0;
  bufReset();
  ppValidConfig(p, 0);
  return buf_;
}
char *showValide(Valide p)
{
  _n_ = 0;
  bufReset();
  shValide(p);
  return buf_;
}
char *showValidSW(ValidSW p)
{
  _n_ = 0;
  bufReset();
  shValidSW(p);
  return buf_;
}
char *showValidConfig(ValidConfig p)
{
  _n_ = 0;
  bufReset();
  shValidConfig(p);
  return buf_;
}
void ppValide(Valide p, int _i_)
{
  switch(p->kind)
  {
  case is_CFGvalid:
    if (_i_ > 0) renderC(_L_PAREN);
    ppValidConfig(p->u.cfgvalid_.validconfig_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_SWvalid:
    if (_i_ > 0) renderC(_L_PAREN);
    ppValidSW(p->u.swvalid_.validsw_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Valide!\n");
    exit(1);
  }
}

void ppValidSW(ValidSW p, int _i_)
{
  switch(p->kind)
  {
  case is_Valid:
    if (_i_ > 0) renderC(_L_PAREN);
    ppListStm(p->u.valid_.liststm_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing ValidSW!\n");
    exit(1);
  }
}

void ppStm(Stm p, int _i_)
{
  switch(p->kind)
  {
  case is_StmPrefix:
    if (_i_ > 0) renderC(_L_PAREN);
    ppPrefix(p->u.stmprefix_.prefix_, 0);
    ppStringval(p->u.stmprefix_.stringval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Stminc:
    if (_i_ > 0) renderC(_L_PAREN);
    ppInclude(p->u.stminc_.include_, 0);
    ppStringval(p->u.stminc_.stringval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Stmx:
    if (_i_ > 0) renderC(_L_PAREN);
    ppDataFlow(p->u.stmx_.dataflow_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Stmn:
    if (_i_ > 0) renderC(_L_PAREN);
    ppNumassgn(p->u.stmn_.numassgn_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Stms:
    if (_i_ > 0) renderC(_L_PAREN);
    ppStrassgn(p->u.stms_.strassgn_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Stmb:
    if (_i_ > 0) renderC(_L_PAREN);
    ppSymAssgn(p->u.stmb_.symassgn_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Stmh:
    if (_i_ > 0) renderC(_L_PAREN);
    ppHermt(p->u.stmh_.hermt_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Stmnet:
    if (_i_ > 0) renderC(_L_PAREN);
    ppSubdef(p->u.stmnet_.subdef_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Stm!\n");
    exit(1);
  }
}

void ppListStm(ListStm liststm, int i)
{
  while(liststm != 0)
  {
    if (liststm->liststm_ == 0)
    {
      ppStm(liststm->stm_, i);
      renderC(';');
      liststm = 0;
    }
    else
    {
      ppStm(liststm->stm_, i);
      renderC(';');
      liststm = liststm->liststm_;
    }
  }
}

void ppSubdef(Subdef p, int _i_)
{
  switch(p->kind)
  {
  case is_Snet:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(p->u.snet_.subid_, 0);
    renderC('{');
    ppListSubnet(p->u.snet_.listsubnet_, 0);
    renderC('}');

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Subdef!\n");
    exit(1);
  }
}

void ppSubnet(Subnet p, int _i_)
{
  switch(p->kind)
  {
  case is_Sneth:
    if (_i_ > 0) renderC(_L_PAREN);
    ppHermt(p->u.sneth_.hermt_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Snets:
    if (_i_ > 0) renderC(_L_PAREN);
    ppDataFlow(p->u.snets_.dataflow_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Snetin:
    if (_i_ > 0) renderC(_L_PAREN);
    ppExtPortIn(p->u.snetin_.extportin_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Snetout:
    if (_i_ > 0) renderC(_L_PAREN);
    ppExtPortOut(p->u.snetout_.extportout_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Subnet!\n");
    exit(1);
  }
}

void ppListSubnet(ListSubnet listsubnet, int i)
{
  while(listsubnet != 0)
  {
    if (listsubnet->listsubnet_ == 0)
    {
      ppSubnet(listsubnet->subnet_, i);
      renderC(';');
      listsubnet = 0;
    }
    else
    {
      ppSubnet(listsubnet->subnet_, i);
      renderC(';');
      listsubnet = listsubnet->listsubnet_;
    }
  }
}

void ppExtPortIn(ExtPortIn p, int _i_)
{
  switch(p->kind)
  {
  case is_Extin:
    if (_i_ > 0) renderC(_L_PAREN);
    ppProc(p->u.extin_.proc_, 0);
    ppPrt(p->u.extin_.prt_, 0);
    ppLarrow(p->u.extin_.larrow_, 0);
    ppTab(p->u.extin_.tab_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_ExtinR:
    if (_i_ > 0) renderC(_L_PAREN);
    ppTab(p->u.extinr_.tab_, 0);
    ppRarrow(p->u.extinr_.rarrow_, 0);
    ppPrt(p->u.extinr_.prt_, 0);
    ppProc(p->u.extinr_.proc_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing ExtPortIn!\n");
    exit(1);
  }
}

void ppExtPortOut(ExtPortOut p, int _i_)
{
  switch(p->kind)
  {
  case is_Extout:
    if (_i_ > 0) renderC(_L_PAREN);
    ppTab(p->u.extout_.tab_, 0);
    ppLarrow(p->u.extout_.larrow_, 0);
    ppPrt(p->u.extout_.prt_, 0);
    ppProc(p->u.extout_.proc_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Extoutr:
    if (_i_ > 0) renderC(_L_PAREN);
    ppProc(p->u.extoutr_.proc_, 0);
    ppPrt(p->u.extoutr_.prt_, 0);
    ppRarrow(p->u.extoutr_.rarrow_, 0);
    ppTab(p->u.extoutr_.tab_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing ExtPortOut!\n");
    exit(1);
  }
}

void ppTab(Tab p, int _i_)
{
  switch(p->kind)
  {
  case is_Tabn:
    if (_i_ > 0) renderC(_L_PAREN);
    ppNumval(p->u.tabn_.numval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Tabs:
    if (_i_ > 0) renderC(_L_PAREN);
    ppSymval(p->u.tabs_.symval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Tab!\n");
    exit(1);
  }
}

void ppDataFlow(DataFlow p, int _i_)
{
  switch(p->kind)
  {
  case is_Streamx:
    if (_i_ > 0) renderC(_L_PAREN);
    ppProc(p->u.streamx_.proc_1, 0);
    ppPrt(p->u.streamx_.prt_1, 0);
    ppLarrow(p->u.streamx_.larrow_, 0);
    ppPrt(p->u.streamx_.prt_2, 0);
    ppProc(p->u.streamx_.proc_2, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Streamrx:
    if (_i_ > 0) renderC(_L_PAREN);
    ppProc(p->u.streamrx_.proc_1, 0);
    ppPrt(p->u.streamrx_.prt_1, 0);
    ppRarrow(p->u.streamrx_.rarrow_, 0);
    ppPrt(p->u.streamrx_.prt_2, 0);
    ppProc(p->u.streamrx_.proc_2, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Streamls:
    if (_i_ > 0) renderC(_L_PAREN);
    ppProc(p->u.streamls_.proc_1, 0);
    ppPrt(p->u.streamls_.prt_1, 0);
    ppLSarrow(p->u.streamls_.lsarrow_, 0);
    ppPrt(p->u.streamls_.prt_2, 0);
    ppProc(p->u.streamls_.proc_2, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Streamrs:
    if (_i_ > 0) renderC(_L_PAREN);
    ppProc(p->u.streamrs_.proc_1, 0);
    ppPrt(p->u.streamrs_.prt_1, 0);
    ppRSarrow(p->u.streamrs_.rsarrow_, 0);
    ppPrt(p->u.streamrs_.prt_2, 0);
    ppProc(p->u.streamrs_.proc_2, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Streamy:
    if (_i_ > 0) renderC(_L_PAREN);
    ppDataFlow(p->u.streamy_.dataflow_, 0);
    ppPrt(p->u.streamy_.prt_1, 0);
    ppLarrow(p->u.streamy_.larrow_, 0);
    ppPrt(p->u.streamy_.prt_2, 0);
    ppProc(p->u.streamy_.proc_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Streamry:
    if (_i_ > 0) renderC(_L_PAREN);
    ppDataFlow(p->u.streamry_.dataflow_, 0);
    ppPrt(p->u.streamry_.prt_1, 0);
    ppRarrow(p->u.streamry_.rarrow_, 0);
    ppPrt(p->u.streamry_.prt_2, 0);
    ppProc(p->u.streamry_.proc_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Streamlsy:
    if (_i_ > 0) renderC(_L_PAREN);
    ppDataFlow(p->u.streamlsy_.dataflow_, 0);
    ppPrt(p->u.streamlsy_.prt_1, 0);
    ppLSarrow(p->u.streamlsy_.lsarrow_, 0);
    ppPrt(p->u.streamlsy_.prt_2, 0);
    ppProc(p->u.streamlsy_.proc_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Streamrsy:
    if (_i_ > 0) renderC(_L_PAREN);
    ppDataFlow(p->u.streamrsy_.dataflow_, 0);
    ppPrt(p->u.streamrsy_.prt_1, 0);
    ppRSarrow(p->u.streamrsy_.rsarrow_, 0);
    ppPrt(p->u.streamrsy_.prt_2, 0);
    ppProc(p->u.streamrsy_.proc_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing DataFlow!\n");
    exit(1);
  }
}

void ppLarrow(Larrow p, int _i_)
{
  switch(p->kind)
  {
  case is_Arrowx:
    if (_i_ > 0) renderC(_L_PAREN);
    renderC('<');
    ppTypeDef(p->u.arrowx_.typedef_, 0);
    ppBuffsize(p->u.arrowx_.buffsize_, 0);
    renderC('-');

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Larrow!\n");
    exit(1);
  }
}

void ppRarrow(Rarrow p, int _i_)
{
  switch(p->kind)
  {
  case is_Arrowr:
    if (_i_ > 0) renderC(_L_PAREN);
    renderC('-');
    ppTypeDef(p->u.arrowr_.typedef_, 0);
    ppBuffsize(p->u.arrowr_.buffsize_, 0);
    renderC('>');

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Rarrow!\n");
    exit(1);
  }
}

void ppLSarrow(LSarrow p, int _i_)
{
  switch(p->kind)
  {
  case is_Arrowsl:
    if (_i_ > 0) renderC(_L_PAREN);
    renderC('<');
    ppTypeDef(p->u.arrowsl_.typedef_, 0);
    ppBuffsize(p->u.arrowsl_.buffsize_, 0);
    renderC('=');

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing LSarrow!\n");
    exit(1);
  }
}

void ppRSarrow(RSarrow p, int _i_)
{
  switch(p->kind)
  {
  case is_Arrowsr:
    if (_i_ > 0) renderC(_L_PAREN);
    renderC('=');
    ppTypeDef(p->u.arrowsr_.typedef_, 0);
    ppBuffsize(p->u.arrowsr_.buffsize_, 0);
    renderC('>');

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing RSarrow!\n");
    exit(1);
  }
}

void ppTypeDef(TypeDef p, int _i_)
{
  switch(p->kind)
  {
  case is_Typedefa:
    if (_i_ > 0) renderC(_L_PAREN);
    ppSymvalu(p->u.typedefa_.symvalu_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Typedefb:
    if (_i_ > 0) renderC(_L_PAREN);
    ppSymvalu(p->u.typedefb_.symvalu_1, 0);
    renderC('.');
    ppSymvalu(p->u.typedefb_.symvalu_2, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Typedefnull:
    if (_i_ > 0) renderC(_L_PAREN);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_TypedefArray:
    if (_i_ > 0) renderC(_L_PAREN);
    renderC('[');
    ppNumval(p->u.typedefarray_.numval_, 0);
    renderC(']');
    ppTypeDef(p->u.typedefarray_.typedef_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Typdefl:
    if (_i_ > 0) renderC(_L_PAREN);
    ppTypeDef(p->u.typdefl_.typedef_1, 0);
    renderC(',');
    ppTypeDef(p->u.typdefl_.typedef_2, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing TypeDef!\n");
    exit(1);
  }
}

void ppBuffsize(Buffsize p, int _i_)
{
  switch(p->kind)
  {
  case is_Bufszi:
    if (_i_ > 0) renderC(_L_PAREN);
    ppNumval(p->u.bufszi_.numval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Bufsze:
    if (_i_ > 0) renderC(_L_PAREN);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Buffsize!\n");
    exit(1);
  }
}

void ppHermt(Hermt p, int _i_)
{
  switch(p->kind)
  {
  case is_Hermtx:
    if (_i_ > 0) renderC(_L_PAREN);
    ppSymvalu(p->u.hermtx_.symvalu_, 0);
    ppComp(p->u.hermtx_.comp_, 0);
    ppListArgument(p->u.hermtx_.listargument_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Hermty:
    if (_i_ > 0) renderC(_L_PAREN);
    ppSymvalu(p->u.hermty_.symvalu_, 0);
    ppListArgument(p->u.hermty_.listargument_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Hermt!\n");
    exit(1);
  }
}

void ppSymvalu(Symvalu p, int _i_)
{
  switch(p->kind)
  {
  case is_Symvaluv:
    if (_i_ > 0) renderC(_L_PAREN);
    ppSymval(p->u.symvaluv_.symval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Symvaluu:
    if (_i_ > 0) renderC(_L_PAREN);
    renderC('_');

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Symvalu!\n");
    exit(1);
  }
}

void ppProc(Proc p, int _i_)
{
  switch(p->kind)
  {
  case is_Processx:
    if (_i_ > 0) renderC(_L_PAREN);
    renderC('(');
    ppSymvalu(p->u.processx_.symvalu_, 0);
    ppComp(p->u.processx_.comp_, 0);
    ppListArgument(p->u.processx_.listargument_, 0);
    ppAttributes(p->u.processx_.attributes_, 0);
    renderC(')');

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Processy:
    if (_i_ > 0) renderC(_L_PAREN);
    renderC('(');
    ppSymvalu(p->u.processy_.symvalu_, 0);
    ppAttributes(p->u.processy_.attributes_, 0);
    renderC(')');

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Proc!\n");
    exit(1);
  }
}

void ppAttributes(Attributes p, int _i_)
{
  switch(p->kind)
  {
  case is_Attribe:
    if (_i_ > 0) renderC(_L_PAREN);
    renderC('[');
    ppListAttr(p->u.attribe_.listattr_, 0);
    renderC(']');

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Attribs:
    if (_i_ > 0) renderC(_L_PAREN);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Attributes!\n");
    exit(1);
  }
}

void ppAttr(Attr p, int _i_)
{
  switch(p->kind)
  {
  case is_Attrs:
    if (_i_ > 0) renderC(_L_PAREN);
    ppSymval(p->u.attrs_.symval_, 0);
    renderC('=');
    ppStringval(p->u.attrs_.stringval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Attrn:
    if (_i_ > 0) renderC(_L_PAREN);
    ppSymval(p->u.attrn_.symval_, 0);
    renderC('=');
    ppNumval(p->u.attrn_.numval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Attr!\n");
    exit(1);
  }
}

void ppListAttr(ListAttr listattr, int i)
{
  while(listattr != 0)
  {
    if (listattr->listattr_ == 0)
    {
      ppAttr(listattr->attr_, i);

      listattr = 0;
    }
    else
    {
      ppAttr(listattr->attr_, i);
      renderC(',');
      listattr = listattr->listattr_;
    }
  }
}

void ppPrt(Prt p, int _i_)
{
  switch(p->kind)
  {
  case is_Portx:
    if (_i_ > 0) renderC(_L_PAREN);
    ppNumval(p->u.portx_.numval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Portni:
    if (_i_ > 0) renderC(_L_PAREN);
    ppNumval(p->u.portni_.numval_, 0);
    renderC('.');
    ppSymval(p->u.portni_.symval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Portin:
    if (_i_ > 0) renderC(_L_PAREN);
    ppSymval(p->u.portin_.symval_, 0);
    renderC('.');
    ppNumval(p->u.portin_.numval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Portn:
    if (_i_ > 0) renderC(_L_PAREN);
    ppSymval(p->u.portn_.symval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Porte:
    if (_i_ > 0) renderC(_L_PAREN);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Prt!\n");
    exit(1);
  }
}

void ppComp(Comp p, int _i_)
{
  switch(p->kind)
  {
  case is_Compx:
    if (_i_ > 0) renderC(_L_PAREN);
    ppSymval(p->u.compx_.symval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Compn:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(p->u.compn_.subid_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Compz:
    if (_i_ > 0) renderC(_L_PAREN);
    ppModPath(p->u.compz_.modpath_, 0);
    ppSymval(p->u.compz_.symval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Compa:
    if (_i_ > 0) renderC(_L_PAREN);
    ppRemPath(p->u.compa_.rempath_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Comp!\n");
    exit(1);
  }
}

void ppModPath(ModPath p, int _i_)
{
  switch(p->kind)
  {
  case is_Modpa:
    if (_i_ > 0) renderC(_L_PAREN);
    renderC('/');
    ppSymval(p->u.modpa_.symval_, 0);
    renderC('/');

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Modpx:
    if (_i_ > 0) renderC(_L_PAREN);
    ppSymval(p->u.modpx_.symval_, 0);
    renderC('/');

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Modpy:
    if (_i_ > 0) renderC(_L_PAREN);
    ppModPath(p->u.modpy_.modpath_, 0);
    ppSymval(p->u.modpy_.symval_, 0);
    renderC('/');

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Modps:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(p->u.modps_.stringvar_, 0);
    renderC('/');

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing ModPath!\n");
    exit(1);
  }
}

void ppRemPath(RemPath p, int _i_)
{
  switch(p->kind)
  {
  case is_RemPatha:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(p->u.rempatha_.validimport_, 0);
    renderC('.');
    ppSymval(p->u.rempatha_.symval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing RemPath!\n");
    exit(1);
  }
}

void ppArgument(Argument p, int _i_)
{
  switch(p->kind)
  {
  case is_Argumentx:
    if (_i_ > 0) renderC(_L_PAREN);
    ppStringval(p->u.argumentx_.stringval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Argument!\n");
    exit(1);
  }
}

void ppListArgument(ListArgument listargument, int i)
{
  while(listargument != 0)
  {
    if (listargument->listargument_ == 0)
    {
      ppArgument(listargument->argument_, i);
      renderS("");
      listargument = 0;
    }
    else
    {
      ppArgument(listargument->argument_, i);
      renderS("");
      listargument = listargument->listargument_;
    }
  }
}

void ppNumassgn(Numassgn p, int _i_)
{
  switch(p->kind)
  {
  case is_NumAssgnv:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(p->u.numassgnv_.numvar_, 0);
    renderC('=');
    ppNumval(p->u.numassgnv_.numval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Numassgn!\n");
    exit(1);
  }
}

void ppStrassgn(Strassgn p, int _i_)
{
  switch(p->kind)
  {
  case is_StrAssgnv:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(p->u.strassgnv_.stringvar_, 0);
    renderC('=');
    ppStringval(p->u.strassgnv_.stringval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Strassgn!\n");
    exit(1);
  }
}

void ppSymAssgn(SymAssgn p, int _i_)
{
  switch(p->kind)
  {
  case is_SymAssgni:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(p->u.symassgni_.symvar_, 0);
    renderC('=');
    ppSymval(p->u.symassgni_.symval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing SymAssgn!\n");
    exit(1);
  }
}

void ppNumval(Numval p, int _i_)
{
  switch(p->kind)
  {
  case is_NumVali:
    if (_i_ > 0) renderC(_L_PAREN);
    ppInteger(p->u.numvali_.integer_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_NumValv:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(p->u.numvalv_.numvar_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Numval!\n");
    exit(1);
  }
}

void ppStringval(Stringval p, int _i_)
{
  switch(p->kind)
  {
  case is_StringVals:
    if (_i_ > 0) renderC(_L_PAREN);
    ppString(p->u.stringvals_.string_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_StringValv:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(p->u.stringvalv_.stringvar_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_StringVale:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(p->u.stringvale_.envar_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Stringval!\n");
    exit(1);
  }
}

void ppSymval(Symval p, int _i_)
{
  switch(p->kind)
  {
  case is_Symvalv:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(p->u.symvalv_.symvar_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Symvali:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(p->u.symvali_.id_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_SymVale:
    if (_i_ > 0) renderC(_L_PAREN);
    ppIdent(p->u.symvale_.envar_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Symval!\n");
    exit(1);
  }
}

void ppInclude(Include p, int _i_)
{
  switch(p->kind)
  {
  case is_Inc1:
    if (_i_ > 0) renderC(_L_PAREN);
    renderS("include");

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Inc2:
    if (_i_ > 0) renderC(_L_PAREN);
    renderS("INCLUDE");

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Include!\n");
    exit(1);
  }
}

void ppPrefix(Prefix p, int _i_)
{
  switch(p->kind)
  {
  case is_Prefu:
    if (_i_ > 0) renderC(_L_PAREN);
    renderS("PREFIX");

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Prefl:
    if (_i_ > 0) renderC(_L_PAREN);
    renderS("prefix");

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Prefix!\n");
    exit(1);
  }
}

void ppValidConfig(ValidConfig p, int _i_)
{
  switch(p->kind)
  {
  case is_Validcfg:
    if (_i_ > 0) renderC(_L_PAREN);
    renderS("StreamWork:");
    ppListEntry(p->u.validcfg_.listentry_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_Validcfgd:
    if (_i_ > 0) renderC(_L_PAREN);
    renderS("---");
    renderS("StreamWork:");
    renderC('{');
    ppListCentry(p->u.validcfgd_.listcentry_, 0);
    renderC('}');

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing ValidConfig!\n");
    exit(1);
  }
}

void ppCentry(Centry p, int _i_)
{
  switch(p->kind)
  {
  case is_CfgcEntrya:
    if (_i_ > 0) renderC(_L_PAREN);
    ppKeyVal(p->u.cfgcentrya_.keyval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_CfgcEntryb:
    if (_i_ > 0) renderC(_L_PAREN);
    ppKeyName(p->u.cfgcentryb_.keyname_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Centry!\n");
    exit(1);
  }
}

void ppListCentry(ListCentry listcentry, int i)
{
  while(listcentry != 0)
  {
    if (listcentry->listcentry_ == 0)
    {
      ppCentry(listcentry->centry_, i);
      renderC(',');
      listcentry = 0;
    }
    else
    {
      ppCentry(listcentry->centry_, i);
      renderC(',');
      listcentry = listcentry->listcentry_;
    }
  }
}

void ppEntry(Entry p, int _i_)
{
  switch(p->kind)
  {
  case is_CfgEntrya:
    if (_i_ > 0) renderC(_L_PAREN);
    ppKeyVal(p->u.cfgentrya_.keyval_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_CfgEntryb:
    if (_i_ > 0) renderC(_L_PAREN);
    ppKeyName(p->u.cfgentryb_.keyname_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing Entry!\n");
    exit(1);
  }
}

void ppListEntry(ListEntry listentry, int i)
{
  while(listentry != 0)
  {
    if (listentry->listentry_ == 0)
    {
      ppEntry(listentry->entry_, i);
      renderS("");
      listentry = 0;
    }
    else
    {
      ppEntry(listentry->entry_, i);
      renderS("");
      listentry = listentry->listentry_;
    }
  }
}

void ppKeyVal(KeyVal p, int _i_)
{
  switch(p->kind)
  {
  case is_CfgKeyvalint:
    if (_i_ > 0) renderC(_L_PAREN);
    ppKeyName(p->u.cfgkeyvalint_.keyname_, 0);
    ppInteger(p->u.cfgkeyvalint_.integer_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_CfgKeyvalstr:
    if (_i_ > 0) renderC(_L_PAREN);
    ppKeyName(p->u.cfgkeyvalstr_.keyname_, 0);
    ppString(p->u.cfgkeyvalstr_.string_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_CfgKeyDate:
    if (_i_ > 0) renderC(_L_PAREN);
    ppKeyName(p->u.cfgkeydate_.keyname_, 0);
    ppIdent(p->u.cfgkeydate_.date_, 0);

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing KeyVal!\n");
    exit(1);
  }
}

void ppKeyName(KeyName p, int _i_)
{
  switch(p->kind)
  {
  case is_KeynameS:
    if (_i_ > 0) renderC(_L_PAREN);
    ppSymval(p->u.keynames_.symval_, 0);
    renderC(':');

    if (_i_ > 0) renderC(_R_PAREN);
    break;

  case is_KeynameM:
    if (_i_ > 0) renderC(_L_PAREN);
    ppModPath(p->u.keynamem_.modpath_, 0);
    ppSymval(p->u.keynamem_.symval_, 0);
    renderC(':');

    if (_i_ > 0) renderC(_R_PAREN);
    break;


  default:
    fprintf(stderr, "Error: bad kind field when printing KeyName!\n");
    exit(1);
  }
}

void ppInteger(Integer n, int i)
{
  char tmp[16];
  sprintf(tmp, "%d", n);
  bufAppendS(tmp);
}
void ppDouble(Double d, int i)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppendS(tmp);
}
void ppChar(Char c, int i)
{
  bufAppendC('\'');
  bufAppendC(c);
  bufAppendC('\'');
}
void ppString(String s, int i)
{
  bufAppendC('\"');
  bufAppendS(s);
  bufAppendC('\"');
}
void ppIdent(String s, int i)
{
  renderS(s);
}

void ppNumvar(String s, int i)
{
  renderS(s);
}


void ppStringvar(String s, int i)
{
  renderS(s);
}


void ppEnvar(String s, int i)
{
  renderS(s);
}


void ppSymvar(String s, int i)
{
  renderS(s);
}


void ppSubId(String s, int i)
{
  renderS(s);
}


void ppId(String s, int i)
{
  renderS(s);
}


void ppValidImport(String s, int i)
{
  renderS(s);
}


void ppDate(String s, int i)
{
  renderS(s);
}


void shValide(Valide p)
{
  switch(p->kind)
  {
  case is_CFGvalid:
    bufAppendC('(');

    bufAppendS("CFGvalid");

    bufAppendC(' ');

    shValidConfig(p->u.cfgvalid_.validconfig_);

    bufAppendC(')');

    break;
  case is_SWvalid:
    bufAppendC('(');

    bufAppendS("SWvalid");

    bufAppendC(' ');

    shValidSW(p->u.swvalid_.validsw_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Valide!\n");
    exit(1);
  }
}

void shValidSW(ValidSW p)
{
  switch(p->kind)
  {
  case is_Valid:
    bufAppendC('(');

    bufAppendS("Valid");

    bufAppendC(' ');

    shListStm(p->u.valid_.liststm_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing ValidSW!\n");
    exit(1);
  }
}

void shStm(Stm p)
{
  switch(p->kind)
  {
  case is_StmPrefix:
    bufAppendC('(');

    bufAppendS("StmPrefix");

    bufAppendC(' ');

    shPrefix(p->u.stmprefix_.prefix_);
  bufAppendC(' ');
    shStringval(p->u.stmprefix_.stringval_);

    bufAppendC(')');

    break;
  case is_Stminc:
    bufAppendC('(');

    bufAppendS("Stminc");

    bufAppendC(' ');

    shInclude(p->u.stminc_.include_);
  bufAppendC(' ');
    shStringval(p->u.stminc_.stringval_);

    bufAppendC(')');

    break;
  case is_Stmx:
    bufAppendC('(');

    bufAppendS("Stmx");

    bufAppendC(' ');

    shDataFlow(p->u.stmx_.dataflow_);

    bufAppendC(')');

    break;
  case is_Stmn:
    bufAppendC('(');

    bufAppendS("Stmn");

    bufAppendC(' ');

    shNumassgn(p->u.stmn_.numassgn_);

    bufAppendC(')');

    break;
  case is_Stms:
    bufAppendC('(');

    bufAppendS("Stms");

    bufAppendC(' ');

    shStrassgn(p->u.stms_.strassgn_);

    bufAppendC(')');

    break;
  case is_Stmb:
    bufAppendC('(');

    bufAppendS("Stmb");

    bufAppendC(' ');

    shSymAssgn(p->u.stmb_.symassgn_);

    bufAppendC(')');

    break;
  case is_Stmh:
    bufAppendC('(');

    bufAppendS("Stmh");

    bufAppendC(' ');

    shHermt(p->u.stmh_.hermt_);

    bufAppendC(')');

    break;
  case is_Stmnet:
    bufAppendC('(');

    bufAppendS("Stmnet");

    bufAppendC(' ');

    shSubdef(p->u.stmnet_.subdef_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Stm!\n");
    exit(1);
  }
}

void shListStm(ListStm liststm)
{
  bufAppendC('[');
  while(liststm != 0)
  {
    if (liststm->liststm_)
    {
      shStm(liststm->stm_);
      bufAppendS(", ");
      liststm = liststm->liststm_;
    }
    else
    {
      shStm(liststm->stm_);
      liststm = 0;
    }
  }
  bufAppendC(']');
}

void shSubdef(Subdef p)
{
  switch(p->kind)
  {
  case is_Snet:
    bufAppendC('(');

    bufAppendS("Snet");

    bufAppendC(' ');

    shIdent(p->u.snet_.subid_);
  bufAppendC(' ');
    shListSubnet(p->u.snet_.listsubnet_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Subdef!\n");
    exit(1);
  }
}

void shSubnet(Subnet p)
{
  switch(p->kind)
  {
  case is_Sneth:
    bufAppendC('(');

    bufAppendS("Sneth");

    bufAppendC(' ');

    shHermt(p->u.sneth_.hermt_);

    bufAppendC(')');

    break;
  case is_Snets:
    bufAppendC('(');

    bufAppendS("Snets");

    bufAppendC(' ');

    shDataFlow(p->u.snets_.dataflow_);

    bufAppendC(')');

    break;
  case is_Snetin:
    bufAppendC('(');

    bufAppendS("Snetin");

    bufAppendC(' ');

    shExtPortIn(p->u.snetin_.extportin_);

    bufAppendC(')');

    break;
  case is_Snetout:
    bufAppendC('(');

    bufAppendS("Snetout");

    bufAppendC(' ');

    shExtPortOut(p->u.snetout_.extportout_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Subnet!\n");
    exit(1);
  }
}

void shListSubnet(ListSubnet listsubnet)
{
  bufAppendC('[');
  while(listsubnet != 0)
  {
    if (listsubnet->listsubnet_)
    {
      shSubnet(listsubnet->subnet_);
      bufAppendS(", ");
      listsubnet = listsubnet->listsubnet_;
    }
    else
    {
      shSubnet(listsubnet->subnet_);
      listsubnet = 0;
    }
  }
  bufAppendC(']');
}

void shExtPortIn(ExtPortIn p)
{
  switch(p->kind)
  {
  case is_Extin:
    bufAppendC('(');

    bufAppendS("Extin");

    bufAppendC(' ');

    shProc(p->u.extin_.proc_);
  bufAppendC(' ');
    shPrt(p->u.extin_.prt_);
  bufAppendC(' ');
    shLarrow(p->u.extin_.larrow_);
  bufAppendC(' ');
    shTab(p->u.extin_.tab_);

    bufAppendC(')');

    break;
  case is_ExtinR:
    bufAppendC('(');

    bufAppendS("ExtinR");

    bufAppendC(' ');

    shTab(p->u.extinr_.tab_);
  bufAppendC(' ');
    shRarrow(p->u.extinr_.rarrow_);
  bufAppendC(' ');
    shPrt(p->u.extinr_.prt_);
  bufAppendC(' ');
    shProc(p->u.extinr_.proc_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing ExtPortIn!\n");
    exit(1);
  }
}

void shExtPortOut(ExtPortOut p)
{
  switch(p->kind)
  {
  case is_Extout:
    bufAppendC('(');

    bufAppendS("Extout");

    bufAppendC(' ');

    shTab(p->u.extout_.tab_);
  bufAppendC(' ');
    shLarrow(p->u.extout_.larrow_);
  bufAppendC(' ');
    shPrt(p->u.extout_.prt_);
  bufAppendC(' ');
    shProc(p->u.extout_.proc_);

    bufAppendC(')');

    break;
  case is_Extoutr:
    bufAppendC('(');

    bufAppendS("Extoutr");

    bufAppendC(' ');

    shProc(p->u.extoutr_.proc_);
  bufAppendC(' ');
    shPrt(p->u.extoutr_.prt_);
  bufAppendC(' ');
    shRarrow(p->u.extoutr_.rarrow_);
  bufAppendC(' ');
    shTab(p->u.extoutr_.tab_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing ExtPortOut!\n");
    exit(1);
  }
}

void shTab(Tab p)
{
  switch(p->kind)
  {
  case is_Tabn:
    bufAppendC('(');

    bufAppendS("Tabn");

    bufAppendC(' ');

    shNumval(p->u.tabn_.numval_);

    bufAppendC(')');

    break;
  case is_Tabs:
    bufAppendC('(');

    bufAppendS("Tabs");

    bufAppendC(' ');

    shSymval(p->u.tabs_.symval_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Tab!\n");
    exit(1);
  }
}

void shDataFlow(DataFlow p)
{
  switch(p->kind)
  {
  case is_Streamx:
    bufAppendC('(');

    bufAppendS("Streamx");

    bufAppendC(' ');

    shProc(p->u.streamx_.proc_1);
  bufAppendC(' ');
    shPrt(p->u.streamx_.prt_1);
  bufAppendC(' ');
    shLarrow(p->u.streamx_.larrow_);
  bufAppendC(' ');
    shPrt(p->u.streamx_.prt_2);
  bufAppendC(' ');
    shProc(p->u.streamx_.proc_2);

    bufAppendC(')');

    break;
  case is_Streamrx:
    bufAppendC('(');

    bufAppendS("Streamrx");

    bufAppendC(' ');

    shProc(p->u.streamrx_.proc_1);
  bufAppendC(' ');
    shPrt(p->u.streamrx_.prt_1);
  bufAppendC(' ');
    shRarrow(p->u.streamrx_.rarrow_);
  bufAppendC(' ');
    shPrt(p->u.streamrx_.prt_2);
  bufAppendC(' ');
    shProc(p->u.streamrx_.proc_2);

    bufAppendC(')');

    break;
  case is_Streamls:
    bufAppendC('(');

    bufAppendS("Streamls");

    bufAppendC(' ');

    shProc(p->u.streamls_.proc_1);
  bufAppendC(' ');
    shPrt(p->u.streamls_.prt_1);
  bufAppendC(' ');
    shLSarrow(p->u.streamls_.lsarrow_);
  bufAppendC(' ');
    shPrt(p->u.streamls_.prt_2);
  bufAppendC(' ');
    shProc(p->u.streamls_.proc_2);

    bufAppendC(')');

    break;
  case is_Streamrs:
    bufAppendC('(');

    bufAppendS("Streamrs");

    bufAppendC(' ');

    shProc(p->u.streamrs_.proc_1);
  bufAppendC(' ');
    shPrt(p->u.streamrs_.prt_1);
  bufAppendC(' ');
    shRSarrow(p->u.streamrs_.rsarrow_);
  bufAppendC(' ');
    shPrt(p->u.streamrs_.prt_2);
  bufAppendC(' ');
    shProc(p->u.streamrs_.proc_2);

    bufAppendC(')');

    break;
  case is_Streamy:
    bufAppendC('(');

    bufAppendS("Streamy");

    bufAppendC(' ');

    shDataFlow(p->u.streamy_.dataflow_);
  bufAppendC(' ');
    shPrt(p->u.streamy_.prt_1);
  bufAppendC(' ');
    shLarrow(p->u.streamy_.larrow_);
  bufAppendC(' ');
    shPrt(p->u.streamy_.prt_2);
  bufAppendC(' ');
    shProc(p->u.streamy_.proc_);

    bufAppendC(')');

    break;
  case is_Streamry:
    bufAppendC('(');

    bufAppendS("Streamry");

    bufAppendC(' ');

    shDataFlow(p->u.streamry_.dataflow_);
  bufAppendC(' ');
    shPrt(p->u.streamry_.prt_1);
  bufAppendC(' ');
    shRarrow(p->u.streamry_.rarrow_);
  bufAppendC(' ');
    shPrt(p->u.streamry_.prt_2);
  bufAppendC(' ');
    shProc(p->u.streamry_.proc_);

    bufAppendC(')');

    break;
  case is_Streamlsy:
    bufAppendC('(');

    bufAppendS("Streamlsy");

    bufAppendC(' ');

    shDataFlow(p->u.streamlsy_.dataflow_);
  bufAppendC(' ');
    shPrt(p->u.streamlsy_.prt_1);
  bufAppendC(' ');
    shLSarrow(p->u.streamlsy_.lsarrow_);
  bufAppendC(' ');
    shPrt(p->u.streamlsy_.prt_2);
  bufAppendC(' ');
    shProc(p->u.streamlsy_.proc_);

    bufAppendC(')');

    break;
  case is_Streamrsy:
    bufAppendC('(');

    bufAppendS("Streamrsy");

    bufAppendC(' ');

    shDataFlow(p->u.streamrsy_.dataflow_);
  bufAppendC(' ');
    shPrt(p->u.streamrsy_.prt_1);
  bufAppendC(' ');
    shRSarrow(p->u.streamrsy_.rsarrow_);
  bufAppendC(' ');
    shPrt(p->u.streamrsy_.prt_2);
  bufAppendC(' ');
    shProc(p->u.streamrsy_.proc_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing DataFlow!\n");
    exit(1);
  }
}

void shLarrow(Larrow p)
{
  switch(p->kind)
  {
  case is_Arrowx:
    bufAppendC('(');

    bufAppendS("Arrowx");

    bufAppendC(' ');

    shTypeDef(p->u.arrowx_.typedef_);
  bufAppendC(' ');
    shBuffsize(p->u.arrowx_.buffsize_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Larrow!\n");
    exit(1);
  }
}

void shRarrow(Rarrow p)
{
  switch(p->kind)
  {
  case is_Arrowr:
    bufAppendC('(');

    bufAppendS("Arrowr");

    bufAppendC(' ');

    shTypeDef(p->u.arrowr_.typedef_);
  bufAppendC(' ');
    shBuffsize(p->u.arrowr_.buffsize_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Rarrow!\n");
    exit(1);
  }
}

void shLSarrow(LSarrow p)
{
  switch(p->kind)
  {
  case is_Arrowsl:
    bufAppendC('(');

    bufAppendS("Arrowsl");

    bufAppendC(' ');

    shTypeDef(p->u.arrowsl_.typedef_);
  bufAppendC(' ');
    shBuffsize(p->u.arrowsl_.buffsize_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing LSarrow!\n");
    exit(1);
  }
}

void shRSarrow(RSarrow p)
{
  switch(p->kind)
  {
  case is_Arrowsr:
    bufAppendC('(');

    bufAppendS("Arrowsr");

    bufAppendC(' ');

    shTypeDef(p->u.arrowsr_.typedef_);
  bufAppendC(' ');
    shBuffsize(p->u.arrowsr_.buffsize_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing RSarrow!\n");
    exit(1);
  }
}

void shTypeDef(TypeDef p)
{
  switch(p->kind)
  {
  case is_Typedefa:
    bufAppendC('(');

    bufAppendS("Typedefa");

    bufAppendC(' ');

    shSymvalu(p->u.typedefa_.symvalu_);

    bufAppendC(')');

    break;
  case is_Typedefb:
    bufAppendC('(');

    bufAppendS("Typedefb");

    bufAppendC(' ');

    shSymvalu(p->u.typedefb_.symvalu_1);
  bufAppendC(' ');
    shSymvalu(p->u.typedefb_.symvalu_2);

    bufAppendC(')');

    break;
  case is_Typedefnull:

    bufAppendS("Typedefnull");




    break;
  case is_TypedefArray:
    bufAppendC('(');

    bufAppendS("TypedefArray");

    bufAppendC(' ');

    shNumval(p->u.typedefarray_.numval_);
  bufAppendC(' ');
    shTypeDef(p->u.typedefarray_.typedef_);

    bufAppendC(')');

    break;
  case is_Typdefl:
    bufAppendC('(');

    bufAppendS("Typdefl");

    bufAppendC(' ');

    shTypeDef(p->u.typdefl_.typedef_1);
  bufAppendC(' ');
    shTypeDef(p->u.typdefl_.typedef_2);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing TypeDef!\n");
    exit(1);
  }
}

void shBuffsize(Buffsize p)
{
  switch(p->kind)
  {
  case is_Bufszi:
    bufAppendC('(');

    bufAppendS("Bufszi");

    bufAppendC(' ');

    shNumval(p->u.bufszi_.numval_);

    bufAppendC(')');

    break;
  case is_Bufsze:

    bufAppendS("Bufsze");




    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Buffsize!\n");
    exit(1);
  }
}

void shHermt(Hermt p)
{
  switch(p->kind)
  {
  case is_Hermtx:
    bufAppendC('(');

    bufAppendS("Hermtx");

    bufAppendC(' ');

    shSymvalu(p->u.hermtx_.symvalu_);
  bufAppendC(' ');
    shComp(p->u.hermtx_.comp_);
  bufAppendC(' ');
    shListArgument(p->u.hermtx_.listargument_);

    bufAppendC(')');

    break;
  case is_Hermty:
    bufAppendC('(');

    bufAppendS("Hermty");

    bufAppendC(' ');

    shSymvalu(p->u.hermty_.symvalu_);
  bufAppendC(' ');
    shListArgument(p->u.hermty_.listargument_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Hermt!\n");
    exit(1);
  }
}

void shSymvalu(Symvalu p)
{
  switch(p->kind)
  {
  case is_Symvaluv:
    bufAppendC('(');

    bufAppendS("Symvaluv");

    bufAppendC(' ');

    shSymval(p->u.symvaluv_.symval_);

    bufAppendC(')');

    break;
  case is_Symvaluu:

    bufAppendS("Symvaluu");




    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Symvalu!\n");
    exit(1);
  }
}

void shProc(Proc p)
{
  switch(p->kind)
  {
  case is_Processx:
    bufAppendC('(');

    bufAppendS("Processx");

    bufAppendC(' ');

    shSymvalu(p->u.processx_.symvalu_);
  bufAppendC(' ');
    shComp(p->u.processx_.comp_);
  bufAppendC(' ');
    shListArgument(p->u.processx_.listargument_);
  bufAppendC(' ');
    shAttributes(p->u.processx_.attributes_);

    bufAppendC(')');

    break;
  case is_Processy:
    bufAppendC('(');

    bufAppendS("Processy");

    bufAppendC(' ');

    shSymvalu(p->u.processy_.symvalu_);
  bufAppendC(' ');
    shAttributes(p->u.processy_.attributes_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Proc!\n");
    exit(1);
  }
}

void shAttributes(Attributes p)
{
  switch(p->kind)
  {
  case is_Attribe:
    bufAppendC('(');

    bufAppendS("Attribe");

    bufAppendC(' ');

    shListAttr(p->u.attribe_.listattr_);

    bufAppendC(')');

    break;
  case is_Attribs:

    bufAppendS("Attribs");




    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Attributes!\n");
    exit(1);
  }
}

void shAttr(Attr p)
{
  switch(p->kind)
  {
  case is_Attrs:
    bufAppendC('(');

    bufAppendS("Attrs");

    bufAppendC(' ');

    shSymval(p->u.attrs_.symval_);
  bufAppendC(' ');
    shStringval(p->u.attrs_.stringval_);

    bufAppendC(')');

    break;
  case is_Attrn:
    bufAppendC('(');

    bufAppendS("Attrn");

    bufAppendC(' ');

    shSymval(p->u.attrn_.symval_);
  bufAppendC(' ');
    shNumval(p->u.attrn_.numval_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Attr!\n");
    exit(1);
  }
}

void shListAttr(ListAttr listattr)
{
  bufAppendC('[');
  while(listattr != 0)
  {
    if (listattr->listattr_)
    {
      shAttr(listattr->attr_);
      bufAppendS(", ");
      listattr = listattr->listattr_;
    }
    else
    {
      shAttr(listattr->attr_);
      listattr = 0;
    }
  }
  bufAppendC(']');
}

void shPrt(Prt p)
{
  switch(p->kind)
  {
  case is_Portx:
    bufAppendC('(');

    bufAppendS("Portx");

    bufAppendC(' ');

    shNumval(p->u.portx_.numval_);

    bufAppendC(')');

    break;
  case is_Portni:
    bufAppendC('(');

    bufAppendS("Portni");

    bufAppendC(' ');

    shNumval(p->u.portni_.numval_);
  bufAppendC(' ');
    shSymval(p->u.portni_.symval_);

    bufAppendC(')');

    break;
  case is_Portin:
    bufAppendC('(');

    bufAppendS("Portin");

    bufAppendC(' ');

    shSymval(p->u.portin_.symval_);
  bufAppendC(' ');
    shNumval(p->u.portin_.numval_);

    bufAppendC(')');

    break;
  case is_Portn:
    bufAppendC('(');

    bufAppendS("Portn");

    bufAppendC(' ');

    shSymval(p->u.portn_.symval_);

    bufAppendC(')');

    break;
  case is_Porte:

    bufAppendS("Porte");




    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Prt!\n");
    exit(1);
  }
}

void shComp(Comp p)
{
  switch(p->kind)
  {
  case is_Compx:
    bufAppendC('(');

    bufAppendS("Compx");

    bufAppendC(' ');

    shSymval(p->u.compx_.symval_);

    bufAppendC(')');

    break;
  case is_Compn:
    bufAppendC('(');

    bufAppendS("Compn");

    bufAppendC(' ');

    shIdent(p->u.compn_.subid_);

    bufAppendC(')');

    break;
  case is_Compz:
    bufAppendC('(');

    bufAppendS("Compz");

    bufAppendC(' ');

    shModPath(p->u.compz_.modpath_);
  bufAppendC(' ');
    shSymval(p->u.compz_.symval_);

    bufAppendC(')');

    break;
  case is_Compa:
    bufAppendC('(');

    bufAppendS("Compa");

    bufAppendC(' ');

    shRemPath(p->u.compa_.rempath_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Comp!\n");
    exit(1);
  }
}

void shModPath(ModPath p)
{
  switch(p->kind)
  {
  case is_Modpa:
    bufAppendC('(');

    bufAppendS("Modpa");

    bufAppendC(' ');

    shSymval(p->u.modpa_.symval_);

    bufAppendC(')');

    break;
  case is_Modpx:
    bufAppendC('(');

    bufAppendS("Modpx");

    bufAppendC(' ');

    shSymval(p->u.modpx_.symval_);

    bufAppendC(')');

    break;
  case is_Modpy:
    bufAppendC('(');

    bufAppendS("Modpy");

    bufAppendC(' ');

    shModPath(p->u.modpy_.modpath_);
  bufAppendC(' ');
    shSymval(p->u.modpy_.symval_);

    bufAppendC(')');

    break;
  case is_Modps:
    bufAppendC('(');

    bufAppendS("Modps");

    bufAppendC(' ');

    shIdent(p->u.modps_.stringvar_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing ModPath!\n");
    exit(1);
  }
}

void shRemPath(RemPath p)
{
  switch(p->kind)
  {
  case is_RemPatha:
    bufAppendC('(');

    bufAppendS("RemPatha");

    bufAppendC(' ');

    shIdent(p->u.rempatha_.validimport_);
  bufAppendC(' ');
    shSymval(p->u.rempatha_.symval_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing RemPath!\n");
    exit(1);
  }
}

void shArgument(Argument p)
{
  switch(p->kind)
  {
  case is_Argumentx:
    bufAppendC('(');

    bufAppendS("Argumentx");

    bufAppendC(' ');

    shStringval(p->u.argumentx_.stringval_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Argument!\n");
    exit(1);
  }
}

void shListArgument(ListArgument listargument)
{
  bufAppendC('[');
  while(listargument != 0)
  {
    if (listargument->listargument_)
    {
      shArgument(listargument->argument_);
      bufAppendS(", ");
      listargument = listargument->listargument_;
    }
    else
    {
      shArgument(listargument->argument_);
      listargument = 0;
    }
  }
  bufAppendC(']');
}

void shNumassgn(Numassgn p)
{
  switch(p->kind)
  {
  case is_NumAssgnv:
    bufAppendC('(');

    bufAppendS("NumAssgnv");

    bufAppendC(' ');

    shIdent(p->u.numassgnv_.numvar_);
  bufAppendC(' ');
    shNumval(p->u.numassgnv_.numval_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Numassgn!\n");
    exit(1);
  }
}

void shStrassgn(Strassgn p)
{
  switch(p->kind)
  {
  case is_StrAssgnv:
    bufAppendC('(');

    bufAppendS("StrAssgnv");

    bufAppendC(' ');

    shIdent(p->u.strassgnv_.stringvar_);
  bufAppendC(' ');
    shStringval(p->u.strassgnv_.stringval_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Strassgn!\n");
    exit(1);
  }
}

void shSymAssgn(SymAssgn p)
{
  switch(p->kind)
  {
  case is_SymAssgni:
    bufAppendC('(');

    bufAppendS("SymAssgni");

    bufAppendC(' ');

    shIdent(p->u.symassgni_.symvar_);
  bufAppendC(' ');
    shSymval(p->u.symassgni_.symval_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing SymAssgn!\n");
    exit(1);
  }
}

void shNumval(Numval p)
{
  switch(p->kind)
  {
  case is_NumVali:
    bufAppendC('(');

    bufAppendS("NumVali");

    bufAppendC(' ');

    shInteger(p->u.numvali_.integer_);

    bufAppendC(')');

    break;
  case is_NumValv:
    bufAppendC('(');

    bufAppendS("NumValv");

    bufAppendC(' ');

    shIdent(p->u.numvalv_.numvar_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Numval!\n");
    exit(1);
  }
}

void shStringval(Stringval p)
{
  switch(p->kind)
  {
  case is_StringVals:
    bufAppendC('(');

    bufAppendS("StringVals");

    bufAppendC(' ');

    shString(p->u.stringvals_.string_);

    bufAppendC(')');

    break;
  case is_StringValv:
    bufAppendC('(');

    bufAppendS("StringValv");

    bufAppendC(' ');

    shIdent(p->u.stringvalv_.stringvar_);

    bufAppendC(')');

    break;
  case is_StringVale:
    bufAppendC('(');

    bufAppendS("StringVale");

    bufAppendC(' ');

    shIdent(p->u.stringvale_.envar_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Stringval!\n");
    exit(1);
  }
}

void shSymval(Symval p)
{
  switch(p->kind)
  {
  case is_Symvalv:
    bufAppendC('(');

    bufAppendS("Symvalv");

    bufAppendC(' ');

    shIdent(p->u.symvalv_.symvar_);

    bufAppendC(')');

    break;
  case is_Symvali:
    bufAppendC('(');

    bufAppendS("Symvali");

    bufAppendC(' ');

    shIdent(p->u.symvali_.id_);

    bufAppendC(')');

    break;
  case is_SymVale:
    bufAppendC('(');

    bufAppendS("SymVale");

    bufAppendC(' ');

    shIdent(p->u.symvale_.envar_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Symval!\n");
    exit(1);
  }
}

void shInclude(Include p)
{
  switch(p->kind)
  {
  case is_Inc1:

    bufAppendS("Inc1");




    break;
  case is_Inc2:

    bufAppendS("Inc2");




    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Include!\n");
    exit(1);
  }
}

void shPrefix(Prefix p)
{
  switch(p->kind)
  {
  case is_Prefu:

    bufAppendS("Prefu");




    break;
  case is_Prefl:

    bufAppendS("Prefl");




    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Prefix!\n");
    exit(1);
  }
}

void shValidConfig(ValidConfig p)
{
  switch(p->kind)
  {
  case is_Validcfg:
    bufAppendC('(');

    bufAppendS("Validcfg");

    bufAppendC(' ');

    shListEntry(p->u.validcfg_.listentry_);

    bufAppendC(')');

    break;
  case is_Validcfgd:
    bufAppendC('(');

    bufAppendS("Validcfgd");

    bufAppendC(' ');

    shListCentry(p->u.validcfgd_.listcentry_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing ValidConfig!\n");
    exit(1);
  }
}

void shCentry(Centry p)
{
  switch(p->kind)
  {
  case is_CfgcEntrya:
    bufAppendC('(');

    bufAppendS("CfgcEntrya");

    bufAppendC(' ');

    shKeyVal(p->u.cfgcentrya_.keyval_);

    bufAppendC(')');

    break;
  case is_CfgcEntryb:
    bufAppendC('(');

    bufAppendS("CfgcEntryb");

    bufAppendC(' ');

    shKeyName(p->u.cfgcentryb_.keyname_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Centry!\n");
    exit(1);
  }
}

void shListCentry(ListCentry listcentry)
{
  bufAppendC('[');
  while(listcentry != 0)
  {
    if (listcentry->listcentry_)
    {
      shCentry(listcentry->centry_);
      bufAppendS(", ");
      listcentry = listcentry->listcentry_;
    }
    else
    {
      shCentry(listcentry->centry_);
      listcentry = 0;
    }
  }
  bufAppendC(']');
}

void shEntry(Entry p)
{
  switch(p->kind)
  {
  case is_CfgEntrya:
    bufAppendC('(');

    bufAppendS("CfgEntrya");

    bufAppendC(' ');

    shKeyVal(p->u.cfgentrya_.keyval_);

    bufAppendC(')');

    break;
  case is_CfgEntryb:
    bufAppendC('(');

    bufAppendS("CfgEntryb");

    bufAppendC(' ');

    shKeyName(p->u.cfgentryb_.keyname_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing Entry!\n");
    exit(1);
  }
}

void shListEntry(ListEntry listentry)
{
  bufAppendC('[');
  while(listentry != 0)
  {
    if (listentry->listentry_)
    {
      shEntry(listentry->entry_);
      bufAppendS(", ");
      listentry = listentry->listentry_;
    }
    else
    {
      shEntry(listentry->entry_);
      listentry = 0;
    }
  }
  bufAppendC(']');
}

void shKeyVal(KeyVal p)
{
  switch(p->kind)
  {
  case is_CfgKeyvalint:
    bufAppendC('(');

    bufAppendS("CfgKeyvalint");

    bufAppendC(' ');

    shKeyName(p->u.cfgkeyvalint_.keyname_);
  bufAppendC(' ');
    shInteger(p->u.cfgkeyvalint_.integer_);

    bufAppendC(')');

    break;
  case is_CfgKeyvalstr:
    bufAppendC('(');

    bufAppendS("CfgKeyvalstr");

    bufAppendC(' ');

    shKeyName(p->u.cfgkeyvalstr_.keyname_);
  bufAppendC(' ');
    shString(p->u.cfgkeyvalstr_.string_);

    bufAppendC(')');

    break;
  case is_CfgKeyDate:
    bufAppendC('(');

    bufAppendS("CfgKeyDate");

    bufAppendC(' ');

    shKeyName(p->u.cfgkeydate_.keyname_);
  bufAppendC(' ');
    shIdent(p->u.cfgkeydate_.date_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing KeyVal!\n");
    exit(1);
  }
}

void shKeyName(KeyName p)
{
  switch(p->kind)
  {
  case is_KeynameS:
    bufAppendC('(');

    bufAppendS("KeynameS");

    bufAppendC(' ');

    shSymval(p->u.keynames_.symval_);

    bufAppendC(')');

    break;
  case is_KeynameM:
    bufAppendC('(');

    bufAppendS("KeynameM");

    bufAppendC(' ');

    shModPath(p->u.keynamem_.modpath_);
  bufAppendC(' ');
    shSymval(p->u.keynamem_.symval_);

    bufAppendC(')');

    break;

  default:
    fprintf(stderr, "Error: bad kind field when showing KeyName!\n");
    exit(1);
  }
}

void shInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppendS(tmp);
}
void shDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppendS(tmp);
}
void shChar(Char c)
{
  bufAppendC('\'');
  bufAppendC(c);
  bufAppendC('\'');
}
void shString(String s)
{
  bufAppendC('\"');
  bufAppendS(s);
  bufAppendC('\"');
}
void shIdent(String s)
{
  bufAppendC('\"');
  bufAppendS(s);
  bufAppendC('\"');
}

void shNumvar(String s)
{
  bufAppendC('\"');
  bufAppendS(s);
  bufAppendC('\"');
}


void shStringvar(String s)
{
  bufAppendC('\"');
  bufAppendS(s);
  bufAppendC('\"');
}


void shEnvar(String s)
{
  bufAppendC('\"');
  bufAppendS(s);
  bufAppendC('\"');
}


void shSymvar(String s)
{
  bufAppendC('\"');
  bufAppendS(s);
  bufAppendC('\"');
}


void shSubId(String s)
{
  bufAppendC('\"');
  bufAppendS(s);
  bufAppendC('\"');
}


void shId(String s)
{
  bufAppendC('\"');
  bufAppendS(s);
  bufAppendC('\"');
}


void shValidImport(String s)
{
  bufAppendC('\"');
  bufAppendS(s);
  bufAppendC('\"');
}


void shDate(String s)
{
  bufAppendC('\"');
  bufAppendS(s);
  bufAppendC('\"');
}


void bufAppendS(const char *s)
{
  int len = strlen(s);
  int n;
  while (cur_ + len > buf_size)
  {
    buf_size *= 2; /* Double the buffer size */
    resizeBuffer();
  }
  for(n = 0; n < len; n++)
  {
    buf_[cur_ + n] = s[n];
  }
  cur_ += len;
  buf_[cur_] = 0;
}
void bufAppendC(const char c)
{
  if (cur_ == buf_size)
  {
    buf_size *= 2; /* Double the buffer size */
    resizeBuffer();
  }
  buf_[cur_] = c;
  cur_++;
  buf_[cur_] = 0;
}
void bufReset(void)
{
  cur_ = 0;
  buf_size = BUFFER_INITIAL;
  resizeBuffer();
  memset(buf_, 0, buf_size);
}
void resizeBuffer(void)
{
  char *temp = (char *) malloc(buf_size);
  if (!temp)
  {
    fprintf(stderr, "Error: Out of memory while attempting to grow buffer!\n");
    exit(1);
  }
  if (buf_)
  {
    strncpy(temp, buf_, buf_size); /* peteg: strlcpy is safer, but not POSIX/ISO C. */
    free(buf_);
  }
  buf_ = temp;
}
char *buf_;
int cur_, buf_size;

