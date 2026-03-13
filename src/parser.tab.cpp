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
#line 1 "src/parser.y"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "ast.h"
#include "parser.tab.hpp"

extern int yylex();
extern int yylineno;
void yyerror(const char *s);

std::unique_ptr<novus::Program> root;

using namespace novus;

template<typename T>
T* setLoc(T* node, const YYLTYPE& loc) {
    if (node) {
        node->loc.line = loc.first_line;
        node->loc.col = loc.first_column;
    }
    return node;
}

#line 97 "src/parser.tab.cpp"

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

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IVAL = 3,                       /* IVAL  */
  YYSYMBOL_FVAL = 4,                       /* FVAL  */
  YYSYMBOL_SVAL = 5,                       /* SVAL  */
  YYSYMBOL_IDENT = 6,                      /* IDENT  */
  YYSYMBOL_IMPORT = 7,                     /* IMPORT  */
  YYSYMBOL_EXTERN = 8,                     /* EXTERN  */
  YYSYMBOL_STRUCT = 9,                     /* STRUCT  */
  YYSYMBOL_IMPL = 10,                      /* IMPL  */
  YYSYMBOL_FN = 11,                        /* FN  */
  YYSYMBOL_VAR = 12,                       /* VAR  */
  YYSYMBOL_IF = 13,                        /* IF  */
  YYSYMBOL_ELSE = 14,                      /* ELSE  */
  YYSYMBOL_WHILE = 15,                     /* WHILE  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_TRUE = 17,                      /* TRUE  */
  YYSYMBOL_FALSE = 18,                     /* FALSE  */
  YYSYMBOL_AS = 19,                        /* AS  */
  YYSYMBOL_VOID = 20,                      /* VOID  */
  YYSYMBOL_INT = 21,                       /* INT  */
  YYSYMBOL_INT16 = 22,                     /* INT16  */
  YYSYMBOL_INT32 = 23,                     /* INT32  */
  YYSYMBOL_INT64 = 24,                     /* INT64  */
  YYSYMBOL_FLOAT = 25,                     /* FLOAT  */
  YYSYMBOL_FLOAT16 = 26,                   /* FLOAT16  */
  YYSYMBOL_FLOAT32 = 27,                   /* FLOAT32  */
  YYSYMBOL_FLOAT64 = 28,                   /* FLOAT64  */
  YYSYMBOL_BOOL = 29,                      /* BOOL  */
  YYSYMBOL_CHAR = 30,                      /* CHAR  */
  YYSYMBOL_STRING = 31,                    /* STRING  */
  YYSYMBOL_SHL = 32,                       /* SHL  */
  YYSYMBOL_SHR = 33,                       /* SHR  */
  YYSYMBOL_EQ = 34,                        /* EQ  */
  YYSYMBOL_NE = 35,                        /* NE  */
  YYSYMBOL_LE = 36,                        /* LE  */
  YYSYMBOL_GE = 37,                        /* GE  */
  YYSYMBOL_ARROW = 38,                     /* ARROW  */
  YYSYMBOL_ELLIPSIS = 39,                  /* ELLIPSIS  */
  YYSYMBOL_40_ = 40,                       /* '='  */
  YYSYMBOL_41_ = 41,                       /* '<'  */
  YYSYMBOL_42_ = 42,                       /* '>'  */
  YYSYMBOL_43_ = 43,                       /* '+'  */
  YYSYMBOL_44_ = 44,                       /* '-'  */
  YYSYMBOL_45_ = 45,                       /* '*'  */
  YYSYMBOL_46_ = 46,                       /* '/'  */
  YYSYMBOL_47_ = 47,                       /* '%'  */
  YYSYMBOL_48_ = 48,                       /* '!'  */
  YYSYMBOL_49_ = 49,                       /* '&'  */
  YYSYMBOL_50_ = 50,                       /* '.'  */
  YYSYMBOL_51_ = 51,                       /* '['  */
  YYSYMBOL_52_ = 52,                       /* '('  */
  YYSYMBOL_53_ = 53,                       /* ';'  */
  YYSYMBOL_54_ = 54,                       /* ')'  */
  YYSYMBOL_55_ = 55,                       /* ','  */
  YYSYMBOL_56_ = 56,                       /* ':'  */
  YYSYMBOL_57_ = 57,                       /* '{'  */
  YYSYMBOL_58_ = 58,                       /* '}'  */
  YYSYMBOL_59_ = 59,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 60,                  /* $accept  */
  YYSYMBOL_program = 61,                   /* program  */
  YYSYMBOL_import_list = 62,               /* import_list  */
  YYSYMBOL_import_stmt = 63,               /* import_stmt  */
  YYSYMBOL_decl_list = 64,                 /* decl_list  */
  YYSYMBOL_decl = 65,                      /* decl  */
  YYSYMBOL_extern_decl = 66,               /* extern_decl  */
  YYSYMBOL_func_decl = 67,                 /* func_decl  */
  YYSYMBOL_param_list = 68,                /* param_list  */
  YYSYMBOL_struct_decl = 69,               /* struct_decl  */
  YYSYMBOL_field_list = 70,                /* field_list  */
  YYSYMBOL_impl_block = 71,                /* impl_block  */
  YYSYMBOL_type = 72,                      /* type  */
  YYSYMBOL_base_type = 73,                 /* base_type  */
  YYSYMBOL_stmt = 74,                      /* stmt  */
  YYSYMBOL_expr_stmt = 75,                 /* expr_stmt  */
  YYSYMBOL_var_decl_stmt = 76,             /* var_decl_stmt  */
  YYSYMBOL_block_stmt = 77,                /* block_stmt  */
  YYSYMBOL_stmt_list = 78,                 /* stmt_list  */
  YYSYMBOL_if_stmt = 79,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 80,                /* while_stmt  */
  YYSYMBOL_return_stmt = 81,               /* return_stmt  */
  YYSYMBOL_expr = 82,                      /* expr  */
  YYSYMBOL_equality_expr = 83,             /* equality_expr  */
  YYSYMBOL_relational_expr = 84,           /* relational_expr  */
  YYSYMBOL_shift_expr = 85,                /* shift_expr  */
  YYSYMBOL_add_expr = 86,                  /* add_expr  */
  YYSYMBOL_mul_expr = 87,                  /* mul_expr  */
  YYSYMBOL_cast_expr = 88,                 /* cast_expr  */
  YYSYMBOL_unary_expr = 89,                /* unary_expr  */
  YYSYMBOL_postfix_expr = 90,              /* postfix_expr  */
  YYSYMBOL_arg_list = 91,                  /* arg_list  */
  YYSYMBOL_primary_expr = 92               /* primary_expr  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   226

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  186

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
       2,     2,     2,    48,     2,     2,     2,    47,    49,     2,
      52,    54,    45,    43,    55,    44,    50,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    56,    53,
      41,    40,    42,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    51,     2,    59,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    57,     2,    58,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    73,    73,    87,    88,    92,    96,    97,   101,   102,
     103,   104,   105,   109,   114,   123,   127,   134,   135,   136,
     140,   147,   148,   149,   153,   169,   170,   171,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   191,   192,   193,   194,   195,   196,   200,   204,   205,
     209,   213,   214,   218,   219,   223,   227,   228,   232,   233,
     237,   238,   239,   243,   244,   245,   246,   247,   251,   252,
     253,   257,   258,   259,   263,   264,   265,   266,   270,   271,
     275,   276,   277,   278,   279,   283,   284,   285,   298,   302,
     303,   304,   308,   309,   310,   311,   312,   313,   314
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
  "\"end of file\"", "error", "\"invalid token\"", "IVAL", "FVAL", "SVAL",
  "IDENT", "IMPORT", "EXTERN", "STRUCT", "IMPL", "FN", "VAR", "IF", "ELSE",
  "WHILE", "RETURN", "TRUE", "FALSE", "AS", "VOID", "INT", "INT16",
  "INT32", "INT64", "FLOAT", "FLOAT16", "FLOAT32", "FLOAT64", "BOOL",
  "CHAR", "STRING", "SHL", "SHR", "EQ", "NE", "LE", "GE", "ARROW",
  "ELLIPSIS", "'='", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'!'", "'&'", "'.'", "'['", "'('", "';'", "')'", "','", "':'", "'{'",
  "'}'", "']'", "$accept", "program", "import_list", "import_stmt",
  "decl_list", "decl", "extern_decl", "func_decl", "param_list",
  "struct_decl", "field_list", "impl_block", "type", "base_type", "stmt",
  "expr_stmt", "var_decl_stmt", "block_stmt", "stmt_list", "if_stmt",
  "while_stmt", "return_stmt", "expr", "equality_expr", "relational_expr",
  "shift_expr", "add_expr", "mul_expr", "cast_expr", "unary_expr",
  "postfix_expr", "arg_list", "primary_expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-93)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -93,    13,    -1,   -93,    10,   -93,   143,   -35,    16,    43,
      46,    55,    58,   -93,   -93,   -93,   -93,   -93,   -93,   -93,
      60,   -26,    38,    68,    75,    71,   106,   -93,   131,   175,
     131,    87,    -5,    99,    93,     2,   -93,   -93,   -93,   -93,
     -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,   -15,
     -93,    25,   175,   135,   -93,   -93,   175,   118,   186,   141,
     -93,   191,   -93,   169,    -2,    40,   175,   -23,   175,   152,
     -93,   -93,   -93,   -93,   -93,   -93,   141,   141,   141,   141,
     141,   156,     5,    34,    72,    56,    70,   -93,   192,    32,
     -93,   151,   175,   158,   -93,    45,   -37,   175,   -93,   114,
     -93,   -93,   -93,   159,   -93,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   175,   141,
     208,   141,   141,   -93,    79,   177,   -93,   -93,   -93,   -93,
     -23,   -93,    34,    34,    72,    72,    72,    72,    56,    56,
      70,    70,   -93,   -93,   -93,   -23,   -93,   -93,   157,   -93,
     115,   -93,   175,    29,   -93,   -93,   141,    97,   165,   166,
       6,   -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,   167,
     -93,   -93,   141,   141,   -93,   168,   -93,   170,   171,   -93,
     123,   123,   205,   -93,   123,   -93
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     6,     1,     0,     4,     2,     0,     0,     0,
       0,     0,     0,     7,     9,     8,    10,    11,    12,     5,
       0,     0,     0,     0,     0,     0,    21,     6,    17,     0,
      17,     0,     0,     0,     0,     0,    40,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     0,
      25,     0,     0,     0,    20,    24,     0,     0,     0,     0,
      26,     0,    48,     0,     0,     0,     0,    18,     0,     0,
      93,    94,    95,    92,    96,    97,     0,     0,     0,     0,
       0,     0,    58,    60,    63,    68,    71,    74,    78,    80,
      85,     0,     0,     0,    22,     0,     0,     0,    81,    80,
      84,    82,    83,     0,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,    27,     0,     0,    23,    16,    51,    15,
      19,    98,    61,    62,    66,    67,    64,    65,    69,    70,
      72,    73,    75,    76,    77,    79,    59,    86,     0,    90,
       0,    13,     0,     0,    88,    87,     0,     0,     0,     0,
       0,    50,    52,    41,    42,    43,    44,    45,    46,     0,
      91,    14,     0,     0,    56,     0,    47,     0,     0,    57,
       0,     0,    53,    55,     0,    54
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -93,   -93,   -93,   -93,   195,   -93,   -93,   -93,   193,   -93,
     -93,   -93,   -49,   -93,   -92,   -93,    -4,   130,   -93,   -93,
     -93,   -93,   -54,   -93,    28,    53,    62,    74,    67,   100,
     -59,   -93,   -93
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     5,     6,    13,    14,    15,    35,    16,
      32,    17,    49,    50,   162,   163,   164,   165,   153,   166,
     167,   168,   169,    82,    83,    84,    85,    86,    87,    88,
      99,   150,    90
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      89,    53,    18,    65,    69,    81,     4,    67,    60,    70,
      71,    72,    73,     3,    61,     7,   127,    95,    19,    96,
     128,    89,    60,    74,    75,    59,   103,    20,    61,    18,
      60,    26,    70,    71,    72,    73,    61,    93,    62,   105,
     106,    12,   158,   124,   159,   160,    74,    75,   130,    21,
      76,    77,    22,    54,    78,    79,    57,    58,    80,   174,
      89,    23,    89,    89,    24,   146,    25,   148,   149,   145,
     107,   108,   119,    76,    77,   109,   110,    78,    79,    63,
      64,    80,   120,   121,   122,    60,   128,   161,   182,   183,
      60,    61,   185,    94,    89,    27,    61,    89,   126,   113,
     114,    89,   170,   157,   111,   112,   175,     8,     9,    10,
      11,    12,    31,    89,    89,   115,   116,   117,   177,   178,
      28,    89,    89,    30,    60,    89,    70,    71,    72,    73,
      61,    29,   151,   132,   133,    12,   158,    34,   159,   160,
      74,    75,    60,    52,    70,    71,    72,    73,    61,    56,
     171,     8,     9,    10,    11,    12,    68,    55,    74,    75,
     134,   135,   136,   137,   120,   121,   122,    76,    77,   155,
     156,    78,    79,   138,   139,    80,    98,   100,   101,   102,
     128,    36,   142,   143,   144,    76,    77,   140,   141,    78,
      79,    66,    69,    80,    91,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    92,    97,   104,
     123,   118,   125,   131,   147,   152,   154,   172,   173,   184,
     176,   179,    33,    51,   180,   181,   129
};

static const yytype_uint8 yycheck[] =
{
      59,     6,     6,    52,     6,    59,     7,    56,    45,     3,
       4,     5,     6,     0,    51,     5,    53,    66,    53,    68,
      57,    80,    45,    17,    18,    40,    80,    11,    51,    33,
      45,    57,     3,     4,     5,     6,    51,    39,    53,    34,
      35,    12,    13,    92,    15,    16,    17,    18,    97,     6,
      44,    45,     6,    58,    48,    49,    54,    55,    52,    53,
     119,     6,   121,   122,     6,   119,     6,   121,   122,   118,
      36,    37,    40,    44,    45,    41,    42,    48,    49,    54,
      55,    52,    50,    51,    52,    45,    57,    58,   180,   181,
      45,    51,   184,    53,   153,    57,    51,   156,    53,    43,
      44,   160,   156,   152,    32,    33,   160,     8,     9,    10,
      11,    12,     6,   172,   173,    45,    46,    47,   172,   173,
      52,   180,   181,    52,    45,   184,     3,     4,     5,     6,
      51,    56,    53,   105,   106,    12,    13,     6,    15,    16,
      17,    18,    45,    56,     3,     4,     5,     6,    51,    56,
      53,     8,     9,    10,    11,    12,    38,    58,    17,    18,
     107,   108,   109,   110,    50,    51,    52,    44,    45,    54,
      55,    48,    49,   111,   112,    52,    76,    77,    78,    79,
      57,     6,   115,   116,   117,    44,    45,   113,   114,    48,
      49,    56,     6,    52,     3,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    38,    56,    53,
      59,    19,    54,    54,     6,    38,    59,    52,    52,    14,
      53,    53,    27,    30,    54,    54,    96
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    61,    62,     0,     7,    63,    64,     5,     8,     9,
      10,    11,    12,    65,    66,    67,    69,    71,    76,    53,
      11,     6,     6,     6,     6,     6,    57,    57,    52,    56,
      52,     6,    70,    64,     6,    68,     6,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    72,
      73,    68,    56,     6,    58,    58,    56,    54,    55,    40,
      45,    51,    53,    54,    55,    72,    56,    72,    38,     6,
       3,     4,     5,     6,    17,    18,    44,    45,    48,    49,
      52,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      92,     3,    38,    39,    53,    72,    72,    56,    89,    90,
      89,    89,    89,    82,    53,    34,    35,    36,    37,    41,
      42,    32,    33,    43,    44,    45,    46,    47,    19,    40,
      50,    51,    52,    59,    72,    54,    53,    53,    57,    77,
      72,    54,    84,    84,    85,    85,    85,    85,    86,    86,
      87,    87,    88,    88,    88,    72,    82,     6,    82,    82,
      91,    53,    38,    78,    59,    54,    55,    72,    13,    15,
      16,    58,    74,    75,    76,    77,    79,    80,    81,    82,
      82,    53,    52,    52,    53,    82,    53,    82,    82,    53,
      54,    54,    74,    74,    14,    74
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    60,    61,    62,    62,    63,    64,    64,    65,    65,
      65,    65,    65,    66,    66,    67,    67,    68,    68,    68,
      69,    70,    70,    70,    71,    72,    72,    72,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    74,    74,    74,    74,    74,    74,    75,    76,    76,
      77,    78,    78,    79,    79,    80,    81,    81,    82,    82,
      83,    83,    83,    84,    84,    84,    84,    84,    85,    85,
      85,    86,    86,    86,    87,    87,    87,    87,    88,    88,
      89,    89,    89,    89,    89,    90,    90,    90,    90,    91,
      91,    91,    92,    92,    92,    92,    92,    92,    92
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     2,     3,     0,     2,     1,     1,
       1,     1,     1,     9,    11,     8,     8,     0,     3,     5,
       5,     0,     4,     5,     5,     1,     2,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     5,     7,
       3,     0,     2,     5,     7,     5,     2,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     3,
       1,     2,     2,     2,     2,     1,     3,     4,     4,     0,
       1,     3,     1,     1,     1,     1,     1,     1,     3
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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


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

  YYLOCATION_PRINT (yyo, yylocationp);
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
  case 2: /* program: import_list decl_list  */
#line 73 "src/parser.y"
                          {
        root = std::make_unique<Program>();
        if ((yyvsp[-1].stmt_list)) {
            for (auto& s : *(yyvsp[-1].stmt_list)) root->imports.push_back(std::move(s));
            delete (yyvsp[-1].stmt_list);
        }
        if ((yyvsp[0].decl_list)) {
            for (auto& d : *(yyvsp[0].decl_list)) root->decls.push_back(std::move(d));
            delete (yyvsp[0].decl_list);
        }
    }
#line 1435 "src/parser.tab.cpp"
    break;

  case 3: /* import_list: %empty  */
#line 87 "src/parser.y"
                { (yyval.stmt_list) = new std::vector<std::unique_ptr<Stmt>>(); }
#line 1441 "src/parser.tab.cpp"
    break;

  case 4: /* import_list: import_list import_stmt  */
#line 88 "src/parser.y"
                              { if ((yyvsp[-1].stmt_list) && (yyvsp[0].stmt)) (yyvsp[-1].stmt_list)->push_back(std::unique_ptr<Stmt>((yyvsp[0].stmt))); (yyval.stmt_list) = (yyvsp[-1].stmt_list); }
#line 1447 "src/parser.tab.cpp"
    break;

  case 5: /* import_stmt: IMPORT SVAL ';'  */
#line 92 "src/parser.y"
                    { (yyval.stmt) = setLoc(new ImportStmt(*(yyvsp[-1].sval)), (yylsp[-2])); delete (yyvsp[-1].sval); }
#line 1453 "src/parser.tab.cpp"
    break;

  case 6: /* decl_list: %empty  */
#line 96 "src/parser.y"
                { (yyval.decl_list) = new std::vector<std::unique_ptr<Decl>>(); }
#line 1459 "src/parser.tab.cpp"
    break;

  case 7: /* decl_list: decl_list decl  */
#line 97 "src/parser.y"
                     { if ((yyvsp[-1].decl_list) && (yyvsp[0].decl)) (yyvsp[-1].decl_list)->push_back(std::unique_ptr<Decl>((yyvsp[0].decl))); (yyval.decl_list) = (yyvsp[-1].decl_list); }
#line 1465 "src/parser.tab.cpp"
    break;

  case 8: /* decl: func_decl  */
#line 101 "src/parser.y"
              { (yyval.decl) = (yyvsp[0].decl); }
#line 1471 "src/parser.tab.cpp"
    break;

  case 9: /* decl: extern_decl  */
#line 102 "src/parser.y"
                  { (yyval.decl) = (yyvsp[0].decl); }
#line 1477 "src/parser.tab.cpp"
    break;

  case 10: /* decl: struct_decl  */
#line 103 "src/parser.y"
                  { (yyval.decl) = (yyvsp[0].decl); }
#line 1483 "src/parser.tab.cpp"
    break;

  case 11: /* decl: impl_block  */
#line 104 "src/parser.y"
                 { (yyval.decl) = (yyvsp[0].decl); }
#line 1489 "src/parser.tab.cpp"
    break;

  case 12: /* decl: var_decl_stmt  */
#line 105 "src/parser.y"
                    { (yyval.decl) = new GlobalVarDecl(std::unique_ptr<VarDeclStmt>(static_cast<VarDeclStmt*>((yyvsp[0].stmt)))); }
#line 1495 "src/parser.tab.cpp"
    break;

  case 13: /* extern_decl: EXTERN FN IDENT '(' param_list ')' ARROW type ';'  */
#line 109 "src/parser.y"
                                                      {
        auto* fd = new FunctionDecl(std::shared_ptr<Type>((yyvsp[-1].type)), *(yyvsp[-6].sval), std::move(*(yyvsp[-4].param_list)), nullptr);
        (yyval.decl) = setLoc(fd, (yylsp[-8]));
        delete (yyvsp[-6].sval); delete (yyvsp[-4].param_list);
    }
#line 1505 "src/parser.tab.cpp"
    break;

  case 14: /* extern_decl: EXTERN FN IDENT '(' param_list ',' ELLIPSIS ')' ARROW type ';'  */
#line 114 "src/parser.y"
                                                                     {
        auto* fd = new FunctionDecl(std::shared_ptr<Type>((yyvsp[-1].type)), *(yyvsp[-8].sval), std::move(*(yyvsp[-6].param_list)), nullptr);
        fd->isVariadic = true;
        (yyval.decl) = setLoc(fd, (yylsp[-10]));
        delete (yyvsp[-8].sval); delete (yyvsp[-6].param_list);
    }
#line 1516 "src/parser.tab.cpp"
    break;

  case 15: /* func_decl: FN IDENT '(' param_list ')' ARROW type block_stmt  */
#line 123 "src/parser.y"
                                                      {
        (yyval.decl) = setLoc(new FunctionDecl(std::shared_ptr<Type>((yyvsp[-1].type)), *(yyvsp[-6].sval), std::move(*(yyvsp[-4].param_list)), std::unique_ptr<BlockStmt>(static_cast<BlockStmt*>((yyvsp[0].stmt)))), (yylsp[-7]));
        delete (yyvsp[-6].sval); delete (yyvsp[-4].param_list);
    }
#line 1525 "src/parser.tab.cpp"
    break;

  case 16: /* func_decl: FN IDENT '(' param_list ')' ARROW type ';'  */
#line 127 "src/parser.y"
                                                 {
        (yyval.decl) = setLoc(new FunctionDecl(std::shared_ptr<Type>((yyvsp[-1].type)), *(yyvsp[-6].sval), std::move(*(yyvsp[-4].param_list)), nullptr), (yylsp[-7]));
        delete (yyvsp[-6].sval); delete (yyvsp[-4].param_list);
    }
#line 1534 "src/parser.tab.cpp"
    break;

  case 17: /* param_list: %empty  */
#line 134 "src/parser.y"
                { (yyval.param_list) = new std::vector<FunctionDecl::Param>(); }
#line 1540 "src/parser.tab.cpp"
    break;

  case 18: /* param_list: IDENT ':' type  */
#line 135 "src/parser.y"
                     { (yyval.param_list) = new std::vector<FunctionDecl::Param>(); (yyval.param_list)->push_back({std::shared_ptr<Type>((yyvsp[0].type)), *(yyvsp[-2].sval)}); delete (yyvsp[-2].sval); }
#line 1546 "src/parser.tab.cpp"
    break;

  case 19: /* param_list: param_list ',' IDENT ':' type  */
#line 136 "src/parser.y"
                                    { if ((yyvsp[-4].param_list)) (yyvsp[-4].param_list)->push_back({std::shared_ptr<Type>((yyvsp[0].type)), *(yyvsp[-2].sval)}); delete (yyvsp[-2].sval); (yyval.param_list) = (yyvsp[-4].param_list); }
#line 1552 "src/parser.tab.cpp"
    break;

  case 20: /* struct_decl: STRUCT IDENT '{' field_list '}'  */
#line 140 "src/parser.y"
                                    {
        (yyval.decl) = setLoc(new StructDecl(*(yyvsp[-3].sval), std::move(*(yyvsp[-1].field_list))), (yylsp[-4]));
        delete (yyvsp[-3].sval); delete (yyvsp[-1].field_list);
    }
#line 1561 "src/parser.tab.cpp"
    break;

  case 21: /* field_list: %empty  */
#line 147 "src/parser.y"
                { (yyval.field_list) = new std::vector<StructDecl::Field>(); }
#line 1567 "src/parser.tab.cpp"
    break;

  case 22: /* field_list: IDENT ':' type ';'  */
#line 148 "src/parser.y"
                         { (yyval.field_list) = new std::vector<StructDecl::Field>(); (yyval.field_list)->push_back({std::shared_ptr<Type>((yyvsp[-1].type)), *(yyvsp[-3].sval)}); delete (yyvsp[-3].sval); }
#line 1573 "src/parser.tab.cpp"
    break;

  case 23: /* field_list: field_list IDENT ':' type ';'  */
#line 149 "src/parser.y"
                                    { if ((yyvsp[-4].field_list)) (yyvsp[-4].field_list)->push_back({std::shared_ptr<Type>((yyvsp[-1].type)), *(yyvsp[-3].sval)}); delete (yyvsp[-3].sval); (yyval.field_list) = (yyvsp[-4].field_list); }
#line 1579 "src/parser.tab.cpp"
    break;

  case 24: /* impl_block: IMPL IDENT '{' decl_list '}'  */
#line 153 "src/parser.y"
                                 {
        std::vector<std::unique_ptr<MethodDecl>> methods;
        if ((yyvsp[-1].decl_list)) {
            for(auto& d : *(yyvsp[-1].decl_list)) {
                if (auto* fd = dynamic_cast<FunctionDecl*>(d.release())) {
                    methods.push_back(std::make_unique<MethodDecl>(*(yyvsp[-3].sval), std::unique_ptr<FunctionDecl>(fd)));
                }
            }
            delete (yyvsp[-1].decl_list);
        }
        (yyval.decl) = setLoc(new ImplDecl(*(yyvsp[-3].sval), std::move(methods)), (yylsp[-4]));
        delete (yyvsp[-3].sval);
    }
#line 1597 "src/parser.tab.cpp"
    break;

  case 25: /* type: base_type  */
#line 169 "src/parser.y"
              { (yyval.type) = (yyvsp[0].type); }
#line 1603 "src/parser.tab.cpp"
    break;

  case 26: /* type: type '*'  */
#line 170 "src/parser.y"
               { (yyval.type) = new PointerType(std::shared_ptr<Type>((yyvsp[-1].type))); }
#line 1609 "src/parser.tab.cpp"
    break;

  case 27: /* type: type '[' IVAL ']'  */
#line 171 "src/parser.y"
                        { (yyval.type) = new ArrayType(std::shared_ptr<Type>((yyvsp[-3].type)), (int)(yyvsp[-1].ival)); }
#line 1615 "src/parser.tab.cpp"
    break;

  case 28: /* base_type: VOID  */
#line 175 "src/parser.y"
         { (yyval.type) = new ScalarType(TypeKind::Void); }
#line 1621 "src/parser.tab.cpp"
    break;

  case 29: /* base_type: INT  */
#line 176 "src/parser.y"
          { (yyval.type) = new ScalarType(TypeKind::Int); }
#line 1627 "src/parser.tab.cpp"
    break;

  case 30: /* base_type: INT16  */
#line 177 "src/parser.y"
            { (yyval.type) = new ScalarType(TypeKind::Int16); }
#line 1633 "src/parser.tab.cpp"
    break;

  case 31: /* base_type: INT32  */
#line 178 "src/parser.y"
            { (yyval.type) = new ScalarType(TypeKind::Int32); }
#line 1639 "src/parser.tab.cpp"
    break;

  case 32: /* base_type: INT64  */
#line 179 "src/parser.y"
            { (yyval.type) = new ScalarType(TypeKind::Int64); }
#line 1645 "src/parser.tab.cpp"
    break;

  case 33: /* base_type: FLOAT  */
#line 180 "src/parser.y"
            { (yyval.type) = new ScalarType(TypeKind::Float); }
#line 1651 "src/parser.tab.cpp"
    break;

  case 34: /* base_type: FLOAT16  */
#line 181 "src/parser.y"
              { (yyval.type) = new ScalarType(TypeKind::Float16); }
#line 1657 "src/parser.tab.cpp"
    break;

  case 35: /* base_type: FLOAT32  */
#line 182 "src/parser.y"
              { (yyval.type) = new ScalarType(TypeKind::Float32); }
#line 1663 "src/parser.tab.cpp"
    break;

  case 36: /* base_type: FLOAT64  */
#line 183 "src/parser.y"
              { (yyval.type) = new ScalarType(TypeKind::Float64); }
#line 1669 "src/parser.tab.cpp"
    break;

  case 37: /* base_type: BOOL  */
#line 184 "src/parser.y"
           { (yyval.type) = new ScalarType(TypeKind::Bool); }
#line 1675 "src/parser.tab.cpp"
    break;

  case 38: /* base_type: CHAR  */
#line 185 "src/parser.y"
           { (yyval.type) = new ScalarType(TypeKind::Char); }
#line 1681 "src/parser.tab.cpp"
    break;

  case 39: /* base_type: STRING  */
#line 186 "src/parser.y"
             { (yyval.type) = new ScalarType(TypeKind::String); }
#line 1687 "src/parser.tab.cpp"
    break;

  case 40: /* base_type: IDENT  */
#line 187 "src/parser.y"
            { (yyval.type) = new StructType(*(yyvsp[0].sval)); delete (yyvsp[0].sval); }
#line 1693 "src/parser.tab.cpp"
    break;

  case 41: /* stmt: expr_stmt  */
#line 191 "src/parser.y"
              { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1699 "src/parser.tab.cpp"
    break;

  case 42: /* stmt: var_decl_stmt  */
#line 192 "src/parser.y"
                    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1705 "src/parser.tab.cpp"
    break;

  case 43: /* stmt: block_stmt  */
#line 193 "src/parser.y"
                 { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1711 "src/parser.tab.cpp"
    break;

  case 44: /* stmt: if_stmt  */
#line 194 "src/parser.y"
              { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1717 "src/parser.tab.cpp"
    break;

  case 45: /* stmt: while_stmt  */
#line 195 "src/parser.y"
                 { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1723 "src/parser.tab.cpp"
    break;

  case 46: /* stmt: return_stmt  */
#line 196 "src/parser.y"
                  { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1729 "src/parser.tab.cpp"
    break;

  case 47: /* expr_stmt: expr ';'  */
#line 200 "src/parser.y"
             { (yyval.stmt) = setLoc(new ExprStmt(std::unique_ptr<Expr>((yyvsp[-1].expr))), (yylsp[-1])); }
#line 1735 "src/parser.tab.cpp"
    break;

  case 48: /* var_decl_stmt: VAR IDENT ':' type ';'  */
#line 204 "src/parser.y"
                           { (yyval.stmt) = setLoc(new VarDeclStmt(std::shared_ptr<Type>((yyvsp[-1].type)), *(yyvsp[-3].sval)), (yylsp[-4])); delete (yyvsp[-3].sval); }
#line 1741 "src/parser.tab.cpp"
    break;

  case 49: /* var_decl_stmt: VAR IDENT ':' type '=' expr ';'  */
#line 205 "src/parser.y"
                                      { (yyval.stmt) = setLoc(new VarDeclStmt(std::shared_ptr<Type>((yyvsp[-3].type)), *(yyvsp[-5].sval), std::unique_ptr<Expr>((yyvsp[-1].expr))), (yylsp[-6])); delete (yyvsp[-5].sval); }
#line 1747 "src/parser.tab.cpp"
    break;

  case 50: /* block_stmt: '{' stmt_list '}'  */
#line 209 "src/parser.y"
                      { (yyval.stmt) = setLoc(new BlockStmt(std::move(*(yyvsp[-1].stmt_list))), (yylsp[-2])); delete (yyvsp[-1].stmt_list); }
#line 1753 "src/parser.tab.cpp"
    break;

  case 51: /* stmt_list: %empty  */
#line 213 "src/parser.y"
                { (yyval.stmt_list) = new std::vector<std::unique_ptr<Stmt>>(); }
#line 1759 "src/parser.tab.cpp"
    break;

  case 52: /* stmt_list: stmt_list stmt  */
#line 214 "src/parser.y"
                     { if ((yyvsp[-1].stmt_list) && (yyvsp[0].stmt)) (yyvsp[-1].stmt_list)->push_back(std::unique_ptr<Stmt>((yyvsp[0].stmt))); (yyval.stmt_list) = (yyvsp[-1].stmt_list); }
#line 1765 "src/parser.tab.cpp"
    break;

  case 53: /* if_stmt: IF '(' expr ')' stmt  */
#line 218 "src/parser.y"
                         { (yyval.stmt) = setLoc(new IfStmt(std::unique_ptr<Expr>((yyvsp[-2].expr)), std::unique_ptr<Stmt>((yyvsp[0].stmt))), (yylsp[-4])); }
#line 1771 "src/parser.tab.cpp"
    break;

  case 54: /* if_stmt: IF '(' expr ')' stmt ELSE stmt  */
#line 219 "src/parser.y"
                                     { (yyval.stmt) = setLoc(new IfStmt(std::unique_ptr<Expr>((yyvsp[-4].expr)), std::unique_ptr<Stmt>((yyvsp[-2].stmt)), std::unique_ptr<Stmt>((yyvsp[0].stmt))), (yylsp[-6])); }
#line 1777 "src/parser.tab.cpp"
    break;

  case 55: /* while_stmt: WHILE '(' expr ')' stmt  */
#line 223 "src/parser.y"
                            { (yyval.stmt) = setLoc(new WhileStmt(std::unique_ptr<Expr>((yyvsp[-2].expr)), std::unique_ptr<Stmt>((yyvsp[0].stmt))), (yylsp[-4])); }
#line 1783 "src/parser.tab.cpp"
    break;

  case 56: /* return_stmt: RETURN ';'  */
#line 227 "src/parser.y"
               { (yyval.stmt) = setLoc(new ReturnStmt(), (yylsp[-1])); }
#line 1789 "src/parser.tab.cpp"
    break;

  case 57: /* return_stmt: RETURN expr ';'  */
#line 228 "src/parser.y"
                      { (yyval.stmt) = setLoc(new ReturnStmt(std::unique_ptr<Expr>((yyvsp[-1].expr))), (yylsp[-2])); }
#line 1795 "src/parser.tab.cpp"
    break;

  case 58: /* expr: equality_expr  */
#line 232 "src/parser.y"
                  { (yyval.expr) = (yyvsp[0].expr); }
#line 1801 "src/parser.tab.cpp"
    break;

  case 59: /* expr: postfix_expr '=' expr  */
#line 233 "src/parser.y"
                            { (yyval.expr) = setLoc(new BinaryExpr("=", std::unique_ptr<Expr>((yyvsp[-2].expr)), std::unique_ptr<Expr>((yyvsp[0].expr))), (yylsp[-2])); }
#line 1807 "src/parser.tab.cpp"
    break;

  case 60: /* equality_expr: relational_expr  */
#line 237 "src/parser.y"
                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1813 "src/parser.tab.cpp"
    break;

  case 61: /* equality_expr: equality_expr EQ relational_expr  */
#line 238 "src/parser.y"
                                       { (yyval.expr) = setLoc(new BinaryExpr("==", std::unique_ptr<Expr>((yyvsp[-2].expr)), std::unique_ptr<Expr>((yyvsp[0].expr))), (yylsp[-2])); }
#line 1819 "src/parser.tab.cpp"
    break;

  case 62: /* equality_expr: equality_expr NE relational_expr  */
#line 239 "src/parser.y"
                                       { (yyval.expr) = setLoc(new BinaryExpr("!=", std::unique_ptr<Expr>((yyvsp[-2].expr)), std::unique_ptr<Expr>((yyvsp[0].expr))), (yylsp[-2])); }
#line 1825 "src/parser.tab.cpp"
    break;

  case 63: /* relational_expr: shift_expr  */
#line 243 "src/parser.y"
               { (yyval.expr) = (yyvsp[0].expr); }
#line 1831 "src/parser.tab.cpp"
    break;

  case 64: /* relational_expr: relational_expr '<' shift_expr  */
#line 244 "src/parser.y"
                                     { (yyval.expr) = setLoc(new BinaryExpr("<", std::unique_ptr<Expr>((yyvsp[-2].expr)), std::unique_ptr<Expr>((yyvsp[0].expr))), (yylsp[-2])); }
#line 1837 "src/parser.tab.cpp"
    break;

  case 65: /* relational_expr: relational_expr '>' shift_expr  */
#line 245 "src/parser.y"
                                     { (yyval.expr) = setLoc(new BinaryExpr(">", std::unique_ptr<Expr>((yyvsp[-2].expr)), std::unique_ptr<Expr>((yyvsp[0].expr))), (yylsp[-2])); }
#line 1843 "src/parser.tab.cpp"
    break;

  case 66: /* relational_expr: relational_expr LE shift_expr  */
#line 246 "src/parser.y"
                                    { (yyval.expr) = setLoc(new BinaryExpr("<=", std::unique_ptr<Expr>((yyvsp[-2].expr)), std::unique_ptr<Expr>((yyvsp[0].expr))), (yylsp[-2])); }
#line 1849 "src/parser.tab.cpp"
    break;

  case 67: /* relational_expr: relational_expr GE shift_expr  */
#line 247 "src/parser.y"
                                    { (yyval.expr) = setLoc(new BinaryExpr(">=", std::unique_ptr<Expr>((yyvsp[-2].expr)), std::unique_ptr<Expr>((yyvsp[0].expr))), (yylsp[-2])); }
#line 1855 "src/parser.tab.cpp"
    break;

  case 68: /* shift_expr: add_expr  */
#line 251 "src/parser.y"
             { (yyval.expr) = (yyvsp[0].expr); }
#line 1861 "src/parser.tab.cpp"
    break;

  case 69: /* shift_expr: shift_expr SHL add_expr  */
#line 252 "src/parser.y"
                              { (yyval.expr) = setLoc(new BinaryExpr("<<", std::unique_ptr<Expr>((yyvsp[-2].expr)), std::unique_ptr<Expr>((yyvsp[0].expr))), (yylsp[-2])); }
#line 1867 "src/parser.tab.cpp"
    break;

  case 70: /* shift_expr: shift_expr SHR add_expr  */
#line 253 "src/parser.y"
                              { (yyval.expr) = setLoc(new BinaryExpr(">>", std::unique_ptr<Expr>((yyvsp[-2].expr)), std::unique_ptr<Expr>((yyvsp[0].expr))), (yylsp[-2])); }
#line 1873 "src/parser.tab.cpp"
    break;

  case 71: /* add_expr: mul_expr  */
#line 257 "src/parser.y"
             { (yyval.expr) = (yyvsp[0].expr); }
#line 1879 "src/parser.tab.cpp"
    break;

  case 72: /* add_expr: add_expr '+' mul_expr  */
#line 258 "src/parser.y"
                            { (yyval.expr) = setLoc(new BinaryExpr("+", std::unique_ptr<Expr>((yyvsp[-2].expr)), std::unique_ptr<Expr>((yyvsp[0].expr))), (yylsp[-2])); }
#line 1885 "src/parser.tab.cpp"
    break;

  case 73: /* add_expr: add_expr '-' mul_expr  */
#line 259 "src/parser.y"
                            { (yyval.expr) = setLoc(new BinaryExpr("-", std::unique_ptr<Expr>((yyvsp[-2].expr)), std::unique_ptr<Expr>((yyvsp[0].expr))), (yylsp[-2])); }
#line 1891 "src/parser.tab.cpp"
    break;

  case 74: /* mul_expr: cast_expr  */
#line 263 "src/parser.y"
              { (yyval.expr) = (yyvsp[0].expr); }
#line 1897 "src/parser.tab.cpp"
    break;

  case 75: /* mul_expr: mul_expr '*' cast_expr  */
#line 264 "src/parser.y"
                             { (yyval.expr) = setLoc(new BinaryExpr("*", std::unique_ptr<Expr>((yyvsp[-2].expr)), std::unique_ptr<Expr>((yyvsp[0].expr))), (yylsp[-2])); }
#line 1903 "src/parser.tab.cpp"
    break;

  case 76: /* mul_expr: mul_expr '/' cast_expr  */
#line 265 "src/parser.y"
                             { (yyval.expr) = setLoc(new BinaryExpr("/", std::unique_ptr<Expr>((yyvsp[-2].expr)), std::unique_ptr<Expr>((yyvsp[0].expr))), (yylsp[-2])); }
#line 1909 "src/parser.tab.cpp"
    break;

  case 77: /* mul_expr: mul_expr '%' cast_expr  */
#line 266 "src/parser.y"
                             { (yyval.expr) = setLoc(new BinaryExpr("%", std::unique_ptr<Expr>((yyvsp[-2].expr)), std::unique_ptr<Expr>((yyvsp[0].expr))), (yylsp[-2])); }
#line 1915 "src/parser.tab.cpp"
    break;

  case 78: /* cast_expr: unary_expr  */
#line 270 "src/parser.y"
               { (yyval.expr) = (yyvsp[0].expr); }
#line 1921 "src/parser.tab.cpp"
    break;

  case 79: /* cast_expr: unary_expr AS type  */
#line 271 "src/parser.y"
                         { (yyval.expr) = setLoc(new CastExpr(std::shared_ptr<Type>((yyvsp[0].type)), std::unique_ptr<Expr>((yyvsp[-2].expr))), (yylsp[-1])); }
#line 1927 "src/parser.tab.cpp"
    break;

  case 80: /* unary_expr: postfix_expr  */
#line 275 "src/parser.y"
                 { (yyval.expr) = (yyvsp[0].expr); }
#line 1933 "src/parser.tab.cpp"
    break;

  case 81: /* unary_expr: '-' unary_expr  */
#line 276 "src/parser.y"
                     { (yyval.expr) = setLoc(new UnaryExpr("-", std::unique_ptr<Expr>((yyvsp[0].expr))), (yylsp[-1])); }
#line 1939 "src/parser.tab.cpp"
    break;

  case 82: /* unary_expr: '!' unary_expr  */
#line 277 "src/parser.y"
                     { (yyval.expr) = setLoc(new UnaryExpr("!", std::unique_ptr<Expr>((yyvsp[0].expr))), (yylsp[-1])); }
#line 1945 "src/parser.tab.cpp"
    break;

  case 83: /* unary_expr: '&' unary_expr  */
#line 278 "src/parser.y"
                     { (yyval.expr) = setLoc(new UnaryExpr("&", std::unique_ptr<Expr>((yyvsp[0].expr))), (yylsp[-1])); }
#line 1951 "src/parser.tab.cpp"
    break;

  case 84: /* unary_expr: '*' unary_expr  */
#line 279 "src/parser.y"
                     { (yyval.expr) = setLoc(new UnaryExpr("*", std::unique_ptr<Expr>((yyvsp[0].expr))), (yylsp[-1])); }
#line 1957 "src/parser.tab.cpp"
    break;

  case 85: /* postfix_expr: primary_expr  */
#line 283 "src/parser.y"
                 { (yyval.expr) = (yyvsp[0].expr); }
#line 1963 "src/parser.tab.cpp"
    break;

  case 86: /* postfix_expr: postfix_expr '.' IDENT  */
#line 284 "src/parser.y"
                             { (yyval.expr) = setLoc(new MemberAccessExpr(std::unique_ptr<Expr>((yyvsp[-2].expr)), *(yyvsp[0].sval)), (yylsp[-1])); delete (yyvsp[0].sval); }
#line 1969 "src/parser.tab.cpp"
    break;

  case 87: /* postfix_expr: postfix_expr '(' arg_list ')'  */
#line 285 "src/parser.y"
                                    {
        if (auto* ve = dynamic_cast<VariableExpr*>((yyvsp[-3].expr))) {
            (yyval.expr) = setLoc(new CallExpr(ve->name, std::move(*(yyvsp[-1].expr_list))), (yylsp[-3]));
            delete ve;
        } else if (auto* ma = dynamic_cast<MemberAccessExpr*>((yyvsp[-3].expr))) {
            (yyval.expr) = setLoc(new MethodCallExpr(std::move(ma->object), ma->member, std::move(*(yyvsp[-1].expr_list))), (yylsp[-3]));
            delete ma;
        } else {
            yyerror("Invalid call target");
            (yyval.expr) = (yyvsp[-3].expr);
        }
        delete (yyvsp[-1].expr_list);
    }
#line 1987 "src/parser.tab.cpp"
    break;

  case 88: /* postfix_expr: postfix_expr '[' expr ']'  */
#line 298 "src/parser.y"
                                { (yyval.expr) = setLoc(new IndexExpr(std::unique_ptr<Expr>((yyvsp[-3].expr)), std::unique_ptr<Expr>((yyvsp[-1].expr))), (yylsp[-2])); }
#line 1993 "src/parser.tab.cpp"
    break;

  case 89: /* arg_list: %empty  */
#line 302 "src/parser.y"
                { (yyval.expr_list) = new std::vector<std::unique_ptr<Expr>>(); }
#line 1999 "src/parser.tab.cpp"
    break;

  case 90: /* arg_list: expr  */
#line 303 "src/parser.y"
           { (yyval.expr_list) = new std::vector<std::unique_ptr<Expr>>(); (yyval.expr_list)->push_back(std::unique_ptr<Expr>((yyvsp[0].expr))); }
#line 2005 "src/parser.tab.cpp"
    break;

  case 91: /* arg_list: arg_list ',' expr  */
#line 304 "src/parser.y"
                        { if ((yyvsp[-2].expr_list)) (yyvsp[-2].expr_list)->push_back(std::unique_ptr<Expr>((yyvsp[0].expr))); (yyval.expr_list) = (yyvsp[-2].expr_list); }
#line 2011 "src/parser.tab.cpp"
    break;

  case 92: /* primary_expr: IDENT  */
#line 308 "src/parser.y"
          { (yyval.expr) = setLoc(new VariableExpr(*(yyvsp[0].sval)), (yylsp[0])); delete (yyvsp[0].sval); }
#line 2017 "src/parser.tab.cpp"
    break;

  case 93: /* primary_expr: IVAL  */
#line 309 "src/parser.y"
           { (yyval.expr) = setLoc(new IntLiteral((yyvsp[0].ival)), (yylsp[0])); }
#line 2023 "src/parser.tab.cpp"
    break;

  case 94: /* primary_expr: FVAL  */
#line 310 "src/parser.y"
           { (yyval.expr) = setLoc(new FloatLiteral((yyvsp[0].fval)), (yylsp[0])); }
#line 2029 "src/parser.tab.cpp"
    break;

  case 95: /* primary_expr: SVAL  */
#line 311 "src/parser.y"
           { (yyval.expr) = setLoc(new StringLiteral(*(yyvsp[0].sval)), (yylsp[0])); delete (yyvsp[0].sval); }
#line 2035 "src/parser.tab.cpp"
    break;

  case 96: /* primary_expr: TRUE  */
#line 312 "src/parser.y"
           { (yyval.expr) = setLoc(new BoolLiteral(true), (yylsp[0])); }
#line 2041 "src/parser.tab.cpp"
    break;

  case 97: /* primary_expr: FALSE  */
#line 313 "src/parser.y"
            { (yyval.expr) = setLoc(new BoolLiteral(false), (yylsp[0])); }
#line 2047 "src/parser.tab.cpp"
    break;

  case 98: /* primary_expr: '(' expr ')'  */
#line 314 "src/parser.y"
                   { (yyval.expr) = (yyvsp[-1].expr); }
#line 2053 "src/parser.tab.cpp"
    break;


#line 2057 "src/parser.tab.cpp"

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

#line 317 "src/parser.y"


void yyerror(const char *s) {
    std::cerr << "Parse error: " << s << " at line " << yylineno << std::endl;
}
