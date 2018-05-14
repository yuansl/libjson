%{
#include <stdlib.h>
#include <stdio.h>
void warning(char *s, char *t);

void yyerror(char *s);
extern int yylex (void);

%}

/* %expect 1 */
/* %language "C" */

%union {
	double jnumber;
	const char *jstring;
	char jchar;
	struct list {
		
	} jarray;
}
/* token definition */
%token <jnumber> NUMBER 
%token <jstring> STRING
%token <jchar> LSQUARE_BRAC RSQUARE_BRAC OPENBRACKET CLOSEBRACKET COLON  DOUBLE_QUOTE COMMA
%token <jstring> TRUE FALSE NIL
 /* specify value type for nonterminal symbols */
%type <jstring> json_string
%type <jnumber> json_number
%type <jarray> json_array
/* json grammar */
%%
__start: json_doc
;
json_doc:  json_object { printf("Json doc parsed done:\n"); exit(0); }
          |json_array { printf("Json doc parsed done:\n"); exit(0); }
;

json_object: OPENBRACKET members CLOSEBRACKET 
;

members:%empty
        |member seperator members
;
member: json_pair

json_pair:json_string COLON json_value 
;

json_array: LSQUARE_BRAC elements RSQUARE_BRAC {printf("json_array:%c\n", $1);}
;

elements:%empty
         |element seperator elements 
;
element: json_value { /* printf($$); */}
;

seperator:%empty
          |COMMA 
;

json_value:json_string
           |json_number  
           |json_object 
           |json_array
           |TRUE  {printf("boolean:%s", $1);}
           |FALSE {printf("boolean:%s", $1);}
           |NIL {printf("NIL:%s", $1);}
;

json_string: STRING {printf("string:%s\n", $$);}
;

json_number: NUMBER  {printf("number:%f\n", $1);}
;
%%

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
char *progname;

void warning(char *s, char *t)
{
	fprintf(stderr, "%s: %s\n", progname, s);
	if (t)
		fprintf(stderr, " %s\n", t);
}

void yyerror(char *s)
{
	warning(s, NULL);
	yyparse();
}

int main(int argc, char *argv[])
{
	progname = argv[0];
	/* parser start */
	yyparse();
	
	return 0;
}
