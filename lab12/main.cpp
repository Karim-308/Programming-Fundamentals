#include <SDL2/SDL.h>
#include "picture.h"
#include "line.h"
#include "circle.h"
#include "rectangle.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return 1;
    }
    
    SDL_Window* window = SDL_CreateWindow(
        "Picture Drawing",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    Picture picture;
    picture.setRenderer(renderer);
    
    
    Line* line1 = new Line(Point(100, 100), Point(300, 200));
    Line* line2 = new Line(Point(300, 200), Point(500, 150));
    
    Circle* circle1 = new Circle(Point(400, 300), 50);
    Circle* circle2 = new Circle(Point(200, 250), 30);
    
    Rectangle* rect1 = new Rectangle(Point(200, 400), Point(350, 500));
    Rectangle* rect2 = new Rectangle(Point(500, 350), Point(650, 450));
    
    picture.addShape(line1);
    picture.addShape(line2);
    picture.addShape(circle1);
    picture.addShape(circle2);
    picture.addShape(rect1);
    picture.addShape(rect2);
    
    // Draw frame
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    picture.drawAll();
    SDL_RenderPresent(renderer);
    
    // Wait until the user closes the window
    bool running = true;
    SDL_Event event;
    while (running && SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }
    
    
    delete line1;
    delete line2;
    delete circle1;
    delete circle2;
    delete rect1;
    delete rect2;
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
