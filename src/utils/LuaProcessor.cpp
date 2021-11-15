#include "LuaProcessor.h"

void LuaProcessor::initialize() {
    initState(&functionHolder);
    initState(&systemControl);
    initState(&dirtyRunner);

    systemControl.set("flags", Flagger::getInternal());
}

void LuaProcessor::destroy() {
    for(auto &object : objectStates) {
        auto script = objectScripts[object.first];

        delete script;
    }
}

void LuaProcessor::fetchFlags(const std::string& filePath) {
    Flagger::set("xRes", 1280);
    Flagger::set("yRes", 720);
    Flagger::set("framerate", 60);
    Flagger::set("tickrate", 120);
    Flagger::set("fullscreen", false);
    Flagger::set("spriteSmoothing", true);
    Flagger::set("regenAtlas", false);
    Flagger::set("compatMode", 0);

    auto result = systemControl.script_file(filePath);
}

sol::state* LuaProcessor::initState(sol::state *state) {
    //Basic lua libraries aren't included by default, if you want them you'll have to change that here!
    state->open_libraries(sol::lib::base);

    state->set("newEntity", Manager::newEntity);
    state->new_usertype<Entity>("entity",
                                "kill", &Entity::kill,
                                "orphan", &Entity::orphan,
                                "setActive", &Entity::setActive,
                                "setParent", &Entity::setParent,
                                "addChild", &Entity::addChild,
                                "getData", &Entity::getData,
                                "killedStatus", &Entity::killedStatus,
                                "orphanedStatus", &Entity::orphanedStatus,
                                "activeStatus", &Entity::activeStatus,
                                "getParent", &Entity::getParent,
                                "getChildren", &Entity::getChildren,

                                "addSpriteComponent", &Entity::addComponent<SpriteComponent>
                                //Component adders must be added manually, that's done here!
    );

    return state;
}

void LuaProcessor::uploadScript(unsigned int id, std::string *script) {
    delete objectScripts[id];
    objectScripts[id] = script;
}

unsigned int LuaProcessor::newState() {
    unsigned int new_id;
    if(objectStates.empty()) {
        new_id = 0;
    } else {
        new_id = objectStates.end()->first + 1;
    }

    objectStates[new_id] = sol::state();
    initState(&objectStates[new_id]);

    objectScripts[new_id] = new std::string;

    return new_id;
}

void LuaProcessor::generateEntity(Entity *e, const std::string &initScript) {

}