#include "Engine.h"
#include <chrono> //Just for testing, I need it to sleep the thread.

Engine *engine = nullptr;

void renderThread() {
    
    while(engine->running()) {
        engine->render();
    }
}

int main (int argc, char* argv[]) {
    engine = new Engine();

    engine->init("SomeRandomCrap",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,false);
    
    std::thread render (renderThread);
    
    while(engine->running()) {
        engine->handleEvents();
        engine->update();
        std::cout << engine->dt() << std::endl;
        //engine->dt();
        std::this_thread::sleep_for (std::chrono::milliseconds(12)); //Sleeps the thread
    }

    render.join();

    engine->clean();
    
    return 0;
}