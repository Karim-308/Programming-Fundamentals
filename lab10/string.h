#ifndef MYSTRING_H
#define MYSTRING_H

class MyString {
private:
    char* data;
    int len;

public:
    MyString();
    MyString(const char* s);
    MyString(const MyString& other);
    ~MyString();

    MyString& operator=(const MyString& other);

    char& operator[](int i);
    const char& operator[](int i) const;

    static void copy(char* dst, const char* src);
    static void concat(char* dst, const char* src);

    MyString& operator+=(const MyString& other);
    friend MyString operator+(const MyString& a, const MyString& b);

    const char* get() const;
    void remove(int index);
    int length() const;
};

#endif  // MYSTRING_H
