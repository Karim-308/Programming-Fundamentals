#include "circle.h"

#include <cmath>
#include <SDL2/SDL.h>

Circle::Circle() : center(Point()), radius(0.0) {}

Circle::Circle(const Point& centerPoint, double radiusValue)
    : center(centerPoint), radius(radiusValue) {}

const Point& Circle::getCenter() const { return center; }

double Circle::getRadius() const { return radius; }

void Circle::setCenter(const Point& centerPoint) { center = centerPoint; }

void Circle::setRadius(double radiusValue) { radius = radiusValue; }

void Circle::draw(SDL_Renderer* renderer) const {
    if (!renderer) return;
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow

    const int radiusInt = static_cast<int>(std::round(radius));
    const int diameter = radiusInt * 2;

    int x = radiusInt - 1;
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = tx - diameter;
    const int cx = center.getX();
    const int cy = center.getY();

    while (x >= y) {
        SDL_RenderDrawPoint(renderer, cx + x, cy - y);
        SDL_RenderDrawPoint(renderer, cx + x, cy + y);
        SDL_RenderDrawPoint(renderer, cx - x, cy - y);
        SDL_RenderDrawPoint(renderer, cx - x, cy + y);
        SDL_RenderDrawPoint(renderer, cx + y, cy - x);
        SDL_RenderDrawPoint(renderer, cx + y, cy + x);
        SDL_RenderDrawPoint(renderer, cx - y, cy - x);
        SDL_RenderDrawPoint(renderer, cx - y, cy + x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            --x;
            tx += 2;
            error += tx - diameter;
        }
    }
}
