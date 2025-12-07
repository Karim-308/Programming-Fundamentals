#include "Complex.h"

using namespace std;

Complex::Complex(): real(0), img(0) {};

Complex::Complex(float r, float i): real(r), img(i) {};

Complex::Complex (const Complex& other) : real (other.real), img (other.img){};

void Complex::setReal(float r) { real = r; };

void Complex::setImg(float i) { img = i; };

float Complex::getReal() const { return real; };

float Complex::getImg() const { return img; };

Complex Complex::operator + (const Complex& other) const {
        return Complex(real + other.real , img + other.img);
    }

Complex Complex::operator - (const Complex& other) const {
        return Complex(real - other.real , img - other.img);
    }


Complex Complex::operator * (const Complex& other) const {
        //(a.real b.real – b.img a.img) + i(ad + bc)
        return Complex(real * other.real  - img*other. img  , real * other.img  + img * other.real );
    }


Complex Complex::operator / (const Complex& other) const {
        float denominator = other.real * other.real + other.img * other.img;
        
        if (denominator == 0) {
            throw runtime_error("Math error: Can't divide by Zero\n");
        }
        return Complex((real * other.real + img * other.img) / denominator,
                       (img * other.real - real * other.img) / denominator);
    }

Complex Complex::operator ^ (int power) const {
        //use de moivre's theorem
        float r = sqrt(real * real + img * img);
        float theta = atan2(img, real);
        float r_pow = pow(r, power);
        float real_part = r_pow * cos(power * theta);
        float img_part = r_pow * sin(power * theta);
        return Complex(real_part, img_part);
    }

Complex& Complex::operator++() {
        real += 1;
        img += 1;
        return *this;
    }
Complex& Complex::operator--() {
        real -= 1;
        img -= 1;
        return *this;
    }

Complex Complex::operator++(int) {
        Complex temp(*this);
        ++(*this);
        return temp;
    }

Complex Complex::operator--(int) {
        Complex temp(*this);
        --(*this);  // reuse prefix logic so postfix returns original value
        return temp;
    }



Complex & Complex::operator =(const Complex& other) {
        real = other.real;
        img = other.img;
        return *this;
    }

bool Complex::operator ==(const Complex& other) const {
        return (real == other.real) && (img == other.img);
    }

bool Complex::operator !=(const Complex& other) const {
        return !(*this == other);
    }

bool Complex::operator <(const Complex& other) const {
        return (real < other.real) || (real == other.real && img < other.img);
    }
    
bool Complex::operator >(const Complex& other) const {
        return (real > other.real) || (real == other.real && img > other.img);
    }

bool Complex::operator <=(const Complex& other) const {
        return !(*this > other);
    }

bool Complex::operator >=(const Complex& other) const {
        return !(*this < other);
    }

float Complex::operator [] (int index) const {
        if (index == 0)
            return real;
        else if (index == 1)
            return img;
        else
            throw out_of_range("Index out of range");
    }

ostream& operator<<(ostream& os , const Complex& c){
    
    if (c.real != 0) {
        os << c.real;

        if (c.img > 0)
            os << " + " << c.img << "i";
        else if (c.img < 0)
            os << " - " << -c.img << "i";  // absolute value
    }
    
    else {
        if (c.img == 0)
            os << 0;
        else
            os << c.img << "i";  // print directly -ve or +ve
    }

    return os;

    }


istream& operator>>(istream& is , Complex& c){
        is >> c.real >> c.img ;
        return is;
    }


void Complex::operator()(double r, double i) {
        real = r;
        img = i;
    }

Complex& Complex::operator+=(const Complex& other) {
    real += other.real;
    img  += other.img;
    return *this;
    }

Complex& Complex::operator-=(const Complex& other) {
    real -= other.real;
    img  -= other.img;
    return *this;
    }

Complex& Complex::operator*=(const Complex& other) {
    float tempReal = real * other.real - img * other.img;
    float tempImg = real * other.img + img * other.real;
    real = tempReal;
    img = tempImg;
    return *this;
    }

Complex& Complex::operator/=(const Complex& other) {
    float denominator = other.real * other.real + other.img * other.img;
    if (denominator == 0) {
        throw runtime_error("Math error: Can't divide by Zero\n");
    }
    float tempReal = (real * other.real + img * other.img) / denominator;
    float tempImg = (img * other.real - real * other.img) / denominator;
    real = tempReal;
    img = tempImg;
    return *this;
    }

Complex& Complex::operator^=(int power) {
        *this = *this ^ power;
        return *this;
    }


Complex Complex::operator+() const {
        return *this;
    }

Complex Complex::operator-() const {
        return Complex(-real, -img);
    }

