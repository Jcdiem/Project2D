#include "Engine.h"

Engine *engine = nullptr;

static int renderThread(void *ptr) {

//    while(engine->running()) {
//        engine->render();
//    }
    return 1; //TODO: Fix having to return a 1 uselessly (possibly turn into error helping?)
}

void print_exception(const std::exception& e, int level =  0)
{
    std::cerr << std::string(level, ' ') << "exception: " << e.what() << '\n';
    try {
        std::rethrow_if_nested(e);
    } catch(const std::exception& e) {
        print_exception(e, level+1);
    } catch(...) {}
}

int main (int argc, char* argv[]) {
    srand((int)time(0));//Just for multi cd demo
    try {
        SDL_Thread *renderingThread;
        int threadReturn;

        const int FPS = 120; //target FPS
        const int frameDelay = 1000000000 / FPS; //expected frame delay

        int frameTime;

        engine = new Engine();

        engine->init("SomeRandomCrap",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,640,false, true);

        renderingThread = SDL_CreateThread(renderThread, "RenderThread", nullptr);
        //Check to make sure thread isn't rart
        if (nullptr == renderingThread) {
            printf("SDL_CreateThread failed: %s\n", SDL_GetError());
        }

        while(engine->running()) {
            auto frameStart = std::chrono::high_resolution_clock::now();


            engine->handleEvents();
            engine->update();
            engine->render();

            auto frameEnd = std::chrono::high_resolution_clock::now();
            frameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(frameEnd-frameStart).count();
//          Frame debugging
            std::cout << "Time for frame was: " << frameTime / 1000000.0 << "ms" << std::endl;

            if(frameDelay > frameTime && frameTime != 0){
                using namespace std::chrono_literals;
//                SDL_Delay(frameDelay/frameTime);
                std::this_thread::sleep_for(1ns * frameDelay/frameTime);
            }

        }

//    render.join();
        //Kill the rendering thread
        SDL_WaitThread(renderingThread, &threadReturn);
        printf("Rendering thread finished; value: %d (expected value is 1) \n", threadReturn);

        engine->clean();

        return 0;
    }
    catch(const std::exception& e) {
        print_exception(e);
        return 1;
    }
}