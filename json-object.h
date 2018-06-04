// json_object implement -*- c++ -*-
#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include <map>

namespace json {
    struct json_value;
    class json_object {
    	typedef std::string key_type;
    	typedef json_value  value_type;
    	typedef std::map<key_type, value_type> _Impl_type;
    	typedef _Impl_type::iterator iterator;
    	typedef _Impl_type::const_iterator const_iterator;
    public:
    	json_object();
    	json_object(const json_object &rvalue);
    	json_object(json_object &&rvalue);
	json_object(const value_type &var);
	
    	iterator begin() { return _Impl_object.begin(); }
    	iterator end() { return _Impl_object.end(); }
	const_iterator begin() const { return _Impl_object.begin(); }
	const_iterator end() const { return _Impl_object.end(); }
    	value_type &operator[](const key_type key) {
    	    return _Impl_object[key];
    	}
    	bool empty() const { return _Impl_object.empty(); }
    	void clear() { _Impl_object.clear(); }
    	json_object &operator=(const json_object &rvalue) {
    	    _Impl_object = rvalue._Impl_object;
    	    return *this;
    	}

    	friend std::ostream &operator<<(std::ostream &out, const json_object &rvalue);
    private:
    	_Impl_type _Impl_object;
    };
}

#endif
