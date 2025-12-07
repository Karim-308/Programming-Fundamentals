#include "Value.h"
#include <cctype>
#include <cstdlib>
#include <stdexcept>
 
 Value:: Value() : data("") {};
    Value:: Value(string s) : data(s) {};
 Value::~ Value (){};
 string Value::getData() {
     return data;
 }

 ostream&  operator<< (ostream& os , const Value& val){
        os << val.data;
        return os;
 }
    string Value::getType() {
        if (isBoolean()) return "bool";
        else if (isInteger()) return "int";
        else if (isFloat()) return "float";
        else if (isDouble()) return "double";
        else if (isChar()) return "char";
        else return "string";

        return "";
    }

    bool Value::isBoolean() {
        return (data == "true" || data == "false");
    }
    bool Value::isInteger() {
        if (data.empty()) return false;
        size_t idx = 0;
        try {
            stol(data, &idx);
        } catch (const invalid_argument&) {
            return false;
        } catch (const out_of_range&) {
            return false;
        }
        return idx == data.size();
    }
    bool Value::isFloat() {
        if (data.empty()) return false;
        size_t idx = 0;
        try {
            stof(data, &idx);
        } catch (const invalid_argument&) {
            return false;
        } catch (const out_of_range&) {
            return false;
        }
        return idx == data.size();
    }
    bool Value::isDouble() {
    char* endOfNumber;
        double doubleVersion = strtod(data.c_str(), &endOfNumber);
       if (*endOfNumber != '\0') return false;

         float floatVersion = strtof(data.c_str(), nullptr);
        
        return static_cast<double>(floatVersion) != doubleVersion;

    }
    bool Value::isChar() {
        return data.length() == 1;
    }
