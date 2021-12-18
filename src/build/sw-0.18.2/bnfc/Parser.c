/* A Bison parser, made by GNU Bison 3.7.5.  */

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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         SWparse
#define yylex           SWlex
#define yyerror         SWerror
#define yydebug         SWdebug
#define yynerrs         SWnerrs
#define yylval          SWlval
#define yychar          SWchar
#define yylloc          SWlloc

/* First part of user prologue.  */
#line 3 "SW.y"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Absyn.h"
typedef struct SW_buffer_state *YY_BUFFER_STATE;
YY_BUFFER_STATE SW_scan_string(const char *str);
void SW_delete_buffer(YY_BUFFER_STATE buf);
extern int yyparse(void);
extern int yylex(void);
extern int SW_init_lexer(FILE * inp);
extern void yyerror(const char *str);

Valide YY_RESULT_Valide_ = 0;
ValidSW YY_RESULT_ValidSW_ = 0;
ValidConfig YY_RESULT_ValidConfig_ = 0;

Valide pValide(FILE *inp)
{
  SW_init_lexer(inp);
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
  SW_init_lexer(0);
  buf = SW_scan_string(str);
  int result = yyparse();
  SW_delete_buffer(buf);
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
  SW_init_lexer(inp);
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
  SW_init_lexer(0);
  buf = SW_scan_string(str);
  int result = yyparse();
  SW_delete_buffer(buf);
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
  SW_init_lexer(inp);
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
  SW_init_lexer(0);
  buf = SW_scan_string(str);
  int result = yyparse();
  SW_delete_buffer(buf);
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


#line 255 "Parser.c"

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
extern int SWdebug;
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
    _STRING_ = 287,                /* _STRING_  */
    _INTEGER_ = 288                /* _INTEGER_  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 180 "SW.y"

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


#line 382 "Parser.c"

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


extern YYSTYPE SWlval;
extern YYLTYPE SWlloc;
int SWparse (void);


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
  YYSYMBOL__STRING_ = 32,                  /* _STRING_  */
  YYSYMBOL__INTEGER_ = 33,                 /* _INTEGER_  */
  YYSYMBOL_YYACCEPT = 34,                  /* $accept  */
  YYSYMBOL_Valide = 35,                    /* Valide  */
  YYSYMBOL_ValidSW = 36,                   /* ValidSW  */
  YYSYMBOL_Stm = 37,                       /* Stm  */
  YYSYMBOL_ListStm = 38,                   /* ListStm  */
  YYSYMBOL_Subdef = 39,                    /* Subdef  */
  YYSYMBOL_Subnet = 40,                    /* Subnet  */
  YYSYMBOL_ListSubnet = 41,                /* ListSubnet  */
  YYSYMBOL_ExtPortIn = 42,                 /* ExtPortIn  */
  YYSYMBOL_ExtPortOut = 43,                /* ExtPortOut  */
  YYSYMBOL_Tab = 44,                       /* Tab  */
  YYSYMBOL_DataFlow = 45,                  /* DataFlow  */
  YYSYMBOL_Larrow = 46,                    /* Larrow  */
  YYSYMBOL_Rarrow = 47,                    /* Rarrow  */
  YYSYMBOL_TypeDef = 48,                   /* TypeDef  */
  YYSYMBOL_Buffsize = 49,                  /* Buffsize  */
  YYSYMBOL_Hermt = 50,                     /* Hermt  */
  YYSYMBOL_Symvalu = 51,                   /* Symvalu  */
  YYSYMBOL_Proc = 52,                      /* Proc  */
  YYSYMBOL_Prt = 53,                       /* Prt  */
  YYSYMBOL_Comp = 54,                      /* Comp  */
  YYSYMBOL_ModPath = 55,                   /* ModPath  */
  YYSYMBOL_RemPath = 56,                   /* RemPath  */
  YYSYMBOL_Argument = 57,                  /* Argument  */
  YYSYMBOL_ListArgument = 58,              /* ListArgument  */
  YYSYMBOL_Numassgn = 59,                  /* Numassgn  */
  YYSYMBOL_Strassgn = 60,                  /* Strassgn  */
  YYSYMBOL_SymAssgn = 61,                  /* SymAssgn  */
  YYSYMBOL_Numval = 62,                    /* Numval  */
  YYSYMBOL_Stringval = 63,                 /* Stringval  */
  YYSYMBOL_Symval = 64,                    /* Symval  */
  YYSYMBOL_Include = 65,                   /* Include  */
  YYSYMBOL_Prefix = 66,                    /* Prefix  */
  YYSYMBOL_ValidConfig = 67,               /* ValidConfig  */
  YYSYMBOL_Centry = 68,                    /* Centry  */
  YYSYMBOL_ListCentry = 69,                /* ListCentry  */
  YYSYMBOL_Entry = 70,                     /* Entry  */
  YYSYMBOL_ListEntry = 71,                 /* ListEntry  */
  YYSYMBOL_KeyVal = 72,                    /* KeyVal  */
  YYSYMBOL_KeyName = 73                    /* KeyName  */
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
#define YYLAST   179

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  149

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   288


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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   302,   302,   303,   305,   307,   308,   309,   310,   311,
     312,   313,   314,   316,   317,   319,   321,   322,   323,   324,
     326,   327,   329,   330,   332,   333,   335,   336,   338,   339,
     340,   341,   343,   345,   347,   348,   350,   351,   353,   354,
     356,   357,   359,   360,   362,   363,   364,   365,   366,   368,
     369,   370,   371,   373,   374,   375,   376,   378,   380,   382,
     383,   385,   387,   389,   391,   392,   394,   395,   396,   398,
     399,   400,   402,   403,   405,   406,   408,   409,   411,   412,
     414,   415,   417,   418,   420,   421,   423,   424,   425,   427,
     428
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
  "_SYMB_25", "_SYMB_26", "_SYMB_27", "_STRING_", "_INTEGER_", "$accept",
  "Valide", "ValidSW", "Stm", "ListStm", "Subdef", "Subnet", "ListSubnet",
  "ExtPortIn", "ExtPortOut", "Tab", "DataFlow", "Larrow", "Rarrow",
  "TypeDef", "Buffsize", "Hermt", "Symvalu", "Proc", "Prt", "Comp",
  "ModPath", "RemPath", "Argument", "ListArgument", "Numassgn", "Strassgn",
  "SymAssgn", "Numval", "Stringval", "Symval", "Include", "Prefix",
  "ValidConfig", "Centry", "ListCentry", "Entry", "ListEntry", "KeyVal",
  "KeyName", YY_NULLPTR
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
     285,   286,   287,   288
};
#endif

#define YYPACT_NINF (-75)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-48)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      90,   -75,    -1,    18,   -75,   118,   -75,   142,    26,   -75,
     -75,   122,   -75,   -75,   -75,   -75,     5,    50,   -75,    59,
      79,   -75,    83,   -75,     1,   -75,   136,   146,   -75,   -75,
     -75,   -75,   -13,   -13,    27,    76,   -75,    27,    41,   -75,
     -75,    61,   -75,   136,    -7,   -13,    27,   -75,   -75,   -75,
     -75,   129,    95,   102,   -75,   104,   -75,    27,   -75,   -13,
      89,   129,   -75,   -75,   -75,   -75,   -75,    98,   -75,    43,
     -75,   -75,   -75,   -75,   -75,    10,   -75,    84,   -75,   -75,
     -75,    94,   122,   122,   146,   146,    27,    -7,    27,   -13,
     105,   -75,   -75,   146,   146,   -75,   -75,   -75,   -75,   108,
     -75,    61,    99,   -75,   -75,    93,   -75,   -75,   129,    62,
     -75,   146,   -75,   145,    -7,   -75,    -7,   111,   111,   -75,
     -75,   -75,   111,   111,   -75,   -75,   -75,   146,   146,   129,
     125,   -75,   121,   -75,   -75,   -75,   -75,   111,   111,   146,
     146,   -75,   -75,   -75,   -75,   -75,    34,    58,   -75
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      13,    84,     0,     0,     3,     4,     2,    76,     0,     1,
      41,     0,    73,    74,    72,    75,     0,     0,    71,    69,
       0,    70,     0,    12,    48,    11,    59,    48,     8,     9,
      10,    40,     0,     0,     0,     0,    69,     0,     0,    85,
      82,    83,    80,    59,     0,     0,     0,    20,    14,    65,
      64,     0,    44,    47,    50,     0,    59,     0,    52,    39,
      49,     0,    67,    68,    66,     6,     5,     0,    56,     0,
      54,    89,    88,    87,    86,     0,    59,     0,    61,    62,
      63,     0,    35,    35,    48,    48,     0,     0,     0,    38,
      51,    60,    58,    48,    48,    53,    55,    90,    77,     0,
      78,    79,     0,    43,    15,     0,    18,    19,     0,    48,
      16,    48,    26,    40,    37,    34,    37,     0,     0,    45,
      46,    57,     0,     0,    81,    42,    21,    48,    48,     0,
       0,    36,     0,    30,    31,    28,    29,     0,     0,    48,
      48,    32,    33,    24,    23,    22,    26,    27,    25
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,
      15,    77,   -57,   -47,    74,    44,    78,    -3,   -74,   -26,
     131,     7,   -75,   -75,   -34,   -75,   -75,   -75,   -41,   -22,
      -5,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   101,   103
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,     4,    22,     5,    23,   105,    81,   106,   107,
     108,    24,    84,    85,   114,   130,    25,    26,    27,    51,
      56,    37,    58,    91,    59,    28,    29,    30,    52,    92,
      53,    32,    33,     6,    99,    75,    39,     7,    40,    41
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      31,    61,    38,    78,    93,    -7,    31,   111,    43,    77,
      65,    66,    62,    63,    94,     8,    98,    49,     9,    64,
      44,    60,    89,    79,    34,    49,    50,    18,    36,    67,
      21,    42,    69,    57,    50,    35,    18,    36,    60,    21,
     112,    80,   102,   133,   134,   -44,   120,    86,   135,   136,
      57,   127,    90,    18,    36,    70,    21,    96,   117,   118,
      71,   128,    97,   143,   144,    45,   -17,   122,   123,   -47,
      38,    87,   139,   131,    46,   131,   113,    31,    31,   115,
     115,   119,   140,   121,    47,   129,    49,    48,    18,    36,
      68,    21,    72,    73,    74,    50,   103,   126,   146,   146,
     104,   137,   138,    70,    10,    11,     1,     2,    86,    62,
      63,   125,    95,   122,   123,    87,    64,    88,    49,    96,
      18,    36,    11,    21,    62,    63,   124,    50,    10,    11,
     142,    64,    10,   141,   147,   147,    82,    83,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    18,    36,
      34,    21,   -27,   -27,   145,   148,    34,   116,   109,   110,
     132,    35,    18,    36,    54,    21,    55,    35,    18,    36,
      49,    21,    18,    36,    76,    21,   100,     0,   101,    50
};

static const yytype_int16 yycheck[] =
{
       5,    27,     7,    44,    61,     4,    11,    81,    11,    43,
      32,    33,    25,    26,    61,    16,     6,    24,     0,    32,
      15,    26,    56,    45,    14,    24,    33,    26,    27,    34,
      29,     5,    37,    26,    33,    25,    26,    27,    43,    29,
      81,    46,    76,   117,   118,    11,    87,    13,   122,   123,
      43,   108,    57,    26,    27,    14,    29,    14,    84,    85,
      19,   108,    19,   137,   138,    15,     4,    93,    94,    11,
      75,    13,   129,   114,    15,   116,    81,    82,    83,    82,
      83,    86,   129,    88,     5,   111,    24,     4,    26,    27,
      14,    29,    31,    32,    33,    33,    12,     4,   139,   140,
       6,   127,   128,    14,    10,    11,    16,    17,    13,    25,
      26,    12,    14,   139,   140,    13,    32,    13,    24,    14,
      26,    27,    11,    29,    25,    26,    18,    33,    10,    11,
       9,    32,    10,     8,   139,   140,     7,     8,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    26,    27,
      14,    29,     7,     8,   139,   140,    14,    83,    81,    81,
     116,    25,    26,    27,    28,    29,    30,    25,    26,    27,
      24,    29,    26,    27,    43,    29,    75,    -1,    75,    33
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    16,    17,    35,    36,    38,    67,    71,    16,     0,
      10,    11,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    37,    39,    45,    50,    51,    52,    59,    60,
      61,    64,    65,    66,    14,    25,    27,    55,    64,    70,
      72,    73,     5,    51,    15,    15,    15,     5,     4,    24,
      33,    53,    62,    64,    28,    30,    54,    55,    56,    58,
      64,    53,    25,    26,    32,    63,    63,    64,    14,    64,
      14,    19,    31,    32,    33,    69,    54,    58,    62,    63,
      64,    41,     7,     8,    46,    47,    13,    13,    13,    58,
      64,    57,    63,    46,    47,    14,    14,    19,     6,    68,
      72,    73,    58,    12,     6,    40,    42,    43,    44,    45,
      50,    52,    62,    64,    48,    51,    48,    53,    53,    64,
      62,    64,    53,    53,    18,    12,     4,    46,    47,    53,
      49,    62,    49,    52,    52,    52,    52,    53,    53,    46,
      47,     8,     9,    52,    52,    44,    62,    64,    44
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    34,    35,    35,    36,    37,    37,    37,    37,    37,
      37,    37,    37,    38,    38,    39,    40,    40,    40,    40,
      41,    41,    42,    42,    43,    43,    44,    44,    45,    45,
      45,    45,    46,    47,    48,    48,    49,    49,    50,    50,
      51,    51,    52,    52,    53,    53,    53,    53,    53,    54,
      54,    54,    54,    55,    55,    55,    55,    56,    57,    58,
      58,    59,    60,    61,    62,    62,    63,    63,    63,    64,
      64,    64,    65,    65,    66,    66,    67,    67,    68,    68,
      69,    69,    70,    70,    71,    71,    72,    72,    72,    73,
      73
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     0,     3,     4,     1,     1,     1,     1,
       0,     3,     4,     4,     4,     4,     1,     1,     5,     5,
       5,     5,     4,     4,     1,     0,     1,     0,     3,     2,
       1,     1,     5,     4,     1,     3,     3,     1,     0,     1,
       1,     2,     1,     3,     2,     3,     2,     3,     1,     0,
       2,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     5,     1,     1,
       0,     3,     1,     1,     0,     2,     2,     2,     2,     2,
       3
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
#line 302 "SW.y"
                     { (yyval.valide_) = make_CFGvalid((yyvsp[0].validconfig_)); YY_RESULT_Valide_= (yyval.valide_); }
#line 1663 "Parser.c"
    break;

  case 3: /* Valide: ValidSW  */
#line 303 "SW.y"
            { (yyval.valide_) = make_SWvalid((yyvsp[0].validsw_)); YY_RESULT_Valide_= (yyval.valide_); }
#line 1669 "Parser.c"
    break;

  case 4: /* ValidSW: ListStm  */
#line 305 "SW.y"
                  { (yyval.validsw_) = make_Valid(reverseListStm((yyvsp[0].liststm_))); YY_RESULT_ValidSW_= (yyval.validsw_); }
#line 1675 "Parser.c"
    break;

  case 5: /* Stm: Prefix Stringval  */
#line 307 "SW.y"
                       { (yyval.stm_) = make_StmPrefix((yyvsp[-1].prefix_), (yyvsp[0].stringval_));  }
#line 1681 "Parser.c"
    break;

  case 6: /* Stm: Include Stringval  */
#line 308 "SW.y"
                      { (yyval.stm_) = make_Stminc((yyvsp[-1].include_), (yyvsp[0].stringval_));  }
#line 1687 "Parser.c"
    break;

  case 7: /* Stm: DataFlow  */
#line 309 "SW.y"
             { (yyval.stm_) = make_Stmx((yyvsp[0].dataflow_));  }
#line 1693 "Parser.c"
    break;

  case 8: /* Stm: Numassgn  */
#line 310 "SW.y"
             { (yyval.stm_) = make_Stmn((yyvsp[0].numassgn_));  }
#line 1699 "Parser.c"
    break;

  case 9: /* Stm: Strassgn  */
#line 311 "SW.y"
             { (yyval.stm_) = make_Stms((yyvsp[0].strassgn_));  }
#line 1705 "Parser.c"
    break;

  case 10: /* Stm: SymAssgn  */
#line 312 "SW.y"
             { (yyval.stm_) = make_Stmb((yyvsp[0].symassgn_));  }
#line 1711 "Parser.c"
    break;

  case 11: /* Stm: Hermt  */
#line 313 "SW.y"
          { (yyval.stm_) = make_Stmh((yyvsp[0].hermt_));  }
#line 1717 "Parser.c"
    break;

  case 12: /* Stm: Subdef  */
#line 314 "SW.y"
           { (yyval.stm_) = make_Stmnet((yyvsp[0].subdef_));  }
#line 1723 "Parser.c"
    break;

  case 13: /* ListStm: %empty  */
#line 316 "SW.y"
                      { (yyval.liststm_) = 0;  }
#line 1729 "Parser.c"
    break;

  case 14: /* ListStm: ListStm Stm _SYMB_0  */
#line 317 "SW.y"
                        { (yyval.liststm_) = make_ListStm((yyvsp[-1].stm_), (yyvsp[-2].liststm_));  }
#line 1735 "Parser.c"
    break;

  case 15: /* Subdef: _SYMB_24 _SYMB_1 ListSubnet _SYMB_2  */
#line 319 "SW.y"
                                             { (yyval.subdef_) = make_Snet((yyvsp[-3].string_), reverseListSubnet((yyvsp[-1].listsubnet_)));  }
#line 1741 "Parser.c"
    break;

  case 16: /* Subnet: Hermt  */
#line 321 "SW.y"
               { (yyval.subnet_) = make_Sneth((yyvsp[0].hermt_));  }
#line 1747 "Parser.c"
    break;

  case 17: /* Subnet: DataFlow  */
#line 322 "SW.y"
             { (yyval.subnet_) = make_Snets((yyvsp[0].dataflow_));  }
#line 1753 "Parser.c"
    break;

  case 18: /* Subnet: ExtPortIn  */
#line 323 "SW.y"
              { (yyval.subnet_) = make_Snetin((yyvsp[0].extportin_));  }
#line 1759 "Parser.c"
    break;

  case 19: /* Subnet: ExtPortOut  */
#line 324 "SW.y"
               { (yyval.subnet_) = make_Snetout((yyvsp[0].extportout_));  }
#line 1765 "Parser.c"
    break;

  case 20: /* ListSubnet: %empty  */
#line 326 "SW.y"
                         { (yyval.listsubnet_) = 0;  }
#line 1771 "Parser.c"
    break;

  case 21: /* ListSubnet: ListSubnet Subnet _SYMB_0  */
#line 327 "SW.y"
                              { (yyval.listsubnet_) = make_ListSubnet((yyvsp[-1].subnet_), (yyvsp[-2].listsubnet_));  }
#line 1777 "Parser.c"
    break;

  case 22: /* ExtPortIn: Proc Prt Larrow Tab  */
#line 329 "SW.y"
                                { (yyval.extportin_) = make_Extin((yyvsp[-3].proc_), (yyvsp[-2].prt_), (yyvsp[-1].larrow_), (yyvsp[0].tab_));  }
#line 1783 "Parser.c"
    break;

  case 23: /* ExtPortIn: Tab Rarrow Prt Proc  */
#line 330 "SW.y"
                        { (yyval.extportin_) = make_ExtinR((yyvsp[-3].tab_), (yyvsp[-2].rarrow_), (yyvsp[-1].prt_), (yyvsp[0].proc_));  }
#line 1789 "Parser.c"
    break;

  case 24: /* ExtPortOut: Tab Larrow Prt Proc  */
#line 332 "SW.y"
                                 { (yyval.extportout_) = make_Extout((yyvsp[-3].tab_), (yyvsp[-2].larrow_), (yyvsp[-1].prt_), (yyvsp[0].proc_));  }
#line 1795 "Parser.c"
    break;

  case 25: /* ExtPortOut: Proc Prt Rarrow Tab  */
#line 333 "SW.y"
                        { (yyval.extportout_) = make_Extoutr((yyvsp[-3].proc_), (yyvsp[-2].prt_), (yyvsp[-1].rarrow_), (yyvsp[0].tab_));  }
#line 1801 "Parser.c"
    break;

  case 26: /* Tab: Numval  */
#line 335 "SW.y"
             { (yyval.tab_) = make_Tabn((yyvsp[0].numval_));  }
#line 1807 "Parser.c"
    break;

  case 27: /* Tab: Symval  */
#line 336 "SW.y"
           { (yyval.tab_) = make_Tabs((yyvsp[0].symval_));  }
#line 1813 "Parser.c"
    break;

  case 28: /* DataFlow: Proc Prt Larrow Prt Proc  */
#line 338 "SW.y"
                                    { (yyval.dataflow_) = make_Streamx((yyvsp[-4].proc_), (yyvsp[-3].prt_), (yyvsp[-2].larrow_), (yyvsp[-1].prt_), (yyvsp[0].proc_));  }
#line 1819 "Parser.c"
    break;

  case 29: /* DataFlow: Proc Prt Rarrow Prt Proc  */
#line 339 "SW.y"
                             { (yyval.dataflow_) = make_Streamrx((yyvsp[-4].proc_), (yyvsp[-3].prt_), (yyvsp[-2].rarrow_), (yyvsp[-1].prt_), (yyvsp[0].proc_));  }
#line 1825 "Parser.c"
    break;

  case 30: /* DataFlow: DataFlow Prt Larrow Prt Proc  */
#line 340 "SW.y"
                                 { (yyval.dataflow_) = make_Streamy((yyvsp[-4].dataflow_), (yyvsp[-3].prt_), (yyvsp[-2].larrow_), (yyvsp[-1].prt_), (yyvsp[0].proc_));  }
#line 1831 "Parser.c"
    break;

  case 31: /* DataFlow: DataFlow Prt Rarrow Prt Proc  */
#line 341 "SW.y"
                                 { (yyval.dataflow_) = make_Streamry((yyvsp[-4].dataflow_), (yyvsp[-3].prt_), (yyvsp[-2].rarrow_), (yyvsp[-1].prt_), (yyvsp[0].proc_));  }
#line 1837 "Parser.c"
    break;

  case 32: /* Larrow: _SYMB_3 TypeDef Buffsize _SYMB_4  */
#line 343 "SW.y"
                                          { (yyval.larrow_) = make_Arrowx((yyvsp[-2].typedef_), (yyvsp[-1].buffsize_));  }
#line 1843 "Parser.c"
    break;

  case 33: /* Rarrow: _SYMB_4 TypeDef Buffsize _SYMB_5  */
#line 345 "SW.y"
                                          { (yyval.rarrow_) = make_Arrowr((yyvsp[-2].typedef_), (yyvsp[-1].buffsize_));  }
#line 1849 "Parser.c"
    break;

  case 34: /* TypeDef: Symvalu  */
#line 347 "SW.y"
                  { (yyval.typedef_) = make_Typedefa((yyvsp[0].symvalu_));  }
#line 1855 "Parser.c"
    break;

  case 35: /* TypeDef: %empty  */
#line 348 "SW.y"
                { (yyval.typedef_) = make_Typedefnull();  }
#line 1861 "Parser.c"
    break;

  case 36: /* Buffsize: Numval  */
#line 350 "SW.y"
                  { (yyval.buffsize_) = make_Bufszi((yyvsp[0].numval_));  }
#line 1867 "Parser.c"
    break;

  case 37: /* Buffsize: %empty  */
#line 351 "SW.y"
                { (yyval.buffsize_) = make_Bufsze();  }
#line 1873 "Parser.c"
    break;

  case 38: /* Hermt: Symvalu Comp ListArgument  */
#line 353 "SW.y"
                                  { (yyval.hermt_) = make_Hermtx((yyvsp[-2].symvalu_), (yyvsp[-1].comp_), reverseListArgument((yyvsp[0].listargument_)));  }
#line 1879 "Parser.c"
    break;

  case 39: /* Hermt: Symvalu ListArgument  */
#line 354 "SW.y"
                         { (yyval.hermt_) = make_Hermty((yyvsp[-1].symvalu_), reverseListArgument((yyvsp[0].listargument_)));  }
#line 1885 "Parser.c"
    break;

  case 40: /* Symvalu: Symval  */
#line 356 "SW.y"
                 { (yyval.symvalu_) = make_Symvaluv((yyvsp[0].symval_));  }
#line 1891 "Parser.c"
    break;

  case 41: /* Symvalu: _SYMB_6  */
#line 357 "SW.y"
            { (yyval.symvalu_) = make_Symvaluu();  }
#line 1897 "Parser.c"
    break;

  case 42: /* Proc: _SYMB_7 Symvalu Comp ListArgument _SYMB_8  */
#line 359 "SW.y"
                                                 { (yyval.proc_) = make_Processx((yyvsp[-3].symvalu_), (yyvsp[-2].comp_), reverseListArgument((yyvsp[-1].listargument_)));  }
#line 1903 "Parser.c"
    break;

  case 43: /* Proc: _SYMB_7 Symvalu ListArgument _SYMB_8  */
#line 360 "SW.y"
                                         { (yyval.proc_) = make_Processy((yyvsp[-2].symvalu_), reverseListArgument((yyvsp[-1].listargument_)));  }
#line 1909 "Parser.c"
    break;

  case 44: /* Prt: Numval  */
#line 362 "SW.y"
             { (yyval.prt_) = make_Portx((yyvsp[0].numval_));  }
#line 1915 "Parser.c"
    break;

  case 45: /* Prt: Numval _SYMB_9 Symval  */
#line 363 "SW.y"
                          { (yyval.prt_) = make_Portni((yyvsp[-2].numval_), (yyvsp[0].symval_));  }
#line 1921 "Parser.c"
    break;

  case 46: /* Prt: Symval _SYMB_9 Numval  */
#line 364 "SW.y"
                          { (yyval.prt_) = make_Portin((yyvsp[-2].symval_), (yyvsp[0].numval_));  }
#line 1927 "Parser.c"
    break;

  case 47: /* Prt: Symval  */
#line 365 "SW.y"
           { (yyval.prt_) = make_Portn((yyvsp[0].symval_));  }
#line 1933 "Parser.c"
    break;

  case 48: /* Prt: %empty  */
#line 366 "SW.y"
                { (yyval.prt_) = make_Porte();  }
#line 1939 "Parser.c"
    break;

  case 49: /* Comp: Symval  */
#line 368 "SW.y"
              { (yyval.comp_) = make_Compx((yyvsp[0].symval_));  }
#line 1945 "Parser.c"
    break;

  case 50: /* Comp: _SYMB_24  */
#line 369 "SW.y"
             { (yyval.comp_) = make_Compn((yyvsp[0].string_));  }
#line 1951 "Parser.c"
    break;

  case 51: /* Comp: ModPath Symval  */
#line 370 "SW.y"
                   { (yyval.comp_) = make_Compz((yyvsp[-1].modpath_), (yyvsp[0].symval_));  }
#line 1957 "Parser.c"
    break;

  case 52: /* Comp: RemPath  */
#line 371 "SW.y"
            { (yyval.comp_) = make_Compa((yyvsp[0].rempath_));  }
#line 1963 "Parser.c"
    break;

  case 53: /* ModPath: _SYMB_10 Symval _SYMB_10  */
#line 373 "SW.y"
                                   { (yyval.modpath_) = make_Modpa((yyvsp[-1].symval_));  }
#line 1969 "Parser.c"
    break;

  case 54: /* ModPath: Symval _SYMB_10  */
#line 374 "SW.y"
                    { (yyval.modpath_) = make_Modpx((yyvsp[-1].symval_));  }
#line 1975 "Parser.c"
    break;

  case 55: /* ModPath: ModPath Symval _SYMB_10  */
#line 375 "SW.y"
                            { (yyval.modpath_) = make_Modpy((yyvsp[-2].modpath_), (yyvsp[-1].symval_));  }
#line 1981 "Parser.c"
    break;

  case 56: /* ModPath: _SYMB_21 _SYMB_10  */
#line 376 "SW.y"
                      { (yyval.modpath_) = make_Modps((yyvsp[-1].string_));  }
#line 1987 "Parser.c"
    break;

  case 57: /* RemPath: _SYMB_26 _SYMB_9 Symval  */
#line 378 "SW.y"
                                  { (yyval.rempath_) = make_RemPatha((yyvsp[-2].string_), (yyvsp[0].symval_));  }
#line 1993 "Parser.c"
    break;

  case 58: /* Argument: Stringval  */
#line 380 "SW.y"
                     { (yyval.argument_) = make_Argumentx((yyvsp[0].stringval_));  }
#line 1999 "Parser.c"
    break;

  case 59: /* ListArgument: %empty  */
#line 382 "SW.y"
                           { (yyval.listargument_) = 0;  }
#line 2005 "Parser.c"
    break;

  case 60: /* ListArgument: ListArgument Argument  */
#line 383 "SW.y"
                          { (yyval.listargument_) = make_ListArgument((yyvsp[0].argument_), (yyvsp[-1].listargument_));  }
#line 2011 "Parser.c"
    break;

  case 61: /* Numassgn: _SYMB_20 _SYMB_11 Numval  */
#line 385 "SW.y"
                                    { (yyval.numassgn_) = make_NumAssgnv((yyvsp[-2].string_), (yyvsp[0].numval_));  }
#line 2017 "Parser.c"
    break;

  case 62: /* Strassgn: _SYMB_21 _SYMB_11 Stringval  */
#line 387 "SW.y"
                                       { (yyval.strassgn_) = make_StrAssgnv((yyvsp[-2].string_), (yyvsp[0].stringval_));  }
#line 2023 "Parser.c"
    break;

  case 63: /* SymAssgn: _SYMB_23 _SYMB_11 Symval  */
#line 389 "SW.y"
                                    { (yyval.symassgn_) = make_SymAssgni((yyvsp[-2].string_), (yyvsp[0].symval_));  }
#line 2029 "Parser.c"
    break;

  case 64: /* Numval: _INTEGER_  */
#line 391 "SW.y"
                   { (yyval.numval_) = make_NumVali((yyvsp[0].int_));  }
#line 2035 "Parser.c"
    break;

  case 65: /* Numval: _SYMB_20  */
#line 392 "SW.y"
             { (yyval.numval_) = make_NumValv((yyvsp[0].string_));  }
#line 2041 "Parser.c"
    break;

  case 66: /* Stringval: _STRING_  */
#line 394 "SW.y"
                     { (yyval.stringval_) = make_StringVals((yyvsp[0].string_));  }
#line 2047 "Parser.c"
    break;

  case 67: /* Stringval: _SYMB_21  */
#line 395 "SW.y"
             { (yyval.stringval_) = make_StringValv((yyvsp[0].string_));  }
#line 2053 "Parser.c"
    break;

  case 68: /* Stringval: _SYMB_22  */
#line 396 "SW.y"
             { (yyval.stringval_) = make_StringVale((yyvsp[0].string_));  }
#line 2059 "Parser.c"
    break;

  case 69: /* Symval: _SYMB_23  */
#line 398 "SW.y"
                  { (yyval.symval_) = make_Symvalv((yyvsp[0].string_));  }
#line 2065 "Parser.c"
    break;

  case 70: /* Symval: _SYMB_25  */
#line 399 "SW.y"
             { (yyval.symval_) = make_Symvali((yyvsp[0].string_));  }
#line 2071 "Parser.c"
    break;

  case 71: /* Symval: _SYMB_22  */
#line 400 "SW.y"
             { (yyval.symval_) = make_SymVale((yyvsp[0].string_));  }
#line 2077 "Parser.c"
    break;

  case 72: /* Include: _SYMB_18  */
#line 402 "SW.y"
                   { (yyval.include_) = make_Inc1();  }
#line 2083 "Parser.c"
    break;

  case 73: /* Include: _SYMB_16  */
#line 403 "SW.y"
             { (yyval.include_) = make_Inc2();  }
#line 2089 "Parser.c"
    break;

  case 74: /* Prefix: _SYMB_17  */
#line 405 "SW.y"
                  { (yyval.prefix_) = make_Prefu();  }
#line 2095 "Parser.c"
    break;

  case 75: /* Prefix: _SYMB_19  */
#line 406 "SW.y"
             { (yyval.prefix_) = make_Prefl();  }
#line 2101 "Parser.c"
    break;

  case 76: /* ValidConfig: _SYMB_12 ListEntry  */
#line 408 "SW.y"
                                 { (yyval.validconfig_) = make_Validcfg(reverseListEntry((yyvsp[0].listentry_))); YY_RESULT_ValidConfig_= (yyval.validconfig_); }
#line 2107 "Parser.c"
    break;

  case 77: /* ValidConfig: _SYMB_13 _SYMB_12 _SYMB_1 ListCentry _SYMB_2  */
#line 409 "SW.y"
                                                 { (yyval.validconfig_) = make_Validcfgd(reverseListCentry((yyvsp[-1].listcentry_))); YY_RESULT_ValidConfig_= (yyval.validconfig_); }
#line 2113 "Parser.c"
    break;

  case 78: /* Centry: KeyVal  */
#line 411 "SW.y"
                { (yyval.centry_) = make_CfgcEntrya((yyvsp[0].keyval_));  }
#line 2119 "Parser.c"
    break;

  case 79: /* Centry: KeyName  */
#line 412 "SW.y"
            { (yyval.centry_) = make_CfgcEntryb((yyvsp[0].keyname_));  }
#line 2125 "Parser.c"
    break;

  case 80: /* ListCentry: %empty  */
#line 414 "SW.y"
                         { (yyval.listcentry_) = 0;  }
#line 2131 "Parser.c"
    break;

  case 81: /* ListCentry: ListCentry Centry _SYMB_14  */
#line 415 "SW.y"
                               { (yyval.listcentry_) = make_ListCentry((yyvsp[-1].centry_), (yyvsp[-2].listcentry_));  }
#line 2137 "Parser.c"
    break;

  case 82: /* Entry: KeyVal  */
#line 417 "SW.y"
               { (yyval.entry_) = make_CfgEntrya((yyvsp[0].keyval_));  }
#line 2143 "Parser.c"
    break;

  case 83: /* Entry: KeyName  */
#line 418 "SW.y"
            { (yyval.entry_) = make_CfgEntryb((yyvsp[0].keyname_));  }
#line 2149 "Parser.c"
    break;

  case 84: /* ListEntry: %empty  */
#line 420 "SW.y"
                        { (yyval.listentry_) = 0;  }
#line 2155 "Parser.c"
    break;

  case 85: /* ListEntry: ListEntry Entry  */
#line 421 "SW.y"
                    { (yyval.listentry_) = make_ListEntry((yyvsp[0].entry_), (yyvsp[-1].listentry_));  }
#line 2161 "Parser.c"
    break;

  case 86: /* KeyVal: KeyName _INTEGER_  */
#line 423 "SW.y"
                           { (yyval.keyval_) = make_CfgKeyvalint((yyvsp[-1].keyname_), (yyvsp[0].int_));  }
#line 2167 "Parser.c"
    break;

  case 87: /* KeyVal: KeyName _STRING_  */
#line 424 "SW.y"
                     { (yyval.keyval_) = make_CfgKeyvalstr((yyvsp[-1].keyname_), (yyvsp[0].string_));  }
#line 2173 "Parser.c"
    break;

  case 88: /* KeyVal: KeyName _SYMB_27  */
#line 425 "SW.y"
                     { (yyval.keyval_) = make_CfgKeyDate((yyvsp[-1].keyname_), (yyvsp[0].string_));  }
#line 2179 "Parser.c"
    break;

  case 89: /* KeyName: Symval _SYMB_15  */
#line 427 "SW.y"
                          { (yyval.keyname_) = make_KeynameS((yyvsp[-1].symval_));  }
#line 2185 "Parser.c"
    break;

  case 90: /* KeyName: ModPath Symval _SYMB_15  */
#line 428 "SW.y"
                            { (yyval.keyname_) = make_KeynameM((yyvsp[-2].modpath_), (yyvsp[-1].symval_));  }
#line 2191 "Parser.c"
    break;


#line 2195 "Parser.c"

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

#line 431 "SW.y"

void yyerror(const char *str)
{
  extern char *SWtext;
  fprintf(stderr,"error: %d,%d: %s at %s\n",
  SWlloc.first_line, SWlloc.first_column, str, SWtext);
}

