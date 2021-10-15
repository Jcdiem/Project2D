#include "Engine.h"
#include "src/utils/Flagger.h"
#include "src/utils/Json.h"
#include "utils/draw/atlas/AtlasMan.h"

#ifdef X11
#include <X11/Xlib.h>
#endif

int main(int argc, char *argv[]) {
#ifdef X11
    XInitThreads();
    Logger::print(Level::INFO, "X11 was used for this build.");
#else
    Logger::print(Level::WARN, "X11 was NOT used for this build, this is likely to cause the engine to fail.");
#endif
    Json::fetchFlags("assets/conf.json");
    Flagger::parse(argc, argv);
    AtlasMan::stitchAtlases();

    Engine engine = Engine();

    //Any system can be disabled and everything else **should** work, but it would be rather silly to have a game
    //without any one of these...
    switch (Flagger::getFlag("compatMode")) {
        case 0 :
            Logger::print(Level::INFO, "Basic engine enabled. (0)");
            engine.initSystem(Systems::render, Flagger::getFlag("framerate"));
            engine.initSystem(Systems::update, Flagger::getFlag("tickrate"));
            engine.initSystem(Systems::listen, Flagger::getFlag("tickrate"));
            break;
        case 1 :
            Logger::print(Level::INFO, "Render hijack engine enabled. (1)");
            engine.initSystem(Systems::all, Flagger::getFlag("tickrate"));
            break;
        case 2 :
            Logger::print(Level::INFO, "Partially bundled engine enabled. (2)");
            engine.initSystem(Systems::update, Flagger::getFlag("tickrate"));
            engine.initSystem(Systems::rlSpecial, Flagger::getFlag("tickrate"));
            break;
        case 3 :
            Logger::print(Level::WARN, "Bundled engine enabled. (3)");
            engine.initSystem(Systems::bundled, Flagger::getFlag("tickrate"));
            break;
        default:
            Logger::print(Level::ERROR, "Unknown compatibility mode used.");
            return 1;
            break;
    }

    return 0;
}