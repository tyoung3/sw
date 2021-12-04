/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1

/* Substitute the variable and function names.  */
#define yyparse         sw_parse
#define yylex           sw_lex
#define yyerror         sw_error
#define yylval          sw_lval
#define yychar          sw_char
#define yydebug         sw_debug
#define yynerrs         sw_nerrs
#define yylloc          sw_lloc

/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 20 "SW.y"

/* Begin C preamble code */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Absyn.h"

#define YYMAXDEPTH 10000000

/* The type yyscan_t is defined by flex, but we need it in the parser already. */
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE sw__scan_string(const char *str, yyscan_t scanner);
extern void sw__delete_buffer(YY_BUFFER_STATE buf, yyscan_t scanner);

extern void sw_lex_destroy(yyscan_t scanner);
extern char* sw_get_text(yyscan_t scanner);

extern yyscan_t sw__initialize_lexer(FILE * inp);

/* List reversal functions. */
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

/* End C preamble code */


/* Line 189 of yacc.c  */
#line 176 "Parser.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     _ERROR_ = 258,
     _LPAREN = 259,
     _RPAREN = 260,
     _COMMA = 261,
     _MINUS = 262,
     _SYMB_13 = 263,
     _DOT = 264,
     _SLASH = 265,
     _COLON = 266,
     _SEMI = 267,
     _LT = 268,
     _EQ = 269,
     _GT = 270,
     _KW_INCLUDE = 271,
     _KW_PREFIX = 272,
     _SYMB_12 = 273,
     _UNDERSCORE = 274,
     _KW_include = 275,
     _KW_prefix = 276,
     _LBRACE = 277,
     _RBRACE = 278,
     T_Date = 279,
     T_Envar = 280,
     T_Id = 281,
     T_Numvar = 282,
     T_Stringvar = 283,
     T_SubId = 284,
     T_Symvar = 285,
     T_ValidImport = 286,
     _STRING_ = 287,
     _INTEGER_ = 288
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 116 "SW.y"

  int    _int;
  char   _char;
  double _double;
  char*  _string;
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



/* Line 214 of yacc.c  */
#line 293 "Parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */

/* Line 264 of yacc.c  */
#line 162 "SW.y"

void yyerror(YYLTYPE *loc, yyscan_t scanner, YYSTYPE *result, const char *msg)
{
  fprintf(stderr, "error: %d,%d: %s at %s\n",
    loc->first_line, loc->first_column, msg, sw_get_text(scanner));
}

int yyparse(yyscan_t scanner, YYSTYPE *result);

extern int yylex(YYSTYPE *lvalp, YYLTYPE *llocp, yyscan_t scanner);


/* Line 264 of yacc.c  */
#line 331 "Parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   178

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNRULES -- Number of states.  */
#define YYNSTATES  149

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    12,    15,    17,    19,
      21,    23,    25,    27,    28,    32,    37,    39,    41,    43,
      45,    46,    50,    55,    60,    65,    70,    72,    74,    80,
      86,    92,    98,   103,   108,   110,   111,   113,   114,   118,
     121,   123,   125,   131,   136,   138,   142,   146,   148,   149,
     151,   153,   156,   158,   162,   165,   169,   172,   176,   178,
     179,   182,   186,   190,   194,   196,   198,   200,   202,   204,
     206,   208,   210,   212,   214,   216,   218,   221,   227,   229,
     231,   232,   236,   238,   240,   241,   244,   247,   250,   253,
     256
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      35,     0,    -1,    67,    -1,    36,    -1,    38,    -1,    66,
      63,    -1,    65,    63,    -1,    45,    -1,    59,    -1,    60,
      -1,    61,    -1,    50,    -1,    39,    -1,    -1,    38,    37,
      12,    -1,    29,    22,    41,    23,    -1,    50,    -1,    45,
      -1,    42,    -1,    43,    -1,    -1,    41,    40,    12,    -1,
      52,    53,    46,    44,    -1,    44,    47,    53,    52,    -1,
      44,    46,    53,    52,    -1,    52,    53,    47,    44,    -1,
      62,    -1,    64,    -1,    52,    53,    46,    53,    52,    -1,
      52,    53,    47,    53,    52,    -1,    45,    53,    46,    53,
      52,    -1,    45,    53,    47,    53,    52,    -1,    13,    48,
      49,     7,    -1,     7,    48,    49,    15,    -1,    51,    -1,
      -1,    62,    -1,    -1,    51,    54,    58,    -1,    51,    58,
      -1,    64,    -1,    19,    -1,     4,    51,    54,    58,     5,
      -1,     4,    51,    58,     5,    -1,    62,    -1,    62,     9,
      64,    -1,    64,     9,    62,    -1,    64,    -1,    -1,    64,
      -1,    29,    -1,    55,    64,    -1,    56,    -1,    10,    64,
      10,    -1,    64,    10,    -1,    55,    64,    10,    -1,    28,
      10,    -1,    31,     9,    64,    -1,    63,    -1,    -1,    58,
      57,    -1,    27,    14,    62,    -1,    28,    14,    63,    -1,
      30,    14,    64,    -1,    33,    -1,    27,    -1,    32,    -1,
      28,    -1,    25,    -1,    30,    -1,    26,    -1,    25,    -1,
      20,    -1,    16,    -1,    17,    -1,    21,    -1,    18,    71,
      -1,     8,    18,    22,    69,    23,    -1,    72,    -1,    73,
      -1,    -1,    69,    68,     6,    -1,    72,    -1,    73,    -1,
      -1,    71,    70,    -1,    73,    33,    -1,    73,    32,    -1,
      73,    24,    -1,    64,    11,    -1,    55,    64,    11,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   250,   250,   251,   253,   255,   256,   257,   258,   259,
     260,   261,   262,   264,   265,   267,   269,   270,   271,   272,
     274,   275,   277,   278,   280,   281,   283,   284,   286,   287,
     288,   289,   291,   293,   295,   296,   298,   299,   301,   302,
     304,   305,   307,   308,   310,   311,   312,   313,   314,   316,
     317,   318,   319,   321,   322,   323,   324,   326,   328,   330,
     331,   333,   335,   337,   339,   340,   342,   343,   344,   346,
     347,   348,   350,   351,   353,   354,   356,   357,   359,   360,
     362,   363,   365,   366,   368,   369,   371,   372,   373,   375,
     376
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "_ERROR_", "_LPAREN", "_RPAREN",
  "_COMMA", "_MINUS", "_SYMB_13", "_DOT", "_SLASH", "_COLON", "_SEMI",
  "_LT", "_EQ", "_GT", "_KW_INCLUDE", "_KW_PREFIX", "_SYMB_12",
  "_UNDERSCORE", "_KW_include", "_KW_prefix", "_LBRACE", "_RBRACE",
  "T_Date", "T_Envar", "T_Id", "T_Numvar", "T_Stringvar", "T_SubId",
  "T_Symvar", "T_ValidImport", "_STRING_", "_INTEGER_", "$accept",
  "Valide", "ValidSW", "Stm", "ListStm", "Subdef", "Subnet", "ListSubnet",
  "ExtPortIn", "ExtPortOut", "Tab", "DataFlow", "Larrow", "Rarrow",
  "TypeDef", "Buffsize", "Hermt", "Symvalu", "Proc", "Prt", "Comp",
  "ModPath", "RemPath", "Argument", "ListArgument", "Numassgn", "Strassgn",
  "SymAssgn", "Numval", "Stringval", "Symval", "Include", "Prefix",
  "ValidConfig", "Centry", "ListCentry", "Entry", "ListEntry", "KeyVal",
  "KeyName", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
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

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
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

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      13,     0,    84,     0,     3,     4,     2,     0,    76,     1,
       0,    73,    74,    41,    72,    75,    71,    70,     0,     0,
       0,    69,     0,    12,    48,    11,    59,    48,     8,     9,
      10,    40,     0,     0,    80,     0,     0,    69,     0,     0,
      85,    82,    83,    59,     0,     0,    20,     0,    14,    65,
      64,     0,    44,    47,    50,     0,    59,     0,    52,    39,
      49,     0,    68,    67,    66,     6,     5,     0,     0,    56,
       0,    54,    89,    88,    87,    86,    59,     0,    61,    62,
       0,    63,    35,    35,    48,    48,     0,     0,     0,    38,
      51,    60,    58,    48,    48,    77,     0,    78,    79,    53,
      55,    90,     0,    43,    15,     0,    18,    19,     0,    48,
      16,    48,    26,    40,    37,    34,    37,     0,     0,    45,
      46,    57,     0,     0,    81,    42,    21,    48,    48,     0,
       0,    36,     0,    30,    31,    28,    29,     0,     0,    48,
      48,    33,    32,    24,    23,    22,    26,    27,    25
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    22,     5,    23,   105,    80,   106,   107,
     108,    24,    84,    85,   114,   130,    25,    26,    27,    51,
      56,    38,    58,    91,    59,    28,    29,    30,    52,    92,
      53,    32,    33,     6,    96,    67,    40,     8,    41,    42
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -73
static const yytype_int16 yypact[] =
{
       8,     2,   -73,    13,   -73,    90,   -73,     5,   131,   -73,
     139,   -73,   -73,   -73,   -73,   -73,   -73,   -73,    41,    59,
      31,    72,    77,   -73,    -2,   -73,    98,   141,   -73,   -73,
     -73,   -73,   -10,   -10,   -73,   147,    95,   -73,   147,     1,
     -73,   -73,    39,    98,    21,   -10,   -73,   147,   -73,   -73,
     -73,    28,   103,   112,   -73,   121,   -73,   147,   -73,   -10,
     123,    28,   -73,   -73,   -73,   -73,   -73,   122,   134,   -73,
      86,   -73,   -73,   -73,   -73,   -73,   -73,     4,   -73,   -73,
      65,   -73,   139,   139,   141,   141,   147,    21,   147,   -10,
     143,   -73,   -73,   141,   141,   -73,   116,   -73,    39,   -73,
     -73,   -73,    32,   -73,   -73,   137,   -73,   -73,    28,   113,
     -73,   141,   -73,    80,    21,   -73,    21,   150,   150,   -73,
     -73,   -73,   150,   150,   -73,   -73,   -73,   141,   141,    28,
     136,   -73,   148,   -73,   -73,   -73,   -73,   150,   150,   141,
     141,   -73,   -73,   -73,   -73,   -73,   127,   133,   -73
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,
     -36,    82,   -59,   -47,    87,    44,    83,    -3,   -72,   -26,
     132,    -9,   -73,   -73,   -37,   -73,   -73,   -73,   -40,    11,
      -5,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   109,   111
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -48
static const yytype_int16 yytable[] =
{
      31,    61,    93,    39,    78,    31,    77,    43,   111,   103,
      -7,    71,    72,     9,    94,    62,     1,    57,    63,    89,
       7,    60,    64,    16,    17,    49,     2,    34,    37,    62,
      68,    50,    63,    70,    57,    82,    64,   125,    60,   102,
     112,    83,    81,    65,    66,   133,   134,   120,    49,   127,
     135,   136,    90,    46,    50,    44,    79,    62,   117,   118,
      63,   128,    39,    73,    64,   143,   144,   122,   123,    10,
     139,    74,    75,    45,   131,   113,   131,    31,    31,   115,
     115,   119,   140,   121,    13,   129,    47,   -27,   104,    48,
      16,    17,    49,   -27,    10,    37,   100,   101,    50,   146,
     146,   137,   138,   145,   148,    69,    11,    12,    35,    13,
      14,    15,    86,   122,   123,    16,    17,    18,    19,    20,
      21,    87,   124,    16,    17,   -17,    36,    54,    37,    55,
      88,   -44,    35,    71,   147,   147,    86,   -47,    16,    17,
      49,    35,    87,    37,    99,    95,    50,    16,    17,   126,
      36,   141,    37,   100,    10,   142,    16,    17,    13,    36,
     132,    37,   109,   110,    16,    17,    16,    17,    49,    37,
     116,    37,    16,    17,    50,    76,    97,    37,    98
};

static const yytype_uint8 yycheck[] =
{
       5,    27,    61,     8,    44,    10,    43,    10,    80,     5,
      12,    10,    11,     0,    61,    25,     8,    26,    28,    56,
      18,    26,    32,    25,    26,    27,    18,    22,    30,    25,
      35,    33,    28,    38,    43,     7,    32,     5,    43,    76,
      80,    13,    47,    32,    33,   117,   118,    87,    27,   108,
     122,   123,    57,    22,    33,    14,    45,    25,    84,    85,
      28,   108,    67,    24,    32,   137,   138,    93,    94,     4,
     129,    32,    33,    14,   114,    80,   116,    82,    83,    82,
      83,    86,   129,    88,    19,   111,    14,     7,    23,    12,
      25,    26,    27,    13,     4,    30,    10,    11,    33,   139,
     140,   127,   128,   139,   140,    10,    16,    17,    10,    19,
      20,    21,     9,   139,   140,    25,    26,    27,    28,    29,
      30,     9,     6,    25,    26,    12,    28,    29,    30,    31,
       9,     4,    10,    10,   139,   140,     9,     4,    25,    26,
      27,    10,     9,    30,    10,    23,    33,    25,    26,    12,
      28,    15,    30,    10,     4,     7,    25,    26,    19,    28,
     116,    30,    80,    80,    25,    26,    25,    26,    27,    30,
      83,    30,    25,    26,    33,    43,    67,    30,    67
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    18,    35,    36,    38,    67,    18,    71,     0,
       4,    16,    17,    19,    20,    21,    25,    26,    27,    28,
      29,    30,    37,    39,    45,    50,    51,    52,    59,    60,
      61,    64,    65,    66,    22,    10,    28,    30,    55,    64,
      70,    72,    73,    51,    14,    14,    22,    14,    12,    27,
      33,    53,    62,    64,    29,    31,    54,    55,    56,    58,
      64,    53,    25,    28,    32,    63,    63,    69,    64,    10,
      64,    10,    11,    24,    32,    33,    54,    58,    62,    63,
      41,    64,     7,    13,    46,    47,     9,     9,     9,    58,
      64,    57,    63,    46,    47,    23,    68,    72,    73,    10,
      10,    11,    58,     5,    23,    40,    42,    43,    44,    45,
      50,    52,    62,    64,    48,    51,    48,    53,    53,    64,
      62,    64,    53,    53,     6,     5,    12,    46,    47,    53,
      49,    62,    49,    52,    52,    52,    52,    53,    53,    46,
      47,    15,     7,    52,    52,    44,    62,    64,    44
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (&yylloc, scanner, result, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc, scanner)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location, scanner, result); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, YYSTYPE *result)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, result)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    yyscan_t scanner;
    YYSTYPE *result;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (result);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, YYSTYPE *result)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, result)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    yyscan_t scanner;
    YYSTYPE *result;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, result);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, yyscan_t scanner, YYSTYPE *result)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, scanner, result)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    yyscan_t scanner;
    YYSTYPE *result;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , scanner, result);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, scanner, result); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, yyscan_t scanner, YYSTYPE *result)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, scanner, result)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    yyscan_t scanner;
    YYSTYPE *result;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (result);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (yyscan_t scanner, YYSTYPE *result);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (yyscan_t scanner, YYSTYPE *result)
#else
int
yyparse (scanner, result)
    yyscan_t scanner;
    YYSTYPE *result;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
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
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1464 of yacc.c  */
#line 250 "SW.y"
    { (yyval.valide_) = make_CFGvalid((yyvsp[(1) - (1)].validconfig_)); result->valide_ = (yyval.valide_); ;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 251 "SW.y"
    { (yyval.valide_) = make_SWvalid((yyvsp[(1) - (1)].validsw_)); result->valide_ = (yyval.valide_); ;}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 253 "SW.y"
    { (yyval.validsw_) = make_Valid(reverseListStm((yyvsp[(1) - (1)].liststm_))); result->validsw_ = (yyval.validsw_); ;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 255 "SW.y"
    { (yyval.stm_) = make_StmPrefix((yyvsp[(1) - (2)].prefix_), (yyvsp[(2) - (2)].stringval_)); ;}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 256 "SW.y"
    { (yyval.stm_) = make_Stminc((yyvsp[(1) - (2)].include_), (yyvsp[(2) - (2)].stringval_)); ;}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 257 "SW.y"
    { (yyval.stm_) = make_Stmx((yyvsp[(1) - (1)].dataflow_)); ;}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 258 "SW.y"
    { (yyval.stm_) = make_Stmn((yyvsp[(1) - (1)].numassgn_)); ;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 259 "SW.y"
    { (yyval.stm_) = make_Stms((yyvsp[(1) - (1)].strassgn_)); ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 260 "SW.y"
    { (yyval.stm_) = make_Stmb((yyvsp[(1) - (1)].symassgn_)); ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 261 "SW.y"
    { (yyval.stm_) = make_Stmh((yyvsp[(1) - (1)].hermt_)); ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 262 "SW.y"
    { (yyval.stm_) = make_Stmnet((yyvsp[(1) - (1)].subdef_)); ;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 264 "SW.y"
    { (yyval.liststm_) = 0; ;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 265 "SW.y"
    { (yyval.liststm_) = make_ListStm((yyvsp[(2) - (3)].stm_), (yyvsp[(1) - (3)].liststm_)); ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 267 "SW.y"
    { (yyval.subdef_) = make_Snet((yyvsp[(1) - (4)]._string), reverseListSubnet((yyvsp[(3) - (4)].listsubnet_))); ;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 269 "SW.y"
    { (yyval.subnet_) = make_Sneth((yyvsp[(1) - (1)].hermt_)); ;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 270 "SW.y"
    { (yyval.subnet_) = make_Snets((yyvsp[(1) - (1)].dataflow_)); ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 271 "SW.y"
    { (yyval.subnet_) = make_Snetin((yyvsp[(1) - (1)].extportin_)); ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 272 "SW.y"
    { (yyval.subnet_) = make_Snetout((yyvsp[(1) - (1)].extportout_)); ;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 274 "SW.y"
    { (yyval.listsubnet_) = 0; ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 275 "SW.y"
    { (yyval.listsubnet_) = make_ListSubnet((yyvsp[(2) - (3)].subnet_), (yyvsp[(1) - (3)].listsubnet_)); ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 277 "SW.y"
    { (yyval.extportin_) = make_Extin((yyvsp[(1) - (4)].proc_), (yyvsp[(2) - (4)].prt_), (yyvsp[(3) - (4)].larrow_), (yyvsp[(4) - (4)].tab_)); ;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 278 "SW.y"
    { (yyval.extportin_) = make_ExtinR((yyvsp[(1) - (4)].tab_), (yyvsp[(2) - (4)].rarrow_), (yyvsp[(3) - (4)].prt_), (yyvsp[(4) - (4)].proc_)); ;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 280 "SW.y"
    { (yyval.extportout_) = make_Extout((yyvsp[(1) - (4)].tab_), (yyvsp[(2) - (4)].larrow_), (yyvsp[(3) - (4)].prt_), (yyvsp[(4) - (4)].proc_)); ;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 281 "SW.y"
    { (yyval.extportout_) = make_Extoutr((yyvsp[(1) - (4)].proc_), (yyvsp[(2) - (4)].prt_), (yyvsp[(3) - (4)].rarrow_), (yyvsp[(4) - (4)].tab_)); ;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 283 "SW.y"
    { (yyval.tab_) = make_Tabn((yyvsp[(1) - (1)].numval_)); ;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 284 "SW.y"
    { (yyval.tab_) = make_Tabs((yyvsp[(1) - (1)].symval_)); ;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 286 "SW.y"
    { (yyval.dataflow_) = make_Streamx((yyvsp[(1) - (5)].proc_), (yyvsp[(2) - (5)].prt_), (yyvsp[(3) - (5)].larrow_), (yyvsp[(4) - (5)].prt_), (yyvsp[(5) - (5)].proc_)); ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 287 "SW.y"
    { (yyval.dataflow_) = make_Streamrx((yyvsp[(1) - (5)].proc_), (yyvsp[(2) - (5)].prt_), (yyvsp[(3) - (5)].rarrow_), (yyvsp[(4) - (5)].prt_), (yyvsp[(5) - (5)].proc_)); ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 288 "SW.y"
    { (yyval.dataflow_) = make_Streamy((yyvsp[(1) - (5)].dataflow_), (yyvsp[(2) - (5)].prt_), (yyvsp[(3) - (5)].larrow_), (yyvsp[(4) - (5)].prt_), (yyvsp[(5) - (5)].proc_)); ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 289 "SW.y"
    { (yyval.dataflow_) = make_Streamry((yyvsp[(1) - (5)].dataflow_), (yyvsp[(2) - (5)].prt_), (yyvsp[(3) - (5)].rarrow_), (yyvsp[(4) - (5)].prt_), (yyvsp[(5) - (5)].proc_)); ;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 291 "SW.y"
    { (yyval.larrow_) = make_Arrowx((yyvsp[(2) - (4)].typedef_), (yyvsp[(3) - (4)].buffsize_)); ;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 293 "SW.y"
    { (yyval.rarrow_) = make_Arrowr((yyvsp[(2) - (4)].typedef_), (yyvsp[(3) - (4)].buffsize_)); ;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 295 "SW.y"
    { (yyval.typedef_) = make_Typedefa((yyvsp[(1) - (1)].symvalu_)); ;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 296 "SW.y"
    { (yyval.typedef_) = make_Typedefnull(); ;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 298 "SW.y"
    { (yyval.buffsize_) = make_Bufszi((yyvsp[(1) - (1)].numval_)); ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 299 "SW.y"
    { (yyval.buffsize_) = make_Bufsze(); ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 301 "SW.y"
    { (yyval.hermt_) = make_Hermtx((yyvsp[(1) - (3)].symvalu_), (yyvsp[(2) - (3)].comp_), reverseListArgument((yyvsp[(3) - (3)].listargument_))); ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 302 "SW.y"
    { (yyval.hermt_) = make_Hermty((yyvsp[(1) - (2)].symvalu_), reverseListArgument((yyvsp[(2) - (2)].listargument_))); ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 304 "SW.y"
    { (yyval.symvalu_) = make_Symvaluv((yyvsp[(1) - (1)].symval_)); ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 305 "SW.y"
    { (yyval.symvalu_) = make_Symvaluu(); ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 307 "SW.y"
    { (yyval.proc_) = make_Processx((yyvsp[(2) - (5)].symvalu_), (yyvsp[(3) - (5)].comp_), reverseListArgument((yyvsp[(4) - (5)].listargument_))); ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 308 "SW.y"
    { (yyval.proc_) = make_Processy((yyvsp[(2) - (4)].symvalu_), reverseListArgument((yyvsp[(3) - (4)].listargument_))); ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 310 "SW.y"
    { (yyval.prt_) = make_Portx((yyvsp[(1) - (1)].numval_)); ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 311 "SW.y"
    { (yyval.prt_) = make_Portni((yyvsp[(1) - (3)].numval_), (yyvsp[(3) - (3)].symval_)); ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 312 "SW.y"
    { (yyval.prt_) = make_Portin((yyvsp[(1) - (3)].symval_), (yyvsp[(3) - (3)].numval_)); ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 313 "SW.y"
    { (yyval.prt_) = make_Portn((yyvsp[(1) - (1)].symval_)); ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 314 "SW.y"
    { (yyval.prt_) = make_Porte(); ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 316 "SW.y"
    { (yyval.comp_) = make_Compx((yyvsp[(1) - (1)].symval_)); ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 317 "SW.y"
    { (yyval.comp_) = make_Compn((yyvsp[(1) - (1)]._string)); ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 318 "SW.y"
    { (yyval.comp_) = make_Compz((yyvsp[(1) - (2)].modpath_), (yyvsp[(2) - (2)].symval_)); ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 319 "SW.y"
    { (yyval.comp_) = make_Compa((yyvsp[(1) - (1)].rempath_)); ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 321 "SW.y"
    { (yyval.modpath_) = make_Modpa((yyvsp[(2) - (3)].symval_)); ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 322 "SW.y"
    { (yyval.modpath_) = make_Modpx((yyvsp[(1) - (2)].symval_)); ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 323 "SW.y"
    { (yyval.modpath_) = make_Modpy((yyvsp[(1) - (3)].modpath_), (yyvsp[(2) - (3)].symval_)); ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 324 "SW.y"
    { (yyval.modpath_) = make_Modps((yyvsp[(1) - (2)]._string)); ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 326 "SW.y"
    { (yyval.rempath_) = make_RemPatha((yyvsp[(1) - (3)]._string), (yyvsp[(3) - (3)].symval_)); ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 328 "SW.y"
    { (yyval.argument_) = make_Argumentx((yyvsp[(1) - (1)].stringval_)); ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 330 "SW.y"
    { (yyval.listargument_) = 0; ;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 331 "SW.y"
    { (yyval.listargument_) = make_ListArgument((yyvsp[(2) - (2)].argument_), (yyvsp[(1) - (2)].listargument_)); ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 333 "SW.y"
    { (yyval.numassgn_) = make_NumAssgnv((yyvsp[(1) - (3)]._string), (yyvsp[(3) - (3)].numval_)); ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 335 "SW.y"
    { (yyval.strassgn_) = make_StrAssgnv((yyvsp[(1) - (3)]._string), (yyvsp[(3) - (3)].stringval_)); ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 337 "SW.y"
    { (yyval.symassgn_) = make_SymAssgni((yyvsp[(1) - (3)]._string), (yyvsp[(3) - (3)].symval_)); ;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 339 "SW.y"
    { (yyval.numval_) = make_NumVali((yyvsp[(1) - (1)]._int)); ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 340 "SW.y"
    { (yyval.numval_) = make_NumValv((yyvsp[(1) - (1)]._string)); ;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 342 "SW.y"
    { (yyval.stringval_) = make_StringVals((yyvsp[(1) - (1)]._string)); ;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 343 "SW.y"
    { (yyval.stringval_) = make_StringValv((yyvsp[(1) - (1)]._string)); ;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 344 "SW.y"
    { (yyval.stringval_) = make_StringVale((yyvsp[(1) - (1)]._string)); ;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 346 "SW.y"
    { (yyval.symval_) = make_Symvalv((yyvsp[(1) - (1)]._string)); ;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 347 "SW.y"
    { (yyval.symval_) = make_Symvali((yyvsp[(1) - (1)]._string)); ;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 348 "SW.y"
    { (yyval.symval_) = make_SymVale((yyvsp[(1) - (1)]._string)); ;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 350 "SW.y"
    { (yyval.include_) = make_Inc1(); ;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 351 "SW.y"
    { (yyval.include_) = make_Inc2(); ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 353 "SW.y"
    { (yyval.prefix_) = make_Prefu(); ;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 354 "SW.y"
    { (yyval.prefix_) = make_Prefl(); ;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 356 "SW.y"
    { (yyval.validconfig_) = make_Validcfg(reverseListEntry((yyvsp[(2) - (2)].listentry_))); result->validconfig_ = (yyval.validconfig_); ;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 357 "SW.y"
    { (yyval.validconfig_) = make_Validcfgd(reverseListCentry((yyvsp[(4) - (5)].listcentry_))); result->validconfig_ = (yyval.validconfig_); ;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 359 "SW.y"
    { (yyval.centry_) = make_CfgcEntrya((yyvsp[(1) - (1)].keyval_)); ;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 360 "SW.y"
    { (yyval.centry_) = make_CfgcEntryb((yyvsp[(1) - (1)].keyname_)); ;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 362 "SW.y"
    { (yyval.listcentry_) = 0; ;}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 363 "SW.y"
    { (yyval.listcentry_) = make_ListCentry((yyvsp[(2) - (3)].centry_), (yyvsp[(1) - (3)].listcentry_)); ;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 365 "SW.y"
    { (yyval.entry_) = make_CfgEntrya((yyvsp[(1) - (1)].keyval_)); ;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 366 "SW.y"
    { (yyval.entry_) = make_CfgEntryb((yyvsp[(1) - (1)].keyname_)); ;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 368 "SW.y"
    { (yyval.listentry_) = 0; ;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 369 "SW.y"
    { (yyval.listentry_) = make_ListEntry((yyvsp[(2) - (2)].entry_), (yyvsp[(1) - (2)].listentry_)); ;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 371 "SW.y"
    { (yyval.keyval_) = make_CfgKeyvalint((yyvsp[(1) - (2)].keyname_), (yyvsp[(2) - (2)]._int)); ;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 372 "SW.y"
    { (yyval.keyval_) = make_CfgKeyvalstr((yyvsp[(1) - (2)].keyname_), (yyvsp[(2) - (2)]._string)); ;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 373 "SW.y"
    { (yyval.keyval_) = make_CfgKeyDate((yyvsp[(1) - (2)].keyname_), (yyvsp[(2) - (2)]._string)); ;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 375 "SW.y"
    { (yyval.keyname_) = make_KeynameS((yyvsp[(1) - (2)].symval_)); ;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 376 "SW.y"
    { (yyval.keyname_) = make_KeynameM((yyvsp[(1) - (3)].modpath_), (yyvsp[(2) - (3)].symval_)); ;}
    break;



/* Line 1464 of yacc.c  */
#line 2349 "Parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, scanner, result, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (&yylloc, scanner, result, yymsg);
	  }
	else
	  {
	    yyerror (&yylloc, scanner, result, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

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
		      yytoken, &yylval, &yylloc, scanner, result);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, scanner, result);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, scanner, result, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc, scanner, result);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, scanner, result);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1684 of yacc.c  */
#line 379 "SW.y"



/* Entrypoint: parse Valide from file. */
Valide pValide(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = sw__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  sw_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.valide_;
  }
}

/* Entrypoint: parse Valide from string. */
Valide psValide(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = sw__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = sw__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  sw__delete_buffer(buf, scanner);
  sw_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.valide_;
  }
}

/* Entrypoint: parse ValidSW from file. */
ValidSW pValidSW(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = sw__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  sw_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.validsw_;
  }
}

/* Entrypoint: parse ValidSW from string. */
ValidSW psValidSW(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = sw__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = sw__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  sw__delete_buffer(buf, scanner);
  sw_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.validsw_;
  }
}

/* Entrypoint: parse ValidConfig from file. */
ValidConfig pValidConfig(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = sw__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  sw_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.validconfig_;
  }
}

/* Entrypoint: parse ValidConfig from string. */
ValidConfig psValidConfig(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = sw__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = sw__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  sw__delete_buffer(buf, scanner);
  sw_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.validconfig_;
  }
}




