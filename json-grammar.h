/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_JSON_GRAMMAR_H_INCLUDED
# define YY_YY_JSON_GRAMMAR_H_INCLUDED
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
    NUMBER = 258,
    STRING = 259,
    LSQUARE_BRAC = 260,
    RSQUARE_BRAC = 261,
    OPENBRACKET = 262,
    CLOSEBRACKET = 263,
    COLON = 264,
    DOUBLE_QUOTE = 265,
    COMMA = 266,
    TRUE = 267,
    FALSE = 268,
    NIL = 269
  };
#endif
/* Tokens.  */
#define NUMBER 258
#define STRING 259
#define LSQUARE_BRAC 260
#define RSQUARE_BRAC 261
#define OPENBRACKET 262
#define CLOSEBRACKET 263
#define COLON 264
#define DOUBLE_QUOTE 265
#define COMMA 266
#define TRUE 267
#define FALSE 268
#define NIL 269

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 13 "json-grammar.y" /* yacc.c:1909  */

	double jnumber;
	const char *jstring;
	char jchar;

#line 88 "json-grammar.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_JSON_GRAMMAR_H_INCLUDED  */
