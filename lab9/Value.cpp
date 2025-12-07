#include "Value.h"
#include <cctype>
#include <cstdlib>
#include <stdexcept>
 
Value:: Value() : data("") {};
    Value:: Value(string s) : data(s) {};
    Value:: Value(const char* s) : data(string(s) ) {};
    Value:: Value(int n) : data(to_string(n)) {};
    Value:: Value(bool b) : data(b ? "true" : "false") {};
    Value:: Value(double d) : data(to_string(d)) {};
    Value:: Value(char c) : data(1, c) {};
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
            stoi(data, &idx);
        } catch (...){
            return false;
        }
        return idx == data.size();
    }
    bool Value::isFloat() {
        if (data.empty()) return false;
        size_t idx = 0;
        double doubleVersion;
        try {
            doubleVersion = stod(data, &idx);
        } catch (...){
            return false;
        }
        if (idx != data.size()) return false;

        float floatVersion = static_cast<float>(doubleVersion);
        return static_cast<double>(floatVersion) == doubleVersion;
    }
    bool Value::isDouble() {
        if (data.empty()) return false;
        size_t idx = 0;
        double doubleVersion;
        try {
            doubleVersion = stod(data, &idx);
        }  catch (...){
            return false;
        }
        if (idx != data.size()) return false;

        float floatVersion = static_cast<float>(doubleVersion);
        return static_cast<double>(floatVersion) != doubleVersion;
    }
    bool Value::isChar() {
        return data.length() == 1;
    }
