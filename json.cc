#include <iostream>
#include <sstream>
#include <FlexLexer.h>
#include "json.h"
#include "json-grammar.tab.hh"	// for yyparse

FlexLexer *lex_parser = nullptr;

json::json_object last_object;
json::json_array last_array;
json::json_stack curr_stack;

namespace json {
    json::json(const char *filename, FlexLexer **lex) :
	yyin(filename),
	flex(new yyFlexLexer(yyin, std::cout))
    {
	*lex = flex;

	::yyparse(last_object, last_array);
    }

    json::json(const std::string &filename) :
	yyin(filename),
	flex(new yyFlexLexer(yyin, std::cout))
    {
	::yyparse(last_object, last_array);
    }
    
    json::~json()
    {
	if (flex != nullptr)
	    delete flex;
	flex = nullptr;
    }
    
    void json::load(std::istream &sin)
    {
	if (flex == nullptr) {
	    std::cerr << "Fatal error: flex may be not initialized!\n";
	    return;
	}
	flex->switch_streams(sin, std::cout);
	::yyparse(last_object, last_array);
    }
    
    json_value loads(const char *json_contents)
    {
	json json;
	std::stringstream sout;

	sout << json_contents;
	json.load(sout);
	if (!last_object.empty())
	    return last_object;
	else
	    return last_array;
    }
}

int yylex(void)
{
    if (lex_parser != nullptr)
	return lex_parser->yylex();
    else
	return EOF;
}

void yyerror(json::json_object &jobj, json::json_array &array, const char *msg)
{
    std::cerr << "Error: " << msg << '\n';
}

int main(int argc, char *argv[])
{
#if 0
    if (argc < 2) {
	fprintf(stderr, "Usage: %s json_file\n", argv[0]);
	exit(1);
    }
    std::cout << "Filename: " << argv[1] << '\n';
#endif

    json::json_value val = json::loads("{}");

    std::cout << "Result:\n";
    std::cout << "last object=" << last_object << '\n';
    
    return 0;
}
