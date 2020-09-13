#include "Engine.h"

Engine::Engine()=default;
Engine::~Engine()=default;

//TODO: REMOVE EXAMPLE PLAYER ENTITY & texMap
TextureMap* texMap;


//Globals (SHOULD ALL BE PRIVATE)
int Engine::engineWidth;
int Engine::engineHeight;
SDL_Renderer* Engine::renderer = nullptr;

Manager manager;
auto& newDVD(manager.addEntity());



void Engine::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    engineWidth = width;
    engineHeight = height;

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
    //Random gen setup
    std::random_device randomDevice; //Make a new random gen
    std::mt19937 mt(randomDevice()); //Generate using engine
    std::uniform_int_distribution<int> dist(0, height+width);

    //TODO: Get entities from file
    texMap = new TextureMap();
    newDVD.addComponent<PositionComponent>();
    newDVD.addComponent<SpriteComponent>("assets/dvd.png",200,82);
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
    manager.refresh();
    manager.update();
}

void Engine::render() {
    SDL_RenderClear(renderer);
    //Begin rendering

//    for(EntityType* cEnt : Engine::entsInUse){
//        cEnt->render();
//    }


    //WE ARE USING PAINTERS; FIRST ON LIST IS FIRST TO BE DRAWN, NEXT ON LIST IS DRAWN OVER TOP
    // (Background first, foreground last)
    texMap->drawMap();
    manager.draw();


    //End rendering
    SDL_RenderPresent(renderer);
}

void Engine::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Shutdown complete" << std::endl;
}

int Engine::getEngineWidth() {
    return engineWidth;
}

int Engine::getEngineHeight() {
    return engineHeight;
}

SDL_Renderer *Engine::getRenderer() {
    return renderer;
}
