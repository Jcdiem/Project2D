#ifndef PROJECT2DTD_ENGINE_H
#define PROJECT2DTD_ENGINE_H
#include "SDL2/SDL.h"
#include "TextureHandler.h"
#include "Canvas.h"
#include "ECS/Components.h"
#include "JParser.h"

#include <chrono>
#include <random>
#include <iostream>
#include <thread>

class TextureHandler;

class Engine {
public:
    Engine();
    ~Engine();


    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, bool resizable);

    //void loadEntity(EntityType* entity);

    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() {
        return isRunning;
    }

    static SDL_Renderer *getRenderer();

private:
    bool isRunning{};
    SDL_Window *window{};
    static SDL_Renderer *renderer;
    static Canvas *gameCanvas;
    static int* engineWidth;
    static int* engineHeight;

    Manager manager;
    JParser* jParser = new JParser(&manager);
};

#endif //PROJECT2DTD_ENGINE_H
