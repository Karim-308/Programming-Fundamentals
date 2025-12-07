#include <ostream>
#include <stdexcept>
#include "Stack.h"

template <typename T>
MyStack<T>::MyStack(int capacity): capacity(capacity > 0 ? capacity : 1), top(-1) {
    data = new T[this->capacity];
}

template <typename T>
MyStack<T>::MyStack() : MyStack(10) {}

template <typename T>
MyStack<T>::MyStack(const MyStack& other): capacity(other.capacity), top(other.top) {
    
    
    data(new T[other.capacity]);
    for (int i = 0; i <= top; ++i) {
        data[i] = other.data[i];
    }
}

template <typename T>
MyStack<T>& MyStack<T>::operator=(const MyStack& other) {
    if (this == &other) {
        return *this;
    }
    T* newData = new T[other.capacity];
    for (int i = 0; i <= other.top; ++i) {
        newData[i] = other.data[i];
    }
    delete[] data;
    data = newData;
    capacity = other.capacity;
    top = other.top;
    return *this;
}



template <typename T>
MyStack<T>::~MyStack() {
    delete[] data;
}

template <typename T>
void MyStack<T>::resize() {
    int newCapacity = capacity * 2;
    T* temp = new T[newCapacity];
    for (int i = 0; i <= top; ++i) {
        temp[i] = data[i];
    }
    delete[] data;
    data = temp;
    capacity = newCapacity;
}

template <typename T>
void MyStack<T>::push(const T& value) {
    if (isFull()) {
        resize();
    }
    data[++top] = value;
}

template <typename T>
T MyStack<T>::pop() {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    return data[top--];
}

template <typename T>
const T& MyStack<T>::peek() const {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    return data[top];
}

template <typename T>
bool MyStack<T>::isEmpty() const {
    return top == -1;
}

template <typename T>
bool MyStack<T>::isFull() const {
    return top == capacity - 1;
}

template <typename T>
int MyStack<T>::size() const {
    return top + 1;
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const MyStack<U>& stack) {
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
