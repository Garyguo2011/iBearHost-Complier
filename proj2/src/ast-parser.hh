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

extern YYSTYPE yylval;


