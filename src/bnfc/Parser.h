#ifndef PARSER_HEADER_FILE
#define PARSER_HEADER_FILE

#include "Absyn.h"

typedef union
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
} YYSTYPE;

typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
#define _ERROR_ 258
#define _SYMB_0 259
#define _SYMB_1 260
#define _SYMB_2 261
#define _SYMB_3 262
#define _SYMB_4 263
#define _SYMB_5 264
#define _SYMB_6 265
#define _SYMB_7 266
#define _SYMB_8 267
#define _SYMB_9 268
#define _SYMB_10 269
#define _SYMB_11 270
#define _SYMB_12 271
#define _SYMB_13 272
#define _SYMB_14 273
#define _SYMB_15 274
#define _SYMB_16 275
#define _SYMB_17 276
#define _SYMB_18 277
#define _SYMB_19 278
#define _SYMB_20 279
#define _SYMB_21 280
#define _SYMB_22 281
#define _SYMB_23 282
#define _SYMB_24 283
#define _SYMB_25 284
#define _SYMB_26 285
#define _SYMB_27 286
#define _SYMB_28 287
#define _SYMB_29 288
#define _STRING_ 289
#define _INTEGER_ 290

extern YYLTYPE yylloc;
extern YYSTYPE yylval;
Valide  pValide(FILE *inp);
Valide psValide(const char *str);
ValidSW  pValidSW(FILE *inp);
ValidSW psValidSW(const char *str);
ValidConfig  pValidConfig(FILE *inp);
ValidConfig psValidConfig(const char *str);


#endif
