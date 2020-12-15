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
    //FLAGS
    bool debug = false;
    //FLAGS


    srand((int)time(0));//Just for multi cd demo

    for(int i = 1; i < argc; i++) {
        printf("%s: ", argv[i]);
        //ADD ARGS!
        if(strcmp(argv[i], "--debug") == 0 || strcmp(argv[i], "-d") == 0 ) {
            printf("Debug enabled!\n");
            debug = true;
        } else if(strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0 ) {
            printf("Showing Help!\n");
            printf("The Following flags are available:\n");
            printf("--debug \\ -d | Enable debug mode\n");
            printf("--help  \\ -h | Show this help message\n");
            std::exit(0);
        } else {
            printf("Unknown flag.\n");
        }

    }

    try {
        SDL_Thread *renderingThread;
        int threadReturn;

        const int TPS = 120; //! Target TPS
        //! Different from FPS, this is the cycle speed of main loop, 30 cap is good,
        //! adjusting this number affects game speed
        const int frameDelay = 1000000000 / TPS; //expected frame time in ns
        if (debug) {
            std::cout << "Goal frametime: " << frameDelay / 1000000.0 << "ms"<< std::endl;
        }

        int frameTime;

        int timeLost = 0;

        engine = new Engine();

        engine->init(&engine->getJson()->getTitle()[0],SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,engine->getJson()->getXSize(),engine->getJson()->getYSize(),false, false);

        renderingThread = SDL_CreateThread(renderThread, "RenderThread", nullptr);

        if (nullptr == renderingThread) {
            std::throw_with_nested(SDL_GetError());
        }

        while(engine->running()) {
            auto frameStart = std::chrono::steady_clock::now();

            engine->handleEvents();
            engine->update();
            engine->render();

            auto frameEnd = std::chrono::steady_clock::now();
            frameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(frameEnd-frameStart).count();
//          Frame debugging
            if(debug) {
                std::cout << "Time for frame was: " << frameTime / 1000000.0 << "ms" << std::endl;
            }

            if(frameDelay > frameTime && frameTime != 0){
                using namespace std::chrono_literals;
                if(timeLost == 0) {
                    int sleepTime = frameDelay - frameTime;
                    if(debug) {
                        std::cout << "Sleep time        = " << sleepTime / 1000000.0 << "ms" << std::endl;
                        std::cout << "Total time        = " << sleepTime + frameTime << "ms, (Should be same as goal frametime)" << std::endl;
                    }
                    std::this_thread::sleep_for(1ns * (sleepTime));
                } else {
                    int timeSaved = frameDelay - frameTime;
                    timeLost -= timeSaved;
                    if(debug) {
                        std::cout << timeSaved / 1000000.0 << "ms saved" << std::endl;
                        std::cout << "Currently making up lost time! " << timeLost / 1000000.0 << "ms to make up!" << std::endl;
                    }
                    if(timeLost < 0) {
                        std::this_thread::sleep_for(1ns * abs(timeLost));
                        timeLost = 0;
                        if(debug) {
                            std::cout << "No more time to make up!" << std::endl;
                        }
                    }
                }
            } else {
                float lostFrames = float(frameTime) / frameDelay;
                std::cout << "Uh oh, engine thread can't keep up! About " << lostFrames << " frames behind..." << std::endl;
                timeLost += (frameTime - frameDelay);
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