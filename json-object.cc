#include <iostream>		// for cout,cerr...

#include "json-object.h"
#include "json-value.h"

namespace json {
    json_object::json_object() : _Impl_object()
    {
    }
    
    json_object::json_object(const json_object &rvalue) :
	_Impl_object(rvalue._Impl_object)
    {
    }
    
    json_object::json_object(json_object &&rvalue) :
	_Impl_object(std::move(rvalue._Impl_object))
    {
    }
    
    json_object::json_object(const json_object::value_type &var) :
	_Impl_object()
    {
	if (var.typeof() == "JSON_OBJECT") {
	    *this = var.value._M_json_object;
	} else {
	    std::cerr << "Can't convert '" << var
		      << "' from `" << var.typeof() << "` to `JSON_OBJECT`\n";
	}
    }
    
    std::ostream &operator<<(std::ostream &out, const json_object &rvalue)
    {
	out << '{';
	for (auto it = rvalue.begin(); it != rvalue.end(); it++) {
	    out << (*it).first << ':' << (*it).second;
	    if (std::next(it) != rvalue.end())
		out << ',';
	}
	out << '}';
	
	return out;
    }
}
