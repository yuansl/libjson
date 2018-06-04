/* -*- c++ -*- */
%{
#include "json.h"
#include "json-grammar.tab.hh"

extern json::json_stack curr_stack;
extern json::json_object last_object;
extern json::json_array last_array;
%}

%option noyywrap c++

digit  [0-9]
alnum  [-0-9a-zA-Z]
whitespace [ \t\v\r\n\f]
%%
{digit}+(\.{digit}*((E|e)(\+|\-)?)?{digit}*)?    {
                                                  yylval.jnumber = atof(yytext);
						  return NUMBER;
                                                 }

"{"                  {
	curr_stack.push("{");
	json::json_object jobj;
	json::json_value jtop(jobj);
	curr_stack.push(jtop);
	return OPENBRACKET;
                     }

"}"                  {
	yylval.jchar=yytext[0];

	if (curr_stack.size() < 2) {
		std::cerr << "syntax error detected by yylex at '}' token\n";
	} else {
		last_object = curr_stack.top();
		curr_stack.pop();

		// then, the top of the stack should be '{'	
		if (curr_stack.top().tostring() == std::string("{")) {
			curr_stack.pop();
			curr_stack.push(last_object);
		} else {
			std::cerr << "syntax error detected by yylex at '}' token\n";
			return 0;		// EOF
		}
	}
	return CLOSEBRACKET; }

"["                  {
	yylval.jchar=yytext[0];
	curr_stack.push("[");
	json::json_array jarray;
	json::json_value jtop(jarray);
	curr_stack.push(jtop);
	return LSQUARE_BRAC;
                     }

"]"                  {
	yylval.jchar=yytext[0];
	if (curr_stack.size() < 2) {
		std::cerr << "syntax error detected by yylex at '}' token\n";
	} else {
		last_array = curr_stack.top();
		curr_stack.pop();
		if (!curr_stack.empty() && curr_stack.top().tostring()==std::string("[")) {
			curr_stack.pop();	// pop "["
			curr_stack.push(last_array);
		} else {
			std::cerr << "syntax error detected from yylex at ']' token\n";
			return 0;		// EOF
		}
	}
	return RSQUARE_BRAC;
                     }

":"                  { yylval.jchar=yytext[0]; return COLON;	 }
","                  { yylval.jchar=yytext[0]; return COMMA;	 }
\"(\\.|[^\"\\])*\"   { strcpy(yylval.jstring,yytext); return STRING;	 }
"null"               { strcpy(yylval.jstring,yytext); return NIL;	 }
"false"              { strcpy(yylval.jstring,yytext); return FALSE;	 }
"true"               { strcpy(yylval.jstring,yytext); return TRUE;       }
{whitespace}*
%%
