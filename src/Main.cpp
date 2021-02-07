#include "../include/Engine.h"

Engine *engine = nullptr;

static int renderThread([[maybe_unused]] void *ptr) {
    return 0;
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
    bool fullscreen = false;
    bool resizable = false;
    int width = 0;
    int height = 0;
    //FLAGS

    for(int i = 1; i < argc; i++) {
        printf("%s: ", argv[i]);
        //ADD ARGS!
        if(strcmp(argv[i], "--debug") == 0 || strcmp(argv[i], "-d") == 0 ) {
            printf("Debug enabled!\n");
            debug = true;
        } else if(strcmp(argv[i], "--width") == 0 || strcmp(argv[i], "-w") == 0 ) {
            printf("Forcing Height!\n");
            i += 1;
            try {
                width = std::stoi(argv[i]);
            } catch(...) {
                printf("Unable to parse height, ignoring!");
            }
        } else if(strcmp(argv[i], "--height") == 0 || strcmp(argv[i], "-h") == 0 ) {
            printf("Forcing Width!\n");
            i += 1;
            try {
                height = std::stoi(argv[i]);
            } catch(...) {
                printf("Unable to parse width, ignoring! Did you mean --help?");
            }
        } else if(strcmp(argv[i], "--fullscreen") == 0 || strcmp(argv[i], "-f") == 0) {
            printf("Forcing Fullscreen (If display resolution is less than selected resolution, fullscreen is disabled)\n");
            fullscreen = true;
        } else if(strcmp(argv[i], "--resizable") == 0 || strcmp(argv[i], "-r") == 0) {
            printf("Forcing Resizability\n");
            resizable = true;
        } else if(strcmp(argv[i], "--help") == 0) {
            printf("Showing Help!\n");
            printf("The Following flags are available:\n");
            printf("--debug  \\ -d     | Enable debug mode\n");
            printf("--width  \\ -w     | Ignore width in config file\n");
            printf("--height \\ -h     | Ignore height in config file\n");
            printf("--fullscreen \\ -f | Ignore height in config file\n");
            printf("--resizable \\ -r  | Ignore height in config file\n");
            printf("--help            | Show this help message\n");

            std::exit(0); //This is probably the only acceptable usage to std::exit, other than some weird error
            //handling, and even then it's probably better to throw an exception.
        } else {
            printf("Unknown flag.\n '--help' to get all flags\n");
        }

    }

    //FLAGS DONE :)

    try {
        SDL_Thread *renderingThread;
        int threadReturn;

        const int TPS = 120;//! Target TPS
                            //! Different from FPS, this is the cycle speed of main loop, 30 cap is good,
                            //! adjusting this number affects game speed
        const int frameDelay = 1000000000 / TPS; //expected frame time in ns
        if (debug) {
            std::cout << "Goal frametime: " << frameDelay / 1000000.0 << "ms"<< std::endl;
        }

        int frameTime;
        int timeLost = 0;

        engine = new Engine();

        if(width == 0) {
            width = JParser::getXSize();
        }
        if(height == 0) {
            height = JParser::getYSize();
        }
        if(!fullscreen) {
            fullscreen = JParser::getFullscreen();
        }
        if(!resizable) {
            resizable = JParser::getResizable();
        }

        engine->init(&JParser::getTitle()[0],SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, fullscreen, resizable);

        renderingThread = SDL_CreateThread(renderThread, "renderer", nullptr);

        if (nullptr == renderingThread) {
            std::throw_with_nested(SDL_GetError());
        }

        while(engine->running()) {
            auto frameStart = std::chrono::steady_clock::now();


            //! MAIN LOOP CALLS
            engine->handleEvents();
            engine->update();
            engine->render();
            //! MAIN LOOP CALLS

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
                        std::this_thread::sleep_for(-1ns * timeLost);
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
        printf("Rendering thread finished; value: %d (expected value is 0) \n", threadReturn);

        engine->clean();

        return 0;
    }
    catch(const std::exception& e) {
        print_exception(e);
        return 1;
    }
}