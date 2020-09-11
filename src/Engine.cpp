#include "Engine.h"

Engine::Engine()=default;
Engine::~Engine()=default;

//TODO: REMOVE EXAMPLE PLAYER ENTITY
Entity* dvd;
TextureMap* texMap;


//TODO: Try not to use globals
SDL_Renderer* Engine::renderer = nullptr;



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
        else{
            printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0 , 0, 255);
            std::cout << "Renderer completed properly" << std::endl;
        }
        else{
            printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        }

        isRunning = true;
    }
    else{ //If failed, give errors
        printf("SDL_Init failed: %s\n", SDL_GetError());
        isRunning = false;
    }

    dvd = new Entity("src/assets/dvd.png",200,82,(rand() % (height - 82)),(rand() % (width - 200)));
    texMap = new TextureMap();

}

//void Engine::pushSpriteSheet(SDL_Texture* texture) {
//    spritesheetList.push_back(texture);
//}

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
    dvd->update();
}

void Engine::render() {
    SDL_RenderClear(renderer);
    //Begin rendering

//    for(Entity* cEnt : Engine::entsInUse){
//        cEnt->render();
//    }


    //WE ARE USING PAINTERS; FIRST ON LIST IS FIRST TO BE DRAWN, NEXT ON LIST IS DRAWN OVER TOP (Background first, foreground last)
    texMap->drawMap();
    dvd->render();


    //End rendering
    SDL_RenderPresent(renderer);
}

void Engine::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Shutdown complete" << std::endl;
}