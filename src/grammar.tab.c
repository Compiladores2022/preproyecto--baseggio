/* A Bison parser, made by GNU Bison 3.8.2.  */

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
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "grammar.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"
#include "ast.h"
#include "queue.h"

SymbolTable symbolTable;

int yylex();
void yyerror(const char* s);
void addAll(SymbolTable* symbolTable, Symbol* symbol);

#line 87 "grammar.tab.c"

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

#include "grammar.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_IF = 4,                         /* IF  */
  YYSYMBOL_THEN = 5,                       /* THEN  */
  YYSYMBOL_ELSE = 6,                       /* ELSE  */
  YYSYMBOL_RETURN = 7,                     /* RETURN  */
  YYSYMBOL_EXTERN = 8,                     /* EXTERN  */
  YYSYMBOL_WHILE = 9,                      /* WHILE  */
  YYSYMBOL_ID = 10,                        /* ID  */
  YYSYMBOL_vINT = 11,                      /* vINT  */
  YYSYMBOL_vBOOL = 12,                     /* vBOOL  */
  YYSYMBOL_tINT = 13,                      /* tINT  */
  YYSYMBOL_tBOOL = 14,                     /* tBOOL  */
  YYSYMBOL_VOID = 15,                      /* VOID  */
  YYSYMBOL_OR = 16,                        /* OR  */
  YYSYMBOL_AND = 17,                       /* AND  */
  YYSYMBOL_18_ = 18,                       /* '+'  */
  YYSYMBOL_19_ = 19,                       /* '-'  */
  YYSYMBOL_20_ = 20,                       /* '*'  */
  YYSYMBOL_21_ = 21,                       /* '/'  */
  YYSYMBOL_22_ = 22,                       /* '%'  */
  YYSYMBOL_23_ = 23,                       /* '='  */
  YYSYMBOL_24_ = 24,                       /* '!'  */
  YYSYMBOL_25_ = 25,                       /* '<'  */
  YYSYMBOL_26_ = 26,                       /* '>'  */
  YYSYMBOL_EQT = 27,                       /* EQT  */
  YYSYMBOL_28_ = 28,                       /* '{'  */
  YYSYMBOL_29_ = 29,                       /* '}'  */
  YYSYMBOL_30_ = 30,                       /* ';'  */
  YYSYMBOL_31_ = 31,                       /* '('  */
  YYSYMBOL_32_ = 32,                       /* ')'  */
  YYSYMBOL_33_ = 33,                       /* ','  */
  YYSYMBOL_YYACCEPT = 34,                  /* $accept  */
  YYSYMBOL_program = 35,                   /* program  */
  YYSYMBOL_36_1 = 36,                      /* $@1  */
  YYSYMBOL_lDeclarations = 37,             /* lDeclarations  */
  YYSYMBOL_MethodDeclarations = 38,        /* MethodDeclarations  */
  YYSYMBOL_MethodDeclaration = 39,         /* MethodDeclaration  */
  YYSYMBOL_40_2 = 40,                      /* $@2  */
  YYSYMBOL_Method = 41,                    /* Method  */
  YYSYMBOL_Params = 42,                    /* Params  */
  YYSYMBOL_OneOrMoreParams = 43,           /* OneOrMoreParams  */
  YYSYMBOL_Param = 44,                     /* Param  */
  YYSYMBOL_Block = 45,                     /* Block  */
  YYSYMBOL_lStatements = 46,               /* lStatements  */
  YYSYMBOL_Statement = 47,                 /* Statement  */
  YYSYMBOL_Declaration = 48,               /* Declaration  */
  YYSYMBOL_E = 49,                         /* E  */
  YYSYMBOL_V = 50,                         /* V  */
  YYSYMBOL_Expressions = 51,               /* Expressions  */
  YYSYMBOL_OneOrMoreExpressions = 52,      /* OneOrMoreExpressions  */
  YYSYMBOL_Type = 53,                      /* Type  */
  YYSYMBOL_MethodCall = 54                 /* MethodCall  */
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
typedef yytype_int8 yy_state_t;

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

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   252

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  109

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   273


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
       2,     2,     2,    24,     2,     2,     2,    22,     2,     2,
      31,    32,    20,    18,    33,    19,     2,    21,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    30,
      25,    23,    26,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    28,     2,    29,     2,     2,     2,     2,
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
      15,    16,    17,    27
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    71,    71,    71,    77,    78,    81,    82,    85,    85,
      90,    93,   103,   115,   116,   119,   120,   126,   130,   132,
     133,   136,   140,   141,   142,   143,   144,   145,   146,   147,
     150,   161,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   182,   187,   194,
     195,   198,   199,   202,   203,   206
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
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM", "IF",
  "THEN", "ELSE", "RETURN", "EXTERN", "WHILE", "ID", "vINT", "vBOOL",
  "tINT", "tBOOL", "VOID", "OR", "AND", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'='", "'!'", "'<'", "'>'", "EQT", "'{'", "'}'", "';'", "'('", "')'",
  "','", "$accept", "program", "$@1", "lDeclarations",
  "MethodDeclarations", "MethodDeclaration", "$@2", "Method", "Params",
  "OneOrMoreParams", "Param", "Block", "lStatements", "Statement",
  "Declaration", "E", "V", "Expressions", "OneOrMoreExpressions", "Type",
  "MethodCall", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-47)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -47,    19,     5,   -47,     9,   -47,     8,   -47,   -47,    29,
      27,     8,    50,   -47,    52,    33,   -47,   -47,    56,    38,
      48,    15,   -11,    46,   -47,   -47,   -47,    63,   -11,    47,
     -47,    45,    78,   -11,    61,   -47,   -47,    63,    63,    63,
     131,   -47,   -47,    70,   -47,   -11,   -47,    41,    83,    63,
     204,    17,    97,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,   -47,   -47,   -47,    72,    -6,    63,    26,
     -47,   -47,   -47,   -47,   146,    84,    79,    76,   -47,   -47,
     -10,    17,    64,   204,   211,   218,   225,    28,    82,   -47,
      63,   -47,   161,   191,    63,   -47,    63,   -47,   114,   -47,
     -47,   176,   -47,   105,   -47,    48,   115,    48,   -47
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,     0,     4,     6,    53,    54,     0,
       0,     6,     8,     5,     0,     0,     3,     7,     0,     0,
       0,     0,    13,     0,    10,     4,     9,     0,    13,     0,
      14,    15,     0,    19,    31,    47,    48,     0,     0,     0,
       0,    33,    32,     0,    11,     0,    17,     0,     0,    49,
      44,    45,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    30,    12,    16,     0,     0,     0,    31,
      18,    28,    29,    20,     0,     0,    51,     0,    50,    46,
      42,    43,    34,    35,    36,    37,    38,    39,    40,    41,
       0,    26,     0,     0,     0,    22,     0,    55,     0,    27,
      25,     0,    52,     0,    21,     0,    23,     0,    24
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -47,   -47,   -47,    86,   109,   -47,   -47,   -47,    98,    80,
     -47,   -46,   -47,   -47,   -47,   -27,   -47,   -47,    31,     3,
     -47
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     6,    10,    11,    20,    12,    29,    30,
      31,    26,    47,    73,    13,    76,    41,    77,    78,    32,
      42
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      40,    72,     7,     8,    34,    35,    36,    54,     4,    14,
      50,    51,    52,    37,    18,    60,    61,    62,    38,     3,
      74,     7,     8,     9,    91,    39,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    48,     5,    27,    15,
      92,    93,    60,    61,    62,    66,    28,   100,    67,    94,
      68,    69,    35,    36,    61,    62,    16,    49,    19,   106,
      37,   108,    21,    98,    22,    38,    23,   101,    24,    25,
      70,    71,    39,    34,    35,    36,    25,    28,    45,    44,
      53,    54,    37,    56,    57,    58,    59,    38,    46,    60,
      61,    62,    49,    75,    39,    53,    54,    55,    56,    57,
      58,    59,    64,    90,    60,    61,    62,    27,    97,    62,
     105,    33,    96,    53,    54,    55,    56,    57,    58,    59,
      17,   107,    60,    61,    62,    65,    43,   102,     0,    79,
      53,    54,    55,    56,    57,    58,    59,     0,     0,    60,
      61,    62,     0,     0,     0,     0,   103,    53,    54,    55,
      56,    57,    58,    59,     0,     0,    60,    61,    62,     0,
       0,    63,    53,    54,    55,    56,    57,    58,    59,     0,
       0,    60,    61,    62,     0,     0,    95,    53,    54,    55,
      56,    57,    58,    59,     0,     0,    60,    61,    62,     0,
       0,    99,    53,    54,    55,    56,    57,    58,    59,     0,
       0,    60,    61,    62,     0,     0,   104,    53,    54,    55,
      56,    57,    58,    59,     0,     0,    60,    61,    62,    25,
      53,    54,     0,     0,    57,    58,    59,    53,    54,    60,
      61,    62,    58,    59,    53,    54,    60,    61,    62,     0,
      59,    53,    54,    60,    61,    62,     0,     0,     0,     0,
      60,    61,    62
};

static const yytype_int8 yycheck[] =
{
      27,    47,    13,    14,    10,    11,    12,    17,     3,     6,
      37,    38,    39,    19,    11,    25,    26,    27,    24,     0,
      47,    13,    14,    15,    30,    31,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    33,    28,    23,    10,
      67,    68,    25,    26,    27,     4,    31,    93,     7,    23,
       9,    10,    11,    12,    26,    27,    29,    31,     8,   105,
      19,   107,    10,    90,    31,    24,    10,    94,    30,    28,
      29,    30,    31,    10,    11,    12,    28,    31,    33,    32,
      16,    17,    19,    19,    20,    21,    22,    24,    10,    25,
      26,    27,    31,    10,    31,    16,    17,    18,    19,    20,
      21,    22,    32,    31,    25,    26,    27,    23,    32,    27,
       5,    25,    33,    16,    17,    18,    19,    20,    21,    22,
      11,     6,    25,    26,    27,    45,    28,    96,    -1,    32,
      16,    17,    18,    19,    20,    21,    22,    -1,    -1,    25,
      26,    27,    -1,    -1,    -1,    -1,    32,    16,    17,    18,
      19,    20,    21,    22,    -1,    -1,    25,    26,    27,    -1,
      -1,    30,    16,    17,    18,    19,    20,    21,    22,    -1,
      -1,    25,    26,    27,    -1,    -1,    30,    16,    17,    18,
      19,    20,    21,    22,    -1,    -1,    25,    26,    27,    -1,
      -1,    30,    16,    17,    18,    19,    20,    21,    22,    -1,
      -1,    25,    26,    27,    -1,    -1,    30,    16,    17,    18,
      19,    20,    21,    22,    -1,    -1,    25,    26,    27,    28,
      16,    17,    -1,    -1,    20,    21,    22,    16,    17,    25,
      26,    27,    21,    22,    16,    17,    25,    26,    27,    -1,
      22,    16,    17,    25,    26,    27,    -1,    -1,    -1,    -1,
      25,    26,    27
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    35,    36,     0,     3,    28,    37,    13,    14,    15,
      38,    39,    41,    48,    53,    10,    29,    38,    53,     8,
      40,    10,    31,    10,    30,    28,    45,    23,    31,    42,
      43,    44,    53,    37,    10,    11,    12,    19,    24,    31,
      49,    50,    54,    42,    32,    33,    10,    46,    53,    31,
      49,    49,    49,    16,    17,    18,    19,    20,    21,    22,
      25,    26,    27,    30,    32,    43,     4,     7,     9,    10,
      29,    30,    45,    47,    49,    10,    49,    51,    52,    32,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      31,    30,    49,    49,    23,    30,    33,    32,    49,    30,
      45,    49,    52,    32,    30,     5,    45,     6,    45
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    34,    36,    35,    37,    37,    38,    38,    40,    39,
      39,    41,    41,    42,    42,    43,    43,    44,    45,    46,
      46,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      48,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    50,    50,    51,
      51,    52,    52,    53,    53,    54
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     6,     0,     2,     0,     2,     0,     3,
       3,     5,     5,     0,     1,     1,     3,     2,     4,     0,
       2,     4,     2,     6,     8,     3,     2,     3,     1,     1,
       5,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     3,     1,     1,     0,
       1,     1,     3,     1,     1,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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
    YYNOMEM;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 71 "grammar.y"
        { constructSymbolTable(&symbolTable); }
#line 1222 "grammar.tab.c"
    break;

  case 3: /* program: $@1 PROGRAM '{' lDeclarations MethodDeclarations '}'  */
#line 71 "grammar.y"
                                                                                                  { 
       
        ASTNode* root = composeTree(flag_SEMICOLON, ";", (yyvsp[-2].n), NULL, (yyvsp[-1].n));
        printAST(root);
}
#line 1232 "grammar.tab.c"
    break;

  case 4: /* lDeclarations: %empty  */
#line 77 "grammar.y"
               { (yyval.n) = NULL; }
#line 1238 "grammar.tab.c"
    break;

  case 5: /* lDeclarations: lDeclarations Declaration  */
#line 78 "grammar.y"
                                         { (yyval.n) = composeTree(flag_SEMICOLON, ";", (yyvsp[-1].n), NULL, (yyvsp[0].n)); }
#line 1244 "grammar.tab.c"
    break;

  case 6: /* MethodDeclarations: %empty  */
#line 81 "grammar.y"
                    { (yyval.n) = NULL; }
#line 1250 "grammar.tab.c"
    break;

  case 7: /* MethodDeclarations: MethodDeclaration MethodDeclarations  */
#line 82 "grammar.y"
                                                         { (yyval.n) = composeTree(flag_SEMICOLON, ";", (yyvsp[-1].n), NULL, (yyvsp[0].n)); }
#line 1256 "grammar.tab.c"
    break;

  case 8: /* $@2: %empty  */
#line 85 "grammar.y"
                          { openLevel(&symbolTable);
		            ASTNode* n     = (yyvsp[0].n);
		            Symbol* params = n->symbol->params;
                            addAll(&symbolTable, params);
                          }
#line 1266 "grammar.tab.c"
    break;

  case 9: /* MethodDeclaration: Method $@2 Block  */
#line 89 "grammar.y"
                                   { closeLevel(&symbolTable); (yyval.n) = composeTree(0, "Method declaration", (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1272 "grammar.tab.c"
    break;

  case 10: /* MethodDeclaration: Method EXTERN ';'  */
#line 90 "grammar.y"
                                     { (yyval.n) = composeTree(0, "Method declaration", (yyvsp[-2].n), NULL, NULL); }
#line 1278 "grammar.tab.c"
    break;

  case 11: /* Method: VOID ID '(' Params ')'  */
#line 93 "grammar.y"
                               { Symbol* symbol = constructPtrToSymbol(flag_METHOD, TYPE_VOID, (yyvsp[-3].s), 0);
                                 if(addSymbol(&symbolTable, symbol)) {
                                     symbol->params = (yyvsp[-1].sb);
                                     ASTNode* n = node(symbol);
                                     (yyval.n) = n;
                                 } else {
                                     printf("Redeclared identifier: %s\n", (yyvsp[-3].s));
                                     exit(EXIT_FAILURE);
                                 }
                               }
#line 1293 "grammar.tab.c"
    break;

  case 12: /* Method: Type ID '(' Params ')'  */
#line 103 "grammar.y"
                               { Symbol* symbol = constructPtrToSymbol(flag_METHOD, (yyvsp[-4].t), (yyvsp[-3].s), 0);
                                 if(addSymbol(&symbolTable, symbol)) {
                                     symbol->params = (yyvsp[-1].sb);
                                     ASTNode* n = node(symbol);
                                     (yyval.n) = n;
                                 } else {
                                     printf("Redeclared identifier: %s\n", (yyvsp[-3].s));
                                     exit(EXIT_FAILURE);
                                 }
                               }
#line 1308 "grammar.tab.c"
    break;

  case 13: /* Params: %empty  */
#line 115 "grammar.y"
                        { (yyval.sb) = NULL; }
#line 1314 "grammar.tab.c"
    break;

  case 14: /* Params: OneOrMoreParams  */
#line 116 "grammar.y"
                        { (yyval.sb) = (yyvsp[0].sb);   }
#line 1320 "grammar.tab.c"
    break;

  case 15: /* OneOrMoreParams: Param  */
#line 119 "grammar.y"
                                            { (yyval.sb) = (yyvsp[0].sb); }
#line 1326 "grammar.tab.c"
    break;

  case 16: /* OneOrMoreParams: Param ',' OneOrMoreParams  */
#line 120 "grammar.y"
                                            { Symbol* symbol = (yyvsp[-2].sb);
                                              symbol->params = (yyvsp[0].sb);
                                              (yyval.sb) = symbol;
                                            }
#line 1335 "grammar.tab.c"
    break;

  case 17: /* Param: Type ID  */
#line 126 "grammar.y"
               { Symbol* symbol = constructPtrToSymbol(flag_PARAM, (yyvsp[-1].t), (yyvsp[0].s), 0);
                 (yyval.sb) = symbol;
               }
#line 1343 "grammar.tab.c"
    break;

  case 18: /* Block: '{' lDeclarations lStatements '}'  */
#line 130 "grammar.y"
                                         { (yyval.n) = composeTree(flag_SEMICOLON, ";", (yyvsp[-2].n), NULL, (yyvsp[-1].n)); }
#line 1349 "grammar.tab.c"
    break;

  case 19: /* lStatements: %empty  */
#line 132 "grammar.y"
             { (yyval.n) = NULL; }
#line 1355 "grammar.tab.c"
    break;

  case 20: /* lStatements: lStatements Statement  */
#line 133 "grammar.y"
                                   { (yyval.n) = composeTree(flag_SEMICOLON, ";", (yyvsp[-1].n), NULL, (yyvsp[0].n)); }
#line 1361 "grammar.tab.c"
    break;

  case 21: /* Statement: ID '=' E ';'  */
#line 136 "grammar.y"
                        { Symbol* symbol = checkIdentifierIsDeclared(symbolTable, (yyvsp[-3].s));
	                  ASTNode* lSide = node(symbol);
                          (yyval.n) = composeTree(flag_ASSIGNMENT, "=", lSide, NULL, (yyvsp[-1].n));
	                }
#line 1370 "grammar.tab.c"
    break;

  case 22: /* Statement: E ';'  */
#line 140 "grammar.y"
                                               { (yyval.n) = (yyvsp[-1].n); }
#line 1376 "grammar.tab.c"
    break;

  case 23: /* Statement: IF '(' E ')' THEN Block  */
#line 141 "grammar.y"
                                               { (yyval.n) = composeTree(flag_IF, "if-then", (yyvsp[-3].n), NULL, (yyvsp[0].n)); }
#line 1382 "grammar.tab.c"
    break;

  case 24: /* Statement: IF '(' E ')' THEN Block ELSE Block  */
#line 142 "grammar.y"
                                               { (yyval.n) = composeTree(flag_IF_ELSE, "if-then-else", (yyvsp[-5].n), (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1388 "grammar.tab.c"
    break;

  case 25: /* Statement: WHILE E Block  */
#line 143 "grammar.y"
                                               { (yyval.n) = composeTree(flag_WHILE, "while", (yyvsp[-1].n), NULL, (yyvsp[0].n)); }
#line 1394 "grammar.tab.c"
    break;

  case 26: /* Statement: RETURN ';'  */
#line 144 "grammar.y"
                                               { (yyval.n) = composeTree(flag_RETURN, "return", NULL, NULL, NULL); }
#line 1400 "grammar.tab.c"
    break;

  case 27: /* Statement: RETURN E ';'  */
#line 145 "grammar.y"
                                               { (yyval.n) = composeTree(flag_RETURN, "return", (yyvsp[-1].n), NULL, NULL); }
#line 1406 "grammar.tab.c"
    break;

  case 28: /* Statement: ';'  */
#line 146 "grammar.y"
                                               { (yyval.n) = composeTree(flag_SEMICOLON, ";", NULL, NULL, NULL); }
#line 1412 "grammar.tab.c"
    break;

  case 29: /* Statement: Block  */
#line 147 "grammar.y"
                                               { (yyval.n) = (yyvsp[0].n); }
#line 1418 "grammar.tab.c"
    break;

  case 30: /* Declaration: Type ID '=' E ';'  */
#line 150 "grammar.y"
                               { Symbol* symbol = constructPtrToSymbol(flag_IDENTIFIER, (yyvsp[-4].t), (yyvsp[-3].s), 0); 
	                         if(addSymbol(&symbolTable, symbol)) {
                                   ASTNode* n = node(symbol);
                                   (yyval.n) = n;
				 } else {
                                   printf("Redeclared var\n");
                                   exit(EXIT_FAILURE);
				 }
                               }
#line 1432 "grammar.tab.c"
    break;

  case 31: /* E: ID  */
#line 161 "grammar.y"
              { Symbol* symbol = checkIdentifierIsDeclared(symbolTable, (yyvsp[0].s)); 
                ASTNode* n = node(symbol);
                (yyval.n) = n;
              }
#line 1441 "grammar.tab.c"
    break;

  case 32: /* E: MethodCall  */
#line 165 "grammar.y"
              { (yyval.n) = (yyvsp[0].n); }
#line 1447 "grammar.tab.c"
    break;

  case 33: /* E: V  */
#line 166 "grammar.y"
              { (yyval.n) = (yyvsp[0].n); }
#line 1453 "grammar.tab.c"
    break;

  case 34: /* E: E '+' E  */
#line 167 "grammar.y"
              { (yyval.n) = composeTree(flag_ADDITION, "+", (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1459 "grammar.tab.c"
    break;

  case 35: /* E: E '-' E  */
#line 168 "grammar.y"
              { (yyval.n) = composeTree(flag_SUBSTRACTION, "-", (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1465 "grammar.tab.c"
    break;

  case 36: /* E: E '*' E  */
#line 169 "grammar.y"
              { (yyval.n) = composeTree(flag_MULTIPLICATION, "*", (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1471 "grammar.tab.c"
    break;

  case 37: /* E: E '/' E  */
#line 170 "grammar.y"
              { (yyval.n) = composeTree(flag_DIVISION, "/", (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1477 "grammar.tab.c"
    break;

  case 38: /* E: E '%' E  */
#line 171 "grammar.y"
              { (yyval.n) = composeTree(flag_MOD, "%", (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1483 "grammar.tab.c"
    break;

  case 39: /* E: E '<' E  */
#line 172 "grammar.y"
              { (yyval.n) = composeTree(flag_LT, "<", (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1489 "grammar.tab.c"
    break;

  case 40: /* E: E '>' E  */
#line 173 "grammar.y"
              { (yyval.n) = composeTree(flag_GT, ">", (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1495 "grammar.tab.c"
    break;

  case 41: /* E: E EQT E  */
#line 174 "grammar.y"
              { (yyval.n) = composeTree(flag_EQT, "==", (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1501 "grammar.tab.c"
    break;

  case 42: /* E: E OR E  */
#line 175 "grammar.y"
              { (yyval.n) = composeTree(flag_OR, "||", (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1507 "grammar.tab.c"
    break;

  case 43: /* E: E AND E  */
#line 176 "grammar.y"
              { (yyval.n) = composeTree(flag_AND, "&&", (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1513 "grammar.tab.c"
    break;

  case 44: /* E: '-' E  */
#line 177 "grammar.y"
              { (yyval.n) = composeTree(flag_MINUS, "-", (yyvsp[0].n), NULL, NULL); }
#line 1519 "grammar.tab.c"
    break;

  case 45: /* E: '!' E  */
#line 178 "grammar.y"
              { (yyval.n) = composeTree(flag_NEG, "!", (yyvsp[0].n), NULL, NULL); }
#line 1525 "grammar.tab.c"
    break;

  case 46: /* E: '(' E ')'  */
#line 179 "grammar.y"
              { (yyval.n) = (yyvsp[-1].n); }
#line 1531 "grammar.tab.c"
    break;

  case 47: /* V: vINT  */
#line 182 "grammar.y"
        {  char* name = (char*) malloc(sizeof(char));
           sprintf(name, "%d", (yyvsp[0].i));
           ASTNode* n = node(constructPtrToSymbol(flag_VALUE_INT, TYPE_INT, name, (yyvsp[0].i)));
           (yyval.n) = n;
        }
#line 1541 "grammar.tab.c"
    break;

  case 48: /* V: vBOOL  */
#line 187 "grammar.y"
         { char* name = (char*) malloc(sizeof(char));
           sprintf(name, "%d", (yyvsp[0].i));
           ASTNode* n = node(constructPtrToSymbol(flag_VALUE_BOOL, TYPE_BOOL, name, (yyvsp[0].i)));
           (yyval.n) = n;
         }
#line 1551 "grammar.tab.c"
    break;

  case 49: /* Expressions: %empty  */
#line 194 "grammar.y"
             { (yyval.n) = NULL; }
#line 1557 "grammar.tab.c"
    break;

  case 50: /* Expressions: OneOrMoreExpressions  */
#line 195 "grammar.y"
                                  { (yyval.n) = (yyvsp[0].n); }
#line 1563 "grammar.tab.c"
    break;

  case 51: /* OneOrMoreExpressions: E  */
#line 198 "grammar.y"
                        { (yyval.n) = (yyvsp[0].n); }
#line 1569 "grammar.tab.c"
    break;

  case 52: /* OneOrMoreExpressions: E ',' OneOrMoreExpressions  */
#line 199 "grammar.y"
                                                 { (yyval.n) = composeTree(flag_SEMICOLON, ";", (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1575 "grammar.tab.c"
    break;

  case 53: /* Type: tINT  */
#line 202 "grammar.y"
             { (yyval.t) = (yyvsp[0].t); }
#line 1581 "grammar.tab.c"
    break;

  case 54: /* Type: tBOOL  */
#line 203 "grammar.y"
             { (yyval.t) = (yyvsp[0].t); }
#line 1587 "grammar.tab.c"
    break;

  case 55: /* MethodCall: ID '(' Expressions ')'  */
#line 206 "grammar.y"
                                   { (yyval.n) = NULL; }
#line 1593 "grammar.tab.c"
    break;


#line 1597 "grammar.tab.c"

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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 208 "grammar.y"


void addAll(SymbolTable* symbolTable, Symbol* symbol) {
    if(symbol) {
        addSymbol(symbolTable, symbol);
        addAll(symbolTable, symbol->params);
    }
}
