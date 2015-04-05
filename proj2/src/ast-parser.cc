/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2009, 2010 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* "%code top" blocks.  */

/* Line 171 of yacc.c  */
#line 4 "ast-parser.y"


#define YYPARAM Tree_Semantics< AST >
#define YYPRODUCING_TREES
#define YYERROR_FUNCTION_NAME parse_error

# define YY_PARSER_1
# include "horn-parse-lex.cc"



/* Line 171 of yacc.c  */
#line 82 "ast-parser.cc"


/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 14 "ast-parser.y"


    YYNAMESPACE_OPEN


/* Line 189 of yacc.c  */
#line 9 "ast.hn"

    #include <string>
    #include <cstring>
    #include "apyc.h"
    #include "ast.h"

    using namespace std;

    static GCINIT _gcdummy;

    static AST_Ptr theTree;
   
    /** Return a location string (Unix format) formed from the name of
     *  the source file producing this AST and the number in NODE (an
     *  INT token). */
    static const char* make_ast_loc (AST* node);
    void parse_error (const char* loc, const char* message, ...);

/* Line 189 of yacc.c  */
#line 112 "ast-parser.y"


#define YY_PARSER_2
#include "horn-parse-lex.cc"


/* Line 189 of yacc.c  */
#line 132 "ast-parser.y"

static yyvar yyv_ID;
static yyvar yyv_INT_LITERAL;
static yyvar yyv_STRING_LITERAL;
static yyvar yyv_TYPE_VAR_ID;
static yyvar yyv_ast_node_type;
static yyvar yyv_expr;
static yyvar yyv_id;
static yyvar yyv_num;
static yyvar yyv_operands;
static yyvar yyv_val;



/* Line 189 of yacc.c  */
#line 139 "ast-parser.cc"

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
# define YYTOKEN_TABLE 1
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     AND = 258,
     ASSIGN = 259,
     ATTRIBUTEREF = 260,
     BINOP = 261,
     BLOCK = 262,
     BREAK = 263,
     CALL = 264,
     CALL1 = 265,
     CLASS = 266,
     COMPARE = 267,
     CONTINUE = 268,
     DEDENT = 269,
     DEF = 270,
     DICT_DISPLAY = 271,
     FALSE = 272,
     FOR = 273,
     FORMALS_LIST = 274,
     FUNCTION_TYPE = 275,
     EXPR_LIST = 276,
     ID = 277,
     IF = 278,
     IF_EXPR = 279,
     INDENT = 280,
     INT_LITERAL = 281,
     LEFT_COMPARE = 282,
     LIST_DISPLAY = 283,
     METHOD = 284,
     MODULE = 285,
     NATIVE = 286,
     NEXT_VALUE = 287,
     NONE = 288,
     NOT = 289,
     OR = 290,
     PAIR = 291,
     PRINT = 292,
     PRINTLN = 293,
     RETURN = 294,
     SLICE = 295,
     SLICE_ASSIGN = 296,
     STMT_LIST = 297,
     STRING_LITERAL = 298,
     SUBSCRIPT = 299,
     SUBSCRIPT_ASSIGN = 300,
     TARGET_LIST = 301,
     TRUE = 302,
     TUPLE = 303,
     TYPE = 304,
     TYPED_ID = 305,
     TYPE_FORMALS_LIST = 306,
     TYPE_LIST = 307,
     TYPE_VAR = 308,
     UNOP = 309,
     WHILE = 310,
     NEW = 311,
     _TOK_0 = 312,
     _TOK_1 = 313,
     _TOK_2 = 314,
     TYPE_VAR_ID = 315
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 241 "ast-parser.cc"

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
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  52
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   117

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  7
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNRULES -- Number of states.  */
#define YYNSTATES  76

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   315

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      57,    58,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    59,    60,    61,    62
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,    11,    17,    23,    29,    35,    37,
      39,    41,    43,    45,    47,    49,    51,    53,    55,    57,
      59,    61,    63,    65,    67,    69,    71,    73,    75,    77,
      79,    81,    83,    85,    87,    89,    91,    93,    95,    97,
      99,   101,   103,   105,   107,   109,   111,   113,   115,   117,
     119,   121,   123,   125,   127,   129,   131,   133,   135,   136
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      64,     0,    -1,    65,    -1,    57,    67,    26,    66,    58,
      -1,    57,    59,    26,    68,    58,    -1,    57,    26,    26,
      26,    58,    -1,    57,    60,    26,    43,    58,    -1,    57,
      61,    26,    62,    58,    -1,    69,    -1,     3,    -1,     4,
      -1,     5,    -1,     6,    -1,     7,    -1,     8,    -1,     9,
      -1,    11,    -1,    12,    -1,    13,    -1,    15,    -1,    16,
      -1,    17,    -1,    18,    -1,    19,    -1,    20,    -1,    23,
      -1,    24,    -1,    27,    -1,    28,    -1,    30,    -1,    31,
      -1,    32,    -1,    33,    -1,    35,    -1,    36,    -1,    37,
      -1,    38,    -1,    39,    -1,    40,    -1,    41,    -1,    42,
      -1,    44,    -1,    45,    -1,    46,    -1,    47,    -1,    48,
      -1,    49,    -1,    50,    -1,    51,    -1,    52,    -1,    54,
      -1,    55,    -1,    22,    -1,    67,    -1,    59,    -1,    26,
      -1,    60,    -1,    61,    -1,    -1,    69,    65,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   112,   112,   116,   121,   124,   127,   130,   135,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   185,   186,   187,   188,   189,   190,   193,   135
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"and\"", "\"assign\"",
  "\"attributeref\"", "\"binop\"", "\"block\"", "\"break\"", "\"call\"",
  "\"call1\"", "\"class\"", "\"compare\"", "\"continue\"", "DEDENT",
  "\"def\"", "\"dict_display\"", "\"False\"", "\"for\"",
  "\"formals_list\"", "\"function_type\"", "\"expr_list\"", "ID", "\"if\"",
  "\"if_expr\"", "INDENT", "\"int_literal\"", "\"left_compare\"",
  "\"list_display\"", "\"@method\"", "\"module\"", "\"native\"",
  "\"next_value\"", "\"None\"", "\"not\"", "\"or\"", "\"pair\"",
  "\"print\"", "\"println\"", "\"return\"", "\"slice\"",
  "\"slice_assign\"", "\"stmt_list\"", "STRING_LITERAL", "\"subscript\"",
  "\"subscript_assign\"", "\"target_list\"", "\"True\"", "\"tuple\"",
  "\"type\"", "\"typed_id\"", "\"type_formals_list\"", "\"type_list\"",
  "TYPE_VAR", "\"unop\"", "\"while\"", "\"new\"", "\"(\"", "\")\"",
  "\"id\"", "\"string_literal\"", "\"type_var\"", "TYPE_VAR_ID", "$accept",
  "program", "expr", "operands", "ast_node_type", "id", "__0", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,    40,    41,   312,
     313,   314,   315
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    63,    64,    65,    65,    65,    65,    65,    66,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    68,    68,    68,    68,    68,    68,    69,    69
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     5,     5,     5,     5,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,     0,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,     0,     0,
       0,     0,     1,     0,     0,     0,     0,    58,     0,    52,
      55,    54,    56,    57,    53,     0,     0,     0,     0,     8,
       5,     4,     6,     7,     3,    59
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,    68,    51,    65,    69
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -51
static const yytype_int8 yypact[] =
{
     -50,    56,    11,   -51,   -51,   -51,   -51,   -51,   -51,   -51,
     -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,
     -51,   -51,    -8,   -51,   -51,   -51,   -51,   -51,   -51,   -51,
     -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,
     -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,    -4,     0,
       5,    14,   -51,    24,    -3,    10,    -7,   -51,     8,   -51,
     -51,   -51,   -51,   -51,   -51,    12,    19,    20,    23,   -50,
     -51,   -51,   -51,   -51,   -51,   -51
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -51,   -51,   -15,   -51,    31,   -51,   -51
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
       4,     5,     6,     7,     8,     9,    10,     1,    11,    12,
      13,    52,    14,    15,    16,    17,    18,    19,    53,    59,
      20,    21,    54,    60,    23,    24,    55,    25,    26,    27,
      28,    56,    29,    30,    31,    32,    33,    34,    35,    36,
      57,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      58,    46,    47,    66,    75,    67,    61,    62,    63,     4,
       5,     6,     7,     8,     9,    10,    70,    11,    12,    13,
      71,    14,    15,    16,    17,    18,    19,    72,    73,    20,
      21,    74,    22,    23,    24,    64,    25,    26,    27,    28,
       0,    29,    30,    31,    32,    33,    34,    35,    36,     0,
      37,    38,    39,    40,    41,    42,    43,    44,    45,     0,
      46,    47,     0,     0,     0,    48,    49,    50
};

static const yytype_int8 yycheck[] =
{
       3,     4,     5,     6,     7,     8,     9,    57,    11,    12,
      13,     0,    15,    16,    17,    18,    19,    20,    26,    22,
      23,    24,    26,    26,    27,    28,    26,    30,    31,    32,
      33,    26,    35,    36,    37,    38,    39,    40,    41,    42,
      26,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      26,    54,    55,    43,    69,    62,    59,    60,    61,     3,
       4,     5,     6,     7,     8,     9,    58,    11,    12,    13,
      58,    15,    16,    17,    18,    19,    20,    58,    58,    23,
      24,    58,    26,    27,    28,    54,    30,    31,    32,    33,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    -1,
      54,    55,    -1,    -1,    -1,    59,    60,    61
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    57,    64,    65,     3,     4,     5,     6,     7,     8,
       9,    11,    12,    13,    15,    16,    17,    18,    19,    20,
      23,    24,    26,    27,    28,    30,    31,    32,    33,    35,
      36,    37,    38,    39,    40,    41,    42,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    54,    55,    59,    60,
      61,    67,     0,    26,    26,    26,    26,    26,    26,    22,
      26,    59,    60,    61,    67,    68,    43,    62,    66,    69,
      58,    58,    58,    58,    58,    65
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
      yyerror (YY_("syntax error: cannot back up")); \
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
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
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
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 3: /* "\"and\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1232 "ast-parser.cc"
	break;
      case 4: /* "\"assign\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1241 "ast-parser.cc"
	break;
      case 5: /* "\"attributeref\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1250 "ast-parser.cc"
	break;
      case 6: /* "\"binop\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1259 "ast-parser.cc"
	break;
      case 7: /* "\"block\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1268 "ast-parser.cc"
	break;
      case 8: /* "\"break\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1277 "ast-parser.cc"
	break;
      case 9: /* "\"call\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1286 "ast-parser.cc"
	break;
      case 10: /* "\"call1\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1295 "ast-parser.cc"
	break;
      case 11: /* "\"class\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1304 "ast-parser.cc"
	break;
      case 12: /* "\"compare\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1313 "ast-parser.cc"
	break;
      case 13: /* "\"continue\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1322 "ast-parser.cc"
	break;
      case 14: /* "DEDENT" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1331 "ast-parser.cc"
	break;
      case 15: /* "\"def\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1340 "ast-parser.cc"
	break;
      case 16: /* "\"dict_display\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1349 "ast-parser.cc"
	break;
      case 17: /* "\"False\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1358 "ast-parser.cc"
	break;
      case 18: /* "\"for\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1367 "ast-parser.cc"
	break;
      case 19: /* "\"formals_list\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1376 "ast-parser.cc"
	break;
      case 20: /* "\"function_type\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1385 "ast-parser.cc"
	break;
      case 21: /* "\"expr_list\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1394 "ast-parser.cc"
	break;
      case 22: /* "ID" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1403 "ast-parser.cc"
	break;
      case 23: /* "\"if\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1412 "ast-parser.cc"
	break;
      case 24: /* "\"if_expr\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1421 "ast-parser.cc"
	break;
      case 25: /* "INDENT" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1430 "ast-parser.cc"
	break;
      case 26: /* "\"int_literal\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1439 "ast-parser.cc"
	break;
      case 27: /* "\"left_compare\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1448 "ast-parser.cc"
	break;
      case 28: /* "\"list_display\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1457 "ast-parser.cc"
	break;
      case 29: /* "\"@method\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1466 "ast-parser.cc"
	break;
      case 30: /* "\"module\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1475 "ast-parser.cc"
	break;
      case 31: /* "\"native\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1484 "ast-parser.cc"
	break;
      case 32: /* "\"next_value\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1493 "ast-parser.cc"
	break;
      case 33: /* "\"None\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1502 "ast-parser.cc"
	break;
      case 34: /* "\"not\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1511 "ast-parser.cc"
	break;
      case 35: /* "\"or\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1520 "ast-parser.cc"
	break;
      case 36: /* "\"pair\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1529 "ast-parser.cc"
	break;
      case 37: /* "\"print\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1538 "ast-parser.cc"
	break;
      case 38: /* "\"println\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1547 "ast-parser.cc"
	break;
      case 39: /* "\"return\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1556 "ast-parser.cc"
	break;
      case 40: /* "\"slice\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1565 "ast-parser.cc"
	break;
      case 41: /* "\"slice_assign\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1574 "ast-parser.cc"
	break;
      case 42: /* "\"stmt_list\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1583 "ast-parser.cc"
	break;
      case 43: /* "STRING_LITERAL" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1592 "ast-parser.cc"
	break;
      case 44: /* "\"subscript\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1601 "ast-parser.cc"
	break;
      case 45: /* "\"subscript_assign\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1610 "ast-parser.cc"
	break;
      case 46: /* "\"target_list\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1619 "ast-parser.cc"
	break;
      case 47: /* "\"True\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1628 "ast-parser.cc"
	break;
      case 48: /* "\"tuple\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1637 "ast-parser.cc"
	break;
      case 49: /* "\"type\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1646 "ast-parser.cc"
	break;
      case 50: /* "\"typed_id\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1655 "ast-parser.cc"
	break;
      case 51: /* "\"type_formals_list\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1664 "ast-parser.cc"
	break;
      case 52: /* "\"type_list\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1673 "ast-parser.cc"
	break;
      case 53: /* "TYPE_VAR" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1682 "ast-parser.cc"
	break;
      case 54: /* "\"unop\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1691 "ast-parser.cc"
	break;
      case 55: /* "\"while\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1700 "ast-parser.cc"
	break;
      case 56: /* "\"new\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1709 "ast-parser.cc"
	break;
      case 57: /* "\"(\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1718 "ast-parser.cc"
	break;
      case 58: /* "\")\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1727 "ast-parser.cc"
	break;
      case 59: /* "\"id\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1736 "ast-parser.cc"
	break;
      case 60: /* "\"string_literal\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1745 "ast-parser.cc"
	break;
      case 61: /* "\"type_var\"" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1754 "ast-parser.cc"
	break;
      case 62: /* "TYPE_VAR_ID" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1763 "ast-parser.cc"
	break;
      case 64: /* "program" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1772 "ast-parser.cc"
	break;
      case 65: /* "expr" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1781 "ast-parser.cc"
	break;
      case 66: /* "operands" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1790 "ast-parser.cc"
	break;
      case 67: /* "ast_node_type" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1799 "ast-parser.cc"
	break;
      case 68: /* "id" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1808 "ast-parser.cc"
	break;
      case 69: /* "__0" */

/* Line 1009 of yacc.c  */
#line 130 "ast-parser.y"
	{ (*yyvaluep)._destructor (); };

/* Line 1009 of yacc.c  */
#line 1817 "ast-parser.cc"
	break;

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
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



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
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1464 of yacc.c  */
#line 112 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  yyv_expr = (yyvsp[(1) - (1)]);theTree = yyv_expr.value (); ;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 117 "ast.hn"
    { YYCTLPA((yyval),0,5,&(yyvsp[(1) - (5)]),&(yyvsp[(2) - (5)]),&(yyvsp[(3) - (5)]),&(yyvsp[(4) - (5)]),&(yyvsp[(5) - (5)]));  (yyvsp[(1) - (5)]).ignore(); (yyvsp[(5) - (5)]).ignore(); yyv_ast_node_type = (yyvsp[(2) - (5)]); yyv_num = (yyvsp[(3) - (5)]); yyv_INT_LITERAL = (yyvsp[(3) - (5)]); yyv_operands = (yyvsp[(4) - (5)]);yylhs = YYMAKE_TREE(yyv_ast_node_type.value (), 
                            yyv_operands.list_value ());
                    yylhs.set_loc (make_ast_loc (yyv_INT_LITERAL.value ())); ;}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 122 "ast.hn"
    { YYCTLPA((yyval),0,5,&(yyvsp[(1) - (5)]),&(yyvsp[(2) - (5)]),&(yyvsp[(3) - (5)]),&(yyvsp[(4) - (5)]),&(yyvsp[(5) - (5)]));  yyv_INT_LITERAL = (yyvsp[(3) - (5)]); yyv_id = (yyvsp[(4) - (5)]);yylhs = yyv_id;
                    yylhs.set_loc (make_ast_loc (yyv_INT_LITERAL.value ())); ;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 125 "ast.hn"
    { YYCTLPA((yyval),0,5,&(yyvsp[(1) - (5)]),&(yyvsp[(2) - (5)]),&(yyvsp[(3) - (5)]),&(yyvsp[(4) - (5)]),&(yyvsp[(5) - (5)]));  yyv_num = (yyvsp[(3) - (5)]); yyv_INT_LITERAL = (yyvsp[(3) - (5)]); yyv_val = (yyvsp[(4) - (5)]); yyv_INT_LITERAL = (yyvsp[(4) - (5)]);yylhs = yyv_val;
                    yylhs.set_loc (make_ast_loc (yyv_num.value ())); ;}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 128 "ast.hn"
    { YYCTLPA((yyval),0,5,&(yyvsp[(1) - (5)]),&(yyvsp[(2) - (5)]),&(yyvsp[(3) - (5)]),&(yyvsp[(4) - (5)]),&(yyvsp[(5) - (5)]));  yyv_INT_LITERAL = (yyvsp[(3) - (5)]); yyv_STRING_LITERAL = (yyvsp[(4) - (5)]);yylhs = yyv_STRING_LITERAL;
                    yylhs.set_loc (make_ast_loc (yyv_INT_LITERAL.value ())); ;}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 131 "ast.hn"
    { YYCTLPA((yyval),0,5,&(yyvsp[(1) - (5)]),&(yyvsp[(2) - (5)]),&(yyvsp[(3) - (5)]),&(yyvsp[(4) - (5)]),&(yyvsp[(5) - (5)]));  yyv_INT_LITERAL = (yyvsp[(3) - (5)]); yyv_TYPE_VAR_ID = (yyvsp[(4) - (5)]);yylhs = YYMAKE_TREE (TYPE_VAR, yyv_TYPE_VAR_ID.value ());
                    yylhs.set_loc (make_ast_loc (yyv_INT_LITERAL.value ())); ;}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 135 "ast.hn"
    { YYCTLA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 140 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 141 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 142 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 143 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 144 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 145 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 146 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 147 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 148 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 149 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 150 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 151 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 152 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 153 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 154 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 155 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 156 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 157 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 158 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 159 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 160 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 161 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 162 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 163 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 164 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 165 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 166 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 167 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 168 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 169 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 170 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 171 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 172 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 173 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 174 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 175 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 176 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 177 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 178 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 179 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 180 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 181 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 182 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 185 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  yyv_ID = (yyvsp[(1) - (1)]); ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 186 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  yyv_ast_node_type = (yyvsp[(1) - (1)]); ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 187 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 188 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 189 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 190 "ast.hn"
    { YYCTLPA((yyval),0,1,&(yyvsp[(1) - (1)]));  ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 193 "ast.hn"
    { YYCTLPC((yyval),0,0);  ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 136 "ast.hn"
    { YYCTLC((yyval),0,2,&(yyvsp[(1) - (2)]),&(yyvsp[(2) - (2)]));  yyv_expr = (yyvsp[(2) - (2)]); ;}
    break;



/* Line 1464 of yacc.c  */
#line 2534 "ast-parser.cc"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

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
      yyerror (YY_("syntax error"));
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
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



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
		      yytoken, &yylval);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
#line 361 "ast-parser.y"



#line 194 "ast.hn"


static gcstring current_python_file;
static gcstring current_ast_file;

const char*
AST::lineNumber ()
{
    if (loc () == NULL)
        return "0";
    const char* suffix = strrchr (loc (), ':');
    if (suffix == NULL)
        return "0";
    return suffix + 1;
}

void
parse_error (const char* loc, const char* message, ...)
{
    if (loc == NULL)
        error ((current_ast_file + ":?").c_str (), message);
    else {
        char *place = new char[current_ast_file.size() + 12];
        sprintf(place, "%s:%d", current_ast_file.c_str (),
                yylocation_line (loc));
        error (place, message);
    }
    fatal ("bad AST");
}

static const char*
make_ast_loc (AST* node)
{
    return GC_strdup ((current_python_file + ":" + node->as_string ()).c_str ());
}

AST_Ptr
readAst (const gcstring& ast_file_name,
         const gcstring& python_file_name)
{
    current_ast_file = ast_file_name;
    FILE* f = fopen (ast_file_name.c_str (), "r");

    if (f == NULL) {
        errorNoFile ("Could not open %s", ast_file_name.c_str ());
        return NULL;
    }
    yypush_lexer (f, ast_file_name);
    current_python_file = python_file_name;

    theTree = NULL;
    yyparse ();
    fclose (f);
    yypop_lexer ();
            
    return theTree;
}


#line 425 "ast-parser.y"

const char* 
yyexternal_token_name (int syntax)
{
    int internal_num = YYTRANSLATE (syntax);
    return yytname[internal_num];
}

#undef YY_NULL
#include "ast-lexer.cc"

YYNAMESPACE_CLOSE

template <class Type>
Type Simple_Value_Semantics<Type>::default_make_token (int syn,
						       size_t len,
						       const char* text)
{
    return YY_DEFAULT_MAKE_TOKEN(syn, len, text);
}

