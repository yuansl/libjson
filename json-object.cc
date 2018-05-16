#include <cstddef>

#include <iostream>
#include <map>
#include <utility>

namespace json {
    enum json_type {
	JSON_NULL,   // null
	JSON_INT,    // 000
	JSON_NUMBER, // 000.000
	JSON_CHAR,   // 'c'
	JSON_STRING, // ""
	JSON_ARRAY,  // []
	JSON_OBJECT, // {}
	JSON_BOOL    // true or false
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
	json_object(const json_object &rvalue) : _Imp_object(rvalue._Imp_object){}
	json_object(json_object &&rvalue) : _Imp_object(std::move(rvalue._Imp_object)) {}
	~json_object() {_Imp_object.~_Imp_type(); }
	
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
	json_value() : value() {}
	json_value(double number) : value_type(JSON_NUMBER), value(number) {}
	json_value(int integer) : value_type(JSON_INT), value(integer) {}
	json_value(const char *str) : value_type(JSON_STRING), value(str) {}
	json_value(std::string str) : value_type(JSON_STRING), value(str) {}
	json_value(std::nullptr_t null) : value_type(JSON_NULL), value(null) {}
	json_value(bool boolean) : value_type(JSON_BOOL), value(boolean) {}
	json_value(json_object jobj) : value_type(JSON_OBJECT), value(jobj) {
	    std::cout << __FUNCTION__ << '\n';
	}
	
	// move constructor
	json_value(json_value &&rvalue) {}
	json_value(const json_value &rvalue) { *this = rvalue; }
	json_value &operator=(const json_value &rvalue);
	
	enum json_type value_type;
	union _Imp_type {
	    _Imp_type() {}
	    _Imp_type(int i) : json_int(i) {}
	    _Imp_type(char c) : json_char(c) {}
	    _Imp_type(const char *name) : json_string(name) {}
	    _Imp_type(std::string name) : json_string(name) {}
	    _Imp_type(double d) : json_number(d) {}
	    _Imp_type(std::nullptr_t null) : json_null(null) {}
	    _Imp_type(bool boolean) : json_bool(boolean) {}
	    _Imp_type(json_object jobj) : json_obj(jobj) {
		std::cout << __func__ << '\n';
	    }
	    char json_char;
	    int json_int;
	    double json_number;
	    std::string json_string;
	    std::nullptr_t json_null;
	    bool json_bool;
	    json_object json_obj;
	    ~_Imp_type() {}
	} value;
	friend std::ostream &operator<<(std::ostream &out, const json_value &other);
    };
        
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
	    value.json_string = rvalue.value.json_string;
	    break;
	case JSON_OBJECT:
	{
	    json_object tmp = rvalue.value.json_obj;
	    value.json_obj = tmp;
	}
	    break;
	default:
	    break;
	}
	return *this;
    }
    
    std::ostream &operator<<(std::ostream &out, const json_value &other)
    {
	out << "type:" << other.value_type << ' ';
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
	for (auto &item : rvalue._Imp_object)
	    out << '"' << item.first << '"' << ':' << item.second << ',';
	out << '}';
	
	return out;
    }
}

void print(const json::json_value &rvalue)
{
    std::cout << rvalue << '\n';
}

int main(void)
{
    json::json_value integer(3);
    json::json_value name = "John";
    json::json_value price = 3.44;
    json::json_value is_male = true;
    json::json_value is_dead = false;

    print(integer);
    print(name);
    print(price);
    print(is_male);
    print(is_dead);
    
    json::json_object obj2;

    obj2["info"] = name;
    // std::cout << obj2 << '\n';

    // json::json_object obj3 = std::move(obj2);
    // std::cout << "obj3=" << obj3 << '\n'
    // 	      << "obj2 is empty=" << obj2.empty() << '\n';

    // json::json_value jobj(obj3);
    // std::cout << "json_value jobj=" << jobj << '\n';
    
    
    // json::json_value extra_info = jobj;
    // std::cout << "extra_info=" << extra_info << '\n';
    // json::json_object map1;
    // map1["name"] = name;
    // map1["age"] = integer;
    // map1["is_male"] = is_male;
    // map1["is_dead"] = is_dead;
    // map1["extra_info"] = extra_info;
    // std::cout << map1 << '\n';

    return 0;
}
