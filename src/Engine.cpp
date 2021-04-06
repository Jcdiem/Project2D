#include <iostream>
#include "Engine.h"

Engine::Engine(const std::string& title, int width, int height, bool fullscreen, int threads) {
    if(fullscreen) {
        window = new sf::RenderWindow(sf::VideoMode(width,height),title, sf::Style::Fullscreen);
    } else {
        window = new sf::RenderWindow(sf::VideoMode(width,height),title, sf::Style::Close);
    }

    isRunning = true;
}

Engine::~Engine() { //Destructor used to destroy the sfml window and join any threads that need joining.
    window->close();

    for(std::thread& system : systems) {
        system.join();
    }
}

void Engine::initSystem(Systems system, int tickrate) {  //Used to init some or all engine systems, error handling may go here.
    switch(system) {
        case event_listener: //Hijacks the current thread to run the listener function (via clock runner)
            clockRunner(&Engine::listen, tickrate);
            break;
        case engine_update: //Calls the clock runner function (as a new thread) with a function ptr to update.
            systems[0] = std::thread(&Engine::clockRunner, this, &Engine::update, tickrate);
            break;
        case engine_render: //Calls the clock runner function (as a new thread) with a function ptr to render.
            systems[1] = std::thread(&Engine::clockRunner, this, &Engine::render, tickrate);
            break;
        case engine_all: //Calls the clock runner function (as a new thread) with a function ptr to update and render, then hijacks the thread for the listener.
            systems[0] = std::thread(&Engine::clockRunner, this, &Engine::update, tickrate);
            systems[1] = std::thread(&Engine::clockRunner, this, &Engine::render, tickrate);
            clockRunner(&Engine::listen, tickrate);
            break;
    }
}

void Engine::listen() { //Used to handle various sfml events, currently only exits, but could be more!
    switch (event.type) {
        case sf::Event::Closed: //The issue lies here, it seems the program receives an exit event constantly for some reason?
            quit();
            break;
        default:
            break;
    }
}

void Engine::update() {
    //Manager calls
}

void Engine::render() {
    //Render calls
    window->clear();

    //Render things here!

    window->display();
}

bool Engine::running() const {
    return isRunning;
}

void Engine::quit() { //Handles exit operations that need to be done before the destructor is called to finish the job.
    isRunning = false;
}

void Engine::clockRunner(void (Engine::*system)(), int tickrate) { //This function calls the Engine function supplied [tickrate] times per second, and attempts to account for lag.
    const uint64_t tickDelay = 1000000000 / tickrate; //expected frame time in ns
    u_int64_t tickTime;
    uint64_t timeLost = 0;

    while(isRunning) {
        auto tickStart = std::chrono::steady_clock::now();

        (this->*system)();

        auto tickEnd = std::chrono::steady_clock::now();
        tickTime = std::chrono::duration_cast<std::chrono::nanoseconds>(tickEnd-tickStart).count();

        if(tickDelay > tickTime && tickTime != 0){
            using namespace std::chrono_literals;
            if(timeLost == 0) {
                uint64_t sleepTime = tickDelay - tickTime;
                std::this_thread::sleep_for(1ns * (sleepTime));
            } else {
                uint64_t timeSaved = tickDelay - tickTime;
                timeLost -= timeSaved;
                if(timeLost < 0) {
                    std::this_thread::sleep_for(-1ns * timeLost);
                    timeLost = 0;
                }
            }
        } else {
            timeLost += (tickTime - tickDelay);
        }
    }
}