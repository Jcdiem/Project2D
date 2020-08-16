#include "Engine.h"

Engine::Engine(){

}
Engine::~Engine(){

}

void Engine::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
    Engine::winH = height;
    Engine::winW = width;
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
    //All the sprites bb
    loadSprite(Sprite(200,82,"src/assets/dvd.png"));
}

void Engine::loadSprite(Sprite sprite) {
    Engine::spriteCollection.push_back(sprite);
}

Sprite Engine::getSprite(int spriteNum) {
    return Engine::spriteCollection[spriteNum];
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
    //Checking if Mr. DVD has moved on in life
    int dvdX = spriteCollection[0].getX();
    int dvdY = spriteCollection[0].getY();
    //Has hit right side
    if(dvdX >= (Engine::winW - dvdX)){

    }
    //Has hit left side
    else if(dvdX <= 0){

    }
    //has hit the bottom
    else if(dvdY >= (Engine::winH - dvdY)){

    }
    //Has hit the top
    else if(dvdY <= 0){

    }
    spriteCollection[0].setX(dvdX + double(dvdSpeed * dt()) / 5000);
    //std::cout << dvdX << std::endl;
}

void Engine::render() {
    SDL_RenderClear(renderer);
    //Begin rendering
    for(Sprite currentSprite: Engine::spriteCollection){
        SDL_FreeSurface(IMG_Load(currentSprite.getFile()));
        SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, IMG_Load(currentSprite.getFile())), NULL, currentSprite.getRect());
    }
    //End rendering
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
    int delta;
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