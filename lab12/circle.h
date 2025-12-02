#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL2/SDL.h>
#include "point.h"
#include "shape.h"

class Circle : public Shape {
    Point center;
    double radius;

public:
    Circle();
    Circle(const Point& centerPoint, double radiusValue);

    const Point& getCenter() const;
    double getRadius() const;

    void setCenter(const Point& centerPoint);
    void setRadius(double radiusValue);

    void draw(SDL_Renderer* renderer) const override;
};

#endif  // CIRCLE_H
