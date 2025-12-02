#ifndef PICTURE_H
#define PICTURE_H

#include <SDL2/SDL.h>
#include "shape.h"

class Picture {
    Shape** shapes;
    int shapeCount;
    int shapeCapacity;
    
    SDL_Renderer* renderer;

public:
    Picture();
    ~Picture();
    
    void setRenderer(SDL_Renderer* rend);
    
    void addShape(Shape* shape);
    
    void drawAll() const;
    
    void clear();
    
    int getShapeCount() const { return shapeCount; }
};

#endif
