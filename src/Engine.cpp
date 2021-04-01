#include "Engine.h"

Engine::Engine() = default;

Engine::~Engine() = default;

//Engine Globals (SHOULD ALL BE PRIVATE)
int *Engine::engineHeight = nullptr;
int *Engine::engineWidth = nullptr;

void Engine::init(const char *title, int xPos, int yPos, int width, int height,
                  bool fullscreen, bool resizable, int threads) {
}


//void Engine::handleEvents() {
//    SDL_PumpEvents();
//}

void Engine::update() {
//    manager.refresh();
//    manager.update(threads);
}

void Engine::render() {

}

void Engine::clean() {

}

void Engine::quit() {
    isRunning = false;
}
