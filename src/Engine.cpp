#include "Engine.h"

Engine::Engine() = default;

Engine::~Engine() = default;

//Engine Globals (PRIVATE)
sf::CircleShape testCircle;

void Engine::init(const char *title, int width, int height,
                  bool fullscreen, bool resizable, int threads) {
    window = new sf::RenderWindow(sf::VideoMode(width,height),"Project 2D");


    testCircle = sf::CircleShape(100.f);
    testCircle.setFillColor(sf::Color::Green);

    isRunning = true;
}


//void Engine::handleEvents() {
//    SDL_PumpEvents();
//}

void Engine::update() {
//    manager.refresh();
//    manager.update(threads);
}

void Engine::render() {
    window->clear();

    //window->draw things go here
    window->draw(testCircle);

    window->display();
}

void Engine::clean() {
}

void Engine::quit() {
    isRunning = false;
}
