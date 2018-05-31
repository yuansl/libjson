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

#include "json-object.h"

#include "json-grammar.tab.hh"

extern FlexLexer *lex_parser;
namespace json {
    class json {
    public:
	json() : yyin("/dev/tty"), flex(nullptr) {}
	json(const char *filename, FlexLexer **lex) : yyin(filename),
				     flex(new yyFlexLexer(yyin, std::cout)) {

	    *lex = flex;

	    yyparse(jobj, jarray);
	    
	    if (!jarray.empty())
		json_doc_type = JSON_ARRAY;
	    switch (json_doc_type) {
	    case JSON_OBJECT:
		std::cout << "{\n";
		for (auto it = jobj.begin(); it != jobj.end(); it++) {
		    std::cout << (*it).first << ':' << (*it).second;
		    if (std::next(it) != jobj.end())
			std::cout << ',';
		    std::cout << "\n";
		}
		std::cout << "}\n";
		break;
	    case JSON_ARRAY:
		for (auto &item : jarray)
		    std::cout << item << '\n';
		break;
	    default:
		break;
	    }
	}

	json(const std::string &filename) : yyin(filename),
				       flex(new yyFlexLexer(yyin, std::cout)) {

	    yyparse(jobj, jarray);
	}
	
	~json() {
	    if (yyin.is_open())
		yyin.close();
	    
	    if (flex != nullptr)
		delete flex;
	}
	json(const json &rhs) = delete;
	json(json &&) = delete;
	json &operator=(const json &rhs) = delete;
	json &operator=(json &&) = delete;
    
	json_object loads(const char *json_contents) {
	    json_object jobj;
	    
	    return jobj;
	}
	void load(int fd) {
	    
	}
	void load(std::istream &fin) {
	    flex->switch_streams(fin, std::cout);
	    if (flex != nullptr)
		delete flex;
	    flex = new yyFlexLexer(yyin, std::cout);

	    yyparse(jobj, jarray);
	}
	friend int yylex(FlexLexer *flex = nullptr);
	void dumps(std::string);

	void json_parser(const char *json_contents);

	std::string version() const { return "v1.0"; }
    private:
	std::ifstream yyin;
	FlexLexer *flex;
	enum json_type json_doc_type = JSON_OBJECT;
	json_object jobj;
	json_array jarray;
    };
}

#endif
