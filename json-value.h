// json_value implement -*- c++ -*-
#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <stack>

#include "json-array.h"
#include "json-object.h"

namespace json {
    enum json_type {
	JSON_EMPTY,  // empty object
	JSON_NULL,   // null
	JSON_INT,    // 000
	JSON_NUMBER, // 000.000
	JSON_CHAR,   // 'c'
	JSON_STRING, // ""
	JSON_ARRAY,  // []
	JSON_OBJECT, // {}
	JSON_BOOL    // true or false
    };
    
    struct json_value {
	json_value() : value_type(JSON_EMPTY), value() {}
	json_value(double number) : value_type(JSON_NUMBER), value(number) {}
	json_value(int integer) : value_type(JSON_INT), value(integer) {}
	explicit json_value(char character) : value_type(JSON_CHAR), value(character) {}
	json_value(const char *str) : value_type(JSON_STRING), value(str) {}
	json_value(std::string &str) : value_type(JSON_STRING), value(str) {}
	json_value(std::nullptr_t null) : value_type(JSON_NULL), value(null) {}
	json_value(bool boolean) : value_type(JSON_BOOL), value(boolean) {}
	json_value(json_object &jobj) : value_type(JSON_OBJECT), value(jobj) {}
	json_value(json_array &jarray) : value_type(JSON_ARRAY), value(jarray) {}
	// move constructor
	//json_value(json_value &&rvalue) {}
	
	json_value(const json_value &rvalue) : value_type(rvalue.value_type) {
	    *this = rvalue;
	}
	// copy assignment operator
	json_value &operator=(const json_value &rvalue);
	// move assignment operator
	json_value &operator=(json_value &&rvalue);
	const std::string typeof(void) const;
	std::string tostring(void) const;
	
	enum json_type value_type;
	union _Imp_type {
	    _Imp_type() {}
	    ~_Imp_type() {}
	    _Imp_type(int i) : _M_json_int(i) {}
	    _Imp_type(char c) : _M_json_char(c) {}
	    _Imp_type(const char *name) : _M_json_string(name) {}
	    _Imp_type(std::string &name) : _M_json_string(name) {}
	    _Imp_type(double d) : _M_json_number(d) {}
	    _Imp_type(std::nullptr_t null) : _M_json_null(null) {}
	    _Imp_type(bool boolean) : _M_json_bool(boolean) {}
	    _Imp_type(json_object &jobj) : _M_json_object(jobj) {}
	    _Imp_type(json_array &jarray) : _M_json_array(jarray) {}
	 
	    char _M_json_char;
	    int _M_json_int;
	    double _M_json_number;
	    std::string _M_json_string;
	    std::nullptr_t _M_json_null;
	    bool _M_json_bool;
	    json_object _M_json_object;
	    json_array _M_json_array;
 	} value;

	friend std::ostream &operator<<(std::ostream &out, const json_value &other);
    };
    
    typedef std::stack<json_value> json_stack;
}
#endif
