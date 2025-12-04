#ifndef MYSTRING_H
#define MYSTRING_H

#include <cstddef>

class MyString {
private:
    char* data;
    std::size_t len;

public:
    MyString();
    explicit MyString(const char* s);
    MyString(const MyString& other);
    ~MyString();

    MyString& operator=(const MyString& other);

    char& operator[](std::size_t i);
    const char& operator[](std::size_t i) const;

    static std::size_t length(const char* s);
    static void copy(char* dst, const char* src);
    static void concat(char* dst, const char* src);

    MyString& operator+=(const MyString& other);
    friend MyString operator+(const MyString& a, const MyString& b);

    const char* get() const;
    std::size_t size() const;
};

#endif  // MYSTRING_H
