#include "point.h"

Point::Point() : x(0), y(0) {}

Point::Point(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}

int Point::getX() const { return x; }

int Point::getY() const { return y; }

void Point::setX(int xCoord) { x = xCoord; }

void Point::setY(int yCoord) { y = yCoord; }
