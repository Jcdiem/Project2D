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

    //Any system can be disabled and everything else **should** work, but it would be rather silly to have a game
    //without any one of these...
    engine.initSystem(Systems::render, Flagger::getFlag("framerate"));
    engine.initSystem(Systems::update, 120);
    engine.initSystem(Systems::listen, 120);

    return 0;
}