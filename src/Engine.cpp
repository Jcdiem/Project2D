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
    loadTexture(SDL_CreateTextureFromSurface(
                renderer,
                IMG_Load(spriteCollection[0].getFile())
            )
    );
    srand(dt());
    spriteCollection[0].setY((rand() % height) - 82);
    spriteCollection[0].setX((rand() % width) -200);
}

void Engine::loadSprite(Sprite sprite) {
    spriteCollection.push_back(sprite);
}

Sprite Engine::getSprite(int spriteNum) {
    return Engine::spriteCollection[spriteNum];
}

void Engine::loadTexture(SDL_Texture* texture) {
    texturesInUse.push_back(texture);
}

SDL_Texture* Engine::getTexture(int texNum){
    return texturesInUse[texNum];
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
    int dvdH = spriteCollection[0].getH();
    int dvdW = spriteCollection[0].getW();
    //Has hit right side
    if(dvdX >= (Engine::winW - dvdW)){
        dvdSpeedX = -1;
        //dvdSpeedY = rand() % 5;

    }
    //Has hit left side
    else if(dvdX <= 0){
        dvdSpeedX = 1;
        //dvdSpeedY = rand() % 5;
    }
    //has hit the bottom
    else if(dvdY >= (Engine::winH - dvdH)){
        //dvdSpeedX = -1*(rand() % 5);
        dvdSpeedY = -1;
    }
    //Has hit the top
    else if(dvdY <= 0){
        //dvdSpeedX = -1*(rand() % 5);
        dvdSpeedY = 1;
    }
//    spriteCollection[0].setX(dvdSpeedX + double(dvdSpeedX * dt()) / 1);
//    spriteCollection[0].setY(dvdSpeedY + double(dvdSpeedX * dt()) / 1);
    spriteCollection[0].setX(dvdSpeedX+dvdX);
    spriteCollection[0].setY(dvdSpeedY+dvdY);
//    std::cout << dvdX << ", " << dvdY << "," << dt() << std::endl;
}

void Engine::render() {
    SDL_RenderClear(renderer);
    //Begin rendering
    for(int i = 0; i < int(Engine::texturesInUse.size()); i++){

        SDL_RenderCopy(renderer, texturesInUse[i], NULL, spriteCollection[i].getRect());
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