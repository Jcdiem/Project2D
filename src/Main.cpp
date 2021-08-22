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
#endif
    Json::fetchFlags("assets/conf.json");
    Flagger::parse(argc, argv);
    AtlasMan::stitchAtlases();

    Engine engine;

    //Any system can be disabled and everything else **should** work, but it would be rather silly to have a game
    //without any one of these...
    if(Flagger::getFlag("threaded")) {
        engine.initSystem(Systems::render, Flagger::getFlag("framerate"));
        engine.initSystem(Systems::update, 120);
        engine.initSystem(Systems::listen, 120);
    } else {
        engine.initSystem(Systems::bundled, 120);
    }


    return 0;
}