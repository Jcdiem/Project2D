#include "Engine.h"

Engine::Engine()=default;
Engine::~Engine()=default;

//TODO: REMOVE EXAMPLE PLAYER ENTITY
Entity* dvd;


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
    srand(dt());
    //All the sprites bb
    pushSpriteSheet(TextureHandler::loadTexture("src/assets/dvd.png", renderer));
    dvd = new Entity("src/assets/dvd.png",renderer,200,82,(rand() % (height - 82)),(rand() % (width - 200)));
    loadEntity(dvd);
//    loadEntity(Sprite(200, 82, spritesheetList[0]));
}

void Engine::loadEntity(Entity* entity) {
    entsInUse.push_back(entity);
}

void Engine::pushSpriteSheet(SDL_Texture* texture) {
    spritesheetList.push_back(texture);
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
    dvd->update();
}

void Engine::render() {
    SDL_RenderClear(renderer);
    //Begin rendering
    for(Entity* cEnt : Engine::entsInUse){
        cEnt->render();
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
    nsec = int(ts.tv_nsec);
    // ^^^Set up nsec var with latest nanosecond
    
    std::cout << nsec << std::endl;
    
    if(nsec >= nsecced) {
        delta = nsec - nsecced;
    } else {
        delta = nsec + (1000000000 - nsecced);
    }
    
    nsecced = nsec;
    
    return delta;
}