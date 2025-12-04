#ifndef STACK_H
#define STACK_H

#include <ostream>

class MyStack{
    int *data;
    int capacity;
    int top;
    void resize();
public:
    MyStack(int capacity);
    MyStack();
    MyStack(const MyStack& other);
    MyStack& operator=(const MyStack& other);
    ~MyStack();

    void push(const int value);
    int pop();
    int peek() const;
    bool isEmpty() const;
    bool isFull() const;
    int size() const;
    

    friend std::ostream& operator<<(std::ostream& os, const MyStack& stack);
};

#endif
