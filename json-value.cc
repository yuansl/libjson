#include <sstream>		// for std::stringstream

#include "json-value.h"

namespace json {
    static const char *__json_type_desc[] = {
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
	*this = rvalue;
	return *this;
    }
    
    json_value &json_value::operator=(const json_value &rvalue) {

	value_type = rvalue.value_type;
	switch (rvalue.value_type) {
	case JSON_NULL:
	    value._M_json_null = rvalue.value._M_json_null;
	    break;
	case JSON_NUMBER:
	    value._M_json_number = rvalue.value._M_json_number;
	    break;
	case JSON_INT:
	    value._M_json_int = rvalue.value._M_json_int;
	    break;
	case JSON_STRING:
	    new (&value._M_json_string) std::string; // it needed to active another member
	    value._M_json_string = rvalue.value._M_json_string;
	    break;
	case JSON_OBJECT:
	    new (&value._M_json_object) json_object;
	    value._M_json_object = rvalue.value._M_json_object;
	    break;
	case JSON_BOOL:
	    value._M_json_bool = rvalue.value._M_json_bool;
	    break;
	case JSON_ARRAY:
	    new (&value._M_json_array) json_array;
	    value._M_json_array = rvalue.value._M_json_array;
	    break;
	default:
	    break;
	}
	return *this;
    }
    
    const std::string json_value::typeof(void) const
    {
	if (JSON_EMPTY <= value_type && value_type <= JSON_BOOL)
	    return std::string(__json_type_desc[value_type]);
	else
	    return std::string("unknown type");
    }
    
    std::string json_value::tostring(void) const
    {
	std::string s;
	std::stringstream sio;
	switch (value_type) {
	case JSON_CHAR:
	    sio << value._M_json_char;
	    break;
	case JSON_INT:
	    sio << value._M_json_int;
	    break;
	case JSON_NUMBER:
	    sio << value._M_json_number;
	    break;
	case JSON_STRING:
	    sio << value._M_json_string;
	    break;
	case JSON_NULL:
	    sio << "null";
	    break;
	case JSON_BOOL:
	    if (value._M_json_bool)
		sio << "true";
	    else
		sio << "false";
	    break;
	case JSON_OBJECT:
	    sio << value._M_json_object;
	    break;
	case JSON_ARRAY:
	    sio << value._M_json_array;
	    break;
	default:
	    break;
	}
	sio >> s;
	return s;
    }
    
    std::ostream &operator<<(std::ostream &out, const json_value &other)
    {
	switch (other.value_type) {
	case JSON_CHAR:
	    out << other.value._M_json_char;
	    break;
	case JSON_INT:
	    out << other.value._M_json_int;
	    break;
	case JSON_NUMBER:
	    out << other.value._M_json_number;
	    break;
	case JSON_STRING:
	    out << other.value._M_json_string;
	    break;
	case JSON_NULL:
	    out << "null";
	    break;
	case JSON_BOOL:
	    if (other.value._M_json_bool)
		out << "true";
	    else
		out << "false";
	    break;
	case JSON_OBJECT:
	    out << other.value._M_json_object;
	    break;
	case JSON_ARRAY:
	    out << other.value._M_json_array;
	    break;
	default:
	    break;
	}
	return out;
    }
}
