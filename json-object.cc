#include <cstddef>

#include <iostream>
#include <map>
#include <utility>

#include <FlexLexer.h>

#include "json-object.h"
#include "json-grammar.tab.hh"

namespace json {
    const char *__json_type_desc[] = {
	[JSON_EMPTY] = "JSON_EMPTY",
	[JSON_NULL] = "JSON_NULL",
	[JSON_INT] = "JSON_INT",
	[JSON_NUMBER] = "JSON_NUMBER",
	[JSON_CHAR] = "JSON_CHAR",
	[JSON_STRING] = "JSON_STRING",
	[JSON_ARRAY] = "JSON_ARRAY",
	[JSON_OBJECT] = "JSON_OBJECT",
	[JSON_BOOL] = "JSON_BOOL"
    };

    json_value &json_value::operator=(json_value &&rvalue)
    {
	// std::cout << __PRETTY_FUNCTION__ << ":::::" << rvalue;
	
	*this = rvalue;
	return *this;
    }
        
    json_value &json_value::operator=(const json_value &rvalue) {

	// std::cout << __PRETTY_FUNCTION__ << "\n";
	
	value_type = rvalue.value_type;
	switch (rvalue.value_type) {
	case JSON_NULL:
	    value.json_null = rvalue.value.json_null;
	    break;
	case JSON_NUMBER:
	    value.json_number = rvalue.value.json_number;
	    break;
	case JSON_INT:
	    value.json_int = rvalue.value.json_int;
	    break;
	case JSON_STRING:
	    new (&value.json_string) std::string; // it needed to active another member
	    value.json_string = rvalue.value.json_string;
	    break;
	case JSON_OBJECT:
	    new (&value.json_obj) json_object;
	    value.json_obj = rvalue.value.json_obj;
	    break;
	case JSON_BOOL:
	    value.json_bool = rvalue.value.json_bool;
	    break;
	default:
	    break;
	}
	return *this;
    }
    
    const char *json_value::type_of(void)
    {
	if (JSON_EMPTY <= value_type && value_type <= JSON_BOOL)
	    return __json_type_desc[value_type];
	else
	    return "unknown type";
    }
    
    std::ostream &operator<<(std::ostream &out, const json_value &other)
    {
	switch (other.value_type) {
	case JSON_CHAR:
	    out << other.value.json_char;
	    break;
	case JSON_INT:
	    out << other.value.json_int;
	    break;
	case JSON_NUMBER:
	    out << other.value.json_number;
	    break;
	case JSON_STRING:
	    out << '"' << other.value.json_string << '"';
	    break;
	case JSON_NULL:
	    out << "null";
	    break;
	case JSON_BOOL:
	    if (other.value.json_bool)
		out << "true";
	    else
		out << "false";
	    break;
	case JSON_OBJECT:
	    out << other.value.json_obj;
	    break;
	default:
	    break;
	}
	return out;
    }
    
    std::ostream &operator<<(std::ostream &out, const json_object &rvalue)
    {
	out << '{';
	for (auto it = rvalue._Imp_object.begin(); it != rvalue._Imp_object.end(); it++) {
	    out << '"' << (*it).first << '"' << ':' << (*it).second;
	    if (std::next(it) != rvalue._Imp_object.end())
		out << ',';
	}
	out << '}';
	
	return out;
    }
}
json::json_object map1;

FlexLexer *lex_parser = new yyFlexLexer;

int yylex(void)
{
    return lex_parser->yylex();
}

int main(void)
{
    /* parser start */
    yyparse();

    return 0;
}
