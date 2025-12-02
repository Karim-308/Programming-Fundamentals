#ifndef SQUARE_H
#define SQUARE_H

#include "Rectangle.h"

class Square : private Rectangle {
    public:
        Square(double side = 0);
        void setSide(double side);
        double getSide() const;
        double area() const;
};

#endif
