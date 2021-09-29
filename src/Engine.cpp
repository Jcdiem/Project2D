#include "Engine.h"

Engine::Engine() {
    int xRes = Flagger::getFlag("xRes");
    int yRes = Flagger::getFlag("yRes");
    bool vsync = Flagger::getFlag("vSync");

    if(Flagger::getFlag("fullscreen")) {
        window = new sf::RenderWindow(sf::VideoMode(xRes, yRes), "P2D", sf::Style::Fullscreen);
    } else {
        window = new sf::RenderWindow(sf::VideoMode(xRes, yRes), "P2D", sf::Style::Default);
    }

    window->setActive(false);

    window->setVerticalSyncEnabled(vsync);

    isRunning = true;
}

Engine::Engine(const std::string& title, int width, int height, bool fullscreen, bool vsync) {
    if(fullscreen) {
        window = new sf::RenderWindow(sf::VideoMode(width,height),title, sf::Style::Fullscreen);
    } else {
        window = new sf::RenderWindow(sf::VideoMode(width,height),title, sf::Style::Close);
    }

    window->setActive(false);

    window->setVerticalSyncEnabled(vsync);

    isRunning = true;
}

Engine::~Engine() {
    for(std::thread& system : systems) {
        if(system.joinable()) system.join();
    }

    window->close();

    delete window;
}

void Engine::initSystem(Systems system, int tickrate) {  //Used to init some or all engine systems, error handling may go here.
    switch(system) {
        case Systems::render: //Calls the clock runner function (as a new thread) with a function ptr to render.
            systems[0] = std::thread(&Engine::clockRunner, this, &Engine::render, tickrate);
            break;
        case Systems::update: //Calls the clock runner function (as a new thread) with a function ptr to update.
            systems[1] = std::thread(&Engine::clockRunner, this, &Engine::update, tickrate);
            break;
        case Systems::listen: //Calls the clock runner function with a function ptr to listen (Hijacking the current thread).
            Engine::clockRunner(&Engine::listen, tickrate);
            break;
        case Systems::all: //Initializes all systems and then hijacks current thread for --event listening-- rendering
            systems[0] = std::thread(&Engine::clockRunner, this, &Engine::listen, tickrate);
            systems[1] = std::thread(&Engine::clockRunner, this, &Engine::update, tickrate);
            Engine::clockRunner(&Engine::render, tickrate);
            break;
        case Systems::bundled:
            Engine::clockRunner(&Engine::bundledSystems, tickrate);
            break;
    }

    //TODO: Remove debug canvas
    spriteDebugList = {Sprite(0, 0, 1280, 7, "dvd"), Sprite(35, 500, "tiles", "10xConcreteTile")};
    canvas.fillCanvasLayer(spriteDebugList,0);
}

void Engine::listen() {
    while(window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                quit();
                break;
            case sf::Event::Resized:
                Flagger::setFlag("xRes", event.size.width);
                Flagger::setFlag("yRes", event.size.height);
                window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
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
    window->setActive(true);

    //Render calls
    window->clear(sf::Color::Black);

    //Render things here!
//    window->draw(canvas);

    window->display();

    window->setActive(false);
}

void Engine::bundledSystems() {
    listen();
    update();
    render();
}

void Engine::quit() {
    isRunning = false;
}

void Engine::clockRunner(void (Engine::*system)(), int tickrate) {
    const uint64_t tickDelay = 1000000000 / tickrate; //expected frame time in ns
    uint64_t tickTime;
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
