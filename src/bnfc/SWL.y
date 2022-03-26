/* This Bison file was machine-generated by BNFC */
%locations
%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Absyn.h"
typedef struct SWL_buffer_state *YY_BUFFER_STATE;
YY_BUFFER_STATE SWL_scan_string(const char *str);
void SWL_delete_buffer(YY_BUFFER_STATE buf);
extern int yyparse(void);
extern int yylex(void);
extern int SWL_init_lexer(FILE * inp);
extern void yyerror(const char *str);

Valide YY_RESULT_Valide_ = 0;
ValidSW YY_RESULT_ValidSW_ = 0;
ValidConfig YY_RESULT_ValidConfig_ = 0;

Valide pValide(FILE *inp)
{
  SWL_init_lexer(inp);
  int result = yyparse();
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Valide_;
  }
}
Valide psValide(const char *str)
{
  YY_BUFFER_STATE buf;
  SWL_init_lexer(0);
  buf = SWL_scan_string(str);
  int result = yyparse();
  SWL_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Valide_;
  }
}

ValidSW pValidSW(FILE *inp)
{
  SWL_init_lexer(inp);
  int result = yyparse();
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ValidSW_;
  }
}
ValidSW psValidSW(const char *str)
{
  YY_BUFFER_STATE buf;
  SWL_init_lexer(0);
  buf = SWL_scan_string(str);
  int result = yyparse();
  SWL_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ValidSW_;
  }
}

ValidConfig pValidConfig(FILE *inp)
{
  SWL_init_lexer(inp);
  int result = yyparse();
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ValidConfig_;
  }
}
ValidConfig psValidConfig(const char *str)
{
  YY_BUFFER_STATE buf;
  SWL_init_lexer(0);
  buf = SWL_scan_string(str);
  int result = yyparse();
  SWL_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ValidConfig_;
  }
}


ListStm reverseListStm(ListStm l)
{
  ListStm prev = 0;
  ListStm tmp = 0;
  while (l)
  {
    tmp = l->liststm_;
    l->liststm_ = prev;
    prev = l;
    l = tmp;
  }
  return prev;
}
ListSubnet reverseListSubnet(ListSubnet l)
{
  ListSubnet prev = 0;
  ListSubnet tmp = 0;
  while (l)
  {
    tmp = l->listsubnet_;
    l->listsubnet_ = prev;
    prev = l;
    l = tmp;
  }
  return prev;
}
ListAttr reverseListAttr(ListAttr l)
{
  ListAttr prev = 0;
  ListAttr tmp = 0;
  while (l)
  {
    tmp = l->listattr_;
    l->listattr_ = prev;
    prev = l;
    l = tmp;
  }
  return prev;
}
ListArgument reverseListArgument(ListArgument l)
{
  ListArgument prev = 0;
  ListArgument tmp = 0;
  while (l)
  {
    tmp = l->listargument_;
    l->listargument_ = prev;
    prev = l;
    l = tmp;
  }
  return prev;
}
ListCentry reverseListCentry(ListCentry l)
{
  ListCentry prev = 0;
  ListCentry tmp = 0;
  while (l)
  {
    tmp = l->listcentry_;
    l->listcentry_ = prev;
    prev = l;
    l = tmp;
  }
  return prev;
}
ListEntry reverseListEntry(ListEntry l)
{
  ListEntry prev = 0;
  ListEntry tmp = 0;
  while (l)
  {
    tmp = l->listentry_;
    l->listentry_ = prev;
    prev = l;
    l = tmp;
  }
  return prev;
}

%}

%union
{
  int int_;
  char char_;
  double double_;
  char* string_;
  Valide valide_;
  ValidSW validsw_;
  Stm stm_;
  ListStm liststm_;
  Subdef subdef_;
  Subnet subnet_;
  ListSubnet listsubnet_;
  ExtPortIn extportin_;
  ExtPortOut extportout_;
  Tab tab_;
  DataFlow dataflow_;
  Larrow larrow_;
  Rarrow rarrow_;
  LSarrow lsarrow_;
  RSarrow rsarrow_;
  TypeDef typedef_;
  Buffsize buffsize_;
  Hermt hermt_;
  Symvalu symvalu_;
  Proc proc_;
  Attributes attributes_;
  Attr attr_;
  ListAttr listattr_;
  Prt prt_;
  Comp comp_;
  ModPath modpath_;
  RemPath rempath_;
  Argument argument_;
  ListArgument listargument_;
  Numassgn numassgn_;
  Strassgn strassgn_;
  SymAssgn symassgn_;
  Numval numval_;
  Stringval stringval_;
  Symval symval_;
  Include include_;
  Prefix prefix_;
  ValidConfig validconfig_;
  Centry centry_;
  ListCentry listcentry_;
  Entry entry_;
  ListEntry listentry_;
  KeyVal keyval_;
  KeyName keyname_;

}

%token _ERROR_
%token _SYMB_0    /*   ;   */
%token _SYMB_1    /*   {   */
%token _SYMB_2    /*   }   */
%token _SYMB_3    /*   <   */
%token _SYMB_4    /*   -   */
%token _SYMB_5    /*   >   */
%token _SYMB_6    /*   =   */
%token _SYMB_7    /*   .   */
%token _SYMB_8    /*   [   */
%token _SYMB_9    /*   ]   */
%token _SYMB_10    /*   ,   */
%token _SYMB_11    /*   _   */
%token _SYMB_12    /*   (   */
%token _SYMB_13    /*   )   */
%token _SYMB_14    /*   /   */
%token _SYMB_15    /*   StreamWork:   */
%token _SYMB_16    /*   ---   */
%token _SYMB_17    /*   :   */
%token _SYMB_18    /*   INCLUDE   */
%token _SYMB_19    /*   PREFIX   */
%token _SYMB_20    /*   include   */
%token _SYMB_21    /*   prefix   */
%token<string_> _SYMB_22    /*   Numvar   */
%token<string_> _SYMB_23    /*   Stringvar   */
%token<string_> _SYMB_24    /*   Envar   */
%token<string_> _SYMB_25    /*   Symvar   */
%token<string_> _SYMB_26    /*   SubId   */
%token<string_> _SYMB_27    /*   Id   */
%token<string_> _SYMB_28    /*   ValidImport   */
%token<string_> _SYMB_29    /*   Date   */

%type <valide_> Valide
%type <validsw_> ValidSW
%type <stm_> Stm
%type <liststm_> ListStm
%type <subdef_> Subdef
%type <subnet_> Subnet
%type <listsubnet_> ListSubnet
%type <extportin_> ExtPortIn
%type <extportout_> ExtPortOut
%type <tab_> Tab
%type <dataflow_> DataFlow
%type <larrow_> Larrow
%type <rarrow_> Rarrow
%type <lsarrow_> LSarrow
%type <rsarrow_> RSarrow
%type <typedef_> TypeDef
%type <buffsize_> Buffsize
%type <hermt_> Hermt
%type <symvalu_> Symvalu
%type <proc_> Proc
%type <attributes_> Attributes
%type <attr_> Attr
%type <listattr_> ListAttr
%type <prt_> Prt
%type <comp_> Comp
%type <modpath_> ModPath
%type <rempath_> RemPath
%type <argument_> Argument
%type <listargument_> ListArgument
%type <numassgn_> Numassgn
%type <strassgn_> Strassgn
%type <symassgn_> SymAssgn
%type <numval_> Numval
%type <stringval_> Stringval
%type <symval_> Symval
%type <include_> Include
%type <prefix_> Prefix
%type <validconfig_> ValidConfig
%type <centry_> Centry
%type <listcentry_> ListCentry
%type <entry_> Entry
%type <listentry_> ListEntry
%type <keyval_> KeyVal
%type <keyname_> KeyName

%token<string_> _STRING_
%token<int_> _INTEGER_

%start Valide
%%
Valide : ValidConfig { $$ = make_CFGvalid($1); YY_RESULT_Valide_= $$; }
  | ValidSW { $$ = make_SWvalid($1); YY_RESULT_Valide_= $$; }
;
ValidSW : ListStm { $$ = make_Valid(reverseListStm($1)); YY_RESULT_ValidSW_= $$; }
;
Stm : Prefix Stringval { $$ = make_StmPrefix($1, $2);  }
  | Include Stringval { $$ = make_Stminc($1, $2);  }
  | DataFlow { $$ = make_Stmx($1);  }
  | Numassgn { $$ = make_Stmn($1);  }
  | Strassgn { $$ = make_Stms($1);  }
  | SymAssgn { $$ = make_Stmb($1);  }
  | Hermt { $$ = make_Stmh($1);  }
  | Subdef { $$ = make_Stmnet($1);  }
;
ListStm : /* empty */ { $$ = 0;  }
  | ListStm Stm _SYMB_0 { $$ = make_ListStm($2, $1);  }
;
Subdef : _SYMB_26 _SYMB_1 ListSubnet _SYMB_2 { $$ = make_Snet($1, reverseListSubnet($3));  }
;
Subnet : Hermt { $$ = make_Sneth($1);  }
  | DataFlow { $$ = make_Snets($1);  }
  | ExtPortIn { $$ = make_Snetin($1);  }
  | ExtPortOut { $$ = make_Snetout($1);  }
;
ListSubnet : /* empty */ { $$ = 0;  }
  | ListSubnet Subnet _SYMB_0 { $$ = make_ListSubnet($2, $1);  }
;
ExtPortIn : Proc Prt Larrow Tab { $$ = make_Extin($1, $2, $3, $4);  }
  | Tab Rarrow Prt Proc { $$ = make_ExtinR($1, $2, $3, $4);  }
;
ExtPortOut : Tab Larrow Prt Proc { $$ = make_Extout($1, $2, $3, $4);  }
  | Proc Prt Rarrow Tab { $$ = make_Extoutr($1, $2, $3, $4);  }
;
Tab : Numval { $$ = make_Tabn($1);  }
  | Symval { $$ = make_Tabs($1);  }
;
DataFlow : Proc Prt Larrow Prt Proc { $$ = make_Streamx($1, $2, $3, $4, $5);  }
  | Proc Prt Rarrow Prt Proc { $$ = make_Streamrx($1, $2, $3, $4, $5);  }
  | Proc Prt LSarrow Prt Proc { $$ = make_Streamls($1, $2, $3, $4, $5);  }
  | Proc Prt RSarrow Prt Proc { $$ = make_Streamrs($1, $2, $3, $4, $5);  }
  | DataFlow Prt Larrow Prt Proc { $$ = make_Streamy($1, $2, $3, $4, $5);  }
  | DataFlow Prt Rarrow Prt Proc { $$ = make_Streamry($1, $2, $3, $4, $5);  }
  | DataFlow Prt LSarrow Prt Proc { $$ = make_Streamlsy($1, $2, $3, $4, $5);  }
  | DataFlow Prt RSarrow Prt Proc { $$ = make_Streamrsy($1, $2, $3, $4, $5);  }
;
Larrow : _SYMB_3 TypeDef Buffsize _SYMB_4 { $$ = make_Arrowx($2, $3);  }
;
Rarrow : _SYMB_4 TypeDef Buffsize _SYMB_5 { $$ = make_Arrowr($2, $3);  }
;
LSarrow : _SYMB_3 TypeDef Buffsize _SYMB_6 { $$ = make_Arrowsl($2, $3);  }
;
RSarrow : _SYMB_6 TypeDef Buffsize _SYMB_5 { $$ = make_Arrowsr($2, $3);  }
;
TypeDef : Symvalu { $$ = make_Typedefa($1);  }
  | Symvalu _SYMB_7 Symvalu { $$ = make_Typedefb($1, $3);  }
  | /* empty */ { $$ = make_Typedefnull();  }
  | _SYMB_8 Numval _SYMB_9 TypeDef { $$ = make_TypedefArray($2, $4);  }
  | TypeDef _SYMB_10 TypeDef { $$ = make_Typdefl($1, $3);  }
;
Buffsize : Numval { $$ = make_Bufszi($1);  }
  | /* empty */ { $$ = make_Bufsze();  }
;
Hermt : Symvalu Comp ListArgument { $$ = make_Hermtx($1, $2, reverseListArgument($3));  }
  | Symvalu ListArgument { $$ = make_Hermty($1, reverseListArgument($2));  }
;
Symvalu : Symval { $$ = make_Symvaluv($1);  }
  | _SYMB_11 { $$ = make_Symvaluu();  }
;
Proc : _SYMB_12 Symvalu Comp ListArgument Attributes _SYMB_13 { $$ = make_Processx($2, $3, reverseListArgument($4), $5);  }
  | _SYMB_12 Symvalu Attributes _SYMB_13 { $$ = make_Processy($2, $3);  }
;
Attributes : _SYMB_8 ListAttr _SYMB_9 { $$ = make_Attribe($2);  }
  | /* empty */ { $$ = make_Attribs();  }
;
Attr : Symval _SYMB_6 Stringval { $$ = make_Attrs($1, $3);  }
  | Symval _SYMB_6 Numval { $$ = make_Attrn($1, $3);  }
;
ListAttr : /* empty */ { $$ = 0;  }
  | Attr { $$ = make_ListAttr($1, 0);  }
  | Attr _SYMB_10 ListAttr { $$ = make_ListAttr($1, $3);  }
;
Prt : Numval { $$ = make_Portx($1);  }
  | Numval _SYMB_7 Symval { $$ = make_Portni($1, $3);  }
  | Symval _SYMB_7 Numval { $$ = make_Portin($1, $3);  }
  | Symval { $$ = make_Portn($1);  }
  | /* empty */ { $$ = make_Porte();  }
;
Comp : Symval { $$ = make_Compx($1);  }
  | _SYMB_26 { $$ = make_Compn($1);  }
  | ModPath Symval { $$ = make_Compz($1, $2);  }
  | RemPath { $$ = make_Compa($1);  }
;
ModPath : _SYMB_14 Symval _SYMB_14 { $$ = make_Modpa($2);  }
  | Symval _SYMB_14 { $$ = make_Modpx($1);  }
  | ModPath Symval _SYMB_14 { $$ = make_Modpy($1, $2);  }
  | _SYMB_23 _SYMB_14 { $$ = make_Modps($1);  }
;
RemPath : _SYMB_28 _SYMB_7 Symval { $$ = make_RemPatha($1, $3);  }
;
Argument : Stringval { $$ = make_Argumentx($1);  }
;
ListArgument : /* empty */ { $$ = 0;  }
  | ListArgument Argument { $$ = make_ListArgument($2, $1);  }
;
Numassgn : _SYMB_22 _SYMB_6 Numval { $$ = make_NumAssgnv($1, $3);  }
;
Strassgn : _SYMB_23 _SYMB_6 Stringval { $$ = make_StrAssgnv($1, $3);  }
;
SymAssgn : _SYMB_25 _SYMB_6 Symval { $$ = make_SymAssgni($1, $3);  }
;
Numval : _INTEGER_ { $$ = make_NumVali($1);  }
  | _SYMB_22 { $$ = make_NumValv($1);  }
;
Stringval : _STRING_ { $$ = make_StringVals($1);  }
  | _SYMB_23 { $$ = make_StringValv($1);  }
  | _SYMB_24 { $$ = make_StringVale($1);  }
;
Symval : _SYMB_25 { $$ = make_Symvalv($1);  }
  | _SYMB_27 { $$ = make_Symvali($1);  }
  | _SYMB_24 { $$ = make_SymVale($1);  }
;
Include : _SYMB_20 { $$ = make_Inc1();  }
  | _SYMB_18 { $$ = make_Inc2();  }
;
Prefix : _SYMB_19 { $$ = make_Prefu();  }
  | _SYMB_21 { $$ = make_Prefl();  }
;
ValidConfig : _SYMB_15 ListEntry { $$ = make_Validcfg(reverseListEntry($2)); YY_RESULT_ValidConfig_= $$; }
  | _SYMB_16 _SYMB_15 _SYMB_1 ListCentry _SYMB_2 { $$ = make_Validcfgd(reverseListCentry($4)); YY_RESULT_ValidConfig_= $$; }
;
Centry : KeyVal { $$ = make_CfgcEntrya($1);  }
  | KeyName { $$ = make_CfgcEntryb($1);  }
;
ListCentry : /* empty */ { $$ = 0;  }
  | ListCentry Centry _SYMB_10 { $$ = make_ListCentry($2, $1);  }
;
Entry : KeyVal { $$ = make_CfgEntrya($1);  }
  | KeyName { $$ = make_CfgEntryb($1);  }
;
ListEntry : /* empty */ { $$ = 0;  }
  | ListEntry Entry { $$ = make_ListEntry($2, $1);  }
;
KeyVal : KeyName _INTEGER_ { $$ = make_CfgKeyvalint($1, $2);  }
  | KeyName _STRING_ { $$ = make_CfgKeyvalstr($1, $2);  }
  | KeyName _SYMB_29 { $$ = make_CfgKeyDate($1, $2);  }
;
KeyName : Symval _SYMB_17 { $$ = make_KeynameS($1);  }
  | ModPath Symval _SYMB_17 { $$ = make_KeynameM($1, $2);  }
;

%%
void yyerror(const char *str)
{
  extern char *SWLtext;
  fprintf(stderr,"error: %d,%d: %s at %s\n",
  SWLlloc.first_line, SWLlloc.first_column, str, SWLtext);
}
