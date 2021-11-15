#include "Manager.h"

void Manager::initialize() {
    LuaProcessor::registerFunction("newEntity", newEntity);
}

void Manager::newEntity(int id) {
    try {
        std::string initScript = cachedInitScripts.at(id);

        auto newEntity = entities.emplace_back();

        LuaProcessor::generateEntity(&newEntity, initScript);
    } catch (std::out_of_range& e) {
        Logger::print(ERROR, "Attempted to create entity of id ", id, " which does not exist.");
    }
}
