#ifndef JSON_H
#define JSON_H

// json object
// object := { members
//             |empty
//           }
// members := pair, members
//            |empty
// pair    := string : value
// array   := [elements
//             |empty
//            ]
// elments := value, elements
//            |empty
// value   := string
//            |number
//            |object
//            |array
//            |true
//            |false
//            |null
// string :=  " CHARS "
// CHARS  :=  char CHARS
//            |empty
// char   :=  [0-9a-zA-Z\" \\ \/ \b \f \n \r \t \uxxxx]
// number :=  int
//            |int frac
//            |int exp
//            |int frac exp
// int    :=  [[:digit:]]
// frac   :=  .[[:digit:]]
// exp    := e digits
// digits := digit digits
//           |empty
// e      := e[+-]?
//          |E[+-]?
//
// string ->  c++-string
// char   ->  c++-char
// number ->  c++-int

#include <string>

class json {
public:
    json() {}
    json(const json &rhs) = delete;
    json &operator=(const json &rhs) = delete;
    
    json *loads(const char *json_contents);
    json *load(std::string);
    void dumps(std::string);

    void json_parser(const char *json_contents);
private:
    void *_M_impl;
};

#endif
