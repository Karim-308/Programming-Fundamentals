#include "picture.h"
#include "line.h"
#include "circle.h"
#include "rectangle.h"
#include <cstring>

Picture::Picture() 
    : shapes(nullptr),
      shapeCount(0),
      shapeCapacity(10),
      renderer(nullptr) 
{
    shapes = new Shape*[shapeCapacity];
}

Picture::~Picture() {
    delete[] shapes;
}

void Picture::setRenderer(SDL_Renderer* rend) {
    renderer = rend;
}

void Picture::addShape(Shape* shape) {
    if (shapeCount >= shapeCapacity) {
        shapeCapacity *= 2;
        Shape** newShapes = new Shape*[shapeCapacity];
        for (int i = 0; i < shapeCount; i++) {
            newShapes[i] = shapes[i];
        }
        delete[] shapes;
        shapes = newShapes;
    }
    shapes[shapeCount++] = shape;
}

void Picture::drawAll() const {
    if (!renderer) return;
    
    for (int i = 0; i < shapeCount; i++) {
        shapes[i]->draw(renderer);
    }
}

void Picture::clear() {
    shapeCount = 0;
}
