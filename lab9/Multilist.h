#ifndef MULTILIST_H
#define MULTILIST_H
#include "Value.h"
#include <stdexcept>
using namespace std;

class Multilist
{
private:
    Value* arr;
    int size;
    int capacity;
    void resize();
public:
    Multilist();
    Multilist(int cap);
    //void push(string v);
    void push(Value v);
    Value pop();
    void insertAt(int index, string v);
    void removeAt(int index);
    Value& operator[] (int index);
    void display() const;
    friend ostream& operator<<(ostream& os, const Multilist& ml);
    int getSize();
    
    ~Multilist();
};


#endif