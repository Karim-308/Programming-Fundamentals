#include "string.h"
#include <stdexcept>

MyString::MyString() : data(new char[1]), len(0) {
    data[0] = '\0';
}

MyString::MyString(const char* s) : data(nullptr), len(0) {
    len = length(s);
    data = new char[len + 1];
    copy(data, s);
}

MyString::MyString(const MyString& other) : data(new char[other.len + 1]), len(other.len) {
    copy(data, other.data);
}

MyString::~MyString() {
    delete[] data;
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        char* newData = new char[other.len + 1];
        copy(newData, other.data);

        delete[] data;
        data = newData;
        len = other.len;
    }
    return *this;
}

char& MyString::operator[](int i) {
    if (i < 0 || i >= len) {
        throw std::out_of_range("MyString::operator[] index out of range");
    }
    return data[i];
}

const char& MyString::operator[](int i) const {
    if (i < 0 || i >= len) {
        throw std::out_of_range("MyString::operator[] index out of range");
    }
    return data[i];
}

int MyString::length(const char* s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

void MyString::copy(char* dst, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

void MyString::concat(char* dst, const char* src) {
    if (!dst || !src) {
        throw std::invalid_argument("MyString::concat null pointer");
    }
    int start = length(dst);
    int i = 0;
    while (src[i] != '\0') {
        dst[start + i] = src[i];
        i++;
    }
    dst[start + i] = '\0';
}

MyString& MyString::operator+=(const MyString& other) {
    int newLen = len + other.len;
    char* newData = new char[newLen + 1];

    copy(newData, data);
    concat(newData, other.data);

    delete[] data;
    data = newData;
    len = newLen;

    return *this;
}

MyString operator+(const MyString& a, const MyString& b) {
    MyString result(a);
    result += b;
    return result;
}

const char* MyString::get() const {
    return data;
}

int MyString::size() const {
    return len;
}
