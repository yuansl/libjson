%{
#include <cstring>		/* for strcpy(...) */
#include <iostream>
#include "json.h"		/* for namespace json and last_object, last_array, curr_stack */
int yylex(void);
void yyerror(json::json_object &jobj, json::json_array &json_array, const char *msg);
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
    char jstring[BUFSIZ*4];
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
	|	json_object { last_array.clear(); YYACCEPT; }
	|	json_array  { last_object.clear(); YYACCEPT; }
		;

json_object:
                OPENBRACKET members CLOSEBRACKET {
		    sprintf($$, "{%s}",$2);
		}
		;

members[group]:
		%empty
	|	member[first_memb] seperator members[Rest_membs] {
		    strcpy($group, $first_memb);
		    if ($seperator == ',') {
			strcat($group, ",");
			strcat($group,$Rest_membs);
		    }
		}
		;
member: 	json_pair { strcpy($$,$1); }
		;

json_pair: 	json_string COLON json_value {
		    strcpy($$, $1);
		    strcat($$,":");
		    strcat($$, $3);
		    
		    json::json_value the_value;
		    if ($json_value[0] == '{' || $json_value[0] == '[') {
			the_value = curr_stack.top();
			curr_stack.pop(); /* pop json_object or json_array */
		    } else {
			if ($json_value == std::string("true")) {
			    the_value = true;
			} else if ($json_value == std::string("false")) {
			    the_value = false;
			} else if ($json_value == std::string("null")) {
			    the_value = nullptr;
			} else {
			    the_value = $3;
			}
		    }
		
		    if (!curr_stack.empty()) {
			jobj = curr_stack.top();
			curr_stack.pop();
			jobj[$1] = the_value;
			curr_stack.push(jobj);
		    } else {
			std::cerr << "syntax error detected on 'json_pair->json_string COLON json_value;' rule\n";
			YYABORT;
		    }
		}
		;

seperator:
		%empty
	|	COMMA 
		;

json_value:
		json_string { strcpy($$, $1); }
	|	json_number { sprintf($$,"%f",$1); }
	|	json_object { strcpy($$,$1); }
	|	json_array  { strcpy($$,$1); }
	|	TRUE        { strcpy($$,$1); }
	|	FALSE       { strcpy($$,$1); }
	|	NIL         { strcpy($$,$1); }
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
                    json::json_value the_element;
		    if ($json_value[0] == '{' || $json_value[0] == '[') {
			the_element = curr_stack.top();
			curr_stack.pop(); /* pop json_object or json_array */
		    } else {
			the_element = $1;
		    }
		    if (!curr_stack.empty()) {
			json_array = curr_stack.top();
		    	curr_stack.pop();
		    } else {
			std::cerr << "syntax error detected at 'element->json_value;' rule\n";
			YYABORT;
		    }

		    json_array.push_back(the_element);
		    curr_stack.push(json_array);
		}
		;

json_string: 	STRING { strcpy($$,$1); }
		;

json_number: 	NUMBER { $$=$1; }
		;
