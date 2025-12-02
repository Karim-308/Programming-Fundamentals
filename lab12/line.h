// Header defining the Line class.
#ifndef LINE_H
#define LINE_H

#include <SDL2/SDL.h>
#include "point.h"
#include "shape.h"

class Line : public Shape {
    Point start;
    Point end;

public:
    Line();
    Line(const Point& startPoint, const Point& endPoint);

    const Point& getStart() const;
    const Point& getEnd() const;

    void setStart(const Point& startPoint);
    void setEnd(const Point& endPoint);

    void draw(SDL_Renderer* renderer) const override;
};

#endif  // LINE_H
