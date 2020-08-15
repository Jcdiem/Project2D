#ifndef PROJECT2DTD_ENGINE_H
#define PROJECT2DTD_ENGINE_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <thread>
#include <time.h>
#include <iostream>

class Engine {
public:
    Engine();
    ~Engine();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();
    int dt();
    bool running() {
        return isRunning;
    }

private:
    int dvdSpeed = 1;
    double dvdX = 0;
    int dvdY = 0;
    int nsec;
    int nsecced;
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer  *renderer;
};

#endif //PROJECT2DTD_ENGINE_H
