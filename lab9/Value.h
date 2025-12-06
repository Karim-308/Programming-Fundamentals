#ifndef VALUE_H
#define VALUE_H

#include <string>
#include <iostream>
using namespace std;
class  Value


{
private:
    string data;
public:
     Value();
     Value(string s);
     string getData();
    ~ Value();
    friend ostream& operator<< (ostream& os , const Value& val);
    string getType();

bool isBoolean(string* str);
bool isInteger(string* str);
bool isFloat(string* str);
bool isDouble(string* str);
bool isChar(string* str);


};

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
        if (isBoolean(&data)) return "bool";
        else if (isInteger(&data)) return "int";
        else if (isFloat(&data)) return "float";
        else if (isDouble(&data)) return "double";
        else if (isChar(&data)) return "char";
        else return "string";

        return "";
    }

    bool Value::isBoolean(string* str) {
        return (*str == "true" || *str == "false");
    }
    bool Value::isInteger(string* str) {
        for (char c : *str) {
            if (!isdigit(c) && c != '-' && c != '+')
                return false;
        }
        return true;
    }
    bool Value::isFloat(string* str) {
        size_t dotCount = 0;
        for (char c : *str) {
            if (c == '.') {
                dotCount++;
                if (dotCount > 1) return false;
            }
            else if (!isdigit(c) && c != '-' && c != '+')
            return false;
        }
        return dotCount == 1;
    }
    bool Value::isDouble(string* str) {
    char* endOfNumber;
        double doubleVersion = strtod(str->c_str(), &endOfNumber);
       if (*endOfNumber != '\0') return false;

         float floatVersion = strtof(str->c_str(), nullptr);
        
        return static_cast<double>(floatVersion) != doubleVersion;

    }
    bool Value::isChar(string* str) {
        return data.length() == 1;
    }

#endif