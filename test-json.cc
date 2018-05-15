#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <cstddef>

#include "json.h"

template<class T>
class Jvalue;

// typedef Jvalue<int> json_int;
// typedef Jvalue<double> json_double;
// typedef Jvalue<std::string> json_string;
// typedef Jvalue<bool> json_boolean;
// typedef Jvalue<nullptr_t> json_null;

template<class T>
class Jobject {
public:
    Jobject() : _imp(std::map<std::string,T>()) {}
    Jobject(const Jobject &other) :_imp(other._imp) {}
    Jobject &operator=(const Jobject &other) {
	_imp = other._imp;
	return *this;
    }
    Jobject operator[](std::string &key) {
	if (!_imp.find(key))
	    _imp[key] = T();
	return _imp[key];
    }
private:
    std::map<std::string, T> _imp;
};

template<class T>
class Jvalue {
public:
    Jvalue() : _imp(T()) { }
    Jvalue(T jvalue) : _imp(jvalue) {}
    void show_value() const { std::cout << _imp << '\n'; }
    friend std::ostream &operator<<(std::ostream &out, const Jvalue &other) {
	out << other._imp;
	return out;
    }
    Jvalue &operator=(T jvalue) {
	_imp = jvalue;
	return *this;
    }
private:
    T _imp;
};

class Jsobject {
};

class Jarray {
};

class json_value {
public:
    json_value() : _imp_data{.json_null=nullptr}, _Imp_jtype(JSON_NULL) {}
    json_value(int integer) : _imp_data{.json_int=integer}, _Imp_jtype(JSON_INT) {}
    json_value(double number) : _imp_data{.json_number=number}, _Imp_jtype(JSON_NUMBER) {}
    json_value(std::string str) : _imp_data{.json_string=str}, _Imp_jtype(JSON_STRING) {}
    json_value(bool boolean) : _imp_data{.json_true=boolean}, _Imp_jtype(JSON_TRUE) {
	if (!boolean) {
	    _imp_data.json_false = false;
	    _Imp_jtype=JSON_FALSE;
	}
    }
    json_value(nullptr_t null) : _imp_data{.json_null=null}, _Imp_jtype(JSON_NULL) {}

    json_value(const json_value &rvalue) {
    }
    
    json_value &operator=(const json_value &rvalue) {
	switch (rvalue._Imp_jtype) {
	case JSON_NUMBER:
	    _imp_data.json_number = rvalue._imp_data.json_number;
	    break;
	case JSON_INT:
	    _imp_data.json_int = rvalue._imp_data.json_int;
	    break;
	case JSON_STRING:
	    _imp_data.json_string = rvalue._imp_data.json_string;
	    break;
	case JSON_TRUE:
	    _imp_data.json_true = rvalue._imp_data.json_true;
	    break;
	case JSON_FALSE:
	    _imp_data.json_false = rvalue._imp_data.json_false;
	    break;
	default:
	    break;
	}
	return *this;
    }
    
    friend std::ostream &operator<<(std::ostream &out, const json_value &jvalue)
    {
    switch (jvalue._Imp_jtype) {
    case json_value::JSON_NUMBER:
	out << jvalue._imp_data.json_number;
	break;
    case json_value::JSON_STRING:
	out << jvalue._imp_data.json_string;
	break;
    case JSON_TRUE:
	out << "true";
	break;
    case JSON_FALSE:
	out << "false";
	break;
    case JSON_NULL:
	out << "null";
	break;
    default:
	break;
    }
    return out;
    }

private:
    union _Imp_type {
	_Imp_type() : json_null{nullptr} {}
	std::string json_string;
	Jsobject json_object;
	Jarray  json_array;
	
	double json_number;
	int json_int;
	bool json_true;
	bool json_false;
	nullptr_t json_null;
	
	~_Imp_type() {}
    } _imp_data;

    enum json_type {
	JSON_STRING,		// -> std::string
	JSON_NUMBER,		// -> double
	JSON_INT,		// -> int
	JSON_OBJECT,		// std::map<std::string, Jvalue>
	JSON_ARRAY,		// std::tuple<Jvalue,...>
	JSON_TRUE,		// -> true
	JSON_FALSE,		// -> flase
	JSON_NULL		// -> nullptr
    } _Imp_jtype;
};

int main(void)
{
    json_value jvalue;
    json_value json_int = 10;
    json_value json_number(3.44);
    json_value json_null(nullptr);
    json_value json_true(true);
    json_value json_false(false);
    json_value json_string("name");

    std::cout << json_int << '\n'
	      << json_number << '\n'
	      << json_null << '\n'
	      << json_true << '\n'
	      << json_false << '\n'
	      << json_string << '\n'
	      << jvalue << '\n';
    
    std::map<std::string, json_value> map1;

    map1["name"] = "yuansl";
    map1["age"] = 26;
    map1["extra_object"] = nullptr;
    map1["is_male"] = true;
    map1["is_programmer"] = false;
    return 0;
}
