#include "Engine.h"
#include "src/utils/Flagger.h"
#include "utils/draw/atlas/AtlasMan.h"
#include "utils/LuaProcessor.h"
#include "utils/MicroLuaProcessor.h"

#ifdef X11
#include <X11/Xlib.h>
#endif

int main(int argc, char *argv[]) {
#ifdef X11
    XInitThreads();
    Logger::print(Level::INFO, "X11 was used for this build.");
#else
    Logger::print(Level::WARN, "X11 was NOT used for this build, this is likely to cause the engine to fail on some compatability settings");
#endif

    LuaProcessor::initialize();
    MicroLuaProcessor::initialize();
    LuaProcessor::fetchFlags("assets/conf.lua");
    Flagger::parse(argc, argv);
    AtlasMan::stitchAtlases();

    Engine engine;

    //Any system can be disabled and everything else **should** work, but it would be rather silly to have a game
    //without any one of these...
    switch (Flagger::find("compatMode")) {
        case 0 :
            Logger::print(Level::INFO, "Basic engine enabled. (0)");
            engine.initSystem(Systems::render, Flagger::find("framerate"));
            engine.initSystem(Systems::update, Flagger::find("tickrate"));
            engine.initSystem(Systems::listen, Flagger::find("tickrate"));
            break;
        case 1 :
            Logger::print(Level::INFO, "Render hijack engine enabled. (1)");
            engine.initSystem(Systems::all, Flagger::find("tickrate"));
            break;
        case 2 :
            Logger::print(Level::INFO, "Partially bundled engine enabled. (2)");
            engine.initSystem(Systems::update, Flagger::find("tickrate"));
            engine.initSystem(Systems::rlSpecial, Flagger::find("tickrate"));
            break;
        case 3 :
            Logger::print(Level::WARN, "Bundled engine enabled. (3)");
            engine.initSystem(Systems::bundled, Flagger::find("tickrate"));
            break;
        default:
            Logger::print(Level::ERROR, "Unknown compatibility mode used.");
            return 1;
//          break;
    }

    return 0;
}