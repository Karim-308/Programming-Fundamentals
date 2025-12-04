#include "Stack.h"
#include <stdexcept>

MyStack::MyStack(int capacity) : capacity(capacity > 0 ? capacity : 1), top(-1) {
    data = new int[this->capacity];
}

MyStack::MyStack() : capacity(10), top(-1) {
    data = new int[capacity];
}

MyStack::MyStack(const MyStack& other) : capacity(other.capacity), top(other.top) {
    data = new int[capacity];
    for (int i = 0; i <= top; ++i) {
        data[i] = other.data[i];
    }
}

MyStack& MyStack::operator=(const MyStack& other) {
    if (this == &other) {
        return *this;
    }
    int *newData = new int[other.capacity];
    for (int i = 0; i <= other.top; ++i) {
        newData[i] = other.data[i];
    }
    delete[] data;
    data = newData;
    capacity = other.capacity;
    top = other.top;
    return *this;
}


MyStack::~MyStack() {
    delete[] data;
}

void MyStack::resize(){
    int newCapacity = capacity > 0 ? capacity * 2 : 1;
    int * temp = new int[newCapacity];
    for(int i=0; i<=top; i++){
        temp[i] = data[i];
    }
    delete[] data;
    data = temp;
    capacity = newCapacity;
}

void MyStack::push(const int value) {
    if (isFull()) {
        resize();
    }
    data[++top] = value;
}


int MyStack::pop(){
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    return data[top--];
}


bool MyStack::isEmpty() const {
    return top == -1;
}

bool MyStack::isFull() const {
    return top == capacity - 1;
}

int MyStack::size() const {
    return top + 1;
}

int MyStack::peek() const {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    return data[top];
}

std::ostream& operator<<(std::ostream& os, const MyStack& stack) {
    os << "[";
    for (int i = stack.top; i >= 0; --i) {
        os << stack.data[i];
        if (i > 0) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
