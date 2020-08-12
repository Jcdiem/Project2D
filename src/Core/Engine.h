#ifndef PROJECT2DTD_ENGINE_H
#define PROJECT2DTD_ENGINE_H
#include "SDL2/SDL.h"
#include "stdio.h"

class Engine {
public:
    Engine();
    ~Engine();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() {
        return isRunning;
    }

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer  *renderer;
};


#endif //PROJECT2DTD_ENGINE_H
