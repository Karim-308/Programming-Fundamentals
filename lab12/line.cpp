#include "line.h"

#include <cstdlib>
#include <SDL2/SDL.h>

Line::Line() : start(Point()), end(Point()) {}

Line::Line(const Point& startPoint, const Point& endPoint)
    : start(startPoint), end(endPoint) {}

const Point& Line::getStart() const { return start; }

const Point& Line::getEnd() const { return end; }

void Line::setStart(const Point& startPoint) { start = startPoint; }

void Line::setEnd(const Point& endPoint) { end = endPoint; }

void Line::draw(SDL_Renderer* renderer) const {
    if (!renderer) return;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // I am using white color for lines
    SDL_RenderDrawLine(renderer, start.getX(), start.getY(), end.getX(), end.getY());
}
