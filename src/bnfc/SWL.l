/* -*- c -*- This FLex file was machine-generated by the BNF converter */
%option noyywrap noinput nounput
%{
#define yylval SWLlval
#define yylloc SWLlloc
#define YY_BUFFER_APPEND SWL_BUFFER_APPEND
#define YY_BUFFER_RESET SWL_BUFFER_RESET
#define init_lexer SWL_init_lexer
#include <string.h>
#include "Parser.h"
#define YY_BUFFER_LENGTH 4096
char YY_PARSED_STRING[YY_BUFFER_LENGTH];
void YY_BUFFER_APPEND(char *s)
{
  strcat(YY_PARSED_STRING, s); //Do something better here!
}
void YY_BUFFER_RESET(void)
{
  int x;
  for(x = 0; x < YY_BUFFER_LENGTH; x++)
    YY_PARSED_STRING[x] = 0;
}
static void update_loc(YYLTYPE* loc, char* text)
{
  loc->first_line = loc->last_line;
  loc->first_column = loc->last_column;
  for (int i = 0; text[i] != '\0'; ++i) {
      if (text[i] == '\n') {
          ++loc->last_line;
          loc->last_column = 0;
      } else {
          ++loc->last_column;
      }
  }
}
#define YY_USER_ACTION update_loc(&yylloc, yytext);

%}

LETTER [a-zA-Z]
CAPITAL [A-Z]
SMALL [a-z]
DIGIT [0-9]
IDENT [a-zA-Z0-9'_]
%START YYINITIAL COMMENT CHAR CHARESC CHAREND STRING ESCAPED
%%

<YYINITIAL>";"      	 return _SYMB_0;
<YYINITIAL>"{"      	 return _SYMB_1;
<YYINITIAL>"}"      	 return _SYMB_2;
<YYINITIAL>"<"      	 return _SYMB_3;
<YYINITIAL>"-"      	 return _SYMB_4;
<YYINITIAL>">"      	 return _SYMB_5;
<YYINITIAL>"="      	 return _SYMB_6;
<YYINITIAL>"."      	 return _SYMB_7;
<YYINITIAL>"["      	 return _SYMB_8;
<YYINITIAL>"]"      	 return _SYMB_9;
<YYINITIAL>","      	 return _SYMB_10;
<YYINITIAL>"_"      	 return _SYMB_11;
<YYINITIAL>"("      	 return _SYMB_12;
<YYINITIAL>")"      	 return _SYMB_13;
<YYINITIAL>"/"      	 return _SYMB_14;
<YYINITIAL>"StreamWork:"      	 return _SYMB_15;
<YYINITIAL>"---"      	 return _SYMB_16;
<YYINITIAL>":"      	 return _SYMB_17;
<YYINITIAL>"INCLUDE"      	 return _SYMB_18;
<YYINITIAL>"PREFIX"      	 return _SYMB_19;
<YYINITIAL>"include"      	 return _SYMB_20;
<YYINITIAL>"prefix"      	 return _SYMB_21;

<YYINITIAL>"#"[^\n]*\n /* skip */; // BNFC: comment "#";
<YYINITIAL>"{#" BEGIN COMMENT; // BNFC: comment "{#" "#}";
<COMMENT>"#}" BEGIN YYINITIAL;
<COMMENT>. /* skip */;
<COMMENT>[\n] /* skip */;

<YYINITIAL>\%{LETTER}({LETTER}|{DIGIT})*     	 yylval.string_ = strdup(yytext); return _SYMB_22;
<YYINITIAL>\${LETTER}({LETTER}|{DIGIT})*     	 yylval.string_ = strdup(yytext); return _SYMB_23;
<YYINITIAL>\$\_{LETTER}({LETTER}|{DIGIT})*     	 yylval.string_ = strdup(yytext); return _SYMB_24;
<YYINITIAL>\&{LETTER}({LETTER}|{DIGIT}|\_)*     	 yylval.string_ = strdup(yytext); return _SYMB_25;
<YYINITIAL>\^{LETTER}({LETTER}|{DIGIT}|\_)*     	 yylval.string_ = strdup(yytext); return _SYMB_26;
<YYINITIAL>{LETTER}({LETTER}|{DIGIT}|\_)*     	 yylval.string_ = strdup(yytext); return _SYMB_27;
<YYINITIAL>\{({LETTER}|{DIGIT}|\_|\.|\/)*\}     	 yylval.string_ = strdup(yytext); return _SYMB_28;
<YYINITIAL>{DIGIT}{DIGIT}{DIGIT}{DIGIT}(\-{DIGIT}{DIGIT})*T(\:|{DIGIT}|\-)*     	 yylval.string_ = strdup(yytext); return _SYMB_29;
<YYINITIAL>"\""      	 BEGIN STRING;
<STRING>\\      	 BEGIN ESCAPED;
<STRING>\"      	 yylval.string_ = strdup(YY_PARSED_STRING); YY_BUFFER_RESET(); BEGIN YYINITIAL; return _STRING_;
<STRING>.      	 YY_BUFFER_APPEND(yytext);
<ESCAPED>n      	 YY_BUFFER_APPEND("\n"); BEGIN STRING;
<ESCAPED>\"      	 YY_BUFFER_APPEND("\""); BEGIN STRING ;
<ESCAPED>\\      	 YY_BUFFER_APPEND("\\"); BEGIN STRING;
<ESCAPED>t       	 YY_BUFFER_APPEND("\t"); BEGIN STRING;
<ESCAPED>.       	 YY_BUFFER_APPEND(yytext); BEGIN STRING;
<YYINITIAL>{DIGIT}+      	 yylval.int_ = atoi(yytext); return _INTEGER_;
<YYINITIAL>[ \t\r\n\f]      	 /* ignore white space. */;
<YYINITIAL>.      	 return _ERROR_;
%%
void init_lexer(FILE *inp)
{
  yyrestart(inp);
  yylloc.first_line = 1;
  yylloc.first_column = 1;
  yylloc.last_line = 1;
  yylloc.last_column = 1;
  BEGIN YYINITIAL;
}
