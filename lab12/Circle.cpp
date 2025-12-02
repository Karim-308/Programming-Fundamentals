#include "Circle.h"

Circle::Circle(double radius) : GeoShape(radius, 0) {}

void Circle::setRadius(double radius) {
    dim1 = radius;
}

double Circle::getRadius() const {
    return dim1;
}

double Circle::area() const {
    return 3.14 * dim1 * dim1;
}
