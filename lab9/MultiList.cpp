#include "MultiList.h"

#include <iostream>
#include <string>
#include <typeinfo>

MultiList::MultiList() : data(nullptr), length(0), capacity(0) {}

MultiList::~MultiList() {
    delete[] data;
}

void MultiList::grow() {
    int new_capacity = (capacity == 0 ? 4 : capacity * 2);
    std::any* new_data = new std::any[new_capacity];

    for (int i = 0; i < length; ++i) {
        new_data[i] = data[i];
    }

    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

void MultiList::push(const std::any& value) {
    if (length == capacity) {
        grow();
    }

    data[length++] = value;
}

std::any& MultiList::get(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of bounds");
    }

    return data[index];
}

std::any& MultiList::operator[](int index) {
    return get(index);
}

void MultiList::insert(int index, const std::any& value) {
    if (index < 0 || index > length) {
        throw std::out_of_range("Insert index out of bounds");
    }

    if (length == capacity) {
        grow();
    }

    for (int i = length; i > index; --i) {
        data[i] = data[i - 1];
    }

    data[index] = value;
    ++length;
}

std::any MultiList::pop() {
    if (length == 0) {
        throw std::runtime_error("Pop from empty list");
    }

    return data[--length];
}

void MultiList::remove(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Remove index out of bounds");
    }

    for (int i = index; i < length - 1; ++i) {
        data[i] = data[i + 1];
    }

    --length;
}

void MultiList::clear() {
    length = 0;
}

int MultiList::size() const {
    return length;
}

void MultiList::print() const {
    std::cout << "[";
    for (int i = 0; i < length; ++i) {
        try {
            if (data[i].type() == typeid(int)) {
                std::cout << std::any_cast<int>(data[i]);
            } else if (data[i].type() == typeid(double)) {
                std::cout << std::any_cast<double>(data[i]);
            } else if (data[i].type() == typeid(bool)) {
                std::cout << (std::any_cast<bool>(data[i]) ? "true" : "false");
            } else if (data[i].type() == typeid(std::string)) {
                std::cout << "\"" << std::any_cast<std::string>(data[i]) << "\"";
            } else {
                std::cout << "<unknown>";
            }
        } catch (...) {
            std::cout << "<error>";
        }

        if (i + 1 != length) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}
