#include <iostream>

#include "json.h"

FlexLexer *lex_parser = nullptr;

int yylex(void)
{
    if (lex_parser != nullptr)
	return lex_parser->yylex();
    else
	return EOF;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
	fprintf(stderr, "Usage: %s json_file\n", argv[0]);
	exit(1);
    }
    std::cout << "Filename: " << argv[1] << '\n';
    
    //json::json json(argv[1], &lex_parser);

    json::json_array jarray;
    jarray.push_back(3);
    jarray.push_back("hello");

    json::json_value v = jarray[1];

    json::json_value v2 = jarray;
    v = v2;

    std::cout << "v2(" << v << ").type=" << v.type_of() << '\n';
    
    return 0;
}
