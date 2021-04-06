#include "Engine.h"
#include "ObjectBuilder.h"

int main(int argc, char *argv[]) {
    //FLAGS
    bool fullscreen = false;
    int width = 0;
    int height = 0;
    int TPS = 0;
    int threads = 0;
    //FLAGS

    for (int i = 1; i < argc; i++) {
        printf("%s: ", argv[i]);
        //ADD ARGS!
        if (strcmp(argv[i], "--width") == 0 || strcmp(argv[i], "-w") == 0) {
            printf("Forcing Height!\n");
            i += 1;
            try {
                width = std::stoi(argv[i]);
            } catch (...) {
                printf("Unable to parse height, ignoring!");
            }
        } else if (strcmp(argv[i], "--height") == 0 || strcmp(argv[i], "-h") == 0) {
            printf("Forcing Width!\n");
            i += 1;
            try {
                height = std::stoi(argv[i]);
            } catch (...) {
                printf("Unable to parse width, ignoring! Did you mean --help?");
            }
        } else if (strcmp(argv[i], "--tps") == 0 || strcmp(argv[i], "-t") == 0) {
            printf("Forcing TPS!\n");
            i += 1;
            try {
                TPS = std::stoi(argv[i]);
            } catch (...) {
                printf("Unable to parse TPS, ignoring!");
            }
        } else if (strcmp(argv[i], "--objthreads") == 0 || strcmp(argv[i], "-o") == 0) {
            printf("Forcing obj Threads!\n");
            i += 1;
            try {
                TPS = std::stoi(argv[i]);
            } catch (...) {
                printf("Unable to parse thread count, ignoring!");
            }
        } else if (strcmp(argv[i], "--fullscreen") == 0 || strcmp(argv[i], "-f") == 0) {
            printf("Forcing Fullscreen (If display resolution is less than selected resolution, fullscreen is disabled)\n");
            fullscreen = true;
        } else if (strcmp(argv[i], "--help") == 0) {
            printf("Showing Help!\n");
            printf("The Following flags are available:\n");
            printf("--debug  \\ -d     | Enable debug mode\n");
            printf("--width  \\ -w     | Ignore width in config file\n");
            printf("--height \\ -h     | Ignore height in config file\n");
            printf("--fullscreen \\ -f | Ignore height in config file\n");
            printf("--help            | Show this help message\n");

            std::exit(0); //This is probably the only acceptable usage to std::exit, other than some weird error
            //handling, and even then it's probably better to throw an exception.
        } else {
            printf("Unknown flag.\n '--help' to get all flags\n");
        }

    }

    using ObjectBuilder::getValue;
    const std::string configFile = "assets/engineSettings.json";

    auto name = getValue<std::string>(configFile, "Title");
    if (width == 0) {
        width = getValue<int>(configFile, "WindowXRes");
    }
    if (height == 0) {
        height = getValue<int>(configFile, "WindowYRes");
    }
    if (!fullscreen) {
        fullscreen = getValue<bool>(configFile, "Fullscreen");
    }
    if (TPS == 0) {
        TPS = getValue<int>(configFile, "Tickrate");
        //! Target TPS
        //! Different from FPS, this is the cycle speed of main loop, 120 cap is good,
        //! adjusting this number affects game speed
    }

    Engine engine = Engine(name , width, height, fullscreen, threads);

    engine.initSystem(engine_all, TPS); // Somethings amiss?

    return 0;
}