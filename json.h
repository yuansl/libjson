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

#include "json-value.h"

extern json::json_object last_object;
extern json::json_array last_array;
extern json::json_stack curr_stack;

class FlexLexer;
namespace json {
    struct json {
	json() : yyin("/dev/tty"), flex(new yyFlexLexer) {}
	json(const char *filename, FlexLexer **lex); 
	json(const std::string &filename);
	~json();
	json(const json &rhs) = delete;
	json(json &&) = delete;
	json &operator=(const json &rhs) = delete;
	json &operator=(json &&) = delete;
	
	void load(int fd);
	void load(std::istream &fin);
	void dumps(std::string);
	
	static json_value loads(const char *json_contents);
	// friend int yylex(FlexLexer *flex = nullptr);
    private:
	std::ifstream yyin;
	FlexLexer *flex;
	enum json_type json_doc_type = JSON_OBJECT;
    };
}

#endif
