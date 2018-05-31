#include <cstdlib>

#include <iostream>
#include <map>
#include <vector>
#include <utility>

#include <FlexLexer.h>

//#include "json-grammar.tab.hh"
#include "json-object.h"

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
    
    std::ostream &operator<<(std::ostream &out, const json_object &rvalue)
    {
	out << '{';
#if 0
	for (auto it = rvalue._Imp_.begin(); it != rvalue._Imp_object.end(); it++) {
	    out << (*it).first << ':' << (*it).second;
	    if (std::next(it) != rvalue._Imp_object.end())
		out << ',';
	}
#endif
	for (auto it = rvalue.begin(); it != rvalue.end(); it=std::next(it)) {
	    out << (*it).first << ':' << (*it).second;
	    if (std::next(it) != rvalue.end())
		out << ',';
	}
	    
	out << '}';
	
	return out;
    }

    std::ostream &operator<<(std::ostream &out, const json_array &array)
    {
	out << "[";
	for (auto it = array.begin(); it != array.end(); it++) {
	    out << *it;
	    if (std::next(it) != array.end())
		out << ',';
	}
	out << "]";
	return out;
    }

    json_value &json_value::operator=(json_value &&rvalue)
    {
	*this = rvalue;
	return *this;
    }

    json_value &json_value::operator=(const json_value &rvalue) {

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
	case JSON_ARRAY:
	    new (&value.jarray) json_array;
	    value.jarray = rvalue.value.jarray;
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
	case JSON_ARRAY:
	    out << other.value.jarray;
	    break;
	default:
	    break;
	}
	return out;
    }
}
