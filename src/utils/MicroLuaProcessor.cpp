#include "MicroLuaProcessor.h"

void MicroLuaProcessor::initialize() {
    dirtyRunner = sol::state();
}

void MicroLuaProcessor::generateEntity(Entity *e, const std::string &initScript) {

}
