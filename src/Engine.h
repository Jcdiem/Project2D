#pragma once
#ifndef PROJECT2DTD_ENGINE_H
#define PROJECT2DTD_ENGINE_H
#include <SDL2/SDL.h>
#include <chrono>
#include <random>
#include <iostream>
#include <thread>
#include <vector>

#include "TextureHandler.h"
#include "Canvas.h"
#include "ObjectBuilder.h"

#include "ECS/Components.h"
#include "ECS/InputManager.h"

class TextureHandler;

class Engine {
public:
    Engine();
    ~Engine();


    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, bool resizable, bool multithreaded);

    //void loadEntity(EntityType* entity);

    void handleEvents();
    void update();
    void render();
    void clean();
    void quit();

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
    bool multithread;

    Manager manager;
    std::vector<std::string> levelList;
};

#endif //PROJECT2DTD_ENGINE_H
