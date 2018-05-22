#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <FlexLexer.h>
#include "json-grammar.tab.hh"

#include "json-object.h"

#include "json.h"

json::json_object jobj;

FlexLexer *lex_parser = new yyFlexLexer;

int yylex(void)
{
    return lex_parser->yylex();
}

int main(void)
{
    /* parser start */
    yyparse();

    std::cout << "yyparse done\n";

    for (auto &item : jobj)
	std::cout << item.first << ":" << item.second << '\n';

    delete lex_parser;

    return 0;
}
