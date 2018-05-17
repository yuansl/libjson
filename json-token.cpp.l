/* -*- mode: c++ -*- */
%{
#include "json-grammar.tab.hpp"
%}

digit  [0-9]
alnum  [-0-9a-zA-Z]
whitespace [ \t\v\r\n\f]
%%
{digit}+(\.{digit}*((E|e)(\+|\-)?)?{digit}*)? { yylval.jnumber = atof(yytext); return NUMBER;      }
"{"                                           { yylval.jchar = yytext[0];printf("%s", yytext); return OPENBRACKET; }
"}"                                           {yylval.jchar = yytext[0]; return CLOSEBRACKET;}
"["                                           {yylval.jchar = yytext[0]; return LSQUARE_BRAC;}
"]"                                           {yylval.jchar = yytext[0]; return RSQUARE_BRAC;}
":"                                           {yylval.jchar = yytext[0]; return COLON;	    }
","                                           {yylval.jchar = yytext[0]; return COMMA;	    }
\"(\\.|[^\"\\])*\"                            { yylval.jstring = yytext; return STRING;	    }
"null"                                        { yylval.jstring=yytext; return NIL;	    }
"false"                                       { yylval.jstring=yytext; return FALSE;	    }
"true"                                        { yylval.jstring=yytext; return TRUE;	    }
{whitespace}*
%%
