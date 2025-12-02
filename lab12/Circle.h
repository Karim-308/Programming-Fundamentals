#ifndef CIRCLE_H
#define CIRCLE_H

#include "GeoShape.h"

class Circle : private GeoShape {
    public:
        Circle(double radius = 0);
        void setRadius(double radius);
        double getRadius() const;
        double area() const override;
};

#endif
