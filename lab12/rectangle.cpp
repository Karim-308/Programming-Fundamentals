#include "rectangle.h"

Rectangle::Rectangle() : topLeft(Point()), bottomRight(Point()) {}

Rectangle::Rectangle(const Point& tl, const Point& br): topLeft(tl), bottomRight(br) {}

const Point& Rectangle::getTopLeft() const { return topLeft; }

const Point& Rectangle::getBottomRight() const { return bottomRight; }

void Rectangle::setTopLeft(const Point& tl) { topLeft = tl; }

void Rectangle::setBottomRight(const Point& br) { bottomRight = br; }

int Rectangle::getWidth() const { return bottomRight.getX() - topLeft.getX(); }

int Rectangle::getHeight() const { return bottomRight.getY() - topLeft.getY(); }

void Rectangle::draw(SDL_Renderer* renderer) const {
    if (!renderer) return;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    SDL_Rect rect;
    rect.x = topLeft.getX();
    rect.y = topLeft.getY();
    rect.w = getWidth();
    rect.h = getHeight();

    SDL_RenderDrawRect(renderer, &rect);
}
