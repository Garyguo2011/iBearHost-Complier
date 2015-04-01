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
     ID = 276,
     IF = 277,
     IF_EXPR = 278,
     INDENT = 279,
     INT_LITERAL = 280,
     LEFT_COMPARE = 281,
     LIST_DISPLAY = 282,
     METHOD = 283,
     MODULE = 284,
     NATIVE = 285,
     NEXT_VALUE = 286,
     NONE = 287,
     NOT = 288,
     OR = 289,
     PAIR = 290,
     PRINT = 291,
     PRINTLN = 292,
     RETURN = 293,
     SLICE = 294,
     SLICE_ASSIGN = 295,
     STMT_LIST = 296,
     STRING_LITERAL = 297,
     SUBSCRIPT = 298,
     SUBSCRIPT_ASSIGN = 299,
     TARGET_LIST = 300,
     TRUE = 301,
     TUPLE = 302,
     TYPE = 303,
     TYPED_ID = 304,
     TYPE_FORMALS_LIST = 305,
     TYPE_LIST = 306,
     TYPE_VAR = 307,
     UNOP = 308,
     WHILE = 309,
     NEW = 310,
     _TOK_0 = 311,
     _TOK_1 = 312,
     _TOK_2 = 313,
     TYPE_VAR_ID = 314
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


