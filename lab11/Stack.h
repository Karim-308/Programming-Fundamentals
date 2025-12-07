#ifndef STACK_H
#define STACK_H
#include <iostream>

template <typename T>
class MyStack {
private:
    T* data;
    int capacity;
    int top;

    void resize();

public:
    MyStack(int capacity);
    MyStack();
    MyStack(const MyStack& other);
    MyStack& operator=(const MyStack& other);
    ~MyStack();

    void push(const T& value);
    T pop();
    const T& peek() const;
    bool isEmpty() const;
    bool isFull() const;
    int size() const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const MyStack<U>& stack);
};

#endif
