#include <iostream>
#include <fstream>

#include <FlexLexer.h>
#include "json-grammar.tab.hh"

#include "json-object.h"

#include "json.h"

json::json_object jobj;
std::vector<json::json_value> json_array;

FlexLexer *lex_parser;

int yylex(void)
{
    return lex_parser->yylex();
}

int main(int argc, char *argv[])
{
    if (argc < 1) {
	fprintf(stderr, "Usage: %s json_file\n", argv[0]);
	exit(1);
    }

    json::json json(argv[1]);
    
    std::ifstream fp(argv[1]);
    lex_parser = new yyFlexLexer(fp, std::cout);

    /* parser start */
    yyparse();

    std::cout << "yyparse done\n";

    for (auto &item : jobj)
	std::cout << item.first << ":" << item.second << '\n';

    std::cout << "json_array in doc:\n";
    for (auto &item : json_array)
	std::cout << item << '\n';

    delete lex_parser;

    return 0;
}
