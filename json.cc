#include <iostream>
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
    
    json::~json() {
	if (yyin.is_open())
	    yyin.close();
	    
	if (flex != nullptr)
	    delete flex;
    }

    void json::load(std::istream &fin)
    {
	flex->switch_streams(fin, std::cout);
	if (flex != nullptr)
	    delete flex;
	flex = new yyFlexLexer(yyin, std::cout);

	::yyparse(last_object, last_array);
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

    json::json json(argv[1], &lex_parser);
    using namespace std;
    cout << "json parsed result:\n";
    cout << "'";
    if (!last_object.empty()) {
	cout << last_object << '\n';
    } else {
	cout << last_array << '\n';
    }
    cout << "'\n";
    return 0;
}
