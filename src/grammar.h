/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 136 "grammar.y"

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



/* Line 1685 of yacc.c  */
#line 133 "grammar.h"
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



