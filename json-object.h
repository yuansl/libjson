#ifndef JSON_OBJECT_H /* -*- c++ -*- */
#define JSON_OBJECT_H

#include <iostream>
#include <map>
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

    class json_value;
    class json_object {
    public:
	typedef std::string key_type;
	typedef json_value  value_type;
	typedef std::map<key_type, value_type> _Imp_type;
	typedef _Imp_type::iterator iterator;
	typedef _Imp_type::const_iterator const_iterator;
	
	json_object() : _Imp_object() {}
	json_object(const json_object &rvalue) : _Imp_object(rvalue._Imp_object){
	    // std::cout << __PRETTY_FUNCTION__ << '\n';
	}
	json_object(json_object &&rvalue) : _Imp_object(std::move(rvalue._Imp_object)) {
	    // std::cout << __PRETTY_FUNCTION__ << '\n';
	}
	
	iterator begin() { return _Imp_object.begin(); }
	iterator end() { return _Imp_object.end(); }
	value_type &operator[](const std::string key) {
	    return _Imp_object[key];
	}
	bool empty() const { return _Imp_object.empty(); }
	json_object &operator=(const json_object &rvalue) {
	    _Imp_object = rvalue._Imp_object;
	    return *this;
	}

	friend std::ostream &operator<<(std::ostream &out, const json_object &rvalue);
    private:
	_Imp_type _Imp_object;
    };
    
    struct json_value {
	json_value() : value_type(JSON_EMPTY), value() {}
	json_value(double number) : value_type(JSON_NUMBER), value(number) {}
	json_value(int integer) : value_type(JSON_INT), value(integer) {}
	json_value(const char *str) : value_type(JSON_STRING), value(str) {}
	json_value(std::string &str) : value_type(JSON_STRING), value(str) {}
	json_value(std::nullptr_t null) : value_type(JSON_NULL), value(null) {}
	json_value(bool boolean) : value_type(JSON_BOOL), value(boolean) {}
	json_value(json_object &jobj) : value_type(JSON_OBJECT), value(jobj) {
	    // std::cout << __PRETTY_FUNCTION__ << "::this=" << *this << '\n';
	}
	
	// move constructor
	//json_value(json_value &&rvalue) {}
	
	json_value(const json_value &rvalue) : value_type(rvalue.value_type), value(rvalue.value) {
	    // *this = rvalue;
	    // std::cout << __PRETTY_FUNCTION__ << "::rvalue=" << rvalue << '\n';
	}
	// copy assignment operator
	json_value &operator=(const json_value &rvalue);
	// move assignment operator
	json_value &operator=(json_value &&rvalue);
	
	enum json_type value_type;
	union _Imp_type {
	    _Imp_type() {}
	    _Imp_type(int i) : json_int(i) {}
	    _Imp_type(char c) : json_char(c) {}
	    _Imp_type(const char *name) : json_string(name) {}
	    _Imp_type(std::string &name) : json_string(name) {}
	    _Imp_type(double d) : json_number(d) {}
	    _Imp_type(std::nullptr_t null) : json_null(null) {}
	    _Imp_type(bool boolean) : json_bool(boolean) {}
	    _Imp_type(json_object &jobj) : json_obj(jobj) {
		// std::cout << __PRETTY_FUNCTION__ << '\n';
	    }
	    _Imp_type(const _Imp_type &rvalue) {
		
	    }
	    ~_Imp_type() {}
	    char json_char;
	    int json_int;
	    double json_number;
	    std::string json_string;
	    std::nullptr_t json_null;
	    bool json_bool;
	    json_object json_obj;
	} value;

	friend std::ostream &operator<<(std::ostream &out, const json_value &other);
    };
}

#endif
