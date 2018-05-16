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

class json_array {
public:
    
};

class json_object {
public:
};

class json_value {
public:
    json_value() : jvalue_type(JSON_NULL), _imp_data{.json_null=nullptr} {}
    json_value(int integer) : jvalue_type(JSON_INT), _imp_data{.json_int=integer} {}
    json_value(double number) : jvalue_type(JSON_NUMBER), _imp_data{.json_number=number} {}
    json_value(std::string str) : jvalue_type(JSON_STRING), _imp_data{.json_string=str} {}
    json_value(const char *str) : jvalue_type(JSON_STRING), _imp_data{.json_string=str} {}
    
    // json_value &operator=(std::string &&str) { _imp_data.json_string = std::move(str); return *this; }
    // json_value &operator=(const char* &&str) { _imp_data.json_string = std::move(std::string(str)); return *this; }

    json_value &operator=(json_value &&jvalue) {
	switch (jvalue.jvalue_type) {
	case JSON_INT:
	    _imp_data.json_int = jvalue._imp_data.json_int;
	    break;
	case JSON_NUMBER:
	    _imp_data.json_number = rvalue._imp_data.json_number;
	    break;
	case JSON_STRING:
	    _imp_data.json_string = rvalue._imp_data.json_string;
	    break;
	case JSON_ARRAY:
	    break;
	case JSON_OBJECT:
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
	case JSON_NULL:
	    break;
	default:
	    break;
	}
	return *this;
    }
    json_value(bool boolean) : jvalue_type(JSON_TRUE), _imp_data{.json_bool=boolean} { if (!boolean) jvalue_type=JSON_FALSE; }
    json_value(nullptr_t null) : jvalue_type(JSON_NULL), _imp_data{.json_null=null} {}
    json_value(json_array array);
    json_value(json_object jobj);

    friend std::ostream &operator<<(std::ostream &out, json_value &jvalue) {
	return out;
    }
private:
    enum Jvalue_type {
	JSON_INT,
	JSON_NUMBER,		// -> double
	JSON_STRING,		// -> std::string	
	JSON_OBJECT,		// std::map<std::string, Jvalue>
	JSON_ARRAY,		// std::tuple<Jvalue,...>
	JSON_TRUE,		// -> true
	JSON_FALSE,		// -> flase
	JSON_NULL		// -> nullptr
    } jvalue_type;
    
    union _Imp_type {
	~_Imp_type() {}
	
	friend std::ostream &operator<<(std::ostream &out, _Imp_type tp) {
	    out << tp.json_int;
	    return out;
	}
	int json_int;
	double json_number;
	std::string json_string;
	bool json_bool;
	nullptr_t json_null;
    } _imp_data;
};

int main(void)
{
    // json_int INT(26);
    // json_double NUMBER(2.33);
    // json_string name("myname");
    
    // INT.show_value();
    // NUMBER.show_value();
    // name.show_value();

    // std::map<std::string, json_int> person;
    // person["age"] = INT;
    // std::cout << person["age"] << '\n';

    // Jobject<json_string> json;
    // json["name"] = "yuansl";
    // json["age"] = 26;
    // json["is_dead"] = true;
    // json["extra_object"] = nullptr;
    // json["height"] = 1.75;
    // INT = 37;
    // INT.show_value();
    // std::map<std::string, json_string> map1;
    // map1["name"] = name;
    // print_map(map1);

    // std::map<std::string, Json_value> map2;

    // map2["name"] = 37;
    json_value jvalue;
    json_value json_int(10);
    json_value json_number(3.144);
    json_value json_string("json");
    json_value json_null(nullptr);
    json_value json_bool(true);
    json_value json_bool2(false);
    json_value json_num = 3.44;

    std::map<std::string, json_value> map2;
    map2["name"] = "yuansl";
    map2["age"] = 26;
    map2["is_male"] = true;
    map2["is_tall"] = false;
    map2["extra_info"] = nullptr;

    union value_type {
    	double number;
    	int integer;
    	std::string jstr;
    	~value_type() {}
    } value = {.jstr="jsonstring"};
    
    return 0;
}
