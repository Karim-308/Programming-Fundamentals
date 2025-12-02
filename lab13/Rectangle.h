#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "GeoShape.h"

class Rectangle : public GeoShape {
    public:
        Rectangle(double width = 0, double height = 0);
        void setWidth(double width);
        void setHeight(double height);
        double getWidth() const;
        double getHeight() const;
        double area() const override;
};

#endif
