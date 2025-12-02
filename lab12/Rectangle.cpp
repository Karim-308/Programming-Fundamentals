#include "Rectangle.h"

Rectangle::Rectangle(double width, double height) : GeoShape(width, height) {}

void Rectangle::setWidth(double width) {
    dim1 = width;
}

void Rectangle::setHeight(double height) {
    dim2 = height;
}

double Rectangle::getWidth() const {
    return dim1;
}

double Rectangle::getHeight() const {
    return dim2;
}

double Rectangle::area() const {
    return dim1 * dim2;
}
