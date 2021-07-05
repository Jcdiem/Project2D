#include "Engine.h"
#include "src/utils/Flagger.h"
#include "src/utils/Json.h"

#ifdef X11
#include <X11/Xlib.h>
#endif

int main(int argc, char *argv[]) {
#ifdef X11
    XInitThreads();
#endif

    Json::initDefaultFlags("assets/conf.json");
    Flagger::parse(argc, argv);
    Flagger::printFlags();

    Engine engine;

    engine.initSystem(Systems::event_listener, 120);
    engine.initSystem(Systems::engine_update, 120);
    engine.initSystem(Systems::engine_render, Flagger::getFlag("framerate"));

    return 0;
}