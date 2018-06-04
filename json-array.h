// json_array implement -*- c++ -*-
#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

#include <vector>

namespace json {
    struct json_value;
    class json_array {
	typedef json_value value_type;
	typedef std::vector<json_value> _Impl_type;
	typedef _Impl_type::iterator iterator;
	typedef _Impl_type::const_iterator const_iterator;
	typedef _Impl_type::size_type size_type;
    public:
	json_array();
	json_array(const json_array &rvalue);
	json_array(json_array &&rvalue);
	json_array(const json_value &var);
	
	json_array &operator=(const json_array &rvalue) {
	    _Impl_array = rvalue._Impl_array;
	    return *this;
	}
	json_array &operator=(json_array &&rvalue) {
	    _Impl_array = std::move(rvalue._Impl_array);
	    return *this;
	}
	
	// array element access
	void push_back(const value_type &value) { _Impl_array.push_back(value); }
	value_type &operator[](int index) { return _Impl_array[index]; }
	const_iterator begin() const { return _Impl_array.begin(); }
	const_iterator end() const { return _Impl_array.end(); }
	bool empty() const { return _Impl_array.empty(); }
	size_type size() const { return _Impl_array.size(); }
	void clear() { _Impl_array.clear(); }

	friend std::ostream &operator<<(std::ostream &out, const json_array &rvalue);
    private:
	_Impl_type _Impl_array;
    };
}

#endif
