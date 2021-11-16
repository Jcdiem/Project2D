#include "Manager.h"

void Manager::initialize() {
    LuaProcessor::registerFunction("newEntity", newEntity);
}

void Manager::newEntity(std::string id) {
    try {
        std::string* initScript = &cachedEntityScripts.at(id);

        auto newEntity = entities.emplace_back();

        unsigned int objID = LuaProcessor::generateEntity(&newEntity, initScript);
        newEntity.getData()->type = id;
        newEntity.getData()->objID = objID;
    } catch (std::out_of_range& e) {
        Logger::print(ERROR, "Attempted to create entity of id ", id,
                      " which does not exist, or hasn't been cached yet...");
    }
}
