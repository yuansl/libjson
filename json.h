// Json implement in -*- c++ -*-
#ifndef JSON_H
#define JSON_H

// json object
// object := { members
//             |empty
//           }
// members := pair, members
//            |empty
// pair    := string : value
// array   := [elements
//             |empty
//            ]
// elments := value, elements
//            |empty
// value   := string
//            |number
//            |object
//            |array
//            |true
//            |false
//            |null
// string :=  " CHARS "
// CHARS  :=  char CHARS
//            |empty
// char   :=  [0-9a-zA-Z\" \\ \/ \b \f \n \r \t \uxxxx]
// number :=  int
//            |int frac
//            |int exp
//            |int frac exp
// int    :=  [[:digit:]]
// frac   :=  .[[:digit:]]
// exp    := e digits
// digits := digit digits
//           |empty
// e      := e[+-]?
//          |E[+-]?
//
// string ->  c++-string
// char   ->  c++-char
// number ->  c++-int

#include <string>
#include <fstream>

#include <FlexLexer.h>
namespace json {
class json {
public:
    json(const char *filename) : yyin(filename), flex(new yyFlexLexer(yyin, std::cout)) {}
    ~json() {
	yyin.close();
	if (flex != nullptr)
	    delete flex;
    }
    json(const json &rhs) = delete;
    json &operator=(const json &rhs) = delete;
    
    void loads(const char *json_contents);
    void load(std::ifstream &newfile) {
	yyin = newfile;
	if (flex != nullptr)
	    delete flex;
	flex = new yyFlexLexer(yyin, std::cout);

	yyparse();
    }
    friend int yylex(FlexLexer *flex = nullptr);
    void dumps(std::string);

    void json_parser(const char *json_contents);

    std::string version() const { return "v1.0"; }
private:
    std::ifstream yyin;
    FlexLexer *flex;
    int json_doc_type = 0;
    void *_M_impl;

    
};
}

#endif
