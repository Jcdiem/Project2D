#ifndef PROJECT2DTD_ENGINE_H
#define PROJECT2DTD_ENGINE_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Entity.h"
#include <thread>
#include <time.h>
#include <iostream>
#include <vector>

class Engine {
public:
    Engine();
    ~Engine();


    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    //void loadEntity(Entity* entity);
    void pushSpriteSheet(SDL_Texture* texture);

    void handleEvents();
    void update();
    void render();
    void clean();
    int dt();
    bool running() {
        return isRunning;
    }

private:
    //std::vector<Entity*> entsInUse;
    std::vector<SDL_Texture*> spritesheetList;
    int dvdSpeedX = 1;
    int dvdSpeedY = 1;
    int nsec;
    int nsecced;
    bool isRunning;
    int winW;
    int winH;
    SDL_Window *window;
    SDL_Renderer  *renderer;

};

#endif //PROJECT2DTD_ENGINE_H
