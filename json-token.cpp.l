/* -*- c++ -*- */
%{
#include "json-object.h"
#include "json-grammar.tab.hh"
extern bool first_token;
extern bool doc_type_object;
%}

%option noyywrap c++

digit  [0-9]
alnum  [-0-9a-zA-Z]
whitespace [ \t\v\r\n\f]
%%
{digit}+(\.{digit}*((E|e)(\+|\-)?)?{digit}*)? {
	              yylval.jnumber = atof(yytext); return NUMBER; }
"{"                  {if (first_token) { first_token = false; } yylval.jchar=yytext[0];        return OPENBRACKET; }
"}"                  {yylval.jchar=yytext[0];        return CLOSEBRACKET;}
"["                  { if (first_token) { doc_type_object = false; first_token = false; } yylval.jchar=yytext[0];        return LSQUARE_BRAC;}
"]"                  {yylval.jchar=yytext[0];        return RSQUARE_BRAC;}
":"                  {yylval.jchar=yytext[0];        return COLON;	 }
","                  {yylval.jchar=yytext[0];        return COMMA;	 }
\"(\\.|[^\"\\])*\"   {strcpy(yylval.jstring,yytext);         return STRING;	 }
"null"               {strcpy(yylval.jstring,yytext);         return NIL;	 }
"false"              {strcpy(yylval.jstring,yytext);         return FALSE;	 }
"true"               {strcpy(yylval.jstring,yytext);         return TRUE;        }
{whitespace}*
%%
