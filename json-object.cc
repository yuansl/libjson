#include <cstddef>

#include <iostream>
#include <map>
#include <utility>

#include "json-object.h"

namespace json {
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

int main(void)
{
    json::json_value integer(3);
    json::json_value name = "John";
    json::json_value price = 3.44;
    json::json_value is_male = true;
    json::json_value is_dead = false;
    json::json_value name2;    
    json::json_object obj2;
    
    name = "hh";
    obj2["info"] = name;
    std::cout << "obj2=" << obj2 << '\n';

    json::json_object obj3(std::move(obj2));
    std::cout << "obj3=" << obj3 << '\n';

    json::json_value jobj=obj3;

    std::cout << "json_value:jobj=" << jobj << '\n';
    
    json::json_value extra_info = jobj;
    std::cout << "extra_info=" << extra_info << '\n';

    map1["name"] = name;
    map1["age"] = integer;
    map1["is_male"] = is_male;
    map1["is_dead"] = is_dead;
    map1["extra_info"] = extra_info;
    map1["address"] = "Fuxin Road";
    
    std::cout << "\n\n\nmap1=" << map1 << '\n';

    return 0;
}
