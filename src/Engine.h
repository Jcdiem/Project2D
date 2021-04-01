#pragma once
#ifndef PROJECT2DTD_ENGINE_H
#define PROJECT2DTD_ENGINE_H
#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include <iostream>
#include <thread>
#include <vector>

class TextureHandler;

class Engine {
public:
    Engine();
    ~Engine();


    void init(const char* title, int width, int height, bool fullscreen, bool resizable, int threads);

    //void loadEntity(EntityType* entity);

    void handleEvents();
    void update();
    void render();
    void clean();
    void quit();

    bool running() const {
        return isRunning;
    }

private:
    bool isRunning{};
    sf::RenderWindow *window;
    std::vector<sf::Drawable*> drawQueue;
    int threads;

//    Manager manager;
    std::vector<std::string> levelList;
};

#endif //PROJECT2DTD_ENGINE_H
