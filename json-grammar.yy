%{
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <iostream>

#include "json-object.h"

int yylex();
extern void yyerror(const char *msg);
char tmp[128];
%}
			
/* bison declarations  */
/* %language "c++"			 */
/* %skeleton "lalr1.cc"			 */
/* %define api.value.type variant */

/* %expect 1 */
/* %define api.pure full */
/* %lex-param {YYSTYPE*} */

%union {
    double jnumber;
    char jstring[BUFSIZ];
    char jchar;
    /* json::json_value jvalue; */
}
			
/* token definition */
%token	<jnumber> NUMBER
%token	<jstring> STRING
%token	<jchar> LSQUARE_BRAC RSQUARE_BRAC OPENBRACKET CLOSEBRACKET COLON  DOUBLE_QUOTE COMMA
%token <jstring> TRUE FALSE NIL
 /* specify value type for nonterminal symbols */
%type	<jstring> json_string
%type	<jnumber> json_number
%type	<jstring> json_array
%type	<jstring> json_pair
%type	<jstring> json_value
%type	<jstring> json_object
%type   <jchar>   seperator
%type	<jstring> member
%type	<jstring> members
%type	<jstring> elements
%type	<jstring> element

/* json grammar */
%%
json_doc:
		%empty      { YYACCEPT; }
	|	json_object { YYACCEPT; }
	|	json_array  { YYACCEPT; }
		;

json_object: 	OPENBRACKET members CLOSEBRACKET { sprintf($$, "{%s}",$2); }
		;

members[group]:
		%empty
	|	member[first_memb] seperator members[opt] {
		    strcpy($group, $first_memb);
		    if ($seperator == ',') {
			strcat($group, ",");
			strcat($group,$opt);
		    }
		}
		;
member: 	json_pair { strcpy($$,$1); }
		;

json_pair: 	json_string COLON json_value {
		    strcpy($$, $1);
		    strcat($$,":");
		    strcat($$,$3);
		    jobj[$json_string] = $json_value; }
		;

seperator:
		%empty
	|	COMMA 
		;

json_value:
		json_string { strcpy($$,$1);/* std::cout << "json_string:" << $1 << '\n'; */}
	|	json_number { sprintf($$,"%f",$1);/* std::cout << "json_number:" << $$ << '\n'; */ }
	|	json_object { strcpy($$,$1); }
	|	json_array  { strcpy($$,$1); }
	|	TRUE        { strcpy($$,$1); /* std::cout << $1 << '\n'; */ }
	|	FALSE       { strcpy($$,$1); /* std::cout << $1 << '\n'; */ }
	|	NIL         { strcpy($$,$1); /* std::cout << $1 << '\n'; */ }
		;

json_array: 	LSQUARE_BRAC elements RSQUARE_BRAC { sprintf($$, "[%s]", $2); }
		;

elements:
		%empty
	|	element seperator elements {
		    strcpy($$, $1);
		    if ($seperator == ',') {
			strcat($$, ",");
			strcat($$, $3);
		    }
		}
		;
element: 	json_value {
		    strcpy($$, $1);
		    /* std::cout << "element=" << $element << '\n'; */
		    if ($element[0] == '{') {
			json_array.push_back(jobj);
			jobj.clear();
		    } else {
			json_array.push_back($element);
		    }
		}
		;

json_string: 	STRING { strcpy($$,$1);/* std::cout << "string:" << $$ << '\n'; */ }
		;

json_number: 	NUMBER { $$=$1;/* std::cout << "NUMBER:" << $$ << '\n'; */ }
		;
%%

void yyerror(const char *msg)
{
    std::cerr << "Error: " << msg << '\n';
    yyparse();
}
