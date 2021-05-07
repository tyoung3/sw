/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

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


#line 242 "Parser.c"

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
    _STRING_ = 282,                /* _STRING_  */
    _INTEGER_ = 283                /* _INTEGER_  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 167 "SW.y"

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
  ValidConfig validconfig_;
  Entry entry_;
  ListEntry listentry_;
  KeyVal keyval_;
  KeyName keyname_;


#line 360 "Parser.c"

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
  YYSYMBOL__STRING_ = 27,                  /* _STRING_  */
  YYSYMBOL__INTEGER_ = 28,                 /* _INTEGER_  */
  YYSYMBOL_YYACCEPT = 29,                  /* $accept  */
  YYSYMBOL_Valide = 30,                    /* Valide  */
  YYSYMBOL_ValidSW = 31,                   /* ValidSW  */
  YYSYMBOL_Stm = 32,                       /* Stm  */
  YYSYMBOL_ListStm = 33,                   /* ListStm  */
  YYSYMBOL_Subdef = 34,                    /* Subdef  */
  YYSYMBOL_Subnet = 35,                    /* Subnet  */
  YYSYMBOL_ListSubnet = 36,                /* ListSubnet  */
  YYSYMBOL_ExtPortIn = 37,                 /* ExtPortIn  */
  YYSYMBOL_ExtPortOut = 38,                /* ExtPortOut  */
  YYSYMBOL_Tab = 39,                       /* Tab  */
  YYSYMBOL_DataFlow = 40,                  /* DataFlow  */
  YYSYMBOL_Larrow = 41,                    /* Larrow  */
  YYSYMBOL_Rarrow = 42,                    /* Rarrow  */
  YYSYMBOL_TypeDef = 43,                   /* TypeDef  */
  YYSYMBOL_Buffsize = 44,                  /* Buffsize  */
  YYSYMBOL_Hermt = 45,                     /* Hermt  */
  YYSYMBOL_Symvalu = 46,                   /* Symvalu  */
  YYSYMBOL_Proc = 47,                      /* Proc  */
  YYSYMBOL_Prt = 48,                       /* Prt  */
  YYSYMBOL_Comp = 49,                      /* Comp  */
  YYSYMBOL_ModPath = 50,                   /* ModPath  */
  YYSYMBOL_RemPath = 51,                   /* RemPath  */
  YYSYMBOL_Argument = 52,                  /* Argument  */
  YYSYMBOL_ListArgument = 53,              /* ListArgument  */
  YYSYMBOL_Numassgn = 54,                  /* Numassgn  */
  YYSYMBOL_Strassgn = 55,                  /* Strassgn  */
  YYSYMBOL_SymAssgn = 56,                  /* SymAssgn  */
  YYSYMBOL_Numval = 57,                    /* Numval  */
  YYSYMBOL_Stringval = 58,                 /* Stringval  */
  YYSYMBOL_Symval = 59,                    /* Symval  */
  YYSYMBOL_ValidConfig = 60,               /* ValidConfig  */
  YYSYMBOL_Entry = 61,                     /* Entry  */
  YYSYMBOL_ListEntry = 62,                 /* ListEntry  */
  YYSYMBOL_KeyVal = 63,                    /* KeyVal  */
  YYSYMBOL_KeyName = 64                    /* KeyName  */
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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
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
#define YYLAST   164

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  29
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  131

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   283


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
      25,    26,    27,    28
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   276,   276,   277,   279,   281,   282,   283,   284,   285,
     286,   288,   289,   291,   293,   294,   295,   296,   298,   299,
     301,   302,   304,   305,   307,   308,   310,   311,   312,   313,
     315,   317,   319,   320,   322,   323,   325,   326,   328,   329,
     331,   332,   334,   335,   336,   337,   338,   340,   341,   342,
     343,   345,   346,   347,   349,   351,   353,   354,   356,   358,
     360,   362,   363,   365,   366,   367,   369,   370,   371,   373,
     374,   376,   377,   379,   380,   382,   383,   384,   386,   387
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
  "_SYMB_19", "_SYMB_20", "_SYMB_21", "_SYMB_22", "_STRING_", "_INTEGER_",
  "$accept", "Valide", "ValidSW", "Stm", "ListStm", "Subdef", "Subnet",
  "ListSubnet", "ExtPortIn", "ExtPortOut", "Tab", "DataFlow", "Larrow",
  "Rarrow", "TypeDef", "Buffsize", "Hermt", "Symvalu", "Proc", "Prt",
  "Comp", "ModPath", "RemPath", "Argument", "ListArgument", "Numassgn",
  "Strassgn", "SymAssgn", "Numval", "Stringval", "Symval", "ValidConfig",
  "Entry", "ListEntry", "KeyVal", "KeyName", YY_NULLPTR
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
     275,   276,   277,   278,   279,   280,   281,   282,   283
};
#endif

#define YYPACT_NINF (-47)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-46)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      60,   -47,   -47,    22,   -47,   124,   -47,   140,   140,   -47,
     -47,     5,    13,    16,   -47,    21,    35,   -47,    41,   -47,
      82,   -47,   128,    61,   -47,   -47,   -47,   -47,    32,   -47,
      32,     2,   -47,   -47,    95,   128,   -10,    32,    32,   -47,
     -47,   -47,   -47,   117,    37,    51,   -47,    32,   -47,    32,
     -47,    75,    58,   117,    67,    20,   -47,   -47,   -47,   -47,
     -47,   -47,    -8,   -47,   -47,   -47,   109,     5,     5,    61,
      61,    32,   -10,   -47,    75,    70,   -47,   -47,   -47,   -47,
     -47,    61,    61,   -47,   -47,   -47,    31,   -47,   -47,    93,
     -47,   -47,   117,    90,   -47,    61,   -47,   119,   -10,   -47,
     -10,    87,    87,   -47,   -47,    87,    87,   -47,   -47,    61,
      61,   117,   100,   -47,   104,   -47,   -47,   -47,   -47,    87,
      87,    61,    61,   -47,   -47,   -47,   -47,   -47,    44,    94,
     -47
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      11,    73,    73,     0,     3,     4,     2,    69,    70,     1,
      39,     0,     0,     0,    68,    66,     0,    67,     0,    10,
      46,     9,    56,    46,     6,     7,     8,    38,     0,    66,
       0,     0,    74,    71,    72,    56,     0,     0,     0,    18,
      12,    62,    61,     0,    42,    45,    48,     0,    56,     0,
      50,    37,    47,     0,     0,     0,    52,    78,    77,    76,
      75,    56,     0,    58,    59,    60,     0,    33,    33,    46,
      46,     0,     0,    54,    36,    49,    64,    65,    63,    57,
      55,    46,    46,    51,    53,    79,     0,    41,    13,     0,
      16,    17,     0,    46,    14,    46,    24,    38,    35,    32,
      35,     0,     0,    43,    44,     0,     0,    40,    19,    46,
      46,     0,     0,    34,     0,    28,    29,    26,    27,     0,
       0,    46,    46,    30,    31,    22,    21,    20,    24,    25,
      23
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -47,   -47,   -47,   -47,   -47,   -47,   -47,   -47,   -47,   -47,
      17,    63,   -46,   -43,    64,    36,    74,     3,   -27,   -22,
     106,   -14,   -47,   -47,   -24,   -47,   -47,   -47,   -31,   -47,
      -5,   -47,   -47,   153,   -47,   -47
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,    18,     5,    19,    89,    66,    90,    91,
      92,    20,    69,    70,    98,   112,    21,    22,    23,    43,
      48,    30,    50,    79,    51,    24,    25,    26,    44,    80,
      45,     6,    32,     7,    33,    34
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      27,    53,    31,    31,    87,    63,    27,    81,    49,    41,
      82,    62,    76,    77,    35,    10,    56,    52,    42,    78,
      57,    49,     9,    54,    74,    55,    14,    29,    36,    17,
      52,    37,    64,    65,    84,    96,    38,    86,    85,    95,
      39,   104,    73,   107,    75,    40,   109,   101,   102,   110,
      71,    76,    77,    14,    29,   -42,    17,    71,    78,   105,
     106,    97,    27,    27,    72,   121,   103,   113,   122,   113,
      99,    99,    56,   111,   115,   116,     1,     2,   117,   118,
      41,    83,    14,    29,    84,    17,    -5,   119,   120,    42,
     128,   128,   125,   126,   -15,    76,    77,   108,    11,   105,
     106,    41,    78,    14,    29,   -45,    17,    72,   123,    41,
      42,    14,    29,   124,    17,    88,   129,   129,    42,    10,
      11,    58,    59,    60,    67,    68,   -25,   -25,    41,    93,
      14,    29,   100,    17,    10,    11,   114,    42,   127,   130,
      94,    61,    28,    12,    13,    14,    15,    16,    17,    14,
      29,    46,    17,    47,    28,     8,     0,     0,     0,     0,
       0,    14,    29,     0,    17
};

static const yytype_int8 yycheck[] =
{
       5,    23,     7,     8,    12,    36,    11,    53,    22,    19,
      53,    35,    20,    21,    11,    10,    14,    22,    28,    27,
      18,    35,     0,    28,    48,    30,    21,    22,    15,    24,
      35,    15,    37,    38,    14,    66,    15,    61,    18,    66,
       5,    72,    47,    12,    49,     4,    92,    69,    70,    92,
      13,    20,    21,    21,    22,    11,    24,    13,    27,    81,
      82,    66,    67,    68,    13,   111,    71,    98,   111,   100,
      67,    68,    14,    95,   101,   102,    16,    17,   105,   106,
      19,    14,    21,    22,    14,    24,     4,   109,   110,    28,
     121,   122,   119,   120,     4,    20,    21,     4,    11,   121,
     122,    19,    27,    21,    22,    11,    24,    13,     8,    19,
      28,    21,    22,     9,    24,     6,   121,   122,    28,    10,
      11,    26,    27,    28,     7,     8,     7,     8,    19,    66,
      21,    22,    68,    24,    10,    11,   100,    28,   121,   122,
      66,    35,    14,    19,    20,    21,    22,    23,    24,    21,
      22,    23,    24,    25,    14,     2,    -1,    -1,    -1,    -1,
      -1,    21,    22,    -1,    24
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    16,    17,    30,    31,    33,    60,    62,    62,     0,
      10,    11,    19,    20,    21,    22,    23,    24,    32,    34,
      40,    45,    46,    47,    54,    55,    56,    59,    14,    22,
      50,    59,    61,    63,    64,    46,    15,    15,    15,     5,
       4,    19,    28,    48,    57,    59,    23,    25,    49,    50,
      51,    53,    59,    48,    59,    59,    14,    18,    26,    27,
      28,    49,    53,    57,    59,    59,    36,     7,     8,    41,
      42,    13,    13,    59,    53,    59,    20,    21,    27,    52,
      58,    41,    42,    14,    14,    18,    53,    12,     6,    35,
      37,    38,    39,    40,    45,    47,    57,    59,    43,    46,
      43,    48,    48,    59,    57,    48,    48,    12,     4,    41,
      42,    48,    44,    57,    44,    47,    47,    47,    47,    48,
      48,    41,    42,     8,     9,    47,    47,    39,    57,    59,
      39
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    29,    30,    30,    31,    32,    32,    32,    32,    32,
      32,    33,    33,    34,    35,    35,    35,    35,    36,    36,
      37,    37,    38,    38,    39,    39,    40,    40,    40,    40,
      41,    42,    43,    43,    44,    44,    45,    45,    46,    46,
      47,    47,    48,    48,    48,    48,    48,    49,    49,    49,
      49,    50,    50,    50,    51,    52,    53,    53,    54,    55,
      56,    57,    57,    58,    58,    58,    59,    59,    59,    60,
      60,    61,    61,    62,    62,    63,    63,    63,    64,    64
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     3,     4,     1,     1,     1,     1,     0,     3,
       4,     4,     4,     4,     1,     1,     5,     5,     5,     5,
       4,     4,     1,     0,     1,     0,     3,     2,     1,     1,
       5,     4,     1,     3,     3,     1,     0,     1,     1,     2,
       1,     3,     2,     3,     2,     1,     0,     2,     3,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     1,     1,     0,     2,     2,     2,     2,     2,     3
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
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
#line 276 "SW.y"
                     { (yyval.valide_) = make_CFGvalid((yyvsp[0].validconfig_)); YY_RESULT_Valide_= (yyval.valide_); }
#line 1606 "Parser.c"
    break;

  case 3: /* Valide: ValidSW  */
#line 277 "SW.y"
            { (yyval.valide_) = make_SWvalid((yyvsp[0].validsw_)); YY_RESULT_Valide_= (yyval.valide_); }
#line 1612 "Parser.c"
    break;

  case 4: /* ValidSW: ListStm  */
#line 279 "SW.y"
                  { (yyval.validsw_) = make_Valid(reverseListStm((yyvsp[0].liststm_))); YY_RESULT_ValidSW_= (yyval.validsw_); }
#line 1618 "Parser.c"
    break;

  case 5: /* Stm: DataFlow  */
#line 281 "SW.y"
               { (yyval.stm_) = make_Stmx((yyvsp[0].dataflow_));  }
#line 1624 "Parser.c"
    break;

  case 6: /* Stm: Numassgn  */
#line 282 "SW.y"
             { (yyval.stm_) = make_Stmn((yyvsp[0].numassgn_));  }
#line 1630 "Parser.c"
    break;

  case 7: /* Stm: Strassgn  */
#line 283 "SW.y"
             { (yyval.stm_) = make_Stms((yyvsp[0].strassgn_));  }
#line 1636 "Parser.c"
    break;

  case 8: /* Stm: SymAssgn  */
#line 284 "SW.y"
             { (yyval.stm_) = make_Stmb((yyvsp[0].symassgn_));  }
#line 1642 "Parser.c"
    break;

  case 9: /* Stm: Hermt  */
#line 285 "SW.y"
          { (yyval.stm_) = make_Stmh((yyvsp[0].hermt_));  }
#line 1648 "Parser.c"
    break;

  case 10: /* Stm: Subdef  */
#line 286 "SW.y"
           { (yyval.stm_) = make_Stmnet((yyvsp[0].subdef_));  }
#line 1654 "Parser.c"
    break;

  case 11: /* ListStm: %empty  */
#line 288 "SW.y"
                      { (yyval.liststm_) = 0;  }
#line 1660 "Parser.c"
    break;

  case 12: /* ListStm: ListStm Stm _SYMB_0  */
#line 289 "SW.y"
                        { (yyval.liststm_) = make_ListStm((yyvsp[-1].stm_), (yyvsp[-2].liststm_));  }
#line 1666 "Parser.c"
    break;

  case 13: /* Subdef: _SYMB_19 _SYMB_1 ListSubnet _SYMB_2  */
#line 291 "SW.y"
                                             { (yyval.subdef_) = make_Snet((yyvsp[-3].string_), reverseListSubnet((yyvsp[-1].listsubnet_)));  }
#line 1672 "Parser.c"
    break;

  case 14: /* Subnet: Hermt  */
#line 293 "SW.y"
               { (yyval.subnet_) = make_Sneth((yyvsp[0].hermt_));  }
#line 1678 "Parser.c"
    break;

  case 15: /* Subnet: DataFlow  */
#line 294 "SW.y"
             { (yyval.subnet_) = make_Snets((yyvsp[0].dataflow_));  }
#line 1684 "Parser.c"
    break;

  case 16: /* Subnet: ExtPortIn  */
#line 295 "SW.y"
              { (yyval.subnet_) = make_Snetin((yyvsp[0].extportin_));  }
#line 1690 "Parser.c"
    break;

  case 17: /* Subnet: ExtPortOut  */
#line 296 "SW.y"
               { (yyval.subnet_) = make_Snetout((yyvsp[0].extportout_));  }
#line 1696 "Parser.c"
    break;

  case 18: /* ListSubnet: %empty  */
#line 298 "SW.y"
                         { (yyval.listsubnet_) = 0;  }
#line 1702 "Parser.c"
    break;

  case 19: /* ListSubnet: ListSubnet Subnet _SYMB_0  */
#line 299 "SW.y"
                              { (yyval.listsubnet_) = make_ListSubnet((yyvsp[-1].subnet_), (yyvsp[-2].listsubnet_));  }
#line 1708 "Parser.c"
    break;

  case 20: /* ExtPortIn: Proc Prt Larrow Tab  */
#line 301 "SW.y"
                                { (yyval.extportin_) = make_Extin((yyvsp[-3].proc_), (yyvsp[-2].prt_), (yyvsp[-1].larrow_), (yyvsp[0].tab_));  }
#line 1714 "Parser.c"
    break;

  case 21: /* ExtPortIn: Tab Rarrow Prt Proc  */
#line 302 "SW.y"
                        { (yyval.extportin_) = make_ExtinR((yyvsp[-3].tab_), (yyvsp[-2].rarrow_), (yyvsp[-1].prt_), (yyvsp[0].proc_));  }
#line 1720 "Parser.c"
    break;

  case 22: /* ExtPortOut: Tab Larrow Prt Proc  */
#line 304 "SW.y"
                                 { (yyval.extportout_) = make_Extout((yyvsp[-3].tab_), (yyvsp[-2].larrow_), (yyvsp[-1].prt_), (yyvsp[0].proc_));  }
#line 1726 "Parser.c"
    break;

  case 23: /* ExtPortOut: Proc Prt Rarrow Tab  */
#line 305 "SW.y"
                        { (yyval.extportout_) = make_Extoutr((yyvsp[-3].proc_), (yyvsp[-2].prt_), (yyvsp[-1].rarrow_), (yyvsp[0].tab_));  }
#line 1732 "Parser.c"
    break;

  case 24: /* Tab: Numval  */
#line 307 "SW.y"
             { (yyval.tab_) = make_Tabn((yyvsp[0].numval_));  }
#line 1738 "Parser.c"
    break;

  case 25: /* Tab: Symval  */
#line 308 "SW.y"
           { (yyval.tab_) = make_Tabs((yyvsp[0].symval_));  }
#line 1744 "Parser.c"
    break;

  case 26: /* DataFlow: Proc Prt Larrow Prt Proc  */
#line 310 "SW.y"
                                    { (yyval.dataflow_) = make_Streamx((yyvsp[-4].proc_), (yyvsp[-3].prt_), (yyvsp[-2].larrow_), (yyvsp[-1].prt_), (yyvsp[0].proc_));  }
#line 1750 "Parser.c"
    break;

  case 27: /* DataFlow: Proc Prt Rarrow Prt Proc  */
#line 311 "SW.y"
                             { (yyval.dataflow_) = make_Streamrx((yyvsp[-4].proc_), (yyvsp[-3].prt_), (yyvsp[-2].rarrow_), (yyvsp[-1].prt_), (yyvsp[0].proc_));  }
#line 1756 "Parser.c"
    break;

  case 28: /* DataFlow: DataFlow Prt Larrow Prt Proc  */
#line 312 "SW.y"
                                 { (yyval.dataflow_) = make_Streamy((yyvsp[-4].dataflow_), (yyvsp[-3].prt_), (yyvsp[-2].larrow_), (yyvsp[-1].prt_), (yyvsp[0].proc_));  }
#line 1762 "Parser.c"
    break;

  case 29: /* DataFlow: DataFlow Prt Rarrow Prt Proc  */
#line 313 "SW.y"
                                 { (yyval.dataflow_) = make_Streamry((yyvsp[-4].dataflow_), (yyvsp[-3].prt_), (yyvsp[-2].rarrow_), (yyvsp[-1].prt_), (yyvsp[0].proc_));  }
#line 1768 "Parser.c"
    break;

  case 30: /* Larrow: _SYMB_3 TypeDef Buffsize _SYMB_4  */
#line 315 "SW.y"
                                          { (yyval.larrow_) = make_Arrowx((yyvsp[-2].typedef_), (yyvsp[-1].buffsize_));  }
#line 1774 "Parser.c"
    break;

  case 31: /* Rarrow: _SYMB_4 TypeDef Buffsize _SYMB_5  */
#line 317 "SW.y"
                                          { (yyval.rarrow_) = make_Arrowr((yyvsp[-2].typedef_), (yyvsp[-1].buffsize_));  }
#line 1780 "Parser.c"
    break;

  case 32: /* TypeDef: Symvalu  */
#line 319 "SW.y"
                  { (yyval.typedef_) = make_Typedefa((yyvsp[0].symvalu_));  }
#line 1786 "Parser.c"
    break;

  case 33: /* TypeDef: %empty  */
#line 320 "SW.y"
                { (yyval.typedef_) = make_Typedefnull();  }
#line 1792 "Parser.c"
    break;

  case 34: /* Buffsize: Numval  */
#line 322 "SW.y"
                  { (yyval.buffsize_) = make_Bufszi((yyvsp[0].numval_));  }
#line 1798 "Parser.c"
    break;

  case 35: /* Buffsize: %empty  */
#line 323 "SW.y"
                { (yyval.buffsize_) = make_Bufsze();  }
#line 1804 "Parser.c"
    break;

  case 36: /* Hermt: Symvalu Comp ListArgument  */
#line 325 "SW.y"
                                  { (yyval.hermt_) = make_Hermtx((yyvsp[-2].symvalu_), (yyvsp[-1].comp_), reverseListArgument((yyvsp[0].listargument_)));  }
#line 1810 "Parser.c"
    break;

  case 37: /* Hermt: Symvalu ListArgument  */
#line 326 "SW.y"
                         { (yyval.hermt_) = make_Hermty((yyvsp[-1].symvalu_), reverseListArgument((yyvsp[0].listargument_)));  }
#line 1816 "Parser.c"
    break;

  case 38: /* Symvalu: Symval  */
#line 328 "SW.y"
                 { (yyval.symvalu_) = make_Symvaluv((yyvsp[0].symval_));  }
#line 1822 "Parser.c"
    break;

  case 39: /* Symvalu: _SYMB_6  */
#line 329 "SW.y"
            { (yyval.symvalu_) = make_Symvaluu();  }
#line 1828 "Parser.c"
    break;

  case 40: /* Proc: _SYMB_7 Symvalu Comp ListArgument _SYMB_8  */
#line 331 "SW.y"
                                                 { (yyval.proc_) = make_Processx((yyvsp[-3].symvalu_), (yyvsp[-2].comp_), reverseListArgument((yyvsp[-1].listargument_)));  }
#line 1834 "Parser.c"
    break;

  case 41: /* Proc: _SYMB_7 Symvalu ListArgument _SYMB_8  */
#line 332 "SW.y"
                                         { (yyval.proc_) = make_Processy((yyvsp[-2].symvalu_), reverseListArgument((yyvsp[-1].listargument_)));  }
#line 1840 "Parser.c"
    break;

  case 42: /* Prt: Numval  */
#line 334 "SW.y"
             { (yyval.prt_) = make_Portx((yyvsp[0].numval_));  }
#line 1846 "Parser.c"
    break;

  case 43: /* Prt: Numval _SYMB_9 Symval  */
#line 335 "SW.y"
                          { (yyval.prt_) = make_Portni((yyvsp[-2].numval_), (yyvsp[0].symval_));  }
#line 1852 "Parser.c"
    break;

  case 44: /* Prt: Symval _SYMB_9 Numval  */
#line 336 "SW.y"
                          { (yyval.prt_) = make_Portin((yyvsp[-2].symval_), (yyvsp[0].numval_));  }
#line 1858 "Parser.c"
    break;

  case 45: /* Prt: Symval  */
#line 337 "SW.y"
           { (yyval.prt_) = make_Portn((yyvsp[0].symval_));  }
#line 1864 "Parser.c"
    break;

  case 46: /* Prt: %empty  */
#line 338 "SW.y"
                { (yyval.prt_) = make_Porte();  }
#line 1870 "Parser.c"
    break;

  case 47: /* Comp: Symval  */
#line 340 "SW.y"
              { (yyval.comp_) = make_Compx((yyvsp[0].symval_));  }
#line 1876 "Parser.c"
    break;

  case 48: /* Comp: _SYMB_19  */
#line 341 "SW.y"
             { (yyval.comp_) = make_Compn((yyvsp[0].string_));  }
#line 1882 "Parser.c"
    break;

  case 49: /* Comp: ModPath Symval  */
#line 342 "SW.y"
                   { (yyval.comp_) = make_Compz((yyvsp[-1].modpath_), (yyvsp[0].symval_));  }
#line 1888 "Parser.c"
    break;

  case 50: /* Comp: RemPath  */
#line 343 "SW.y"
            { (yyval.comp_) = make_Compa((yyvsp[0].rempath_));  }
#line 1894 "Parser.c"
    break;

  case 51: /* ModPath: _SYMB_10 Symval _SYMB_10  */
#line 345 "SW.y"
                                   { (yyval.modpath_) = make_Modpa((yyvsp[-1].symval_));  }
#line 1900 "Parser.c"
    break;

  case 52: /* ModPath: Symval _SYMB_10  */
#line 346 "SW.y"
                    { (yyval.modpath_) = make_Modpx((yyvsp[-1].symval_));  }
#line 1906 "Parser.c"
    break;

  case 53: /* ModPath: ModPath Symval _SYMB_10  */
#line 347 "SW.y"
                            { (yyval.modpath_) = make_Modpy((yyvsp[-2].modpath_), (yyvsp[-1].symval_));  }
#line 1912 "Parser.c"
    break;

  case 54: /* RemPath: _SYMB_21 Symval  */
#line 349 "SW.y"
                          { (yyval.rempath_) = make_RemPatha((yyvsp[-1].string_), (yyvsp[0].symval_));  }
#line 1918 "Parser.c"
    break;

  case 55: /* Argument: Stringval  */
#line 351 "SW.y"
                     { (yyval.argument_) = make_Argumentx((yyvsp[0].stringval_));  }
#line 1924 "Parser.c"
    break;

  case 56: /* ListArgument: %empty  */
#line 353 "SW.y"
                           { (yyval.listargument_) = 0;  }
#line 1930 "Parser.c"
    break;

  case 57: /* ListArgument: ListArgument Argument  */
#line 354 "SW.y"
                          { (yyval.listargument_) = make_ListArgument((yyvsp[0].argument_), (yyvsp[-1].listargument_));  }
#line 1936 "Parser.c"
    break;

  case 58: /* Numassgn: _SYMB_15 _SYMB_11 Numval  */
#line 356 "SW.y"
                                    { (yyval.numassgn_) = make_NumAssgnv((yyvsp[-2].string_), (yyvsp[0].numval_));  }
#line 1942 "Parser.c"
    break;

  case 59: /* Strassgn: _SYMB_16 _SYMB_11 Symval  */
#line 358 "SW.y"
                                    { (yyval.strassgn_) = make_StrAssgnv((yyvsp[-2].string_), (yyvsp[0].symval_));  }
#line 1948 "Parser.c"
    break;

  case 60: /* SymAssgn: _SYMB_18 _SYMB_11 Symval  */
#line 360 "SW.y"
                                    { (yyval.symassgn_) = make_SymAssgni((yyvsp[-2].string_), (yyvsp[0].symval_));  }
#line 1954 "Parser.c"
    break;

  case 61: /* Numval: _INTEGER_  */
#line 362 "SW.y"
                   { (yyval.numval_) = make_NumVali((yyvsp[0].int_));  }
#line 1960 "Parser.c"
    break;

  case 62: /* Numval: _SYMB_15  */
#line 363 "SW.y"
             { (yyval.numval_) = make_NumValv((yyvsp[0].string_));  }
#line 1966 "Parser.c"
    break;

  case 63: /* Stringval: _STRING_  */
#line 365 "SW.y"
                     { (yyval.stringval_) = make_StringVals((yyvsp[0].string_));  }
#line 1972 "Parser.c"
    break;

  case 64: /* Stringval: _SYMB_16  */
#line 366 "SW.y"
             { (yyval.stringval_) = make_StringValv((yyvsp[0].string_));  }
#line 1978 "Parser.c"
    break;

  case 65: /* Stringval: _SYMB_17  */
#line 367 "SW.y"
             { (yyval.stringval_) = make_StringVale((yyvsp[0].string_));  }
#line 1984 "Parser.c"
    break;

  case 66: /* Symval: _SYMB_18  */
#line 369 "SW.y"
                  { (yyval.symval_) = make_Symvalv((yyvsp[0].string_));  }
#line 1990 "Parser.c"
    break;

  case 67: /* Symval: _SYMB_20  */
#line 370 "SW.y"
             { (yyval.symval_) = make_Symvali((yyvsp[0].string_));  }
#line 1996 "Parser.c"
    break;

  case 68: /* Symval: _SYMB_17  */
#line 371 "SW.y"
             { (yyval.symval_) = make_SymVale((yyvsp[0].string_));  }
#line 2002 "Parser.c"
    break;

  case 69: /* ValidConfig: _SYMB_12 ListEntry  */
#line 373 "SW.y"
                                 { (yyval.validconfig_) = make_Validcfg(reverseListEntry((yyvsp[0].listentry_))); YY_RESULT_ValidConfig_= (yyval.validconfig_); }
#line 2008 "Parser.c"
    break;

  case 70: /* ValidConfig: _SYMB_13 ListEntry  */
#line 374 "SW.y"
                       { (yyval.validconfig_) = make_Validcfgd(reverseListEntry((yyvsp[0].listentry_))); YY_RESULT_ValidConfig_= (yyval.validconfig_); }
#line 2014 "Parser.c"
    break;

  case 71: /* Entry: KeyVal  */
#line 376 "SW.y"
               { (yyval.entry_) = make_CfgEntrya((yyvsp[0].keyval_));  }
#line 2020 "Parser.c"
    break;

  case 72: /* Entry: KeyName  */
#line 377 "SW.y"
            { (yyval.entry_) = make_CfgEntryb((yyvsp[0].keyname_));  }
#line 2026 "Parser.c"
    break;

  case 73: /* ListEntry: %empty  */
#line 379 "SW.y"
                        { (yyval.listentry_) = 0;  }
#line 2032 "Parser.c"
    break;

  case 74: /* ListEntry: ListEntry Entry  */
#line 380 "SW.y"
                    { (yyval.listentry_) = make_ListEntry((yyvsp[0].entry_), (yyvsp[-1].listentry_));  }
#line 2038 "Parser.c"
    break;

  case 75: /* KeyVal: KeyName _INTEGER_  */
#line 382 "SW.y"
                           { (yyval.keyval_) = make_CfgKeyvalint((yyvsp[-1].keyname_), (yyvsp[0].int_));  }
#line 2044 "Parser.c"
    break;

  case 76: /* KeyVal: KeyName _STRING_  */
#line 383 "SW.y"
                     { (yyval.keyval_) = make_CfgKeyvalstr((yyvsp[-1].keyname_), (yyvsp[0].string_));  }
#line 2050 "Parser.c"
    break;

  case 77: /* KeyVal: KeyName _SYMB_22  */
#line 384 "SW.y"
                     { (yyval.keyval_) = make_CfgKeyDate((yyvsp[-1].keyname_), (yyvsp[0].string_));  }
#line 2056 "Parser.c"
    break;

  case 78: /* KeyName: Symval _SYMB_14  */
#line 386 "SW.y"
                          { (yyval.keyname_) = make_KeynameS((yyvsp[-1].symval_));  }
#line 2062 "Parser.c"
    break;

  case 79: /* KeyName: ModPath Symval _SYMB_14  */
#line 387 "SW.y"
                            { (yyval.keyname_) = make_KeynameM((yyvsp[-2].modpath_), (yyvsp[-1].symval_));  }
#line 2068 "Parser.c"
    break;


#line 2072 "Parser.c"

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

#line 390 "SW.y"

void yyerror(const char *str)
{
  extern char *SWtext;
  fprintf(stderr,"error: %d,%d: %s at %s\n",
  SWlloc.first_line, SWlloc.first_column, str, SWtext);
}

