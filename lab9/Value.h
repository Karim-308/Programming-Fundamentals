#ifndef VALUE_H
#define VALUE_H

#include <string>
#include <iostream>
using namespace std;

class  Value{
private:
    string data;


public:
     Value();
     Value(const char* s);
     Value(const string &s);
     Value(int n);
     Value(bool b);
     Value(double d);
     Value(char c);
     string getData();
    ~ Value();
    friend ostream& operator<< (ostream& os , const Value& val);
    string getType();

    bool isBoolean();
    bool isInteger();
    bool isFloat();
    bool isDouble();
    bool isChar();

};
#endif
