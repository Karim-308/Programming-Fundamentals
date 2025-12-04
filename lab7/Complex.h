#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <stdexcept>
#include <cmath>
using namespace std;


class Complex {
    public:
    float real;
    float img;

    Complex();

    Complex(float r, float i);

    Complex (const Complex& other);

    void setReal(float r);

    void setImg(float i);

    float getReal() const;

    float getImg() const;

    Complex operator + (const Complex& other) const;

    Complex operator - (const Complex& other) const;

    Complex operator * (const Complex& other) const;

    Complex operator / (const Complex& other) const;

    Complex operator ^ (int power) const;

    Complex& operator++();

    Complex& operator--();

    Complex operator++(int);

    Complex operator--(int);

    Complex & operator =(const Complex& other);

    bool operator ==(const Complex& other) const;

    bool operator !=(const Complex& other) const;

    bool operator <(const Complex& other) const;

    bool operator >(const Complex& other) const;

    bool operator <=(const Complex& other) const;

    bool operator >=(const Complex& other) const;

    float operator [] (int index) const;

    friend ostream& operator<<(ostream& os , const Complex& c);

    friend istream& operator>>(istream& is , Complex& c);

    void operator()(double r, double i);

    Complex& operator+=(const Complex& other);

    Complex& operator-=(const Complex& other);

    Complex& operator*=(const Complex& other);

    Complex& operator/=(const Complex& other);

    Complex& operator^=(int power);
    
    Complex operator+() const;
    
    Complex operator-() const;
};


#endif
