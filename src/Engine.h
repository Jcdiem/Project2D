#ifndef PROJECT2DTD_ENGINE_H
#define PROJECT2DTD_ENGINE_H
#include "SDL2/SDL.h"
#include "TextureHandler.h"
#include "TextureMap.h"
#include "ECS/Components.h"
#include "JParser.h"

#include <chrono>
#include <random>
#include <iostream>

class TextureHandler;

class Engine {
public:
    Engine();
    ~Engine();


    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, bool resizable);

    //void loadEntity(EntityType* entity);

    void pushSpriteSheet(SDL_Texture* texture);

    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() {
        return isRunning;
    }

    JParser* getJson();

    static int* getEngineWidth();
    static int* getEngineHeight();

    static SDL_Renderer *getRenderer();

private:
    bool isRunning;
    SDL_Window *window;
    static SDL_Renderer *renderer;
    static int* engineWidth;
    static int* engineHeight;

    Manager manager;
    JParser* jParser = new JParser(&manager);
};

#endif //PROJECT2DTD_ENGINE_H
