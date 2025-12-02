#include "Triangle.h"

Triangle::Triangle(double base, double height) : GeoShape(base, height) {}

void Triangle::setBase(double base) {
    dim1 = base;
}

void Triangle::setHeight(double height) {
    dim2 = height;
}

double Triangle::getBase() const {
    return dim1;
}

double Triangle::getHeight() const {
    return dim2;
}

double Triangle::area() const {
    return 0.5 * dim1 * dim2;
}
