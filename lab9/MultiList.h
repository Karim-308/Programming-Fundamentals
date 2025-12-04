#pragma once

#include <any>
class MultiList {
private:
    std::any* data;
    int length;
    int capacity;

    void grow();

public:
    MultiList();
    ~MultiList();

    void push(const std::any& value);
    std::any& get(int index);
    std::any& operator[](int index);
    void insert(int index, const std::any& value);
    std::any pop();
    void remove(int index);
    void clear();
    int size() const;
    void print() const;
};
