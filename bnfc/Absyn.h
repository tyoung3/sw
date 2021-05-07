#ifndef ABSYN_HEADER
#define ABSYN_HEADER

/* C++ Abstract Syntax Interface generated by the BNF Converter.*/

/********************   TypeDef Section    ********************/
typedef int Integer;
typedef char Char;
typedef double Double;
typedef char* String;
typedef char* Ident;
typedef char* Numvar;
typedef char* Stringvar;
typedef char* Envar;
typedef char* Symvar;
typedef char* SubId;
typedef char* Id;
typedef char* ValidImport;
typedef char* Date;


/********************   Forward Declarations    ********************/

struct ListStm_;
typedef struct ListStm_ *ListStm;
struct ListSubnet_;
typedef struct ListSubnet_ *ListSubnet;
struct ListArgument_;
typedef struct ListArgument_ *ListArgument;
struct ListEntry_;
typedef struct ListEntry_ *ListEntry;
struct Valide_;
typedef struct Valide_ *Valide;
struct ValidSW_;
typedef struct ValidSW_ *ValidSW;
struct Stm_;
typedef struct Stm_ *Stm;
struct Subdef_;
typedef struct Subdef_ *Subdef;
struct Subnet_;
typedef struct Subnet_ *Subnet;
struct ExtPortIn_;
typedef struct ExtPortIn_ *ExtPortIn;
struct ExtPortOut_;
typedef struct ExtPortOut_ *ExtPortOut;
struct Tab_;
typedef struct Tab_ *Tab;
struct DataFlow_;
typedef struct DataFlow_ *DataFlow;
struct Larrow_;
typedef struct Larrow_ *Larrow;
struct Rarrow_;
typedef struct Rarrow_ *Rarrow;
struct TypeDef_;
typedef struct TypeDef_ *TypeDef;
struct Buffsize_;
typedef struct Buffsize_ *Buffsize;
struct Hermt_;
typedef struct Hermt_ *Hermt;
struct Symvalu_;
typedef struct Symvalu_ *Symvalu;
struct Proc_;
typedef struct Proc_ *Proc;
struct Prt_;
typedef struct Prt_ *Prt;
struct Comp_;
typedef struct Comp_ *Comp;
struct ModPath_;
typedef struct ModPath_ *ModPath;
struct RemPath_;
typedef struct RemPath_ *RemPath;
struct Argument_;
typedef struct Argument_ *Argument;
struct Numassgn_;
typedef struct Numassgn_ *Numassgn;
struct Strassgn_;
typedef struct Strassgn_ *Strassgn;
struct SymAssgn_;
typedef struct SymAssgn_ *SymAssgn;
struct Numval_;
typedef struct Numval_ *Numval;
struct Stringval_;
typedef struct Stringval_ *Stringval;
struct Symval_;
typedef struct Symval_ *Symval;
struct ValidConfig_;
typedef struct ValidConfig_ *ValidConfig;
struct Entry_;
typedef struct Entry_ *Entry;
struct KeyVal_;
typedef struct KeyVal_ *KeyVal;
struct KeyName_;
typedef struct KeyName_ *KeyName;


/********************   Abstract Syntax Classes    ********************/

struct Valide_
{

  enum { is_CFGvalid, is_SWvalid } kind;
  union
  {
    struct { ValidConfig validconfig_; } cfgvalid_;
    struct { ValidSW validsw_; } swvalid_;
  } u;
};

Valide make_CFGvalid(ValidConfig p0);
Valide make_SWvalid(ValidSW p0);

struct ValidSW_
{

  enum { is_Valid } kind;
  union
  {
    struct { ListStm liststm_; } valid_;
  } u;
};

ValidSW make_Valid(ListStm p0);

struct Stm_
{

  enum { is_Stmx, is_Stmn, is_Stms, is_Stmb, is_Stmh, is_Stmnet } kind;
  union
  {
    struct { DataFlow dataflow_; } stmx_;
    struct { Numassgn numassgn_; } stmn_;
    struct { Strassgn strassgn_; } stms_;
    struct { SymAssgn symassgn_; } stmb_;
    struct { Hermt hermt_; } stmh_;
    struct { Subdef subdef_; } stmnet_;
  } u;
};

Stm make_Stmx(DataFlow p0);
Stm make_Stmn(Numassgn p0);
Stm make_Stms(Strassgn p0);
Stm make_Stmb(SymAssgn p0);
Stm make_Stmh(Hermt p0);
Stm make_Stmnet(Subdef p0);

struct ListStm_
{
  Stm stm_;
  ListStm liststm_;
};

ListStm make_ListStm(Stm p1, ListStm p2);
struct Subdef_
{

  enum { is_Snet } kind;
  union
  {
    struct { ListSubnet listsubnet_; SubId subid_; } snet_;
  } u;
};

Subdef make_Snet(SubId p0, ListSubnet p1);

struct Subnet_
{

  enum { is_Sneth, is_Snets, is_Snetin, is_Snetout } kind;
  union
  {
    struct { Hermt hermt_; } sneth_;
    struct { DataFlow dataflow_; } snets_;
    struct { ExtPortIn extportin_; } snetin_;
    struct { ExtPortOut extportout_; } snetout_;
  } u;
};

Subnet make_Sneth(Hermt p0);
Subnet make_Snets(DataFlow p0);
Subnet make_Snetin(ExtPortIn p0);
Subnet make_Snetout(ExtPortOut p0);

struct ListSubnet_
{
  Subnet subnet_;
  ListSubnet listsubnet_;
};

ListSubnet make_ListSubnet(Subnet p1, ListSubnet p2);
struct ExtPortIn_
{

  enum { is_Extin, is_ExtinR } kind;
  union
  {
    struct { Larrow larrow_; Proc proc_; Prt prt_; Tab tab_; } extin_;
    struct { Proc proc_; Prt prt_; Rarrow rarrow_; Tab tab_; } extinr_;
  } u;
};

ExtPortIn make_Extin(Proc p0, Prt p1, Larrow p2, Tab p3);
ExtPortIn make_ExtinR(Tab p0, Rarrow p1, Prt p2, Proc p3);

struct ExtPortOut_
{

  enum { is_Extout, is_Extoutr } kind;
  union
  {
    struct { Larrow larrow_; Proc proc_; Prt prt_; Tab tab_; } extout_;
    struct { Proc proc_; Prt prt_; Rarrow rarrow_; Tab tab_; } extoutr_;
  } u;
};

ExtPortOut make_Extout(Tab p0, Larrow p1, Prt p2, Proc p3);
ExtPortOut make_Extoutr(Proc p0, Prt p1, Rarrow p2, Tab p3);

struct Tab_
{

  enum { is_Tabn, is_Tabs } kind;
  union
  {
    struct { Numval numval_; } tabn_;
    struct { Symval symval_; } tabs_;
  } u;
};

Tab make_Tabn(Numval p0);
Tab make_Tabs(Symval p0);

struct DataFlow_
{

  enum { is_Streamx, is_Streamrx, is_Streamy, is_Streamry } kind;
  union
  {
    struct { Larrow larrow_; Proc proc_1, proc_2; Prt prt_1, prt_2; } streamx_;
    struct { Proc proc_1, proc_2; Prt prt_1, prt_2; Rarrow rarrow_; } streamrx_;
    struct { DataFlow dataflow_; Larrow larrow_; Proc proc_; Prt prt_1, prt_2; } streamy_;
    struct { DataFlow dataflow_; Proc proc_; Prt prt_1, prt_2; Rarrow rarrow_; } streamry_;
  } u;
};

DataFlow make_Streamx(Proc p0, Prt p1, Larrow p2, Prt p3, Proc p4);
DataFlow make_Streamrx(Proc p0, Prt p1, Rarrow p2, Prt p3, Proc p4);
DataFlow make_Streamy(DataFlow p0, Prt p1, Larrow p2, Prt p3, Proc p4);
DataFlow make_Streamry(DataFlow p0, Prt p1, Rarrow p2, Prt p3, Proc p4);

struct Larrow_
{

  enum { is_Arrowx } kind;
  union
  {
    struct { Buffsize buffsize_; TypeDef typedef_; } arrowx_;
  } u;
};

Larrow make_Arrowx(TypeDef p0, Buffsize p1);

struct Rarrow_
{

  enum { is_Arrowr } kind;
  union
  {
    struct { Buffsize buffsize_; TypeDef typedef_; } arrowr_;
  } u;
};

Rarrow make_Arrowr(TypeDef p0, Buffsize p1);

struct TypeDef_
{

  enum { is_Typedefa, is_Typedefnull } kind;
  union
  {
    struct { Symvalu symvalu_; } typedefa_;
  } u;
};

TypeDef make_Typedefa(Symvalu p0);
TypeDef make_Typedefnull(void);

struct Buffsize_
{

  enum { is_Bufszi, is_Bufsze } kind;
  union
  {
    struct { Numval numval_; } bufszi_;
  } u;
};

Buffsize make_Bufszi(Numval p0);
Buffsize make_Bufsze(void);

struct Hermt_
{

  enum { is_Hermtx, is_Hermty } kind;
  union
  {
    struct { Comp comp_; ListArgument listargument_; Symvalu symvalu_; } hermtx_;
    struct { ListArgument listargument_; Symvalu symvalu_; } hermty_;
  } u;
};

Hermt make_Hermtx(Symvalu p0, Comp p1, ListArgument p2);
Hermt make_Hermty(Symvalu p0, ListArgument p1);

struct Symvalu_
{

  enum { is_Symvaluv, is_Symvaluu } kind;
  union
  {
    struct { Symval symval_; } symvaluv_;
  } u;
};

Symvalu make_Symvaluv(Symval p0);
Symvalu make_Symvaluu(void);

struct Proc_
{

  enum { is_Processx, is_Processy } kind;
  union
  {
    struct { Comp comp_; ListArgument listargument_; Symvalu symvalu_; } processx_;
    struct { ListArgument listargument_; Symvalu symvalu_; } processy_;
  } u;
};

Proc make_Processx(Symvalu p0, Comp p1, ListArgument p2);
Proc make_Processy(Symvalu p0, ListArgument p1);

struct Prt_
{

  enum { is_Portx, is_Portni, is_Portin, is_Portn, is_Porte } kind;
  union
  {
    struct { Numval numval_; } portx_;
    struct { Numval numval_; Symval symval_; } portni_;
    struct { Numval numval_; Symval symval_; } portin_;
    struct { Symval symval_; } portn_;
  } u;
};

Prt make_Portx(Numval p0);
Prt make_Portni(Numval p0, Symval p1);
Prt make_Portin(Symval p0, Numval p1);
Prt make_Portn(Symval p0);
Prt make_Porte(void);

struct Comp_
{

  enum { is_Compx, is_Compn, is_Compz, is_Compa } kind;
  union
  {
    struct { Symval symval_; } compx_;
    struct { SubId subid_; } compn_;
    struct { ModPath modpath_; Symval symval_; } compz_;
    struct { RemPath rempath_; } compa_;
  } u;
};

Comp make_Compx(Symval p0);
Comp make_Compn(SubId p0);
Comp make_Compz(ModPath p0, Symval p1);
Comp make_Compa(RemPath p0);

struct ModPath_
{

  enum { is_Modpa, is_Modpx, is_Modpy } kind;
  union
  {
    struct { Symval symval_; } modpa_;
    struct { Symval symval_; } modpx_;
    struct { ModPath modpath_; Symval symval_; } modpy_;
  } u;
};

ModPath make_Modpa(Symval p0);
ModPath make_Modpx(Symval p0);
ModPath make_Modpy(ModPath p0, Symval p1);

struct RemPath_
{

  enum { is_RemPatha } kind;
  union
  {
    struct { Symval symval_; ValidImport validimport_; } rempatha_;
  } u;
};

RemPath make_RemPatha(ValidImport p0, Symval p1);

struct Argument_
{

  enum { is_Argumentx } kind;
  union
  {
    struct { Stringval stringval_; } argumentx_;
  } u;
};

Argument make_Argumentx(Stringval p0);

struct ListArgument_
{
  Argument argument_;
  ListArgument listargument_;
};

ListArgument make_ListArgument(Argument p1, ListArgument p2);
struct Numassgn_
{

  enum { is_NumAssgnv } kind;
  union
  {
    struct { Numval numval_; Numvar numvar_; } numassgnv_;
  } u;
};

Numassgn make_NumAssgnv(Numvar p0, Numval p1);

struct Strassgn_
{

  enum { is_StrAssgnv } kind;
  union
  {
    struct { Stringvar stringvar_; Symval symval_; } strassgnv_;
  } u;
};

Strassgn make_StrAssgnv(Stringvar p0, Symval p1);

struct SymAssgn_
{

  enum { is_SymAssgni } kind;
  union
  {
    struct { Symval symval_; Symvar symvar_; } symassgni_;
  } u;
};

SymAssgn make_SymAssgni(Symvar p0, Symval p1);

struct Numval_
{

  enum { is_NumVali, is_NumValv } kind;
  union
  {
    struct { Integer integer_; } numvali_;
    struct { Numvar numvar_; } numvalv_;
  } u;
};

Numval make_NumVali(Integer p0);
Numval make_NumValv(Numvar p0);

struct Stringval_
{

  enum { is_StringVals, is_StringValv, is_StringVale } kind;
  union
  {
    struct { String string_; } stringvals_;
    struct { Stringvar stringvar_; } stringvalv_;
    struct { Envar envar_; } stringvale_;
  } u;
};

Stringval make_StringVals(String p0);
Stringval make_StringValv(Stringvar p0);
Stringval make_StringVale(Envar p0);

struct Symval_
{

  enum { is_Symvalv, is_Symvali, is_SymVale } kind;
  union
  {
    struct { Symvar symvar_; } symvalv_;
    struct { Id id_; } symvali_;
    struct { Envar envar_; } symvale_;
  } u;
};

Symval make_Symvalv(Symvar p0);
Symval make_Symvali(Id p0);
Symval make_SymVale(Envar p0);

struct ValidConfig_
{

  enum { is_Validcfg, is_Validcfgd } kind;
  union
  {
    struct { ListEntry listentry_; } validcfg_;
    struct { ListEntry listentry_; } validcfgd_;
  } u;
};

ValidConfig make_Validcfg(ListEntry p0);
ValidConfig make_Validcfgd(ListEntry p0);

struct Entry_
{

  enum { is_CfgEntrya, is_CfgEntryb } kind;
  union
  {
    struct { KeyVal keyval_; } cfgentrya_;
    struct { KeyName keyname_; } cfgentryb_;
  } u;
};

Entry make_CfgEntrya(KeyVal p0);
Entry make_CfgEntryb(KeyName p0);

struct ListEntry_
{
  Entry entry_;
  ListEntry listentry_;
};

ListEntry make_ListEntry(Entry p1, ListEntry p2);
struct KeyVal_
{

  enum { is_CfgKeyvalint, is_CfgKeyvalstr, is_CfgKeyDate } kind;
  union
  {
    struct { Integer integer_; KeyName keyname_; } cfgkeyvalint_;
    struct { KeyName keyname_; String string_; } cfgkeyvalstr_;
    struct { Date date_; KeyName keyname_; } cfgkeydate_;
  } u;
};

KeyVal make_CfgKeyvalint(KeyName p0, Integer p1);
KeyVal make_CfgKeyvalstr(KeyName p0, String p1);
KeyVal make_CfgKeyDate(KeyName p0, Date p1);

struct KeyName_
{

  enum { is_KeynameS, is_KeynameM } kind;
  union
  {
    struct { Symval symval_; } keynames_;
    struct { ModPath modpath_; Symval symval_; } keynamem_;
  } u;
};

KeyName make_KeynameS(Symval p0);
KeyName make_KeynameM(ModPath p0, Symval p1);



#endif
