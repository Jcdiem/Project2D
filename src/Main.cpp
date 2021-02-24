#include "Engine.h"

Engine *engine = nullptr;

void renderThread(bool debug, int framerate) {
    //This function implements nearly identical logic to the engine thread, but this one doesnt try to "Catch Up" if if lags behind

    int frameTime;

    const int frameDelay = 1000000000 / framerate; //expected frame time in ns
    if (debug) {
        std::cout << "Goal frame-time: " << frameDelay / 1000000.0 << "ms"<< std::endl;
    }

    while(engine->running()) {
        auto frameStart = std::chrono::steady_clock::now();

        engine->render();

        auto frameEnd = std::chrono::steady_clock::now();
        frameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(frameEnd-frameStart).count();

        if(frameDelay > frameTime && frameTime != 0){
            using namespace std::chrono_literals;
            int sleepTime = frameDelay - frameTime;
            if(debug) {
                std::cout << "Sleep time        = " << sleepTime / 1000000.0 << "ms" << std::endl;
                std::cout << "Total time        = " << sleepTime + frameTime << "ms, (Should be same as goal frametime)" << std::endl;
            }
            std::this_thread::sleep_for(1ns * (sleepTime));
        } else {
            float lostFrames = float(frameTime) / frameDelay;
            std::cout << "Uh oh, render thread can't keep up! About " << lostFrames << " frames behind..." << std::endl;
        }
    }
}

void printException(const std::exception& e, int level =  0)
{
    std::cerr << std::string(level, ' ') << "exception: " << e.what() << '\n';
    try {
        std::rethrow_if_nested(e);
    } catch(const std::exception& e) {
        printException(e, level+1);
    } catch(...) {}
}

int main (int argc, char* argv[]) {
    //FLAGS
    bool debug = false;
    bool fullscreen = false;
    bool resizable = false;
    int width = 0;
    int height = 0;
    int TPS = 0;
    int FPS = 0;
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
        } else if(strcmp(argv[i], "--fps") == 0 || strcmp(argv[i], "-fr") == 0) {
            printf("Forcing FPS!\n");
            i += 1;
            try {
                FPS = std::stoi(argv[i]);
            } catch(...) {
                printf("Unable to parse TPS, ignoring!");
            }
        } else if(strcmp(argv[i], "--tps") == 0 || strcmp(argv[i], "-t") == 0) {
            printf("Forcing TPS!\n");
            i += 1;
            try {
                TPS = std::stoi(argv[i]);
            } catch(...) {
                printf("Unable to parse TPS, ignoring!");
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
    if(TPS == 0) {
        TPS = JParser::getTPS();
        //! Target TPS
        //! Different from FPS, this is the cycle speed of main loop, 120 cap is good,
        //! adjusting this number affects game speed
    }
    if(FPS == 0) {
        FPS = JParser::getFPS();
        //! Target FPS
        //! Different from TPS, this is the cycle speed of render loop,
        //! should be no more than tps
    }

    if(FPS > TPS) {
        std::cout << "WARNING: A framerate higher than the tickspeed causes redundant frames to be rendered." << std::endl;
    }

    //FLAGS DONE :)

    try {
        const int tickDelay = 1000000000 / TPS; //expected frame time in ns
        if (debug) {
            std::cout << "Goal tick-time: " << tickDelay / 1000000.0 << "ms"<< std::endl;
        }

        int tickTime;
        int timeLost = 0;

        engine = new Engine();

        engine->init(&JParser::getTitle()[0],SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, fullscreen, resizable);

        std::thread renderer(renderThread, debug, FPS);

        while(engine->running()) {
            auto tickStart = std::chrono::steady_clock::now();


            //! MAIN LOOP CALLS
            engine->handleEvents();
            engine->update();
            //! MAIN LOOP CALLS

            auto tickEnd = std::chrono::steady_clock::now();
            tickTime = std::chrono::duration_cast<std::chrono::nanoseconds>(tickEnd-tickStart).count();
//          Frame debugging
            if(debug) {
                std::cout << "Time for tick was: " << tickTime / 1000000.0 << "ms" << std::endl;
            }

            if(tickDelay > tickTime && tickTime != 0){
                using namespace std::chrono_literals;
                if(timeLost == 0) {
                    int sleepTime = tickDelay - tickTime;
                    if(debug) {
                        std::cout << "Sleep time        = " << sleepTime / 1000000.0 << "ms" << std::endl;
                        std::cout << "Total time        = " << sleepTime + tickTime << "ms, (Should be same as goal ticktime)" << std::endl;
                    }
                    std::this_thread::sleep_for(1ns * (sleepTime));
                } else {
                    int timeSaved = tickDelay - tickTime;
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
                float lostTicks = float(tickTime) / tickDelay;
                std::cout << "Uh oh, engine thread can't keep up! About " << lostTicks << " ticks behind..." << std::endl;
                timeLost += (tickTime - tickDelay);
            }
        }

        renderer.join();

        engine->clean();

        return 0;
    }
    catch(const std::exception& e) {
        printException(e);
        return 1;
    }
}