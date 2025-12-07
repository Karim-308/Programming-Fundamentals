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
     Value(string s);
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
