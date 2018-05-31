%{
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

#include "json-object.h"

int yylex();
void yyerror(json::json_object &jobj, json::json_array &array, const char *msg);

static json::json_object tmp_jobj;
static json::json_array tmp_jarray;
static json::json_stack curr_stack;
bool first_token = true;
bool doc_type_object = true;
%}
			
/* bison declarations  */
/* %language "c++"			 */
/* %skeleton "lalr1.cc"			 */
/* %define api.value.type variant */

/* %expect 1 */
/* %define api.pure full */
/* %lex-param {YYSTYPE*} */
%parse-param {json::json_object &jobj} {json::json_array &json_array}

%union {
    double jnumber;
    char jstring[BUFSIZ];
    char jchar;
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
	|	member[first_memb] seperator members[Rest] {
		    strcpy($group, $first_memb);
		    if ($seperator == ',') {
			strcat($group, ",");
			strcat($group,$Rest);
		    }
		}
		;
member: 	json_pair { strcpy($$,$1); }
		;

json_pair: 	json_string COLON json_value {
		    strcpy($$, $1);
		    strcat($$,":");
		    strcat($$, $3);
		    if ($json_value[0] == '[') {
			tmp_jobj[$json_string] = tmp_jarray;
			tmp_jarray.clear();
		    } else {
			tmp_jobj[$json_string] = $json_value;
		    }
		}
		;

seperator:
		%empty
	|	COMMA 
		;

json_value:
		json_string { strcpy($$, $1);/* std::cout << "json_string:" << $1 << '\n'; */}
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
		    std::cout << "element=" << $element << '\n';
		    tmp_jarray.push_back($element);
		    
		    if ($element[0] == '{') {
			tmp_jarray.push_back(tmp_jobj);
			tmp_jobj.clear();
		    } else {
			tmp_jarray.push_back($element);
		    }
		}
		;

json_string: 	STRING { strcpy($$,$1);/* std::cout << "string:" << $$ << '\n'; */ }
		;

json_number: 	NUMBER { $$=$1;/* std::cout << "NUMBER:" << $$ << '\n'; */ }
		;
%%
#include "json-object.h"
void yyerror(json::json_object &jobj, json::json_array &array, const char *msg)
{
    std::cerr << "Error: " << msg << '\n';
}
