#include <iostream>

#include "json-array.h"
#include "json-value.h"

namespace json {
    json_array::json_array() : _Impl_array() {}
    json_array::json_array(const json_array &rvalue) : _Impl_array(rvalue._Impl_array) {}
    json_array::json_array(json_array &&rvalue) : _Impl_array(std::move(rvalue._Impl_array)) {}
    json_array::json_array(const json_array::value_type &var) : _Impl_array()
    {
	if (var.typeof() == "JSON_ARRAY") {
	    *this = var.value._M_json_array;
	} else {
	    std::cerr << "Can't convert '" << var
		      << "' from `" << var.typeof() << "` to `JSON_ARRAY`\n";
	}
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
}
