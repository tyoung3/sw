/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         SWLparse
#define yylex           SWLlex
#define yyerror         SWLerror
#define yydebug         SWLdebug
#define yynerrs         SWLnerrs
#define yylval          SWLlval
#define yychar          SWLchar
#define yylloc          SWLlloc

/* First part of user prologue.  */
#line 3 "SWL.y"

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


#line 268 "Parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int SWLdebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    _ERROR_ = 258,                 /* _ERROR_  */
    _SYMB_0 = 259,                 /* _SYMB_0  */
    _SYMB_1 = 260,                 /* _SYMB_1  */
    _SYMB_2 = 261,                 /* _SYMB_2  */
    _SYMB_3 = 262,                 /* _SYMB_3  */
    _SYMB_4 = 263,                 /* _SYMB_4  */
    _SYMB_5 = 264,                 /* _SYMB_5  */
    _SYMB_6 = 265,                 /* _SYMB_6  */
    _SYMB_7 = 266,                 /* _SYMB_7  */
    _SYMB_8 = 267,                 /* _SYMB_8  */
    _SYMB_9 = 268,                 /* _SYMB_9  */
    _SYMB_10 = 269,                /* _SYMB_10  */
    _SYMB_11 = 270,                /* _SYMB_11  */
    _SYMB_12 = 271,                /* _SYMB_12  */
    _SYMB_13 = 272,                /* _SYMB_13  */
    _SYMB_14 = 273,                /* _SYMB_14  */
    _SYMB_15 = 274,                /* _SYMB_15  */
    _SYMB_16 = 275,                /* _SYMB_16  */
    _SYMB_17 = 276,                /* _SYMB_17  */
    _SYMB_18 = 277,                /* _SYMB_18  */
    _SYMB_19 = 278,                /* _SYMB_19  */
    _SYMB_20 = 279,                /* _SYMB_20  */
    _SYMB_21 = 280,                /* _SYMB_21  */
    _SYMB_22 = 281,                /* _SYMB_22  */
    _SYMB_23 = 282,                /* _SYMB_23  */
    _SYMB_24 = 283,                /* _SYMB_24  */
    _SYMB_25 = 284,                /* _SYMB_25  */
    _SYMB_26 = 285,                /* _SYMB_26  */
    _SYMB_27 = 286,                /* _SYMB_27  */
    _SYMB_28 = 287,                /* _SYMB_28  */
    _STRING_ = 288,                /* _STRING_  */
    _INTEGER_ = 289                /* _INTEGER_  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 193 "SWL.y"

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


#line 399 "Parser.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE SWLlval;
extern YYLTYPE SWLlloc;
int SWLparse (void);


/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL__ERROR_ = 3,                    /* _ERROR_  */
  YYSYMBOL__SYMB_0 = 4,                    /* _SYMB_0  */
  YYSYMBOL__SYMB_1 = 5,                    /* _SYMB_1  */
  YYSYMBOL__SYMB_2 = 6,                    /* _SYMB_2  */
  YYSYMBOL__SYMB_3 = 7,                    /* _SYMB_3  */
  YYSYMBOL__SYMB_4 = 8,                    /* _SYMB_4  */
  YYSYMBOL__SYMB_5 = 9,                    /* _SYMB_5  */
  YYSYMBOL__SYMB_6 = 10,                   /* _SYMB_6  */
  YYSYMBOL__SYMB_7 = 11,                   /* _SYMB_7  */
  YYSYMBOL__SYMB_8 = 12,                   /* _SYMB_8  */
  YYSYMBOL__SYMB_9 = 13,                   /* _SYMB_9  */
  YYSYMBOL__SYMB_10 = 14,                  /* _SYMB_10  */
  YYSYMBOL__SYMB_11 = 15,                  /* _SYMB_11  */
  YYSYMBOL__SYMB_12 = 16,                  /* _SYMB_12  */
  YYSYMBOL__SYMB_13 = 17,                  /* _SYMB_13  */
  YYSYMBOL__SYMB_14 = 18,                  /* _SYMB_14  */
  YYSYMBOL__SYMB_15 = 19,                  /* _SYMB_15  */
  YYSYMBOL__SYMB_16 = 20,                  /* _SYMB_16  */
  YYSYMBOL__SYMB_17 = 21,                  /* _SYMB_17  */
  YYSYMBOL__SYMB_18 = 22,                  /* _SYMB_18  */
  YYSYMBOL__SYMB_19 = 23,                  /* _SYMB_19  */
  YYSYMBOL__SYMB_20 = 24,                  /* _SYMB_20  */
  YYSYMBOL__SYMB_21 = 25,                  /* _SYMB_21  */
  YYSYMBOL__SYMB_22 = 26,                  /* _SYMB_22  */
  YYSYMBOL__SYMB_23 = 27,                  /* _SYMB_23  */
  YYSYMBOL__SYMB_24 = 28,                  /* _SYMB_24  */
  YYSYMBOL__SYMB_25 = 29,                  /* _SYMB_25  */
  YYSYMBOL__SYMB_26 = 30,                  /* _SYMB_26  */
  YYSYMBOL__SYMB_27 = 31,                  /* _SYMB_27  */
  YYSYMBOL__SYMB_28 = 32,                  /* _SYMB_28  */
  YYSYMBOL__STRING_ = 33,                  /* _STRING_  */
  YYSYMBOL__INTEGER_ = 34,                 /* _INTEGER_  */
  YYSYMBOL_YYACCEPT = 35,                  /* $accept  */
  YYSYMBOL_Valide = 36,                    /* Valide  */
  YYSYMBOL_ValidSW = 37,                   /* ValidSW  */
  YYSYMBOL_Stm = 38,                       /* Stm  */
  YYSYMBOL_ListStm = 39,                   /* ListStm  */
  YYSYMBOL_Subdef = 40,                    /* Subdef  */
  YYSYMBOL_Subnet = 41,                    /* Subnet  */
  YYSYMBOL_ListSubnet = 42,                /* ListSubnet  */
  YYSYMBOL_ExtPortIn = 43,                 /* ExtPortIn  */
  YYSYMBOL_ExtPortOut = 44,                /* ExtPortOut  */
  YYSYMBOL_Tab = 45,                       /* Tab  */
  YYSYMBOL_DataFlow = 46,                  /* DataFlow  */
  YYSYMBOL_Larrow = 47,                    /* Larrow  */
  YYSYMBOL_Rarrow = 48,                    /* Rarrow  */
  YYSYMBOL_TypeDef = 49,                   /* TypeDef  */
  YYSYMBOL_Buffsize = 50,                  /* Buffsize  */
  YYSYMBOL_Hermt = 51,                     /* Hermt  */
  YYSYMBOL_Symvalu = 52,                   /* Symvalu  */
  YYSYMBOL_Proc = 53,                      /* Proc  */
  YYSYMBOL_Attributes = 54,                /* Attributes  */
  YYSYMBOL_Attr = 55,                      /* Attr  */
  YYSYMBOL_ListAttr = 56,                  /* ListAttr  */
  YYSYMBOL_Prt = 57,                       /* Prt  */
  YYSYMBOL_Comp = 58,                      /* Comp  */
  YYSYMBOL_ModPath = 59,                   /* ModPath  */
  YYSYMBOL_RemPath = 60,                   /* RemPath  */
  YYSYMBOL_Argument = 61,                  /* Argument  */
  YYSYMBOL_ListArgument = 62,              /* ListArgument  */
  YYSYMBOL_Numassgn = 63,                  /* Numassgn  */
  YYSYMBOL_Strassgn = 64,                  /* Strassgn  */
  YYSYMBOL_SymAssgn = 65,                  /* SymAssgn  */
  YYSYMBOL_Numval = 66,                    /* Numval  */
  YYSYMBOL_Stringval = 67,                 /* Stringval  */
  YYSYMBOL_Symval = 68,                    /* Symval  */
  YYSYMBOL_Include = 69,                   /* Include  */
  YYSYMBOL_Prefix = 70,                    /* Prefix  */
  YYSYMBOL_ValidConfig = 71,               /* ValidConfig  */
  YYSYMBOL_Centry = 72,                    /* Centry  */
  YYSYMBOL_ListCentry = 73,                /* ListCentry  */
  YYSYMBOL_Entry = 74,                     /* Entry  */
  YYSYMBOL_ListEntry = 75,                 /* ListEntry  */
  YYSYMBOL_KeyVal = 76,                    /* KeyVal  */
  YYSYMBOL_KeyName = 77                    /* KeyName  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   204

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  163

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   322,   322,   323,   325,   327,   328,   329,   330,   331,
     332,   333,   334,   336,   337,   339,   341,   342,   343,   344,
     346,   347,   349,   350,   352,   353,   355,   356,   358,   359,
     360,   361,   363,   365,   367,   368,   369,   371,   372,   374,
     375,   377,   378,   380,   381,   383,   384,   386,   387,   389,
     390,   391,   393,   394,   395,   396,   397,   399,   400,   401,
     402,   404,   405,   406,   407,   409,   411,   413,   414,   416,
     418,   420,   422,   423,   425,   426,   427,   429,   430,   431,
     433,   434,   436,   437,   439,   440,   442,   443,   445,   446,
     448,   449,   451,   452,   454,   455,   456,   458,   459
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "_ERROR_", "_SYMB_0",
  "_SYMB_1", "_SYMB_2", "_SYMB_3", "_SYMB_4", "_SYMB_5", "_SYMB_6",
  "_SYMB_7", "_SYMB_8", "_SYMB_9", "_SYMB_10", "_SYMB_11", "_SYMB_12",
  "_SYMB_13", "_SYMB_14", "_SYMB_15", "_SYMB_16", "_SYMB_17", "_SYMB_18",
  "_SYMB_19", "_SYMB_20", "_SYMB_21", "_SYMB_22", "_SYMB_23", "_SYMB_24",
  "_SYMB_25", "_SYMB_26", "_SYMB_27", "_SYMB_28", "_STRING_", "_INTEGER_",
  "$accept", "Valide", "ValidSW", "Stm", "ListStm", "Subdef", "Subnet",
  "ListSubnet", "ExtPortIn", "ExtPortOut", "Tab", "DataFlow", "Larrow",
  "Rarrow", "TypeDef", "Buffsize", "Hermt", "Symvalu", "Proc",
  "Attributes", "Attr", "ListAttr", "Prt", "Comp", "ModPath", "RemPath",
  "Argument", "ListArgument", "Numassgn", "Strassgn", "SymAssgn", "Numval",
  "Stringval", "Symval", "Include", "Prefix", "ValidConfig", "Centry",
  "ListCentry", "Entry", "ListEntry", "KeyVal", "KeyName", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289
};
#endif

#define YYPACT_NINF (-75)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-56)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      77,   -75,    17,    58,   -75,   141,   -75,    -4,    70,   -75,
     -75,    37,   -75,   -75,   -75,   -75,    52,    74,   -75,    76,
     112,   -75,   117,   -75,    15,   -75,   156,   109,   -75,   -75,
     -75,   -75,    85,    85,   -10,    97,   -75,   -10,    14,   -75,
     -75,   108,   -75,    73,    38,    85,   -10,   -75,   -75,   -75,
     -75,   149,   132,   135,   -75,   139,   -75,   -10,   -75,    85,
     144,   149,   -75,   -75,   -75,   -75,   -75,   145,   -75,    55,
     -75,   -75,   -75,   -75,   -75,     9,   168,   161,   -75,   -75,
     -75,   -75,   121,    37,    37,   109,   109,   -10,    38,   -10,
      85,   159,   -75,   -75,   109,   109,   -75,   -75,   -75,   -75,
     166,   -75,   108,   -10,   -75,    24,   -75,   173,   -75,   -75,
     149,   101,   -75,   109,   -75,   151,    21,   -75,    21,   167,
     167,   -75,   -75,   -75,   167,   167,   -75,   170,   172,   177,
     179,   -75,   109,   109,   149,    37,   185,   -75,   186,   -75,
     -75,   -75,   -75,   -10,   -75,   163,   -75,   167,   167,   109,
     109,   171,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,
      61,   110,   -75
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      13,    92,     0,     0,     3,     4,     2,    84,     0,     1,
      42,     0,    81,    82,    80,    83,     0,     0,    79,    77,
       0,    78,     0,    12,    56,    11,    67,    56,     8,     9,
      10,    41,     0,     0,     0,     0,    77,     0,     0,    93,
      90,    91,    88,    46,     0,     0,     0,    20,    14,    73,
      72,     0,    52,    55,    58,     0,    67,     0,    60,    40,
      57,     0,    75,    76,    74,     6,     5,     0,    64,     0,
      62,    97,    96,    95,    94,     0,     0,     0,    67,    69,
      70,    71,     0,    35,    35,    56,    56,     0,     0,     0,
      39,    59,    68,    66,    56,    56,    61,    63,    98,    85,
       0,    86,    87,    49,    44,    46,    15,     0,    18,    19,
       0,    56,    16,    56,    26,    41,    38,    34,    38,     0,
       0,    53,    54,    65,     0,     0,    89,    50,     0,     0,
       0,    21,    56,    56,     0,    35,     0,    37,     0,    30,
      31,    28,    29,    49,    45,     0,    43,     0,     0,    56,
      56,    36,    32,    33,    51,    48,    47,    24,    23,    22,
      26,    27,    25
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,
     -41,   116,   -54,   -48,   -74,    81,   118,     3,   -28,    89,
     -75,    59,   -26,   158,   -15,   -75,   -75,   -51,   -75,   -75,
     -75,   -35,   -29,    -5,   -75,   -75,   -75,   -75,   -75,   -75,
     -75,   128,   129
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,     4,    22,     5,    23,   107,    82,   108,   109,
     110,    24,    85,    86,   116,   136,    25,   117,    27,    77,
     127,   128,    51,    56,    37,    58,    92,    59,    28,    29,
      30,    52,    93,    53,    32,    33,     6,   100,    75,    39,
       7,    40,    41
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      31,    61,    38,    65,    66,    90,    31,    94,    26,    79,
     118,    57,    34,    95,    43,    99,    80,    18,    36,    -7,
      21,    60,    35,    18,    36,    34,    21,   105,    57,    67,
      70,   135,    69,    71,     8,    35,    18,    36,    60,    21,
      49,    81,    18,    36,    76,    21,    49,   114,    10,    50,
      62,    63,    91,   122,   113,    50,   132,    64,     9,   119,
     120,   151,   133,    49,    18,    36,    44,    21,   124,   125,
      38,    97,    50,   -52,    98,    42,    87,   115,    31,    31,
     149,   137,   121,   137,   123,    26,   150,   134,    45,    34,
      46,   139,   140,    76,     1,     2,   141,   142,   129,    35,
      18,    36,    54,    21,    55,   -17,   147,   148,   159,   162,
     155,    62,    63,    68,   160,   160,   156,    47,    64,   157,
     158,    48,   -55,   124,   125,    88,    49,   106,    18,    36,
      31,    21,    10,    11,    49,    50,    18,    36,   129,    21,
      72,    73,    74,    50,   161,   161,    49,    87,    18,    36,
      88,    21,    10,    11,    89,    50,    83,    84,   -27,   -27,
      70,    96,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    34,   103,   104,    97,   126,   131,   144,    11,
     143,   135,    35,    18,    36,    54,    21,    55,    49,    62,
      63,   145,   146,   152,   130,   153,    64,    50,   111,   138,
     112,    78,   154,   101,   102
};

static const yytype_uint8 yycheck[] =
{
       5,    27,     7,    32,    33,    56,    11,    61,     5,    44,
      84,    26,    16,    61,    11,     6,    45,    27,    28,     4,
      30,    26,    26,    27,    28,    16,    30,    78,    43,    34,
      16,    10,    37,    19,    17,    26,    27,    28,    43,    30,
      25,    46,    27,    28,    20,    30,    25,    82,    11,    34,
      26,    27,    57,    88,    82,    34,   110,    33,     0,    85,
      86,   135,   110,    25,    27,    28,    14,    30,    94,    95,
      75,    16,    34,    12,    19,     5,    15,    82,    83,    84,
     134,   116,    87,   118,    89,    82,   134,   113,    14,    16,
      14,   119,   120,    20,    17,    18,   124,   125,   103,    26,
      27,    28,    29,    30,    31,     4,   132,   133,   149,   150,
     145,    26,    27,    16,   149,   150,   145,     5,    33,   147,
     148,     4,    12,   149,   150,    15,    25,     6,    27,    28,
     135,    30,    11,    12,    25,    34,    27,    28,   143,    30,
      32,    33,    34,    34,   149,   150,    25,    15,    27,    28,
      15,    30,    11,    12,    15,    34,     7,     8,     7,     8,
      16,    16,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    16,     5,    13,    16,    10,     4,     6,    12,
      10,    10,    26,    27,    28,    29,    30,    31,    25,    26,
      27,    14,    13,     8,   105,     9,    33,    34,    82,   118,
      82,    43,   143,    75,    75
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    17,    18,    36,    37,    39,    71,    75,    17,     0,
      11,    12,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    38,    40,    46,    51,    52,    53,    63,    64,
      65,    68,    69,    70,    16,    26,    28,    59,    68,    74,
      76,    77,     5,    52,    14,    14,    14,     5,     4,    25,
      34,    57,    66,    68,    29,    31,    58,    59,    60,    62,
      68,    57,    26,    27,    33,    67,    67,    68,    16,    68,
      16,    19,    32,    33,    34,    73,    20,    54,    58,    66,
      67,    68,    42,     7,     8,    47,    48,    15,    15,    15,
      62,    68,    61,    67,    47,    48,    16,    16,    19,     6,
      72,    76,    77,     5,    13,    62,     6,    41,    43,    44,
      45,    46,    51,    53,    66,    68,    49,    52,    49,    57,
      57,    68,    66,    68,    57,    57,    10,    55,    56,    68,
      54,     4,    47,    48,    57,    10,    50,    66,    50,    53,
      53,    53,    53,    10,     6,    14,    13,    57,    57,    47,
      48,    49,     8,     9,    56,    66,    67,    53,    53,    45,
      66,    68,    45
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    36,    37,    38,    38,    38,    38,    38,
      38,    38,    38,    39,    39,    40,    41,    41,    41,    41,
      42,    42,    43,    43,    44,    44,    45,    45,    46,    46,
      46,    46,    47,    48,    49,    49,    49,    50,    50,    51,
      51,    52,    52,    53,    53,    54,    54,    55,    55,    56,
      56,    56,    57,    57,    57,    57,    57,    58,    58,    58,
      58,    59,    59,    59,    59,    60,    61,    62,    62,    63,
      64,    65,    66,    66,    67,    67,    67,    68,    68,    68,
      69,    69,    70,    70,    71,    71,    72,    72,    73,    73,
      74,    74,    75,    75,    76,    76,    76,    77,    77
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     0,     3,     4,     1,     1,     1,     1,
       0,     3,     4,     4,     4,     4,     1,     1,     5,     5,
       5,     5,     4,     4,     1,     0,     3,     1,     0,     3,
       2,     1,     1,     6,     4,     4,     0,     3,     3,     0,
       1,     3,     1,     3,     3,     1,     0,     1,     1,     2,
       1,     3,     2,     3,     2,     3,     1,     0,     2,     3,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     5,     1,     1,     0,     3,
       1,     1,     0,     2,     2,     2,     2,     2,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Valide: ValidConfig  */
#line 322 "SWL.y"
                     { (yyval.valide_) = make_CFGvalid((yyvsp[0].validconfig_)); YY_RESULT_Valide_= (yyval.valide_); }
#line 1698 "Parser.c"
    break;

  case 3: /* Valide: ValidSW  */
#line 323 "SWL.y"
            { (yyval.valide_) = make_SWvalid((yyvsp[0].validsw_)); YY_RESULT_Valide_= (yyval.valide_); }
#line 1704 "Parser.c"
    break;

  case 4: /* ValidSW: ListStm  */
#line 325 "SWL.y"
                  { (yyval.validsw_) = make_Valid(reverseListStm((yyvsp[0].liststm_))); YY_RESULT_ValidSW_= (yyval.validsw_); }
#line 1710 "Parser.c"
    break;

  case 5: /* Stm: Prefix Stringval  */
#line 327 "SWL.y"
                       { (yyval.stm_) = make_StmPrefix((yyvsp[-1].prefix_), (yyvsp[0].stringval_));  }
#line 1716 "Parser.c"
    break;

  case 6: /* Stm: Include Stringval  */
#line 328 "SWL.y"
                      { (yyval.stm_) = make_Stminc((yyvsp[-1].include_), (yyvsp[0].stringval_));  }
#line 1722 "Parser.c"
    break;

  case 7: /* Stm: DataFlow  */
#line 329 "SWL.y"
             { (yyval.stm_) = make_Stmx((yyvsp[0].dataflow_));  }
#line 1728 "Parser.c"
    break;

  case 8: /* Stm: Numassgn  */
#line 330 "SWL.y"
             { (yyval.stm_) = make_Stmn((yyvsp[0].numassgn_));  }
#line 1734 "Parser.c"
    break;

  case 9: /* Stm: Strassgn  */
#line 331 "SWL.y"
             { (yyval.stm_) = make_Stms((yyvsp[0].strassgn_));  }
#line 1740 "Parser.c"
    break;

  case 10: /* Stm: SymAssgn  */
#line 332 "SWL.y"
             { (yyval.stm_) = make_Stmb((yyvsp[0].symassgn_));  }
#line 1746 "Parser.c"
    break;

  case 11: /* Stm: Hermt  */
#line 333 "SWL.y"
          { (yyval.stm_) = make_Stmh((yyvsp[0].hermt_));  }
#line 1752 "Parser.c"
    break;

  case 12: /* Stm: Subdef  */
#line 334 "SWL.y"
           { (yyval.stm_) = make_Stmnet((yyvsp[0].subdef_));  }
#line 1758 "Parser.c"
    break;

  case 13: /* ListStm: %empty  */
#line 336 "SWL.y"
                      { (yyval.liststm_) = 0;  }
#line 1764 "Parser.c"
    break;

  case 14: /* ListStm: ListStm Stm _SYMB_0  */
#line 337 "SWL.y"
                        { (yyval.liststm_) = make_ListStm((yyvsp[-1].stm_), (yyvsp[-2].liststm_));  }
#line 1770 "Parser.c"
    break;

  case 15: /* Subdef: _SYMB_25 _SYMB_1 ListSubnet _SYMB_2  */
#line 339 "SWL.y"
                                             { (yyval.subdef_) = make_Snet((yyvsp[-3].string_), reverseListSubnet((yyvsp[-1].listsubnet_)));  }
#line 1776 "Parser.c"
    break;

  case 16: /* Subnet: Hermt  */
#line 341 "SWL.y"
               { (yyval.subnet_) = make_Sneth((yyvsp[0].hermt_));  }
#line 1782 "Parser.c"
    break;

  case 17: /* Subnet: DataFlow  */
#line 342 "SWL.y"
             { (yyval.subnet_) = make_Snets((yyvsp[0].dataflow_));  }
#line 1788 "Parser.c"
    break;

  case 18: /* Subnet: ExtPortIn  */
#line 343 "SWL.y"
              { (yyval.subnet_) = make_Snetin((yyvsp[0].extportin_));  }
#line 1794 "Parser.c"
    break;

  case 19: /* Subnet: ExtPortOut  */
#line 344 "SWL.y"
               { (yyval.subnet_) = make_Snetout((yyvsp[0].extportout_));  }
#line 1800 "Parser.c"
    break;

  case 20: /* ListSubnet: %empty  */
#line 346 "SWL.y"
                         { (yyval.listsubnet_) = 0;  }
#line 1806 "Parser.c"
    break;

  case 21: /* ListSubnet: ListSubnet Subnet _SYMB_0  */
#line 347 "SWL.y"
                              { (yyval.listsubnet_) = make_ListSubnet((yyvsp[-1].subnet_), (yyvsp[-2].listsubnet_));  }
#line 1812 "Parser.c"
    break;

  case 22: /* ExtPortIn: Proc Prt Larrow Tab  */
#line 349 "SWL.y"
                                { (yyval.extportin_) = make_Extin((yyvsp[-3].proc_), (yyvsp[-2].prt_), (yyvsp[-1].larrow_), (yyvsp[0].tab_));  }
#line 1818 "Parser.c"
    break;

  case 23: /* ExtPortIn: Tab Rarrow Prt Proc  */
#line 350 "SWL.y"
                        { (yyval.extportin_) = make_ExtinR((yyvsp[-3].tab_), (yyvsp[-2].rarrow_), (yyvsp[-1].prt_), (yyvsp[0].proc_));  }
#line 1824 "Parser.c"
    break;

  case 24: /* ExtPortOut: Tab Larrow Prt Proc  */
#line 352 "SWL.y"
                                 { (yyval.extportout_) = make_Extout((yyvsp[-3].tab_), (yyvsp[-2].larrow_), (yyvsp[-1].prt_), (yyvsp[0].proc_));  }
#line 1830 "Parser.c"
    break;

  case 25: /* ExtPortOut: Proc Prt Rarrow Tab  */
#line 353 "SWL.y"
                        { (yyval.extportout_) = make_Extoutr((yyvsp[-3].proc_), (yyvsp[-2].prt_), (yyvsp[-1].rarrow_), (yyvsp[0].tab_));  }
#line 1836 "Parser.c"
    break;

  case 26: /* Tab: Numval  */
#line 355 "SWL.y"
             { (yyval.tab_) = make_Tabn((yyvsp[0].numval_));  }
#line 1842 "Parser.c"
    break;

  case 27: /* Tab: Symval  */
#line 356 "SWL.y"
           { (yyval.tab_) = make_Tabs((yyvsp[0].symval_));  }
#line 1848 "Parser.c"
    break;

  case 28: /* DataFlow: Proc Prt Larrow Prt Proc  */
#line 358 "SWL.y"
                                    { (yyval.dataflow_) = make_Streamx((yyvsp[-4].proc_), (yyvsp[-3].prt_), (yyvsp[-2].larrow_), (yyvsp[-1].prt_), (yyvsp[0].proc_));  }
#line 1854 "Parser.c"
    break;

  case 29: /* DataFlow: Proc Prt Rarrow Prt Proc  */
#line 359 "SWL.y"
                             { (yyval.dataflow_) = make_Streamrx((yyvsp[-4].proc_), (yyvsp[-3].prt_), (yyvsp[-2].rarrow_), (yyvsp[-1].prt_), (yyvsp[0].proc_));  }
#line 1860 "Parser.c"
    break;

  case 30: /* DataFlow: DataFlow Prt Larrow Prt Proc  */
#line 360 "SWL.y"
                                 { (yyval.dataflow_) = make_Streamy((yyvsp[-4].dataflow_), (yyvsp[-3].prt_), (yyvsp[-2].larrow_), (yyvsp[-1].prt_), (yyvsp[0].proc_));  }
#line 1866 "Parser.c"
    break;

  case 31: /* DataFlow: DataFlow Prt Rarrow Prt Proc  */
#line 361 "SWL.y"
                                 { (yyval.dataflow_) = make_Streamry((yyvsp[-4].dataflow_), (yyvsp[-3].prt_), (yyvsp[-2].rarrow_), (yyvsp[-1].prt_), (yyvsp[0].proc_));  }
#line 1872 "Parser.c"
    break;

  case 32: /* Larrow: _SYMB_3 TypeDef Buffsize _SYMB_4  */
#line 363 "SWL.y"
                                          { (yyval.larrow_) = make_Arrowx((yyvsp[-2].typedef_), (yyvsp[-1].buffsize_));  }
#line 1878 "Parser.c"
    break;

  case 33: /* Rarrow: _SYMB_4 TypeDef Buffsize _SYMB_5  */
#line 365 "SWL.y"
                                          { (yyval.rarrow_) = make_Arrowr((yyvsp[-2].typedef_), (yyvsp[-1].buffsize_));  }
#line 1884 "Parser.c"
    break;

  case 34: /* TypeDef: Symvalu  */
#line 367 "SWL.y"
                  { (yyval.typedef_) = make_Typedefa((yyvsp[0].symvalu_));  }
#line 1890 "Parser.c"
    break;

  case 35: /* TypeDef: %empty  */
#line 368 "SWL.y"
                { (yyval.typedef_) = make_Typedefnull();  }
#line 1896 "Parser.c"
    break;

  case 36: /* TypeDef: TypeDef _SYMB_6 TypeDef  */
#line 369 "SWL.y"
                            { (yyval.typedef_) = make_Typdefl((yyvsp[-2].typedef_), (yyvsp[0].typedef_));  }
#line 1902 "Parser.c"
    break;

  case 37: /* Buffsize: Numval  */
#line 371 "SWL.y"
                  { (yyval.buffsize_) = make_Bufszi((yyvsp[0].numval_));  }
#line 1908 "Parser.c"
    break;

  case 38: /* Buffsize: %empty  */
#line 372 "SWL.y"
                { (yyval.buffsize_) = make_Bufsze();  }
#line 1914 "Parser.c"
    break;

  case 39: /* Hermt: Symvalu Comp ListArgument  */
#line 374 "SWL.y"
                                  { (yyval.hermt_) = make_Hermtx((yyvsp[-2].symvalu_), (yyvsp[-1].comp_), reverseListArgument((yyvsp[0].listargument_)));  }
#line 1920 "Parser.c"
    break;

  case 40: /* Hermt: Symvalu ListArgument  */
#line 375 "SWL.y"
                         { (yyval.hermt_) = make_Hermty((yyvsp[-1].symvalu_), reverseListArgument((yyvsp[0].listargument_)));  }
#line 1926 "Parser.c"
    break;

  case 41: /* Symvalu: Symval  */
#line 377 "SWL.y"
                 { (yyval.symvalu_) = make_Symvaluv((yyvsp[0].symval_));  }
#line 1932 "Parser.c"
    break;

  case 42: /* Symvalu: _SYMB_7  */
#line 378 "SWL.y"
            { (yyval.symvalu_) = make_Symvaluu();  }
#line 1938 "Parser.c"
    break;

  case 43: /* Proc: _SYMB_8 Symvalu Comp ListArgument Attributes _SYMB_9  */
#line 380 "SWL.y"
                                                            { (yyval.proc_) = make_Processx((yyvsp[-4].symvalu_), (yyvsp[-3].comp_), reverseListArgument((yyvsp[-2].listargument_)), (yyvsp[-1].attributes_));  }
#line 1944 "Parser.c"
    break;

  case 44: /* Proc: _SYMB_8 Symvalu Attributes _SYMB_9  */
#line 381 "SWL.y"
                                       { (yyval.proc_) = make_Processy((yyvsp[-2].symvalu_), (yyvsp[-1].attributes_));  }
#line 1950 "Parser.c"
    break;

  case 45: /* Attributes: _SYMB_16 _SYMB_1 ListAttr _SYMB_2  */
#line 383 "SWL.y"
                                               { (yyval.attributes_) = make_Attribe((yyvsp[-1].listattr_));  }
#line 1956 "Parser.c"
    break;

  case 46: /* Attributes: %empty  */
#line 384 "SWL.y"
                { (yyval.attributes_) = make_Attribs();  }
#line 1962 "Parser.c"
    break;

  case 47: /* Attr: Symval _SYMB_10 Stringval  */
#line 386 "SWL.y"
                                 { (yyval.attr_) = make_Attrs((yyvsp[-2].symval_), (yyvsp[0].stringval_));  }
#line 1968 "Parser.c"
    break;

  case 48: /* Attr: Symval _SYMB_10 Numval  */
#line 387 "SWL.y"
                           { (yyval.attr_) = make_Attrn((yyvsp[-2].symval_), (yyvsp[0].numval_));  }
#line 1974 "Parser.c"
    break;

  case 49: /* ListAttr: %empty  */
#line 389 "SWL.y"
                       { (yyval.listattr_) = 0;  }
#line 1980 "Parser.c"
    break;

  case 50: /* ListAttr: Attr  */
#line 390 "SWL.y"
         { (yyval.listattr_) = make_ListAttr((yyvsp[0].attr_), 0);  }
#line 1986 "Parser.c"
    break;

  case 51: /* ListAttr: Attr _SYMB_6 ListAttr  */
#line 391 "SWL.y"
                          { (yyval.listattr_) = make_ListAttr((yyvsp[-2].attr_), (yyvsp[0].listattr_));  }
#line 1992 "Parser.c"
    break;

  case 52: /* Prt: Numval  */
#line 393 "SWL.y"
             { (yyval.prt_) = make_Portx((yyvsp[0].numval_));  }
#line 1998 "Parser.c"
    break;

  case 53: /* Prt: Numval _SYMB_11 Symval  */
#line 394 "SWL.y"
                           { (yyval.prt_) = make_Portni((yyvsp[-2].numval_), (yyvsp[0].symval_));  }
#line 2004 "Parser.c"
    break;

  case 54: /* Prt: Symval _SYMB_11 Numval  */
#line 395 "SWL.y"
                           { (yyval.prt_) = make_Portin((yyvsp[-2].symval_), (yyvsp[0].numval_));  }
#line 2010 "Parser.c"
    break;

  case 55: /* Prt: Symval  */
#line 396 "SWL.y"
           { (yyval.prt_) = make_Portn((yyvsp[0].symval_));  }
#line 2016 "Parser.c"
    break;

  case 56: /* Prt: %empty  */
#line 397 "SWL.y"
                { (yyval.prt_) = make_Porte();  }
#line 2022 "Parser.c"
    break;

  case 57: /* Comp: Symval  */
#line 399 "SWL.y"
              { (yyval.comp_) = make_Compx((yyvsp[0].symval_));  }
#line 2028 "Parser.c"
    break;

  case 58: /* Comp: _SYMB_25  */
#line 400 "SWL.y"
             { (yyval.comp_) = make_Compn((yyvsp[0].string_));  }
#line 2034 "Parser.c"
    break;

  case 59: /* Comp: ModPath Symval  */
#line 401 "SWL.y"
                   { (yyval.comp_) = make_Compz((yyvsp[-1].modpath_), (yyvsp[0].symval_));  }
#line 2040 "Parser.c"
    break;

  case 60: /* Comp: RemPath  */
#line 402 "SWL.y"
            { (yyval.comp_) = make_Compa((yyvsp[0].rempath_));  }
#line 2046 "Parser.c"
    break;

  case 61: /* ModPath: _SYMB_12 Symval _SYMB_12  */
#line 404 "SWL.y"
                                   { (yyval.modpath_) = make_Modpa((yyvsp[-1].symval_));  }
#line 2052 "Parser.c"
    break;

  case 62: /* ModPath: Symval _SYMB_12  */
#line 405 "SWL.y"
                    { (yyval.modpath_) = make_Modpx((yyvsp[-1].symval_));  }
#line 2058 "Parser.c"
    break;

  case 63: /* ModPath: ModPath Symval _SYMB_12  */
#line 406 "SWL.y"
                            { (yyval.modpath_) = make_Modpy((yyvsp[-2].modpath_), (yyvsp[-1].symval_));  }
#line 2064 "Parser.c"
    break;

  case 64: /* ModPath: _SYMB_22 _SYMB_12  */
#line 407 "SWL.y"
                      { (yyval.modpath_) = make_Modps((yyvsp[-1].string_));  }
#line 2070 "Parser.c"
    break;

  case 65: /* RemPath: _SYMB_27 _SYMB_11 Symval  */
#line 409 "SWL.y"
                                   { (yyval.rempath_) = make_RemPatha((yyvsp[-2].string_), (yyvsp[0].symval_));  }
#line 2076 "Parser.c"
    break;

  case 66: /* Argument: Stringval  */
#line 411 "SWL.y"
                     { (yyval.argument_) = make_Argumentx((yyvsp[0].stringval_));  }
#line 2082 "Parser.c"
    break;

  case 67: /* ListArgument: %empty  */
#line 413 "SWL.y"
                           { (yyval.listargument_) = 0;  }
#line 2088 "Parser.c"
    break;

  case 68: /* ListArgument: ListArgument Argument  */
#line 414 "SWL.y"
                          { (yyval.listargument_) = make_ListArgument((yyvsp[0].argument_), (yyvsp[-1].listargument_));  }
#line 2094 "Parser.c"
    break;

  case 69: /* Numassgn: _SYMB_21 _SYMB_10 Numval  */
#line 416 "SWL.y"
                                    { (yyval.numassgn_) = make_NumAssgnv((yyvsp[-2].string_), (yyvsp[0].numval_));  }
#line 2100 "Parser.c"
    break;

  case 70: /* Strassgn: _SYMB_22 _SYMB_10 Stringval  */
#line 418 "SWL.y"
                                       { (yyval.strassgn_) = make_StrAssgnv((yyvsp[-2].string_), (yyvsp[0].stringval_));  }
#line 2106 "Parser.c"
    break;

  case 71: /* SymAssgn: _SYMB_24 _SYMB_10 Symval  */
#line 420 "SWL.y"
                                    { (yyval.symassgn_) = make_SymAssgni((yyvsp[-2].string_), (yyvsp[0].symval_));  }
#line 2112 "Parser.c"
    break;

  case 72: /* Numval: _INTEGER_  */
#line 422 "SWL.y"
                   { (yyval.numval_) = make_NumVali((yyvsp[0].int_));  }
#line 2118 "Parser.c"
    break;

  case 73: /* Numval: _SYMB_21  */
#line 423 "SWL.y"
             { (yyval.numval_) = make_NumValv((yyvsp[0].string_));  }
#line 2124 "Parser.c"
    break;

  case 74: /* Stringval: _STRING_  */
#line 425 "SWL.y"
                     { (yyval.stringval_) = make_StringVals((yyvsp[0].string_));  }
#line 2130 "Parser.c"
    break;

  case 75: /* Stringval: _SYMB_22  */
#line 426 "SWL.y"
             { (yyval.stringval_) = make_StringValv((yyvsp[0].string_));  }
#line 2136 "Parser.c"
    break;

  case 76: /* Stringval: _SYMB_23  */
#line 427 "SWL.y"
             { (yyval.stringval_) = make_StringVale((yyvsp[0].string_));  }
#line 2142 "Parser.c"
    break;

  case 77: /* Symval: _SYMB_24  */
#line 429 "SWL.y"
                  { (yyval.symval_) = make_Symvalv((yyvsp[0].string_));  }
#line 2148 "Parser.c"
    break;

  case 78: /* Symval: _SYMB_26  */
#line 430 "SWL.y"
             { (yyval.symval_) = make_Symvali((yyvsp[0].string_));  }
#line 2154 "Parser.c"
    break;

  case 79: /* Symval: _SYMB_23  */
#line 431 "SWL.y"
             { (yyval.symval_) = make_SymVale((yyvsp[0].string_));  }
#line 2160 "Parser.c"
    break;

  case 80: /* Include: _SYMB_19  */
#line 433 "SWL.y"
                   { (yyval.include_) = make_Inc1();  }
#line 2166 "Parser.c"
    break;

  case 81: /* Include: _SYMB_17  */
#line 434 "SWL.y"
             { (yyval.include_) = make_Inc2();  }
#line 2172 "Parser.c"
    break;

  case 82: /* Prefix: _SYMB_18  */
#line 436 "SWL.y"
                  { (yyval.prefix_) = make_Prefu();  }
#line 2178 "Parser.c"
    break;

  case 83: /* Prefix: _SYMB_20  */
#line 437 "SWL.y"
             { (yyval.prefix_) = make_Prefl();  }
#line 2184 "Parser.c"
    break;

  case 84: /* ValidConfig: _SYMB_13 ListEntry  */
#line 439 "SWL.y"
                                 { (yyval.validconfig_) = make_Validcfg(reverseListEntry((yyvsp[0].listentry_))); YY_RESULT_ValidConfig_= (yyval.validconfig_); }
#line 2190 "Parser.c"
    break;

  case 85: /* ValidConfig: _SYMB_14 _SYMB_13 _SYMB_1 ListCentry _SYMB_2  */
#line 440 "SWL.y"
                                                 { (yyval.validconfig_) = make_Validcfgd(reverseListCentry((yyvsp[-1].listcentry_))); YY_RESULT_ValidConfig_= (yyval.validconfig_); }
#line 2196 "Parser.c"
    break;

  case 86: /* Centry: KeyVal  */
#line 442 "SWL.y"
                { (yyval.centry_) = make_CfgcEntrya((yyvsp[0].keyval_));  }
#line 2202 "Parser.c"
    break;

  case 87: /* Centry: KeyName  */
#line 443 "SWL.y"
            { (yyval.centry_) = make_CfgcEntryb((yyvsp[0].keyname_));  }
#line 2208 "Parser.c"
    break;

  case 88: /* ListCentry: %empty  */
#line 445 "SWL.y"
                         { (yyval.listcentry_) = 0;  }
#line 2214 "Parser.c"
    break;

  case 89: /* ListCentry: ListCentry Centry _SYMB_6  */
#line 446 "SWL.y"
                              { (yyval.listcentry_) = make_ListCentry((yyvsp[-1].centry_), (yyvsp[-2].listcentry_));  }
#line 2220 "Parser.c"
    break;

  case 90: /* Entry: KeyVal  */
#line 448 "SWL.y"
               { (yyval.entry_) = make_CfgEntrya((yyvsp[0].keyval_));  }
#line 2226 "Parser.c"
    break;

  case 91: /* Entry: KeyName  */
#line 449 "SWL.y"
            { (yyval.entry_) = make_CfgEntryb((yyvsp[0].keyname_));  }
#line 2232 "Parser.c"
    break;

  case 92: /* ListEntry: %empty  */
#line 451 "SWL.y"
                        { (yyval.listentry_) = 0;  }
#line 2238 "Parser.c"
    break;

  case 93: /* ListEntry: ListEntry Entry  */
#line 452 "SWL.y"
                    { (yyval.listentry_) = make_ListEntry((yyvsp[0].entry_), (yyvsp[-1].listentry_));  }
#line 2244 "Parser.c"
    break;

  case 94: /* KeyVal: KeyName _INTEGER_  */
#line 454 "SWL.y"
                           { (yyval.keyval_) = make_CfgKeyvalint((yyvsp[-1].keyname_), (yyvsp[0].int_));  }
#line 2250 "Parser.c"
    break;

  case 95: /* KeyVal: KeyName _STRING_  */
#line 455 "SWL.y"
                     { (yyval.keyval_) = make_CfgKeyvalstr((yyvsp[-1].keyname_), (yyvsp[0].string_));  }
#line 2256 "Parser.c"
    break;

  case 96: /* KeyVal: KeyName _SYMB_28  */
#line 456 "SWL.y"
                     { (yyval.keyval_) = make_CfgKeyDate((yyvsp[-1].keyname_), (yyvsp[0].string_));  }
#line 2262 "Parser.c"
    break;

  case 97: /* KeyName: Symval _SYMB_15  */
#line 458 "SWL.y"
                          { (yyval.keyname_) = make_KeynameS((yyvsp[-1].symval_));  }
#line 2268 "Parser.c"
    break;

  case 98: /* KeyName: ModPath Symval _SYMB_15  */
#line 459 "SWL.y"
                            { (yyval.keyname_) = make_KeynameM((yyvsp[-2].modpath_), (yyvsp[-1].symval_));  }
#line 2274 "Parser.c"
    break;


#line 2278 "Parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 462 "SWL.y"

void yyerror(const char *str)
{
  extern char *SWLtext;
  fprintf(stderr,"error: %d,%d: %s at %s\n",
  SWLlloc.first_line, SWLlloc.first_column, str, SWLtext);
}

