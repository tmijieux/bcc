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
#line 1 "parser.y" /* yacc.c:339  */

/* grammar by Jutta Degener, 1995 */

#include <stdio.h>
#include <stdlib.h>

#include "function.h"
#include "module.h"
#include "program.h"
#include "codegen.h"
#include "scanner.h"

#include "symbol/symbol.h"
#include "symbol/symbol_table.h"
#include "type/type.h"
#include "type/pointer.h"
#include "type/struct.h"
#include "type/specifier.h"
#include "type/enumerator.h"
#include "type/declarator.h"

#include "constant/constant.h"
#include "expression/expression.h"
#include "statement/statement.h"

#include "errorc.h"
#include "util/list.h"
#include "util/alloc.h"
#include "util/error.h"

extern int yylex();
int check_declaration_specifiers(struct list *declarator_specifiers);

#line 100 "parser.c" /* yacc.c:339  */

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
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN_IDENTIFIER = 258,
    TOKEN_CONSTANT = 259,
    TOKEN_TYPE_NAME = 260,
    TOKEN_PTR_OP = 261,
    TOKEN_INC_OP = 262,
    TOKEN_DEC_OP = 263,
    TOKEN_LEFT_OP = 264,
    TOKEN_RIGHT_OP = 265,
    TOKEN_LE_OP = 266,
    TOKEN_GE_OP = 267,
    TOKEN_EQ_OP = 268,
    TOKEN_NE_OP = 269,
    TOKEN_AND_OP = 270,
    TOKEN_OR_OP = 271,
    TOKEN_MUL_ASSIGN = 272,
    TOKEN_DIV_ASSIGN = 273,
    TOKEN_MOD_ASSIGN = 274,
    TOKEN_ADD_ASSIGN = 275,
    TOKEN_SUB_ASSIGN = 276,
    TOKEN_LEFT_ASSIGN = 277,
    TOKEN_RIGHT_ASSIGN = 278,
    TOKEN_AND_ASSIGN = 279,
    TOKEN_XOR_ASSIGN = 280,
    TOKEN_OR_ASSIGN = 281,
    TOKEN_ELLIPSIS = 282,
    TOKEN_TYPEDEF = 283,
    TOKEN_EXTERN = 284,
    TOKEN_STATIC = 285,
    TOKEN_AUTO = 286,
    TOKEN_REGISTER = 287,
    TOKEN_CHAR = 288,
    TOKEN_SHORT = 289,
    TOKEN_INT = 290,
    TOKEN_LONG = 291,
    TOKEN_SIGNED = 292,
    TOKEN_UNSIGNED = 293,
    TOKEN_FLOAT = 294,
    TOKEN_DOUBLE = 295,
    TOKEN_CONST = 296,
    TOKEN_VOLATILE = 297,
    TOKEN_VOID = 298,
    TOKEN_STRUCT = 299,
    TOKEN_UNION = 300,
    TOKEN_ENUM = 301,
    TOKEN_CASE = 302,
    TOKEN_DEFAULT = 303,
    TOKEN_IF = 304,
    TOKEN_ELSE = 305,
    TOKEN_SWITCH = 306,
    TOKEN_WHILE = 307,
    TOKEN_DO = 308,
    TOKEN_FOR = 309,
    TOKEN_GOTO = 310,
    TOKEN_CONTINUE = 311,
    TOKEN_BREAK = 312,
    TOKEN_RETURN = 313,
    TOKEN_SIZEOF = 314
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 136 "parser.y" /* yacc.c:355  */

    char *string;
    char character;
    int integer;
    float fp;
    double doublefp;
    enum type_type type_type;
    struct constant *constant;
    struct symbol *symbol;
    struct function *function;
    struct statement *statement;
    const struct type *type;
    const struct expression *expression;
    struct specifier *specifier;
    struct initializer *initializer;
    struct enumerator *enumerator;
    struct declarator *declarator;
    struct pointer *pointer;
    struct list *list;

#line 221 "parser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 238 "parser.c" /* yacc.c:358  */

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
#define YYFINAL  60
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1173

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  214
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  349

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   314

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    71,     2,     2,     2,    73,    66,     2,
      60,    61,    67,    68,    65,    69,    64,    72,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    79,    81,
      74,    80,    75,    78,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    62,     2,    63,    76,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    82,    77,    83,    70,     2,     2,     2,
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
      55,    56,    57,    58,    59
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   159,   159,   160,   161,   165,   166,   167,   168,   171,
     173,   176,   177,   181,   182,   186,   187,   188,   189,   190,
     191,   195,   196,   197,   198,   199,   200,   204,   205,   209,
     210,   212,   213,   217,   218,   219,   224,   225,   227,   232,
     233,   234,   235,   236,   240,   241,   242,   246,   247,   251,
     252,   256,   257,   261,   262,   267,   268,   273,   274,   279,
     280,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   299,   300,   304,   308,   311,   319,   320,   321,
     323,   324,   325,   329,   330,   334,   335,   339,   340,   341,
     342,   343,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   362,   363,   364,   368,   369,   373,
     374,   378,   382,   383,   384,   385,   389,   390,   394,   395,
     396,   400,   401,   402,   406,   407,   411,   412,   416,   417,
     421,   422,   426,   427,   428,   429,   430,   432,   434,   438,
     439,   440,   441,   445,   446,   450,   451,   457,   458,   462,
     463,   464,   468,   469,   473,   474,   479,   480,   481,   485,
     486,   487,   488,   490,   492,   493,   494,   495,   500,   501,
     502,   506,   507,   511,   512,   513,   514,   515,   516,   520,
     521,   522,   526,   527,   528,   529,   534,   537,   540,   541,
     545,   546,   550,   551,   555,   556,   558,   562,   563,   565,
     567,   572,   573,   574,   575,   576,   580,   581,   585,   586,
     594,   601,   603,   609,   611
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_IDENTIFIER", "TOKEN_CONSTANT",
  "TOKEN_TYPE_NAME", "TOKEN_PTR_OP", "TOKEN_INC_OP", "TOKEN_DEC_OP",
  "TOKEN_LEFT_OP", "TOKEN_RIGHT_OP", "TOKEN_LE_OP", "TOKEN_GE_OP",
  "TOKEN_EQ_OP", "TOKEN_NE_OP", "TOKEN_AND_OP", "TOKEN_OR_OP",
  "TOKEN_MUL_ASSIGN", "TOKEN_DIV_ASSIGN", "TOKEN_MOD_ASSIGN",
  "TOKEN_ADD_ASSIGN", "TOKEN_SUB_ASSIGN", "TOKEN_LEFT_ASSIGN",
  "TOKEN_RIGHT_ASSIGN", "TOKEN_AND_ASSIGN", "TOKEN_XOR_ASSIGN",
  "TOKEN_OR_ASSIGN", "TOKEN_ELLIPSIS", "TOKEN_TYPEDEF", "TOKEN_EXTERN",
  "TOKEN_STATIC", "TOKEN_AUTO", "TOKEN_REGISTER", "TOKEN_CHAR",
  "TOKEN_SHORT", "TOKEN_INT", "TOKEN_LONG", "TOKEN_SIGNED",
  "TOKEN_UNSIGNED", "TOKEN_FLOAT", "TOKEN_DOUBLE", "TOKEN_CONST",
  "TOKEN_VOLATILE", "TOKEN_VOID", "TOKEN_STRUCT", "TOKEN_UNION",
  "TOKEN_ENUM", "TOKEN_CASE", "TOKEN_DEFAULT", "TOKEN_IF", "TOKEN_ELSE",
  "TOKEN_SWITCH", "TOKEN_WHILE", "TOKEN_DO", "TOKEN_FOR", "TOKEN_GOTO",
  "TOKEN_CONTINUE", "TOKEN_BREAK", "TOKEN_RETURN", "TOKEN_SIZEOF", "'('",
  "')'", "'['", "']'", "'.'", "','", "'&'", "'*'", "'+'", "'-'", "'~'",
  "'!'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'", "':'", "'='",
  "';'", "'{'", "'}'", "$accept", "primary_expression",
  "postfix_expression", "argument_expression_list", "unary_expression",
  "unary_operator", "cast_expression", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "declaration", "declaration_specifiers",
  "init_declarator_list", "init_declarator", "storage_class_specifier",
  "type_specifier", "struct_or_union_specifier", "struct_or_union",
  "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "type_qualifier", "declarator", "direct_declarator", "pointer",
  "type_qualifier_list", "parameter_type_list", "parameter_list",
  "parameter_declaration", "identifier_list", "type_name",
  "abstract_declarator", "direct_abstract_declarator", "initializer",
  "initializer_list", "statement", "labeled_statement",
  "compound_statement", "left_brace", "right_brace", "declaration_list",
  "statement_list", "expression_statement", "selection_statement",
  "iteration_statement", "jump_statement", "translation_unit",
  "external_declaration", "function_definition",
  "function_definition_header", YY_NULLPTR
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
      40,    41,    91,    93,    46,    44,    38,    42,    43,    45,
     126,    33,    47,    37,    60,    62,    94,   124,    63,    58,
      61,    59,   123,   125
};
# endif

#define YYPACT_NINF -208

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-208)))

#define YYTABLE_NINF -213

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     940,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,    19,    17,    15,  -208,   116,  1085,  1085,  -208,    22,
    -208,  1085,  1085,     1,    40,   852,  -208,  -208,   -51,   -27,
      16,    26,  -208,  -208,    15,  -208,   -42,  -208,   576,  -208,
    -208,    -4,  1127,  -208,  -208,   116,  1085,   805,   383,     1,
    -208,  -208,   -11,  -208,   427,    16,    27,   -39,  -208,  -208,
    -208,  -208,    17,  -208,   218,  1085,  1127,  1127,   485,  -208,
     148,  1127,    77,  -208,  -208,  -208,    64,    32,    55,  -208,
      -7,  -208,  -208,   754,   754,   794,   641,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,   182,  -208,   808,  -208,   178,
     -16,   265,    36,   266,   111,    89,    95,   184,    11,  -208,
     144,  -208,   130,   808,   140,   183,   192,   204,   496,   221,
     226,   157,   160,   308,  -208,   284,  -208,  -208,    48,  -208,
    -208,  -208,   289,   358,  -208,  -208,  -208,  -208,   -37,   808,
      16,  -208,  -208,   218,  -208,  -208,   552,  -208,  -208,  -208,
     808,   133,  -208,   216,  -208,   896,   656,  -208,    68,  -208,
      13,  -208,  1066,  -208,   259,   808,  -208,  -208,   641,  -208,
      99,    92,   222,   287,  -208,  -208,   685,   808,   311,  -208,
     808,   808,   808,   808,   808,   808,   808,   808,   808,   808,
     808,   808,   808,   808,   808,   808,   808,   808,   808,  -208,
     496,   260,   496,   808,   808,   808,   302,   572,   282,  -208,
    -208,  -208,   152,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,   808,   808,  -208,  -208,  -208,   358,
    -208,  -208,  -208,  -208,  -208,  -208,   -14,  -208,  -208,   148,
    -208,   808,  -208,   312,   323,  -208,   306,    13,  1024,   710,
    -208,  -208,  -208,   324,  -208,   982,    65,  -208,   808,  -208,
    -208,   106,  -208,   121,  -208,  -208,  -208,  -208,   178,   178,
     -16,   -16,   265,   265,   265,   265,    36,    36,   266,   111,
      89,    95,   184,   -15,  -208,   496,  -208,   167,   169,   202,
     328,   572,  -208,  -208,  -208,  -208,  -208,   188,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,   331,  -208,   330,  -208,  -208,
    -208,   808,  -208,   808,  -208,   496,   496,   496,   808,   725,
    -208,  -208,  -208,  -208,  -208,  -208,   344,  -208,  -208,   208,
     496,   211,   496,   314,  -208,   496,  -208,  -208,  -208
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   132,   103,    87,    88,    89,    90,    91,    93,    94,
      95,    96,    99,   100,    97,    98,   128,   129,    92,   107,
     108,     0,     0,   139,   209,     0,    77,    79,   101,     0,
     102,    78,   214,   131,     0,     0,   206,   208,     0,   123,
       0,     0,   143,   141,   140,    75,     0,    83,    85,    80,
      81,   106,     0,    82,   188,     0,   213,     0,     0,   130,
       1,   207,   186,   210,     0,     0,   126,     0,   124,   133,
     144,   142,     0,    76,     0,   211,     0,   113,     0,   109,
       0,   115,    85,   189,   152,   138,   151,     0,   145,   147,
       0,     2,     3,     0,     0,     0,     0,   135,    21,    22,
      23,    24,    25,    26,     5,    15,    27,     0,    29,    33,
      36,    39,    44,    47,    49,    51,    53,    55,    57,    74,
       0,   182,     2,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   192,    27,    59,    72,     0,   190,
     173,   174,     0,     0,   175,   176,   177,   178,     0,     0,
       0,   121,    84,     0,   168,    86,     0,   112,   105,   110,
       0,     0,   116,   118,   114,     0,     0,   149,   156,   150,
     157,   136,     0,   137,     0,     0,    16,    17,     0,    19,
       0,   154,     0,     0,    11,    12,     0,     0,     0,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   134,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   202,
     203,   204,     0,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    61,     0,     0,   193,   187,   184,     0,
     191,   183,   122,   127,   125,   171,     0,   104,   119,     0,
     111,     0,   164,     0,     0,   160,     0,   158,     0,     0,
     146,   148,   153,     0,     4,     0,   156,   155,     0,    10,
       7,     0,    13,     0,     9,    30,    31,    32,    34,    35,
      37,    38,    42,    43,    40,    41,    45,    46,    48,    50,
      52,    54,    56,     0,   179,     0,   181,     0,     0,     0,
       0,     0,   201,   205,    60,    73,   185,     0,   169,   117,
     120,   165,   159,   161,   166,     0,   162,     0,    20,    28,
       8,     0,     6,     0,   180,     0,     0,     0,     0,     0,
     170,   172,   167,   163,    14,    58,   194,   196,   197,     0,
       0,     0,     0,     0,   199,     0,   195,   198,   200
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -208,  -208,  -208,  -208,   -58,  -208,   -94,   105,   185,   153,
     181,   193,   194,   195,   191,   196,  -208,   -57,   -72,  -208,
     -92,   -81,    24,     3,  -208,   327,  -208,   104,  -208,  -208,
     325,   -38,   -63,  -208,   155,  -208,   337,   258,   135,   -10,
     -18,   -12,  -208,   -52,  -208,   247,  -208,   242,   -69,  -160,
    -146,  -208,  -122,  -208,   384,  -208,  -134,   176,   279,  -207,
    -208,  -208,  -208,  -208,   388,  -208,  -208
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   104,   105,   271,   135,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   136,   137,   234,
     138,   120,    54,    55,    46,    47,    26,    27,    28,    29,
      78,    79,    80,   161,   162,    30,    67,    68,    31,    32,
      33,    34,    44,   253,    88,    89,    90,   182,   254,   170,
     155,   246,   139,   140,   141,    64,   238,    56,   143,   144,
     145,   146,   147,    35,    36,    37,    38
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     106,   119,   154,    25,   180,    87,   216,   245,   257,   241,
     301,    43,    41,   189,   157,    48,    59,   169,   164,    66,
       1,   240,    39,    72,    24,    51,   150,   207,   150,    49,
      50,    62,    71,   181,    53,   176,   177,   179,    25,    73,
     159,   222,   211,     1,   151,    82,   242,   197,   198,   106,
     235,   307,   193,   194,   173,    65,    16,    17,   174,    24,
      86,    57,    82,    58,   323,   106,   119,     1,   243,   308,
     163,     1,   121,   258,   168,   259,   167,    22,    76,   248,
      83,   154,    23,   180,    23,   256,   180,    69,   294,   208,
     296,   106,   119,   171,   329,   273,   275,   276,   277,    83,
      22,    40,   106,   119,    52,   306,   257,   149,   106,   119,
     199,   200,   267,   235,   272,   181,   293,   240,   159,     1,
     172,   297,   298,   299,   165,   265,   166,   166,   165,   236,
     166,    23,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
      59,     1,   265,   168,   166,    41,    77,    74,    42,    23,
     264,   331,   304,   305,   235,   204,    83,   320,    86,   266,
     310,   321,   205,   324,   319,    86,    22,   203,   317,    70,
      77,    77,    77,    23,   322,    77,   235,    81,   183,   184,
     185,    91,    92,   106,   119,    93,    94,    45,   249,   206,
      77,   106,   119,   336,   337,   338,   315,   209,    22,   210,
     106,    81,    81,    81,   250,    23,    81,   235,   344,   212,
     346,    91,    92,   348,    75,    93,    94,   160,   325,   218,
     326,    81,   235,   303,   235,   154,   339,   341,   219,   163,
     142,   220,   186,   213,   187,   190,   188,    95,    96,   334,
     191,   192,   214,   266,    98,    99,   100,   101,   102,   103,
      77,    86,   262,   327,   215,   106,   335,   235,    86,   343,
     153,   330,   345,   235,   195,   196,   235,    95,    96,   201,
     202,   217,    77,   268,    98,    99,   100,   101,   102,   103,
     269,    81,   122,    92,     2,   251,    93,    94,   278,   279,
     153,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,    91,    92,    81,   274,    93,    94,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,   123,   124,   125,   295,
     126,   127,   128,   129,   130,   131,   132,   133,    95,    96,
     282,   283,   284,   285,   300,    98,    99,   100,   101,   102,
     103,   122,    92,   302,   233,    93,    94,    95,    96,   313,
     134,    62,   237,   311,    98,    99,   100,   101,   102,   103,
     280,   281,   286,   287,   312,   318,    91,    92,   328,   221,
      93,    94,   332,   333,   342,   347,   288,   291,   289,   152,
     290,   156,   148,   292,   309,   123,   124,   125,   244,   126,
     127,   128,   129,   130,   131,   132,   133,    95,    96,   261,
     263,   239,    63,    61,    98,    99,   100,   101,   102,   103,
     122,    92,     2,     0,    93,    94,     0,     0,     0,   134,
      62,   237,    95,    96,     0,     0,    97,     0,     0,    98,
      99,   100,   101,   102,   103,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,   123,   124,   125,     0,   126,   127,
     128,   129,   130,   131,   132,   133,    95,    96,     0,     0,
       2,     0,     0,    98,    99,   100,   101,   102,   103,   122,
      92,     0,     0,    93,    94,     0,     0,     0,   134,    62,
       0,     0,     0,     0,     0,     0,     0,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   123,   124,   125,     0,   126,   127,   128,
     129,   130,   131,   132,   133,    95,    96,     2,     0,     0,
       0,     0,    98,    99,   100,   101,   102,   103,   158,     0,
       0,     0,     0,     0,     0,    91,    92,   134,    62,    93,
      94,     2,     0,     0,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     0,
       0,     0,     0,     0,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     0,     0,     0,     0,     0,     0,     0,
       0,    95,    96,     0,     0,   247,     0,     0,    98,    99,
     100,   101,   102,   103,    91,    92,     2,     0,    93,    94,
       0,     0,     0,   134,     0,     0,    74,     0,  -212,    91,
      92,     0,     0,    93,    94,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    91,    92,
       0,     0,    93,    94,     0,     0,     0,     0,     0,     0,
      95,    96,     0,     0,     0,     0,     0,    98,    99,   100,
     101,   102,   103,    91,    92,    95,    96,    93,    94,   255,
       0,     0,    98,    99,   100,   101,   102,   103,    91,    92,
       0,     0,    93,    94,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    95,    96,   270,     0,     0,     0,
       0,    98,    99,   100,   101,   102,   103,    91,    92,     0,
       0,    93,    94,     0,     0,     0,     0,     0,     0,    95,
      96,     0,     0,   316,     0,     0,    98,    99,   100,   101,
     102,   103,     0,     0,    95,    96,   340,     0,     0,     0,
       0,    98,    99,   100,   101,   102,   103,    91,    92,     0,
       0,    93,    94,     0,     0,     0,     0,     0,    84,     0,
       2,    91,    92,    95,   175,    93,    94,     0,     0,     0,
      98,    99,   100,   101,   102,   103,     0,     0,     0,     0,
       0,     0,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    60,    95,   178,     1,     0,     2,     0,     0,
      98,    99,   100,   101,   102,   103,    85,    95,    96,     0,
       0,     0,     0,     0,    98,    99,   100,   101,   102,   103,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     1,
       0,     2,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    22,     0,     0,     0,     0,     0,     0,    23,
       0,     0,     0,     0,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     1,     0,     2,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   165,   252,   166,     0,
       0,     0,     0,    23,     0,     0,     0,     0,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     2,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      22,     0,     0,     0,     0,     0,     0,    23,     0,     0,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     2,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   265,   252,   166,     0,     0,     0,     0,    23,
       0,     0,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     2,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   314,     0,     0,     0,     0,
       2,     0,     0,   260,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,     2,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21
};

static const yytype_int16 yycheck[] =
{
      58,    58,    74,     0,    96,    57,   128,   153,   168,   143,
     217,    23,    22,   107,    77,    25,    34,    86,    81,     3,
       3,   143,     3,    65,     0,     3,    65,    16,    65,    26,
      27,    82,    44,    96,    31,    93,    94,    95,    35,    81,
      78,   133,   123,     3,    83,    55,    83,    11,    12,   107,
      65,    65,    68,    69,    61,    82,    41,    42,    65,    35,
      57,    60,    72,    62,    79,   123,   123,     3,   149,    83,
      80,     3,    83,    60,    86,    62,    86,    60,    82,   160,
      56,   153,    67,   175,    67,   166,   178,    61,   210,    78,
     212,   149,   149,    61,   301,   187,   190,   191,   192,    75,
      60,    82,   160,   160,    82,   239,   266,    80,   166,   166,
      74,    75,   181,    65,   186,   178,   208,   239,   156,     3,
      65,   213,   214,   215,    60,    60,    62,    62,    60,    81,
      62,    67,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     168,     3,    60,   165,    62,   165,    52,    80,    23,    67,
      61,   307,   234,   235,    65,    76,   142,    61,   165,   181,
     251,    65,    77,   295,   268,   172,    60,    66,   259,    44,
      76,    77,    78,    67,    63,    81,    65,    52,     6,     7,
       8,     3,     4,   251,   251,     7,     8,    81,    65,    15,
      96,   259,   259,   325,   326,   327,   258,    63,    60,    79,
     268,    76,    77,    78,    81,    67,    81,    65,   340,    79,
     342,     3,     4,   345,    48,     7,     8,    79,    61,     3,
      61,    96,    65,    81,    65,   307,   328,   329,    81,   249,
      64,    81,    60,    60,    62,    67,    64,    59,    60,   321,
      72,    73,    60,   265,    66,    67,    68,    69,    70,    71,
     156,   258,     3,    61,    60,   323,   323,    65,   265,    61,
      82,    83,    61,    65,     9,    10,    65,    59,    60,    13,
      14,    60,   178,    61,    66,    67,    68,    69,    70,    71,
       3,   156,     3,     4,     5,    79,     7,     8,   193,   194,
      82,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,     3,     4,   178,     3,     7,     8,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    79,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
     197,   198,   199,   200,    52,    66,    67,    68,    69,    70,
      71,     3,     4,    81,    80,     7,     8,    59,    60,    63,
      81,    82,    83,    61,    66,    67,    68,    69,    70,    71,
     195,   196,   201,   202,    61,    61,     3,     4,    60,    81,
       7,     8,    61,    63,    50,    81,   203,   206,   204,    72,
     205,    76,    65,   207,   249,    47,    48,    49,   150,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,   172,
     178,   142,    38,    35,    66,    67,    68,    69,    70,    71,
       3,     4,     5,    -1,     7,     8,    -1,    -1,    -1,    81,
      82,    83,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    68,    69,    70,    71,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    -1,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
       5,    -1,    -1,    66,    67,    68,    69,    70,    71,     3,
       4,    -1,    -1,     7,     8,    -1,    -1,    -1,    81,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    49,    -1,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,     5,    -1,    -1,
      -1,    -1,    66,    67,    68,    69,    70,    71,    83,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,    81,    82,     7,
       8,     5,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    59,    60,    -1,    -1,    83,    -1,    -1,    66,    67,
      68,    69,    70,    71,     3,     4,     5,    -1,     7,     8,
      -1,    -1,    -1,    81,    -1,    -1,    80,    -1,    82,     3,
       4,    -1,    -1,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,     3,     4,
      -1,    -1,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,
      69,    70,    71,     3,     4,    59,    60,     7,     8,    63,
      -1,    -1,    66,    67,    68,    69,    70,    71,     3,     4,
      -1,    -1,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    60,    61,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    71,     3,     4,    -1,
      -1,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    59,
      60,    -1,    -1,    63,    -1,    -1,    66,    67,    68,    69,
      70,    71,    -1,    -1,    59,    60,    61,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    71,     3,     4,    -1,
      -1,     7,     8,    -1,    -1,    -1,    -1,    -1,     3,    -1,
       5,     3,     4,    59,    60,     7,     8,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,     0,    59,    60,     3,    -1,     5,    -1,    -1,
      66,    67,    68,    69,    70,    71,    61,    59,    60,    -1,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,    71,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,     3,
      -1,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,     3,    -1,     5,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,     5,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,     5,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    62,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,
       5,    -1,    -1,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    60,    67,   106,   107,   110,   111,   112,   113,
     119,   122,   123,   124,   125,   147,   148,   149,   150,     3,
      82,   123,   122,   125,   126,    81,   108,   109,   123,   107,
     107,     3,    82,   107,   106,   107,   141,    60,    62,   124,
       0,   148,    82,   138,   139,    82,     3,   120,   121,    61,
     122,   125,    65,    81,    80,   141,    82,   111,   114,   115,
     116,   122,   123,   106,     3,    61,   107,   127,   128,   129,
     130,     3,     4,     7,     8,    59,    60,    63,    66,    67,
      68,    69,    70,    71,    85,    86,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     105,    83,     3,    47,    48,    49,    51,    52,    53,    54,
      55,    56,    57,    58,    81,    88,   101,   102,   104,   136,
     137,   138,   141,   142,   143,   144,   145,   146,   120,    80,
      65,    83,   109,    82,   102,   134,   114,   116,    83,   115,
      79,   117,   118,   123,   116,    60,    62,   123,   125,   132,
     133,    61,    65,    61,    65,    60,    88,    88,    60,    88,
     104,   116,   131,     6,     7,     8,    60,    62,    64,    90,
      67,    72,    73,    68,    69,     9,    10,    11,    12,    74,
      75,    13,    14,    66,    76,    77,    15,    16,    78,    63,
      79,   105,    79,    60,    60,    60,   136,    60,     3,    81,
      81,    81,   104,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    80,   103,    65,    81,    83,   140,   142,
     136,   140,    83,   105,   121,   134,   135,    83,   105,    65,
      81,    79,    61,   127,   132,    63,   105,   133,    60,    62,
      27,   129,     3,   131,    61,    60,   125,   132,    61,     3,
      61,    87,   102,   104,     3,    90,    90,    90,    91,    91,
      92,    92,    93,    93,    93,    93,    94,    94,    95,    96,
      97,    98,    99,   104,   136,    79,   136,   104,   104,   104,
      52,   143,    81,    81,   102,   102,   140,    65,    83,   118,
     105,    61,    61,    63,    61,   127,    63,   105,    61,    90,
      61,    65,    63,    79,   136,    61,    61,    61,    60,   143,
      83,   134,    61,    63,   102,   101,   136,   136,   136,   104,
      61,   104,    50,    61,   136,    61,   136,    81,   136
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    84,    85,    85,    85,    86,    86,    86,    86,    86,
      86,    86,    86,    87,    87,    88,    88,    88,    88,    88,
      88,    89,    89,    89,    89,    89,    89,    90,    90,    91,
      91,    91,    91,    92,    92,    92,    93,    93,    93,    94,
      94,    94,    94,    94,    95,    95,    95,    96,    96,    97,
      97,    98,    98,    99,    99,   100,   100,   101,   101,   102,
     102,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   104,   104,   105,   106,   106,   107,   107,   107,
     107,   107,   107,   108,   108,   109,   109,   110,   110,   110,
     110,   110,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   112,   112,   112,   113,   113,   114,
     114,   115,   116,   116,   116,   116,   117,   117,   118,   118,
     118,   119,   119,   119,   120,   120,   121,   121,   122,   122,
     123,   123,   124,   124,   124,   124,   124,   124,   124,   125,
     125,   125,   125,   126,   126,   127,   127,   128,   128,   129,
     129,   129,   130,   130,   131,   131,   132,   132,   132,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   134,   134,
     134,   135,   135,   136,   136,   136,   136,   136,   136,   137,
     137,   137,   138,   138,   138,   138,   139,   140,   141,   141,
     142,   142,   143,   143,   144,   144,   144,   145,   145,   145,
     145,   146,   146,   146,   146,   146,   147,   147,   148,   148,
     149,   150,   150,   150,   150
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     4,     3,     4,     3,
       3,     2,     2,     1,     3,     1,     2,     2,     2,     2,
       4,     1,     1,     1,     1,     1,     1,     1,     4,     1,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     5,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     2,     3,     1,     1,     1,
       2,     2,     2,     1,     3,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     4,     2,     1,     1,     1,
       2,     3,     2,     1,     2,     1,     1,     3,     1,     2,
       3,     4,     5,     2,     1,     3,     1,     3,     1,     1,
       2,     1,     1,     3,     4,     3,     4,     4,     3,     1,
       2,     2,     3,     1,     2,     1,     3,     1,     3,     2,
       2,     1,     1,     3,     1,     2,     1,     1,     2,     3,
       2,     3,     3,     4,     2,     3,     3,     4,     1,     3,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       4,     3,     2,     3,     3,     4,     1,     1,     1,     2,
       1,     2,     1,     2,     5,     7,     5,     5,     7,     6,
       7,     3,     2,     2,     2,     3,     1,     2,     1,     1,
       2,     3,     2,     2,     1
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
#line 159 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_symbol(m, (yyvsp[0].string)); }
#line 1767 "parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 160 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_constant((yyvsp[0].constant)); }
#line 1773 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 161 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[-1].expression); }
#line 1779 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 165 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 1785 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 166 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_array((yyvsp[-3].expression), (yyvsp[-1].expression)); }
#line 1791 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 167 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_funcall((yyvsp[-2].expression), list_new(0)); }
#line 1797 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 169 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_funcall((yyvsp[-3].expression), (yyvsp[-1].list)); }
#line 1803 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 171 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_struct_access((yyvsp[-2].expression), (yyvsp[0].string)); }
#line 1809 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 174 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_struct_deref((yyvsp[-2].expression), (yyvsp[0].string)); }
#line 1815 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 176 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_post_inc((yyvsp[-1].expression)); }
#line 1821 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 177 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_post_dec((yyvsp[-1].expression)); }
#line 1827 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 181 "parser.y" /* yacc.c:1646  */
    { (yyval.list) = list_new(LI_ELEM, (yyvsp[0].expression), NULL); }
#line 1833 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 182 "parser.y" /* yacc.c:1646  */
    { list_append((yyval.list) = (yyvsp[-2].list), (yyvsp[0].expression)); }
#line 1839 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 186 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 1845 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 187 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_pre_inc((yyvsp[0].expression)); }
#line 1851 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 188 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_pre_dec((yyvsp[0].expression)); }
#line 1857 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 189 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_unary((yyvsp[-1].character), (yyvsp[0].expression)); }
#line 1863 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 190 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_sizeof_expr((yyvsp[0].expression)); }
#line 1869 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 191 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_sizeof_typename((yyvsp[-1].type)); }
#line 1875 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 195 "parser.y" /* yacc.c:1646  */
    { (yyval.character) = '&'; }
#line 1881 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 196 "parser.y" /* yacc.c:1646  */
    { (yyval.character) = '*'; }
#line 1887 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 197 "parser.y" /* yacc.c:1646  */
    { (yyval.character) = '+'; }
#line 1893 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 198 "parser.y" /* yacc.c:1646  */
    { (yyval.character) = '-'; }
#line 1899 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 199 "parser.y" /* yacc.c:1646  */
    { (yyval.character) = '~'; }
#line 1905 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 200 "parser.y" /* yacc.c:1646  */
    { (yyval.character) = '!'; }
#line 1911 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 204 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 1917 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 205 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_cast((yyvsp[0].expression), (yyvsp[-2].type)); }
#line 1923 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 209 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 1929 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 211 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_multiplication((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1935 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 212 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_division((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1941 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 213 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_modulo((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1947 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 217 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 1953 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 218 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_addition((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1959 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 220 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_substraction((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1965 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 224 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 1971 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 226 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_shift_left((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1977 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 228 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_shift_right((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1983 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 232 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 1989 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 233 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_lower((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1995 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 234 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_greater((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2001 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 235 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_leq((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2007 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 236 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_geq((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2013 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 240 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 2019 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 241 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_eq((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2025 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 242 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_neq((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2031 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 246 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 2037 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 247 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_and((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2043 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 251 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 2049 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 252 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_xor((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2055 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 256 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 2061 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 257 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_or((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2067 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 261 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 2073 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 263 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_logical_and((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2079 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 267 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 2085 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 269 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_logical_or((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2091 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 273 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 2097 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 275 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_neq((yyvsp[-4].expression), (yyvsp[-2].expression)); }
#line 2103 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 279 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 2109 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 281 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_assignment((yyvsp[-2].expression), (yyvsp[-1].character), (yyvsp[0].expression)); }
#line 2115 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 285 "parser.y" /* yacc.c:1646  */
    { (yyval.character) = '='; }
#line 2121 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 286 "parser.y" /* yacc.c:1646  */
    { (yyval.character) = '*'; }
#line 2127 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 287 "parser.y" /* yacc.c:1646  */
    { (yyval.character) = '/'; }
#line 2133 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 288 "parser.y" /* yacc.c:1646  */
    { (yyval.character) = '%'; }
#line 2139 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 289 "parser.y" /* yacc.c:1646  */
    { (yyval.character) = '+'; }
#line 2145 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 290 "parser.y" /* yacc.c:1646  */
    { (yyval.character) = '-'; }
#line 2151 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 291 "parser.y" /* yacc.c:1646  */
    { (yyval.character) = '<'; }
#line 2157 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 292 "parser.y" /* yacc.c:1646  */
    { (yyval.character) = '>'; }
#line 2163 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 293 "parser.y" /* yacc.c:1646  */
    { (yyval.character) = '&'; }
#line 2169 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 294 "parser.y" /* yacc.c:1646  */
    { (yyval.character) = '^'; }
#line 2175 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 295 "parser.y" /* yacc.c:1646  */
    { (yyval.character) = '|'; }
#line 2181 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 299 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); }
#line 2187 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 300 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = expr_list((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2193 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 304 "parser.y" /* yacc.c:1646  */
    { /*expr_check_constant($1)*/ (yyval.expression) = (yyvsp[0].expression); }
#line 2199 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 308 "parser.y" /* yacc.c:1646  */
    { (yyval.list) = list_new(0);
     warning("declaration does not declare anything\n");
 }
#line 2207 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 312 "parser.y" /* yacc.c:1646  */
    { declarator_process_list((yyvsp[-2].list), (yyvsp[-1].list), &(yyval.list)); }
#line 2213 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 319 "parser.y" /* yacc.c:1646  */
    { (yyval.list) = list_new(LI_ELEM, (yyvsp[0].specifier), NULL); }
#line 2219 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 320 "parser.y" /* yacc.c:1646  */
    { (yyval.list) = list_new(LI_ELEM, (yyvsp[0].specifier), NULL); }
#line 2225 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 321 "parser.y" /* yacc.c:1646  */
    { (yyval.list) = list_new(LI_ELEM, (yyvsp[0].specifier), NULL); }
#line 2231 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 323 "parser.y" /* yacc.c:1646  */
    { list_append((yyval.list) = (yyvsp[0].list), (yyvsp[-1].specifier)); }
#line 2237 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 324 "parser.y" /* yacc.c:1646  */
    { list_append((yyval.list) = (yyvsp[0].list), (yyvsp[-1].specifier)); }
#line 2243 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 325 "parser.y" /* yacc.c:1646  */
    { list_append((yyval.list) = (yyvsp[0].list), (yyvsp[-1].specifier)); }
#line 2249 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 329 "parser.y" /* yacc.c:1646  */
    { (yyval.list) = list_new(LI_ELEM, (yyvsp[0].declarator), NULL); }
#line 2255 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 330 "parser.y" /* yacc.c:1646  */
    { list_append((yyval.list) = (yyvsp[-2].list), (yyvsp[0].declarator)); }
#line 2261 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 334 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = (yyvsp[0].declarator); }
#line 2267 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 335 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_initializer((yyvsp[-2].declarator), (yyvsp[0].initializer)); }
#line 2273 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 339 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_new(SPEC_TYPEDEF); }
#line 2279 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 340 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_new(SPEC_EXTERN); }
#line 2285 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 341 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_new(SPEC_STATIC); }
#line 2291 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 342 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_new(SPEC_AUTO); }
#line 2297 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 343 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_new(SPEC_REGISTER); }
#line 2303 "parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 347 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_new(SPEC_TYPE_VOID); }
#line 2309 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 348 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_new(SPEC_TYPE_CHAR); }
#line 2315 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 349 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_new(SPEC_TYPE_SHORT); }
#line 2321 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 350 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_new(SPEC_TYPE_INT); }
#line 2327 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 351 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_new(SPEC_TYPE_LONG); }
#line 2333 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 352 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_new(SPEC_TYPE_FLOAT); }
#line 2339 "parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 353 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_new(SPEC_TYPE_DOUBLE); }
#line 2345 "parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 354 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_new(SPEC_TYPE_SIGNED); }
#line 2351 "parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 355 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_new(SPEC_TYPE_UNSIGNED); }
#line 2357 "parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 356 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_new(SPEC_UNIMPLEMENTED); }
#line 2363 "parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 357 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_new(SPEC_UNIMPLEMENTED); }
#line 2369 "parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 358 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_typename((yyvsp[0].string)); }
#line 2375 "parser.c" /* yacc.c:1646  */
    break;

  case 109:
#line 373 "parser.y" /* yacc.c:1646  */
    { (yyval.list) = (yyvsp[0].list); }
#line 2381 "parser.c" /* yacc.c:1646  */
    break;

  case 110:
#line 374 "parser.y" /* yacc.c:1646  */
    { list_append_list((yyval.list) = (yyvsp[-1].list), (yyvsp[0].list)); }
#line 2387 "parser.c" /* yacc.c:1646  */
    break;

  case 111:
#line 378 "parser.y" /* yacc.c:1646  */
    { (yyval.list) = (yyvsp[-1].list); }
#line 2393 "parser.c" /* yacc.c:1646  */
    break;

  case 112:
#line 382 "parser.y" /* yacc.c:1646  */
    { list_append((yyval.list) = (yyvsp[0].list), (yyvsp[-1].specifier)); }
#line 2399 "parser.c" /* yacc.c:1646  */
    break;

  case 113:
#line 383 "parser.y" /* yacc.c:1646  */
    { (yyval.list) = list_new(LI_ELEM, (yyvsp[0].specifier), NULL); }
#line 2405 "parser.c" /* yacc.c:1646  */
    break;

  case 114:
#line 384 "parser.y" /* yacc.c:1646  */
    { list_append((yyval.list) = (yyvsp[0].list), (yyvsp[-1].specifier)); }
#line 2411 "parser.c" /* yacc.c:1646  */
    break;

  case 115:
#line 385 "parser.y" /* yacc.c:1646  */
    { (yyval.list) = list_new(LI_ELEM, (yyvsp[0].specifier), NULL); }
#line 2417 "parser.c" /* yacc.c:1646  */
    break;

  case 116:
#line 389 "parser.y" /* yacc.c:1646  */
    { (yyval.list) = list_new(LI_ELEM, (yyvsp[0].declarator), NULL); }
#line 2423 "parser.c" /* yacc.c:1646  */
    break;

  case 117:
#line 390 "parser.y" /* yacc.c:1646  */
    { list_append((yyval.list) = (yyvsp[-2].list), (yyvsp[0].declarator)); }
#line 2429 "parser.c" /* yacc.c:1646  */
    break;

  case 118:
#line 394 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_struct_field((yyvsp[0].declarator), void_expression); }
#line 2435 "parser.c" /* yacc.c:1646  */
    break;

  case 119:
#line 395 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_struct_field(NULL, (yyvsp[0].expression)); }
#line 2441 "parser.c" /* yacc.c:1646  */
    break;

  case 120:
#line 396 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_struct_field((yyvsp[-2].declarator), (yyvsp[0].expression)); }
#line 2447 "parser.c" /* yacc.c:1646  */
    break;

  case 124:
#line 406 "parser.y" /* yacc.c:1646  */
    { (yyval.list) = list_new(LI_ELEM, (yyvsp[0].enumerator), NULL); }
#line 2453 "parser.c" /* yacc.c:1646  */
    break;

  case 125:
#line 407 "parser.y" /* yacc.c:1646  */
    { list_append((yyval.list) = (yyvsp[-2].list), (yyvsp[0].enumerator)); }
#line 2459 "parser.c" /* yacc.c:1646  */
    break;

  case 126:
#line 411 "parser.y" /* yacc.c:1646  */
    { (yyval.enumerator) = enumerator_new((yyvsp[0].string), false, NULL); }
#line 2465 "parser.c" /* yacc.c:1646  */
    break;

  case 127:
#line 412 "parser.y" /* yacc.c:1646  */
    { (yyval.enumerator) = enumerator_new((yyvsp[-2].string), true, (yyvsp[0].expression)); }
#line 2471 "parser.c" /* yacc.c:1646  */
    break;

  case 128:
#line 416 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_new(SPEC_CONST); }
#line 2477 "parser.c" /* yacc.c:1646  */
    break;

  case 129:
#line 417 "parser.y" /* yacc.c:1646  */
    { (yyval.specifier) = specifier_new(SPEC_VOLATILE); }
#line 2483 "parser.c" /* yacc.c:1646  */
    break;

  case 130:
#line 421 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_pointer((yyvsp[0].declarator), (yyvsp[-1].pointer)); }
#line 2489 "parser.c" /* yacc.c:1646  */
    break;

  case 131:
#line 422 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = (yyvsp[0].declarator); }
#line 2495 "parser.c" /* yacc.c:1646  */
    break;

  case 132:
#line 426 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_identifier((yyvsp[0].string)); }
#line 2501 "parser.c" /* yacc.c:1646  */
    break;

  case 133:
#line 427 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = (yyvsp[-1].declarator); }
#line 2507 "parser.c" /* yacc.c:1646  */
    break;

  case 134:
#line 428 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_array((yyvsp[-3].declarator), (yyvsp[-1].expression)); }
#line 2513 "parser.c" /* yacc.c:1646  */
    break;

  case 135:
#line 429 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_array((yyvsp[-2].declarator), void_expression); }
#line 2519 "parser.c" /* yacc.c:1646  */
    break;

  case 136:
#line 431 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_function((yyvsp[-3].declarator), (yyvsp[-1].list)); }
#line 2525 "parser.c" /* yacc.c:1646  */
    break;

  case 137:
#line 433 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_function_old((yyvsp[-3].declarator), (yyvsp[-1].list)); }
#line 2531 "parser.c" /* yacc.c:1646  */
    break;

  case 138:
#line 434 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_function((yyvsp[-2].declarator), list_new(0)); }
#line 2537 "parser.c" /* yacc.c:1646  */
    break;

  case 139:
#line 438 "parser.y" /* yacc.c:1646  */
    { (yyval.pointer) = pointer_new(list_new(0), NULL); }
#line 2543 "parser.c" /* yacc.c:1646  */
    break;

  case 140:
#line 439 "parser.y" /* yacc.c:1646  */
    { (yyval.pointer) = pointer_new((yyvsp[0].list), NULL); }
#line 2549 "parser.c" /* yacc.c:1646  */
    break;

  case 141:
#line 440 "parser.y" /* yacc.c:1646  */
    { (yyval.pointer) = pointer_new(list_new(0), (yyvsp[0].pointer)); }
#line 2555 "parser.c" /* yacc.c:1646  */
    break;

  case 142:
#line 441 "parser.y" /* yacc.c:1646  */
    { (yyval.pointer) = pointer_new((yyvsp[-1].list), (yyvsp[0].pointer)); }
#line 2561 "parser.c" /* yacc.c:1646  */
    break;

  case 143:
#line 445 "parser.y" /* yacc.c:1646  */
    {(yyval.list) = list_new(LI_ELEM, (yyvsp[0].specifier), NULL); }
#line 2567 "parser.c" /* yacc.c:1646  */
    break;

  case 144:
#line 446 "parser.y" /* yacc.c:1646  */
    { list_append((yyval.list) = (yyvsp[-1].list), (yyvsp[0].specifier)); }
#line 2573 "parser.c" /* yacc.c:1646  */
    break;

  case 145:
#line 450 "parser.y" /* yacc.c:1646  */
    { declarator_process_param_list((yyvsp[0].list), &(yyval.list)); }
#line 2579 "parser.c" /* yacc.c:1646  */
    break;

  case 146:
#line 452 "parser.y" /* yacc.c:1646  */
    { declarator_process_param_list((yyvsp[-2].list), &(yyval.list));
  internal_warning("param_list ellipsis not handled "); }
#line 2586 "parser.c" /* yacc.c:1646  */
    break;

  case 147:
#line 457 "parser.y" /* yacc.c:1646  */
    { (yyval.list) = list_new(LI_ELEM, (yyvsp[0].declarator), NULL); }
#line 2592 "parser.c" /* yacc.c:1646  */
    break;

  case 148:
#line 458 "parser.y" /* yacc.c:1646  */
    { list_append((yyval.list) = (yyvsp[-2].list), (yyvsp[0].declarator)); }
#line 2598 "parser.c" /* yacc.c:1646  */
    break;

  case 149:
#line 462 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_specifier((yyvsp[0].declarator), (yyvsp[-1].list)); }
#line 2604 "parser.c" /* yacc.c:1646  */
    break;

  case 150:
#line 463 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_specifier((yyvsp[0].declarator), (yyvsp[-1].list)); }
#line 2610 "parser.c" /* yacc.c:1646  */
    break;

  case 151:
#line 464 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_specifier(NULL, (yyvsp[0].list)); }
#line 2616 "parser.c" /* yacc.c:1646  */
    break;

  case 152:
#line 468 "parser.y" /* yacc.c:1646  */
    { (yyval.list) = list_new(LI_ELEM, (yyvsp[0].string), NULL); }
#line 2622 "parser.c" /* yacc.c:1646  */
    break;

  case 153:
#line 469 "parser.y" /* yacc.c:1646  */
    { list_append((yyval.list) = (yyvsp[-2].list), (yyvsp[0].string)); }
#line 2628 "parser.c" /* yacc.c:1646  */
    break;

  case 154:
#line 473 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = specifier_list_get_type((yyvsp[0].list));  }
#line 2634 "parser.c" /* yacc.c:1646  */
    break;

  case 155:
#line 475 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = declarator_type((yyvsp[0].declarator), specifier_list_get_type((yyvsp[-1].list))); }
#line 2640 "parser.c" /* yacc.c:1646  */
    break;

  case 156:
#line 479 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_pointer(NULL, (yyvsp[0].pointer)); }
#line 2646 "parser.c" /* yacc.c:1646  */
    break;

  case 157:
#line 480 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = (yyvsp[0].declarator); }
#line 2652 "parser.c" /* yacc.c:1646  */
    break;

  case 158:
#line 481 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_pointer((yyvsp[0].declarator), (yyvsp[-1].pointer)); }
#line 2658 "parser.c" /* yacc.c:1646  */
    break;

  case 159:
#line 485 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = (yyvsp[-1].declarator); }
#line 2664 "parser.c" /* yacc.c:1646  */
    break;

  case 160:
#line 486 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_array(NULL, void_expression); }
#line 2670 "parser.c" /* yacc.c:1646  */
    break;

  case 161:
#line 487 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_array(NULL, (yyvsp[-1].expression)); }
#line 2676 "parser.c" /* yacc.c:1646  */
    break;

  case 162:
#line 489 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_array((yyvsp[-2].declarator), void_expression); }
#line 2682 "parser.c" /* yacc.c:1646  */
    break;

  case 163:
#line 491 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_array((yyvsp[-3].declarator), (yyvsp[-1].expression)); }
#line 2688 "parser.c" /* yacc.c:1646  */
    break;

  case 164:
#line 492 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_function(NULL, list_new(0)); }
#line 2694 "parser.c" /* yacc.c:1646  */
    break;

  case 165:
#line 493 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_function(NULL, (yyvsp[-1].list)); }
#line 2700 "parser.c" /* yacc.c:1646  */
    break;

  case 166:
#line 494 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_function((yyvsp[-2].declarator), list_new(0)); }
#line 2706 "parser.c" /* yacc.c:1646  */
    break;

  case 167:
#line 496 "parser.y" /* yacc.c:1646  */
    { (yyval.declarator) = declarator_function((yyvsp[-3].declarator), (yyvsp[-1].list)); }
#line 2712 "parser.c" /* yacc.c:1646  */
    break;

  case 168:
#line 500 "parser.y" /* yacc.c:1646  */
    { (yyval.initializer) = initializer_expression((yyvsp[0].expression)); }
#line 2718 "parser.c" /* yacc.c:1646  */
    break;

  case 169:
#line 501 "parser.y" /* yacc.c:1646  */
    { (yyval.initializer) = initializer_list((yyvsp[-1].list)); }
#line 2724 "parser.c" /* yacc.c:1646  */
    break;

  case 170:
#line 502 "parser.y" /* yacc.c:1646  */
    { (yyval.initializer) = initializer_list((yyvsp[-2].list)); }
#line 2730 "parser.c" /* yacc.c:1646  */
    break;

  case 171:
#line 506 "parser.y" /* yacc.c:1646  */
    { (yyval.list) = list_new(LI_ELEM, (yyvsp[0].initializer), NULL); }
#line 2736 "parser.c" /* yacc.c:1646  */
    break;

  case 172:
#line 507 "parser.y" /* yacc.c:1646  */
    { list_append((yyval.list) = (yyvsp[-2].list), (yyvsp[0].initializer)); }
#line 2742 "parser.c" /* yacc.c:1646  */
    break;

  case 173:
#line 511 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].statement); }
#line 2748 "parser.c" /* yacc.c:1646  */
    break;

  case 174:
#line 512 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].statement); }
#line 2754 "parser.c" /* yacc.c:1646  */
    break;

  case 175:
#line 513 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].statement); }
#line 2760 "parser.c" /* yacc.c:1646  */
    break;

  case 176:
#line 514 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].statement); }
#line 2766 "parser.c" /* yacc.c:1646  */
    break;

  case 177:
#line 515 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].statement); }
#line 2772 "parser.c" /* yacc.c:1646  */
    break;

  case 178:
#line 516 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].statement); }
#line 2778 "parser.c" /* yacc.c:1646  */
    break;

  case 179:
#line 520 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_label((yyvsp[0].statement), (yyvsp[-2].string)); }
#line 2784 "parser.c" /* yacc.c:1646  */
    break;

  case 180:
#line 521 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_case((yyvsp[0].statement), (yyvsp[-2].expression)); }
#line 2790 "parser.c" /* yacc.c:1646  */
    break;

  case 181:
#line 522 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_default((yyvsp[0].statement)); }
#line 2796 "parser.c" /* yacc.c:1646  */
    break;

  case 182:
#line 526 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_compound(list_new(0), list_new(0)); }
#line 2802 "parser.c" /* yacc.c:1646  */
    break;

  case 183:
#line 527 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_compound(list_new(0), (yyvsp[-1].list)); }
#line 2808 "parser.c" /* yacc.c:1646  */
    break;

  case 184:
#line 528 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_compound((yyvsp[-1].list), list_new(0)); }
#line 2814 "parser.c" /* yacc.c:1646  */
    break;

  case 185:
#line 530 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_compound((yyvsp[-2].list), (yyvsp[-1].list)); }
#line 2820 "parser.c" /* yacc.c:1646  */
    break;

  case 186:
#line 534 "parser.y" /* yacc.c:1646  */
    { st_push(); }
#line 2826 "parser.c" /* yacc.c:1646  */
    break;

  case 187:
#line 537 "parser.y" /* yacc.c:1646  */
    { st_pop(); }
#line 2832 "parser.c" /* yacc.c:1646  */
    break;

  case 188:
#line 540 "parser.y" /* yacc.c:1646  */
    { (yyval.list) = (yyvsp[0].list); }
#line 2838 "parser.c" /* yacc.c:1646  */
    break;

  case 189:
#line 541 "parser.y" /* yacc.c:1646  */
    { list_append_list((yyval.list) = (yyvsp[-1].list), (yyvsp[0].list)); }
#line 2844 "parser.c" /* yacc.c:1646  */
    break;

  case 190:
#line 545 "parser.y" /* yacc.c:1646  */
    { (yyval.list) = list_new(LI_ELEM, (yyvsp[0].statement), NULL); }
#line 2850 "parser.c" /* yacc.c:1646  */
    break;

  case 191:
#line 546 "parser.y" /* yacc.c:1646  */
    { list_append((yyval.list) = (yyvsp[-1].list), (yyvsp[0].statement)); }
#line 2856 "parser.c" /* yacc.c:1646  */
    break;

  case 192:
#line 550 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_expression(void_expression); }
#line 2862 "parser.c" /* yacc.c:1646  */
    break;

  case 193:
#line 551 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_expression((yyvsp[-1].expression)); }
#line 2868 "parser.c" /* yacc.c:1646  */
    break;

  case 194:
#line 555 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_if((yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2874 "parser.c" /* yacc.c:1646  */
    break;

  case 195:
#line 557 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_if_else((yyvsp[-4].expression), (yyvsp[-2].statement), (yyvsp[0].statement)); }
#line 2880 "parser.c" /* yacc.c:1646  */
    break;

  case 196:
#line 558 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_switch((yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2886 "parser.c" /* yacc.c:1646  */
    break;

  case 197:
#line 562 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_while((yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2892 "parser.c" /* yacc.c:1646  */
    break;

  case 198:
#line 564 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_do_while((yyvsp[-2].expression), (yyvsp[-5].statement)); }
#line 2898 "parser.c" /* yacc.c:1646  */
    break;

  case 199:
#line 566 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_for((yyvsp[-3].statement)->expr, (yyvsp[-2].statement)->expr, void_expression, (yyvsp[0].statement)); }
#line 2904 "parser.c" /* yacc.c:1646  */
    break;

  case 200:
#line 568 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_for((yyvsp[-4].statement)->expr, (yyvsp[-3].statement)->expr, (yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2910 "parser.c" /* yacc.c:1646  */
    break;

  case 201:
#line 572 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_goto((yyvsp[-1].string)); }
#line 2916 "parser.c" /* yacc.c:1646  */
    break;

  case 202:
#line 573 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_continue(); }
#line 2922 "parser.c" /* yacc.c:1646  */
    break;

  case 203:
#line 574 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_break(); }
#line 2928 "parser.c" /* yacc.c:1646  */
    break;

  case 204:
#line 575 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_return(void_expression); }
#line 2934 "parser.c" /* yacc.c:1646  */
    break;

  case 205:
#line 576 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = stmt_return((yyvsp[-1].expression)); }
#line 2940 "parser.c" /* yacc.c:1646  */
    break;

  case 209:
#line 586 "parser.y" /* yacc.c:1646  */
    { // maybe handle typedef at this level
    int si = list_size((yyvsp[0].list));
    for (int i = 1; i <= si; ++i)
        module_add_global(m, list_get((yyvsp[0].list), i), false);
 }
#line 2950 "parser.c" /* yacc.c:1646  */
    break;

  case 210:
#line 595 "parser.y" /* yacc.c:1646  */
    { (yyval.function) = module_get_or_create_function(m, (yyvsp[-1].symbol));
    fun_set_body((yyval.function), (yyvsp[0].statement));
 }
#line 2958 "parser.c" /* yacc.c:1646  */
    break;

  case 211:
#line 602 "parser.y" /* yacc.c:1646  */
    { error("old style function declaration not supported"); }
#line 2964 "parser.c" /* yacc.c:1646  */
    break;

  case 212:
#line 603 "parser.y" /* yacc.c:1646  */
    {
    struct symbol *sy = symbol_new(
        declarator_get_name((yyvsp[0].declarator)),
        declarator_type((yyvsp[0].declarator), specifier_list_get_type((yyvsp[-1].list))));
    (yyval.symbol) = function_declare(sy, declarator_deepest_param_list((yyvsp[0].declarator)), m);  // FIXME
 }
#line 2975 "parser.c" /* yacc.c:1646  */
    break;

  case 213:
#line 610 "parser.y" /* yacc.c:1646  */
    { error("old style function declaration not supported"); }
#line 2981 "parser.c" /* yacc.c:1646  */
    break;

  case 214:
#line 611 "parser.y" /* yacc.c:1646  */
    {
    struct symbol *sy = symbol_new(declarator_get_name((yyvsp[0].declarator)),
                                   declarator_type((yyvsp[0].declarator), type_int));
    (yyval.symbol) = function_declare(sy, declarator_deepest_param_list((yyvsp[0].declarator)), m);
}
#line 2991 "parser.c" /* yacc.c:1646  */
    break;


#line 2995 "parser.c" /* yacc.c:1646  */
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
#line 618 "parser.y" /* yacc.c:1906  */

