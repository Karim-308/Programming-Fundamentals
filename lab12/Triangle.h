#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "GeoShape.h"

class Triangle : public GeoShape {
    public:
        Triangle(double base = 0, double height = 0);
        void setBase(double base);
        void setHeight(double height);
        double getBase() const;
        double getHeight() const;
        double area() const override;
};

#endif
