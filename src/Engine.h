#pragma once
#ifndef PROJECT2DTD_ENGINE_H
#define PROJECT2DTD_ENGINE_H

#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

enum Systems {
    event_listener = 0,
    engine_update = 1,
    engine_render = 2,
    engine_all = 3
};

class Engine {
public:
    Engine(const std::string& title, int width, int height, bool fullscreen, int threads);
    ~Engine();

    void initSystem(Systems system, int tickrate); //Takes a enum to select which system to init

    void listen();
    void update();
    void render();
    [[nodiscard]] bool running() const;

    void quit();

    void clockRunner(void (Engine::*x)(), int tickrate);
private:
    std::thread systems[2];

    bool isRunning;

    sf::Event event;
    sf::RenderWindow* window;
};

#endif //PROJECT2DTD_ENGINE_H