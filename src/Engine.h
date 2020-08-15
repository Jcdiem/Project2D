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
    int delta;
    int nsec;
    int nsecced;
    timespec dTime [2] = {NULL, NULL};
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer  *renderer;
};

#endif //PROJECT2DTD_ENGINE_H
