/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */

#line 67 "parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "parser.y" /* yacc.c:355  */

  #include "ast.hpp"
  #include <iostream>
  #include <cassert>

  extern Program *g_root;
  extern FILE *yyin;

int yylex(void);
  void yyerror(const char *);

#line 109 "parser.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    times = 258,
    divide = 259,
    plus = 260,
    minus = 261,
    assign = 262,
    condIf = 263,
    condElse = 264,
    notEqualOp = 265,
    bitWiseAndOp = 266,
    bitWiseIorOp = 267,
    bitWiseEorOp = 268,
    logicalAndOp = 269,
    logicalOrOp = 270,
    lBracket = 271,
    rBracket = 272,
    lCurlyBracket = 273,
    rCurlyBracket = 274,
    plusEquals = 275,
    minusEquals = 276,
    timesEquals = 277,
    comma = 278,
    breakT = 279,
    enumT = 280,
    divEquals = 281,
    modEquals = 282,
    andEquals = 283,
    orEquals = 284,
    xorEquals = 285,
    lShiftEquals = 286,
    logicalNotOp = 287,
    rShiftEquals = 288,
    number = 289,
    identifier = 290,
    dataType = 291,
    colon = 292,
    loopWhile = 293,
    loopFor = 294,
    gt = 295,
    gte = 296,
    lt = 297,
    lte = 298,
    leftOp = 299,
    rightOp = 300,
    modulo = 301,
    ret = 302,
    equalsOp = 303,
    lSquareBracket = 304,
    rSquareBracket = 305,
    caseT = 306,
    defaultT = 307,
    condSwitch = 308,
    colonT = 309,
    continueT = 310,
    plusPlus = 311,
    minusMinus = 312
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 15 "parser.y" /* yacc.c:355  */

  Expression *expr;
  std::string *string;
  Program *prog;

#line 185 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 202 "parser.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   625

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  120
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  237

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   313

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    45,    45,    48,    49,    52,    53,    54,    55,    56,
      59,    62,    63,    66,    67,    68,    70,    73,    74,    75,
      78,    79,    82,    85,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   120,   123,
     126,   127,   128,   131,   132,   135,   138,   139,   140,   143,
     146,   147,   148,   149,   150,   151,   154,   155,   156,   157,
     158,   159,   160,   163,   164,   165,   166,   169,   170,   173,
     176,   177,   178,   181,   182,   185,   186,   189,   190,   193,
     194,   197,   198,   201,   202,   203,   204,   205,   206,   209,
     210,   211,   214,   215,   216,   219,   220,   221,   222,   223,
     224,   225,   226,   229,   230,   233,   234,   235,   236,   237,
     238
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "times", "divide", "plus", "minus",
  "assign", "condIf", "condElse", "notEqualOp", "bitWiseAndOp",
  "bitWiseIorOp", "bitWiseEorOp", "logicalAndOp", "logicalOrOp",
  "lBracket", "rBracket", "lCurlyBracket", "rCurlyBracket", "plusEquals",
  "minusEquals", "timesEquals", "comma", "breakT", "enumT", "divEquals",
  "modEquals", "andEquals", "orEquals", "xorEquals", "lShiftEquals",
  "logicalNotOp", "rShiftEquals", "number", "identifier", "dataType",
  "colon", "loopWhile", "loopFor", "gt", "gte", "lt", "lte", "leftOp",
  "rightOp", "modulo", "ret", "equalsOp", "lSquareBracket",
  "rSquareBracket", "caseT", "defaultT", "condSwitch", "colonT",
  "continueT", "plusPlus", "minusMinus", "\"then\"", "$accept", "ROOT",
  "PROG", "PROGELEMENT", "FUNTIONDECLARATION", "FUNCTIONDEFINITION",
  "VARIABLEDECLARATION", "ARRAYDECLARATION", "PARAMETERLIST",
  "STATEMENTLIST", "BREAKSTATEMENT", "CONTINUESTATEMENT", "STATEMENT",
  "ASSIGNMENT", "ENUMERATIONSPECIFIER", "ENUMERATORLIST", "ENUMERATOR",
  "FUNCTIONCALL", "CONCRETEPARAMETERLIST", "RETURNSTATEMENT", "LOOP",
  "CONDITIONAL", "CASELIST", "CASE", "SUBSCRIPT", "EQUALITYEXPRESSION",
  "ANDEXPRESSION", "EXCLUSIVEOREXPRESSION", "INCLUSIVEOREXPRESSION",
  "LOGICALANDEXPRESSION", "LOGICALOREXPRESSION", "RELATIONALEXPRESSION",
  "SHIFTEXPRESSION", "ADDITIVEEXPRESSION", "MULTIPLICATIVEEXPRESSION",
  "UNARYMINUS", "FACTOR", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313
};
# endif

#define YYPACT_NINF -145

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-145)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -9,   -11,    43,    47,    35,  -145,    -9,    53,  -145,    57,
      65,    67,    92,  -145,    13,  -145,  -145,  -145,  -145,  -145,
    -145,    72,   165,    76,   165,   107,    97,    96,   170,   165,
     170,  -145,    59,   170,   170,  -145,  -145,     7,   110,   115,
     111,   130,   132,   244,    55,   127,     8,  -145,   102,   118,
     143,    -8,   165,  -145,    72,  -145,   114,  -145,   165,   165,
    -145,  -145,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   170,   170,
     170,  -145,  -145,   145,   152,  -145,   132,  -145,  -145,   158,
      -5,    -6,   244,   244,     7,   110,   115,   111,   130,    55,
      55,    55,    55,    55,   127,   127,     8,     8,  -145,  -145,
    -145,    76,   285,  -145,   165,  -145,  -145,   167,  -145,  -145,
      23,   150,  -145,   171,   172,   165,   174,  -145,   154,   155,
     184,   173,   176,    32,   178,   179,   181,  -145,  -145,  -145,
     204,    -1,   568,  -145,   165,   536,    -4,   165,   536,     0,
     165,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,
     165,  -145,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,     4,    25,  -145,   132,    16,   183,  -145,    48,
     132,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,
    -145,   319,   353,   165,   205,    32,   215,   388,  -145,    58,
     243,   207,   422,  -145,   209,   536,   165,   182,   243,   211,
     243,   224,    32,  -145,  -145,   222,    -7,    32,  -145,  -145,
    -145,   456,   225,   490,    32,  -145,    32,  -145,  -145,   525,
    -145,  -145,   226,  -145,   228,  -145,  -145
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     2,     3,     0,     9,     0,
       0,     0,     0,    15,    13,     1,     4,     8,     5,     6,
       7,     0,     0,    19,     0,    54,     0,    50,     0,     0,
       0,   115,   117,     0,     0,   119,   118,    83,    85,    87,
      89,    91,    14,    80,    93,    99,   102,   120,   112,     0,
       0,     0,     0,    49,    51,   113,     0,   114,    58,     0,
     107,   108,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   106,    18,    10,    16,    53,    52,   116,     0,
      57,     0,    82,    81,    84,    86,    88,    90,    92,    95,
      97,    94,    96,    98,   100,   101,   103,   104,   109,   110,
     111,    19,     0,    55,    58,    79,    17,     0,    12,    22,
     117,     0,    32,     0,     0,     0,     0,    23,     0,     0,
       0,     0,     0,    20,     0,     0,   119,    33,    24,    30,
     118,     0,   112,    56,     0,     0,    13,     0,     0,     0,
       0,    25,    26,    11,    28,    29,    21,    27,    31,    34,
       0,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   117,    36,    48,     0,     0,    59,     0,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,     0,     0,     0,     0,     0,    66,     0,    60,     0,
      76,     0,     0,    62,     0,     0,     0,     0,    76,     0,
      73,    70,     0,    67,    61,     0,     0,     0,    75,    72,
      74,     0,     0,     0,     0,    78,     0,    68,    69,     0,
      63,    77,     0,    65,     0,    71,    64
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -145,  -145,   242,  -145,  -145,  -145,    22,    80,   139,    40,
    -145,  -145,  -145,  -144,    91,   199,  -145,    17,   140,  -145,
    -145,  -145,  -127,  -145,   -99,   191,   193,   190,   195,   192,
       1,    14,   201,   104,    89,  -145,   -28
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,   128,   129,    50,   208,
     131,   132,   133,   134,   135,    26,    27,    35,    89,   137,
     138,   139,   209,   210,    36,    37,    38,    39,    40,    41,
     141,    43,    44,    45,    46,    47,    48
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      55,   174,    57,    22,   177,    60,    61,    68,    68,    68,
      68,    78,    79,   140,    68,    68,     1,    62,   114,    68,
      22,   191,     9,    42,    12,    51,     2,     3,     9,    23,
     145,    68,   145,   192,   140,    15,   161,   178,    28,    58,
     117,    58,    85,    56,   115,    24,   140,   224,    29,   140,
     108,   109,   110,    86,    80,    63,   119,     1,    13,    90,
      91,   215,    24,    68,    30,   194,    31,   120,   121,   122,
     123,   124,    59,    68,    59,    58,    92,    93,    13,   125,
      10,   218,    14,   220,   142,   126,    10,   127,    33,    34,
      17,    11,   140,   140,    18,   205,   140,    11,   140,    74,
      75,   140,    19,   140,    20,   142,   140,    25,    59,   140,
      21,   140,    49,   140,    52,    90,    53,   142,   140,    54,
     142,    64,   140,    66,   140,   140,   149,   140,    65,   136,
     140,    88,    76,    77,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,    67,   172,   175,    68,   176,   175,
     136,   179,   130,    83,    69,    70,    71,    72,    81,    82,
      84,   180,    73,   142,   142,   106,   107,   142,   111,   142,
     112,    28,   142,   156,   142,   113,    28,   142,   104,   105,
     142,    29,   142,   144,   142,   146,    29,   147,   148,   142,
     150,   151,   152,   142,   199,   142,   142,    30,   142,    31,
      32,   142,    30,   153,    31,    32,   175,   216,   136,   136,
     154,   160,   136,   155,   136,   157,   158,   136,   159,   136,
     193,    33,    34,   200,   202,   136,   211,   136,   214,   136,
     219,   196,   198,   221,   136,   201,   217,   204,   136,   223,
     136,   136,   213,   136,   228,   235,   136,   236,    16,    28,
     116,   117,   222,    87,   143,    94,    96,   225,    95,    29,
      98,   227,    97,   230,   231,     0,   232,   119,     1,   234,
      99,   100,   101,   102,   103,    30,     0,    31,   120,   121,
     122,   123,   124,     0,    69,    70,    71,    72,     0,     0,
     125,    28,    73,   117,   206,   207,   126,     0,   127,    33,
      34,    29,     0,     0,   118,     0,     0,     0,     0,   119,
       1,     0,     0,     0,     0,     0,     0,    30,     0,    31,
     120,   121,   122,   123,   124,    28,     0,   117,     0,     0,
       0,     0,   125,     0,     0,    29,     0,   195,   126,     0,
     127,    33,    34,   119,     1,     0,     0,     0,     0,     0,
       0,    30,     0,    31,   120,   121,   122,   123,   124,    28,
       0,   117,     0,     0,     0,     0,   125,     0,     0,    29,
       0,   197,   126,     0,   127,    33,    34,   119,     1,     0,
       0,     0,     0,     0,     0,    30,     0,    31,   120,   121,
     122,   123,   124,     0,    28,     0,   117,     0,     0,     0,
     125,     0,     0,     0,    29,     0,   126,   203,   127,    33,
      34,     0,   119,     1,     0,     0,     0,     0,     0,     0,
      30,     0,    31,   120,   121,   122,   123,   124,    28,     0,
     117,     0,     0,     0,     0,   125,     0,     0,    29,     0,
     212,   126,     0,   127,    33,    34,   119,     1,     0,     0,
       0,     0,     0,     0,    30,     0,    31,   120,   121,   122,
     123,   124,    28,     0,   117,     0,     0,     0,     0,   125,
       0,     0,    29,     0,   226,   126,     0,   127,    33,    34,
     119,     1,     0,     0,     0,     0,     0,     0,    30,     0,
      31,   120,   121,   122,   123,   124,    28,     0,   117,     0,
       0,     0,     0,   125,     0,     0,    29,     0,   229,   126,
       0,   127,    33,    34,   119,     1,     0,     0,     0,     0,
       0,     0,    30,     0,    31,   120,   121,   122,   123,   124,
       0,    28,     0,   117,     0,     0,     0,   125,     0,     0,
       0,    29,    28,   126,   233,   127,    33,    34,     0,   119,
       1,     0,    29,     0,     0,     0,     0,    30,     0,    31,
     120,   121,   122,   123,   124,     0,     0,     0,    30,     0,
      31,   173,   125,     0,     0,     0,     0,     0,   126,     0,
     127,    33,    34,     0,     0,     0,     0,     0,   162,   163,
     164,     0,    33,    34,   165,   166,   167,   168,   169,   170,
       0,   171,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    81,    82
};

static const yytype_int16 yycheck[] =
{
      28,   145,    30,     7,   148,    33,    34,    15,    15,    15,
      15,     3,     4,   112,    15,    15,    25,    10,    23,    15,
       7,    17,     0,    22,    35,    24,    35,    36,     6,    16,
       7,    15,     7,    17,   133,     0,    37,    37,     6,    16,
       8,    16,    50,    29,    50,    49,   145,    54,    16,   148,
      78,    79,    80,    52,    46,    48,    24,    25,    35,    58,
      59,   205,    49,    15,    32,    17,    34,    35,    36,    37,
      38,    39,    49,    15,    49,    16,    62,    63,    35,    47,
       0,   208,    35,   210,   112,    53,     6,    55,    56,    57,
      37,     0,   191,   192,    37,    37,   195,     6,   197,    44,
      45,   200,    37,   202,    37,   133,   205,    35,    49,   208,
      18,   210,    36,   212,     7,   114,    19,   145,   217,    23,
     148,    11,   221,    12,   223,   224,   125,   226,    13,   112,
     229,    17,     5,     6,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,    14,   144,   145,    15,   147,   148,
     133,   150,   112,    35,    40,    41,    42,    43,    56,    57,
      17,   160,    48,   191,   192,    76,    77,   195,    23,   197,
      18,     6,   200,   133,   202,    17,     6,   205,    74,    75,
     208,    16,   210,    16,   212,    35,    16,    16,    16,   217,
      16,    37,    37,   221,   193,   223,   224,    32,   226,    34,
      35,   229,    32,    19,    34,    35,   205,   206,   191,   192,
      37,     7,   195,    37,   197,    37,    37,   200,    37,   202,
      37,    56,    57,    18,     9,   208,    19,   210,    19,   212,
      19,   191,   192,     9,   217,   195,    54,   197,   221,    17,
     223,   224,   202,   226,    19,    19,   229,    19,     6,     6,
     111,     8,   212,    54,   114,    64,    66,   217,    65,    16,
      68,   221,    67,   223,   224,    -1,   226,    24,    25,   229,
      69,    70,    71,    72,    73,    32,    -1,    34,    35,    36,
      37,    38,    39,    -1,    40,    41,    42,    43,    -1,    -1,
      47,     6,    48,     8,    51,    52,    53,    -1,    55,    56,
      57,    16,    -1,    -1,    19,    -1,    -1,    -1,    -1,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    34,
      35,    36,    37,    38,    39,     6,    -1,     8,    -1,    -1,
      -1,    -1,    47,    -1,    -1,    16,    -1,    18,    53,    -1,
      55,    56,    57,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    -1,    34,    35,    36,    37,    38,    39,     6,
      -1,     8,    -1,    -1,    -1,    -1,    47,    -1,    -1,    16,
      -1,    18,    53,    -1,    55,    56,    57,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    -1,    34,    35,    36,
      37,    38,    39,    -1,     6,    -1,     8,    -1,    -1,    -1,
      47,    -1,    -1,    -1,    16,    -1,    53,    19,    55,    56,
      57,    -1,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    -1,    34,    35,    36,    37,    38,    39,     6,    -1,
       8,    -1,    -1,    -1,    -1,    47,    -1,    -1,    16,    -1,
      18,    53,    -1,    55,    56,    57,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    -1,    34,    35,    36,    37,
      38,    39,     6,    -1,     8,    -1,    -1,    -1,    -1,    47,
      -1,    -1,    16,    -1,    18,    53,    -1,    55,    56,    57,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,
      34,    35,    36,    37,    38,    39,     6,    -1,     8,    -1,
      -1,    -1,    -1,    47,    -1,    -1,    16,    -1,    18,    53,
      -1,    55,    56,    57,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    -1,    34,    35,    36,    37,    38,    39,
      -1,     6,    -1,     8,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    16,     6,    53,    19,    55,    56,    57,    -1,    24,
      25,    -1,    16,    -1,    -1,    -1,    -1,    32,    -1,    34,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    32,    -1,
      34,    35,    47,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      55,    56,    57,    -1,    -1,    -1,    -1,    -1,    20,    21,
      22,    -1,    56,    57,    26,    27,    28,    29,    30,    31,
      -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    25,    35,    36,    60,    61,    62,    63,    64,    65,
      66,    73,    35,    35,    35,     0,    61,    37,    37,    37,
      37,    18,     7,    16,    49,    35,    74,    75,     6,    16,
      32,    34,    35,    56,    57,    76,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    36,
      67,    89,     7,    19,    23,    95,    90,    95,    16,    49,
      95,    95,    10,    48,    11,    13,    12,    14,    15,    40,
      41,    42,    43,    48,    44,    45,     5,     6,     3,     4,
      46,    56,    57,    35,    17,    50,    89,    74,    17,    77,
      89,    89,    90,    90,    84,    85,    86,    87,    88,    91,
      91,    91,    91,    91,    92,    92,    93,    93,    95,    95,
      95,    23,    18,    17,    23,    50,    67,     8,    19,    24,
      35,    36,    37,    38,    39,    47,    53,    55,    65,    66,
      68,    69,    70,    71,    72,    73,    76,    78,    79,    80,
      83,    89,    95,    77,    16,     7,    35,    16,    16,    89,
      16,    37,    37,    19,    37,    37,    68,    37,    37,    37,
       7,    37,    20,    21,    22,    26,    27,    28,    29,    30,
      31,    33,    89,    35,    72,    89,    89,    72,    37,    89,
      89,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    17,    17,    37,    17,    18,    68,    18,    68,    89,
      18,    68,     9,    19,    68,    37,    51,    52,    68,    81,
      82,    19,    18,    68,    19,    72,    89,    54,    81,    19,
      81,     9,    68,    17,    54,    68,    18,    68,    19,    18,
      68,    68,    68,    19,    68,    19,    19
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    60,    61,    61,    62,    62,    62,    62,    62,
      63,    64,    64,    65,    65,    65,    66,    67,    67,    67,
      68,    68,    69,    70,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    73,
      74,    74,    74,    75,    75,    76,    77,    77,    77,    78,
      79,    79,    79,    79,    79,    79,    80,    80,    80,    80,
      80,    80,    80,    81,    81,    81,    81,    82,    82,    83,
      84,    84,    84,    85,    85,    86,    86,    87,    87,    88,
      88,    89,    89,    90,    90,    90,    90,    90,    90,    91,
      91,    91,    92,    92,    92,    93,    93,    93,    93,    93,
      93,    93,    93,    94,    94,    95,    95,    95,    95,    95,
      95
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     2,     2,     2,     1,
       5,     8,     7,     2,     4,     2,     5,     4,     2,     0,
       1,     2,     1,     1,     1,     2,     2,     2,     2,     2,
       1,     2,     1,     1,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     5,
       1,     2,     3,     3,     1,     4,     3,     1,     0,     3,
       5,     7,     6,     9,    11,    10,     5,     7,     9,     9,
       7,    11,     7,     1,     2,     2,     0,     4,     3,     4,
       1,     3,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     2,     2,     2,     2,     3,
       3,     3,     1,     2,     2,     1,     3,     1,     1,     1,
       1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 45 "parser.y" /* yacc.c:1646  */
    {g_root = (yyvsp[0].prog);}
#line 1532 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 48 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = (yyvsp[0].prog);std::cerr << "HELLO THIS IS THE BEGINNING\n";}
#line 1538 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 49 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new Program((yyvsp[-1].prog), (yyvsp[0].prog));}
#line 1544 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 52 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = (yyvsp[-1].prog);}
#line 1550 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 53 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = (yyvsp[-1].prog);}
#line 1556 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 54 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = (yyvsp[-1].prog);}
#line 1562 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 55 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = (yyvsp[-1].prog);}
#line 1568 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 56 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = (yyvsp[0].prog);}
#line 1574 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 59 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new FunctionDeclaration((yyvsp[-3].string)[0], (yyvsp[-1].prog));}
#line 1580 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 62 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new FunctionDefinition((yyvsp[-7].string)[0], (yyvsp[-6].string)[0], (yyvsp[-4].prog), (yyvsp[-1].prog));std::cerr<< "function definition " << (yyvsp[-6].string)[0] << "\n";}
#line 1586 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 63 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new FunctionDefinition((yyvsp[-6].string)[0], (yyvsp[-5].string)[0], (yyvsp[-3].prog));std::cerr<< "function definition " << (yyvsp[-5].string)[0] << "\n";}
#line 1592 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 66 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new VariableDeclaration((yyvsp[-1].string)[0], (yyvsp[0].string)[0]);}
#line 1598 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 67 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new VariableDeclaration((yyvsp[-3].string)[0], (yyvsp[-2].string)[0], (yyvsp[0].expr));}
#line 1604 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 68 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new VariableDeclaration((yyvsp[0].string)[0]);/*enum instantiation*/}
#line 1610 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 70 "parser.y" /* yacc.c:1646  */
    {std::cerr << "array declared\n";(yyval.prog) = new ArrayDeclaration((yyvsp[-4].string)[0], (yyvsp[-3].string)[0], (yyvsp[-1].expr));}
#line 1616 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 73 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new ParameterList((yyvsp[-3].string)[0], (yyvsp[-2].string)[0], (yyvsp[0].prog));}
#line 1622 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 74 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new ParameterList((yyvsp[-1].string)[0], (yyvsp[0].string)[0]);}
#line 1628 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 75 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new ParameterList();}
#line 1634 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 78 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new StatementList((yyvsp[0].prog));}
#line 1640 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 79 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new StatementList((yyvsp[0].prog), (yyvsp[-1].prog));}
#line 1646 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 82 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new BreakStatement();}
#line 1652 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 85 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new ContinueStatement();}
#line 1658 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 88 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = (yyvsp[0].prog);}
#line 1664 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 89 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = (yyvsp[-1].prog);std::cerr << "whanew1\n";}
#line 1670 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 90 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = (yyvsp[-1].prog);std::cerr << "whanew2\n";}
#line 1676 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 91 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = (yyvsp[-1].prog);std::cerr << "whanew3\n";}
#line 1682 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 92 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = (yyvsp[-1].prog);std::cerr << "whanew4\n";}
#line 1688 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 93 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = (yyvsp[-1].prog);std::cerr << "whanew5\n";}
#line 1694 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 94 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = (yyvsp[0].prog);std::cerr << "whanew6\n";}
#line 1700 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 95 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = (yyvsp[-1].prog);std::cerr << "whanew7\n";}
#line 1706 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 96 "parser.y" /* yacc.c:1646  */
    {;std::cerr << "whanew8\n";}
#line 1712 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 97 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = (yyvsp[0].prog);std::cerr << "whanew9\n";}
#line 1718 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 98 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = (yyvsp[-1].expr);std::cerr << "wnew10\n";}
#line 1724 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 99 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = (yyvsp[-1].expr);std::cerr << "whanew11\n";}
#line 1730 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 107 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new Assignment((yyvsp[-2].string)[0], (yyvsp[0].prog)); /*std::cerr << "the identifer found is " << $1[0] << "\n";*/}
#line 1736 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 108 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new Assignment((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1742 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 109 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new PlusEquals ((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1748 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 110 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new MinusEquals ((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1754 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 111 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new TimesEquals ((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1760 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 112 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new DivEquals ((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1766 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 113 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new ModEquals ((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1772 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 114 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new AndEquals ((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1778 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 115 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new OrEquals ((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1784 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 116 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new XorEquals ((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1790 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 117 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new LShiftEquals ((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1796 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 118 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new RShiftEquals ((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1802 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 120 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = (yyvsp[0].expr);}
#line 1808 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 123 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new EnumerationSpecifier((yyvsp[-3].string)[0], (yyvsp[-1].prog));}
#line 1814 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 126 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new EnumeratorList((yyvsp[0].prog));}
#line 1820 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 127 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new EnumeratorList((yyvsp[-1].prog));}
#line 1826 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 128 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new EnumeratorList((yyvsp[-2].prog), (yyvsp[0].prog));}
#line 1832 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 131 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new Enumerator((yyvsp[-2].string)[0], (yyvsp[0].expr));}
#line 1838 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 132 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new Enumerator((yyvsp[0].string)[0]);}
#line 1844 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 135 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new FunctionCall((yyvsp[-3].string)[0], (yyvsp[-1].prog)); std::cerr << "functioncall with identifier "<< (yyvsp[-3].string)[0] << "\n";}
#line 1850 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 138 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new ConcreteParameterList ((yyvsp[-2].expr), (yyvsp[0].prog));}
#line 1856 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 139 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new ConcreteParameterList ((yyvsp[0].expr));}
#line 1862 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 140 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new ConcreteParameterList();}
#line 1868 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 143 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new ReturnStatement((yyvsp[-1].expr));}
#line 1874 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 146 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new WhileLoop((yyvsp[-2].expr), (yyvsp[0].prog));}
#line 1880 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 147 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new WhileLoop((yyvsp[-4].expr), (yyvsp[-1].prog));}
#line 1886 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 148 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new WhileLoop((yyvsp[-3].expr));}
#line 1892 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 149 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new ForLoop((yyvsp[-6].prog), (yyvsp[-4].expr), (yyvsp[-2].prog), (yyvsp[0].prog));}
#line 1898 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 150 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new ForLoop((yyvsp[-8].prog), (yyvsp[-6].expr), (yyvsp[-4].prog), (yyvsp[-1].prog));}
#line 1904 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 151 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new ForLoop((yyvsp[-7].prog), (yyvsp[-5].expr), (yyvsp[-3].prog));}
#line 1910 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 154 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new IfStatement((yyvsp[-2].expr), (yyvsp[0].prog));}
#line 1916 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 155 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new IfStatement((yyvsp[-4].expr), (yyvsp[-2].prog), (yyvsp[0].prog));}
#line 1922 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 156 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new IfStatement((yyvsp[-6].expr), (yyvsp[-3].prog), (yyvsp[0].prog));}
#line 1928 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 157 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new IfStatement((yyvsp[-6].expr), (yyvsp[-4].prog), (yyvsp[-1].prog));}
#line 1934 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 158 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new IfStatement((yyvsp[-4].expr), (yyvsp[-1].prog));}
#line 1940 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 159 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new IfStatement((yyvsp[-8].expr), (yyvsp[-5].prog), (yyvsp[-1].prog));}
#line 1946 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 160 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new SwitchStatement((yyvsp[-4].expr), (yyvsp[-1].prog));}
#line 1952 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 163 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new CaseList((yyvsp[0].prog), false);}
#line 1958 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 164 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new CaseList((yyvsp[0].prog), (yyvsp[-1].prog));}
#line 1964 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 165 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new CaseList((yyvsp[0].prog), true);/*we accept statementlists that will never be executed but they don't get put into the tree so they are never compiled*/;}
#line 1970 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 166 "parser.y" /* yacc.c:1646  */
    {new CaseList();}
#line 1976 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 169 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new CaseNode((yyvsp[-2].expr), (yyvsp[0].prog));}
#line 1982 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 170 "parser.y" /* yacc.c:1646  */
    {(yyval.prog) = new CaseNode((yyvsp[0].prog));}
#line 1988 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 173 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new subscriptOperator((yyvsp[-3].string)[0], (yyvsp[-1].expr));}
#line 1994 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 176 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2000 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 177 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new equalsOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2006 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 178 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new notEqualOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2012 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 181 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2018 "parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 182 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new bitWiseAndOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2024 "parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 185 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2030 "parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 186 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new bitWiseEorOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2036 "parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 189 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2042 "parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 190 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new bitWiseIorOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2048 "parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 193 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2054 "parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 194 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new logicalAndOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2060 "parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 197 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2066 "parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 198 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new logicalOrOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2072 "parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 201 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2078 "parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 202 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new ltOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2084 "parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 203 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new gtOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2090 "parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 204 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new lteOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2096 "parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 205 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new gteOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2102 "parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 206 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new equalsOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2108 "parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 209 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2114 "parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 210 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new lShiftOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2120 "parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 211 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new rShiftOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2126 "parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 214 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2132 "parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 215 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new AddOperator((yyvsp[-2].expr), (yyvsp[0].expr)); std::cerr << "PLUSPLUSPLUSPLUS\n\n\n\n\n\n\n\n\n";}
#line 2138 "parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 216 "parser.y" /* yacc.c:1646  */
    { std::cerr << "MINUSMINUSMINUS\n\n\n\n\n\n\n\n\n";(yyval.expr) = new SubOperator((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2144 "parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 219 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new PostIncrement((yyvsp[-1].expr));}
#line 2150 "parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 220 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new PostDecrement((yyvsp[-1].expr));}
#line 2156 "parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 221 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new PreIncrement((yyvsp[0].expr));}
#line 2162 "parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 222 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new PreDecrement((yyvsp[0].expr));}
#line 2168 "parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 223 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new MulOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2174 "parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 224 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new DivOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2180 "parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 225 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new moduloOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2186 "parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 226 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2192 "parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 229 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new NegOperator((yyvsp[0].expr)); std::cerr << "unary minus\n";}
#line 2198 "parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 230 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new NotOperator((yyvsp[0].expr)); std::cerr << "notoperation\n";}
#line 2204 "parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 233 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new Number( (yyvsp[0].string)[0] ); std::cerr << "number\n"; }
#line 2210 "parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 234 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2216 "parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 235 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new Variable((yyvsp[0].string)[0]);}
#line 2222 "parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 236 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2228 "parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 237 "parser.y" /* yacc.c:1646  */
    {std::cerr << "found a function call factor \n";(yyval.expr) = (yyvsp[0].expr);}
#line 2234 "parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 238 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2240 "parser.cpp" /* yacc.c:1646  */
    break;


#line 2244 "parser.cpp" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 243 "parser.y" /* yacc.c:1906  */


Program *g_root; // Definition of variable (to match declaration earlier)

Program *parseAST(char* inputPath)
{
  g_root=0;
  yyin = fopen(inputPath, "r");
  yyparse();
  return g_root;
}
