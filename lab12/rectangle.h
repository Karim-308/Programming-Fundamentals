#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SDL2/SDL.h>
#include "point.h"
#include "shape.h"

class Rectangle : public Shape {
    Point topLeft;
    Point bottomRight;

public:
    Rectangle();
    Rectangle(const Point& tl, const Point& br);

    const Point& getTopLeft() const;
    const Point& getBottomRight() const;

    void setTopLeft(const Point& tl);
    void setBottomRight(const Point& br);

    int getWidth() const;
    int getHeight() const;

    void draw(SDL_Renderer* renderer) const override;
};

#endif
