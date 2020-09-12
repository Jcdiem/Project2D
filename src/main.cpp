#include "Engine.h"

Engine *engine = nullptr;

//TODO: Fix problem with thread not being properly run on some machines
static int renderThread(void *ptr) {

//    while(engine->running()) {
//        engine->render();
//    }
    return 1; //TODO: Fix having to return a 1 uselessly (possibly turn into error helping?)
}

int main (int argc, char* argv[]) {
    SDL_Thread *renderingThread;
    int threadReturn;

    const int FPS = 60; //target FPS
    const int frameDelay = 1000 / FPS; //expected frame delay

    Uint32 frameStart;
    int frameTime;

    engine = new Engine();

    engine->init("SomeRandomCrap",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,640,false);


    renderingThread = SDL_CreateThread(renderThread, "RenderThread", nullptr);
    //Check to make sure thread isn't rart
    if (nullptr == renderingThread) {
        printf("SDL_CreateThread failed: %s\n", SDL_GetError());
    }


    while(engine->running()) {

        frameStart = SDL_GetTicks(); //Ms since init


        engine->handleEvents();
        engine->update();
        engine->render();


       frameTime = SDL_GetTicks() - frameStart;
//Frame debugging       printf("Time for frame was %d, (%d - %d) \n",frameTime,SDL_GetTicks(),frameStart);

       if(frameDelay > frameTime && frameTime != 0){
           SDL_Delay(frameDelay/frameTime);
       }

    }

//    render.join();
    //Kill the rendering thread
    SDL_WaitThread(renderingThread, &threadReturn);
    printf("Rendering thread finished; value: %d (expected value is 1) \n", threadReturn);

    engine->clean();
    
    return 0;
}