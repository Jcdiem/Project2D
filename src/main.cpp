#include "Engine.h"

Engine *engine = nullptr;

int main (int argc, char* argv[]){
    engine = new Engine();

    engine->init("SomeRandomCrap",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,false);

    while(engine->running()){
        engine->handleEvents();
        engine->update();
        engine->render();
    }

    engine->clean();

    return 0;
}