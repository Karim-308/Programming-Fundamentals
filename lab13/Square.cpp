#include "Square.h"

Square::Square(double side) : Rectangle(side, side) {}

void Square::setSide(double side) {
    setWidth(side);
    setHeight(side);
}

double Square::getSide() const {
    return getWidth();
}

double Square::area() const {
    return Rectangle::area();
}
