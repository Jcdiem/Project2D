#include "Engine.h"
#include "src/utils/Flagger.h"
#include "src/utils/Json.h"
#include "utils/draw/atlas/AtlasMan.h"

//#ifdef X11
//#endif
#include <X11/Xlib.h>

int main(int argc, char *argv[]) {
//#ifdef X11
//#endif
    XInitThreads();
    Json::fetchFlags("assets/conf.json");
    Flagger::parse(argc, argv);
    AtlasMan::stitchAtlases();

    Engine engine = Engine();

    //Any system can be disabled and everything else **should** work, but it would be rather silly to have a game
    //without any one of these...
    if(Flagger::getFlag("threaded")) {
//        engine.initSystem(Systems::render, Flagger::getFlag("framerate"));
//        engine.initSystem(Systems::update, Flagger::getFlag("tickrate"));
//        engine.initSystem(Systems::listen, Flagger::getFlag("tickrate"));
        engine.initSystem(Systems::all, Flagger::getFlag("tickrate"));
    } else {
        engine.initSystem(Systems::all, Flagger::getFlag("tickrate"));
    }


    return 0;
}