#include "Engine.h"

Engine::Engine() {
    int xRes = Flagger::getFlag("xRes");
    int yRes = Flagger::getFlag("yRes");

    if(Flagger::getFlag("fullscreen")) {
        window = new sf::RenderWindow(sf::VideoMode(xRes, yRes), "P2D", sf::Style::Fullscreen);
    } else {
        window = new sf::RenderWindow(sf::VideoMode(xRes, yRes), "P2D", sf::Style::Close);
    }

    isRunning = true;
}

Engine::Engine(const std::string& title, int width, int height, bool fullscreen, int threads) {
    if(fullscreen) {
        window = new sf::RenderWindow(sf::VideoMode(width,height),title, sf::Style::Fullscreen);
    } else {
        window = new sf::RenderWindow(sf::VideoMode(width,height),title, sf::Style::Close);
    }

    isRunning = true;
}

Engine::~Engine() {
    for(std::thread& system : systems) {
        system.join();
    }

    window->close();
    delete window;
}

void Engine::initSystem(Systems system, int tickrate) {  //Used to init some or all engine systems, error handling may go here.
    switch(system) {
        case event_listener: //Calls the clock runner function (as a new thread) with a function ptr to listen.
            systems[0] = std::thread(&Engine::clockRunner, this, &Engine::listen, tickrate);
            break;
        case engine_update: //Calls the clock runner function (as a new thread) with a function ptr to update.
            systems[1] = std::thread(&Engine::clockRunner, this, &Engine::update, tickrate);
            break;
        case engine_render: //Calls the clock runner function, hijacking the current thread
            Engine::clockRunner(&Engine::render, tickrate);
            break;
        case engine_all: //Initializes all systems and then hijacks current thread for rendering
            systems[0] = std::thread(&Engine::clockRunner, this, &Engine::listen, tickrate);
            systems[1] = std::thread(&Engine::clockRunner, this, &Engine::update, tickrate);
            Engine::clockRunner(&Engine::render, tickrate);
            break;
    }
}

void Engine::listen() {
    while(window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                quit();
                break;
            default:
                break;
        }
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

void Engine::quit() {
    isRunning = false;
}

void Engine::clockRunner(void (Engine::*system)(), int tickrate) {
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
