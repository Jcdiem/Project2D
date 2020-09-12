#ifndef PROJECT2DTD_ENGINE_H
#define PROJECT2DTD_ENGINE_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Entity.h"
#include "TextureMap.h"
#include <thread>
#include <ctime>
#include <iostream>
#include <vector>

class Engine {
public:
    Engine();
    ~Engine();


    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    //void loadEntity(Entity* entity);
    int getW();
    int getH();

    void pushSpriteSheet(SDL_Texture* texture);

    void handleEvents();
    static void update();
    static void render();
    void clean();
    bool running() {
        return isRunning;
    }
    static SDL_Renderer *renderer;

private:
//    std::vector<Entity*> entsInUse;
//    std::vector<SDL_Texture*> spritesheetList;
    int windowWidth;
    int windowHeight;
    bool isRunning;
    SDL_Window *window;

};

#endif //PROJECT2DTD_ENGINE_H
