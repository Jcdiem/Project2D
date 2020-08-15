#include "Engine.h"

SDL_Texture* dvdTex;
SDL_Rect srcR, destR;

Engine::Engine(){

}
Engine::~Engine(){

}

void Engine::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL Initialised" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            std::cout << "Window made properly" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0 , 0, 255);
            std::cout << "Renderer completed properly" << std::endl;
        }

        isRunning = true;
    }
    else{
        isRunning = false;
    }
    
    SDL_Surface* tmpSurface = IMG_Load("assets/dvd.png");
    dvdTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
}

void Engine::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

void Engine::update() {
    destR.h = 200;
    destR.w = 200;
}

void Engine::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, dvdTex, NULL, &destR);
    //Rendering loop
    SDL_RenderPresent(renderer);
}

void Engine::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Shutdown complete" << std::endl;
}

int Engine::dt() {
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    nsec = int(ts.tv_nsec) / 1000;
    // ^^^Set up nsec var with latest nanosecond
    
    if(nsec >= nsecced) {
        delta = nsec - nsecced;
    } else {
        delta = nsec + (1000000 - nsecced);
    }
    
    nsecced = nsec;
    
    return delta;
}