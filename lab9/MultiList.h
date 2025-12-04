#pragma once

#include <any>
#include <cstddef>

class MultiList {
private:
    std::any* data;
    std::size_t length;
    std::size_t capacity;

    void grow();

public:
    MultiList();
    ~MultiList();

    void push(const std::any& value);
    std::any& get(std::size_t index);
    std::any& operator[](std::size_t index);
    void insert(std::size_t index, const std::any& value);
    std::any pop();
    void remove(std::size_t index);
    void clear();
    std::size_t size() const;
    void print() const;
};
