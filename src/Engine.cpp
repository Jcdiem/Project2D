#include "../include/Engine.h"

Engine::Engine() = default;

Engine::~Engine() = default;

//TODO: REMOVE EXAMPLE texMap
TextureMap *texMap;


//Globals (SHOULD ALL BE PRIVATE)
Canvas *Engine::gameCanvas = nullptr;
SDL_Renderer *Engine::renderer = nullptr;
int *Engine::engineHeight = nullptr;
int *Engine::engineWidth = nullptr;

void Engine::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen, bool resizable) {
    int flags = 0;
    if (fullscreen) {
        flags += SDL_WINDOW_FULLSCREEN;
    }
    if (resizable) {
        flags += SDL_WINDOW_RESIZABLE;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL Initialised" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            std::cout << "Window made properly" << std::endl;
        } else {
            std::throw_with_nested(std::runtime_error(std::string("SDL_CreateWindow failed: %s\n").append(SDL_GetError())));
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            TextureHandler::setRenderer(renderer);
            std::cout << "Renderer completed properly" << std::endl;
        } else {
            std::throw_with_nested(std::runtime_error(std::string("SDL_CreateRenderer failed: %s\n").append(SDL_GetError())));
        }

        isRunning = true;
    } else {
        std::throw_with_nested(std::runtime_error(std::string("SDL_Init failed: %s\n").append(SDL_GetError())));
    }

    SDL_GetWindowSize(window, engineWidth, engineHeight);

    manager.setWW(width);
    manager.setWH(height);

    try {
        JParser::genLevelList();
    }
    catch(...) {
        std::throw_with_nested(std::runtime_error("Level list generation failed."));
    }

    //TODO: Get entities from file
    texMap = new TextureMap();

    gameCanvas = new Canvas();
    gameCanvas -> importTexMap(texMap);

    jParser->genObjs(JParser::getLevel(0));
}


void Engine::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

void Engine::update() {
//    Manager *man = levelloader->getManager();
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
    gameCanvas.draw();
    manager.draw();


    //End rendering
    SDL_RenderPresent(renderer);
}

void Engine::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    printf("Shutdown complete");
}

SDL_Renderer *Engine::getRenderer() {
    return renderer;
}
