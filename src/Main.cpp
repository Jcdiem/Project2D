#include "Engine.h"

void updateThread(Engine* engine, int TPS, bool debug) {
    const int tickDelay = 1000000000 / TPS; //expected frame time in ns
    int tickTime;
    int timeLost = 0;

    if (debug) {
        std::cout << "Goal tick-time: " << tickDelay / 1000000.0 << "ms"<< std::endl;
    }

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
}

void exitListener(Engine* engine) {
    SDL_Event event;

    do {
        SDL_WaitEvent(&event);
    } while(event.type != SDL_QUIT);

    engine->quit();
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

int main(int argc, char* argv[]) {
    //FLAGS
    bool debug = false;
    bool fullscreen = false;
    bool resizable = false;
    int width = 0;
    int height = 0;
    int TPS = 0;
    int threads = 0;
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
        } else if(strcmp(argv[i], "--tps") == 0 || strcmp(argv[i], "-t") == 0) {
            printf("Forcing TPS!\n");
            i += 1;
            try {
                TPS = std::stoi(argv[i]);
            } catch(...) {
                printf("Unable to parse TPS, ignoring!");
            }
        } else if(strcmp(argv[i], "--objthreads") == 0 || strcmp(argv[i], "-o") == 0) {
            printf("Forcing obj Threads!\n");
            i += 1;
            try {
                TPS = std::stoi(argv[i]);
            } catch(...) {
                printf("Unable to parse thread count, ignoring!");
            }
        } else if(strcmp(argv[i], "--fullscreen") == 0 || strcmp(argv[i], "-f") == 0) {
            printf("Forcing Fullscreen (If display resolution is less than selected resolution, fullscreen is disabled)\n");
            fullscreen = true;
        } else if(strcmp(argv[i], "--resizable") == 0 || strcmp(argv[i], "-r") == 0) {
            printf("Forcing Resizability\n");
            resizable = true;
        }  else if(strcmp(argv[i], "--help") == 0) {
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

    using ObjectBuilder::getValue;
    const std::string configFile = "assets/engineSettings.json";
    if(width == 0) {
        width = getValue<int>(configFile, "WindowXRes");
    }
    if(height == 0) {
        height = getValue<int>(configFile, "WindowYRes");
    }
    if(!fullscreen) {
        fullscreen = getValue<bool>(configFile, "Fullscreen");
    }
    if(!resizable) {
        resizable = getValue<bool>(configFile, "ForceResizable");
    }
    if(TPS == 0) {
        TPS = getValue<int>(configFile, "Tickrate");
        //! Target TPS
        //! Different from FPS, this is the cycle speed of main loop, 120 cap is good,
        //! adjusting this number affects game speed
    }

    if(threads == 0) threads = getValue<int>(configFile, "ObjectThreads");
    if(threads < 1) threads = 1;

    //FLAGS DONE :)

    try {

        Engine* engine = new Engine();

        engine->init(&getValue<std::string>(configFile, "Title")[0], SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, fullscreen, resizable, threads);

        std::thread updater(updateThread, engine, TPS, debug);
        std::thread exiter(exitListener, engine);

        while(engine->running()) {
            engine->render();
        }

        updater.join();
        exiter.join();

        engine->clean();

        return 0;
    }
    catch(const std::exception& e) {
        printException(e);
        return 1;
    }
}