#include "Multilist.h"
#include "Value.h"
#include <iostream>



Multilist::Multilist() : size(0), capacity(10) {
    arr = new Value[capacity];
}

Multilist::Multilist(int cap) : size(0), capacity(cap) {
    arr = new Value[capacity];
}

void Multilist :: push (string v) {
    if (size >= capacity) {
        resize();
    }
    arr[size] = Value(v);
    size++;
}


void Multilist :: push (Value& v) {
    if (size >= capacity) {
        resize();
    }
    arr[size] = v;
    size++;
}
void Multilist :: resize(){
    capacity *= 2;
    Value* newArr = new Value[capacity];
    for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
}
Value Multilist :: pop() {
   if (size == 0) {
       cout << "List is empty" << endl;
       return Value();
   }
   --size;
   return arr[size];
}

void Multilist :: insertAt(int index, string v) {
    if (index < 0 || index > size){
        return;
    }

    if (size >= capacity) {
        resize();
    }
    for (int i = size; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = Value(v);
    size++;
}

void Multilist ::removeAt(int index) {
    if (index < 0 || index >= size) {
        return;
    }
    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    size--;
}
Value& Multilist ::operator[] (int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }
    return arr[index];
}

void Multilist ::display() const{
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

ostream& operator<<(ostream& os, const Multilist& ml) {
    os<< "[ ";
    for (int i = 0; i < ml.size; i++) {
        os << ml.arr[i] << " ";
    }
    os << " ]";
    return os;
}

Multilist::~Multilist()
{
    delete[] arr;
}