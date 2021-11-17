#include "LuaProcessor.h"

void LuaProcessor::initialize() {
    initState(&functionHolder);
    initState(&systemControl);
//  initState(&dirtyRunner); Dirty Runner does not need to be initialized because that would give it access to
//  Many functions that control a lot of the system.
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

    systemControl.script_file(filePath);
    systemControl["conf"]();
}

sol::state* LuaProcessor::initState(sol::state *state) {
    //Basic lua libraries aren't included by default, if you want them you'll have to change that here!
    state->open_libraries(sol::lib::base);

    auto systemNS = (*state)["sys"].get_or_create<sol::table>();

    systemNS.new_usertype<Entity>("entity",
                                "new", Manager::newEntity,
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

    systemNS.set("flags", Flagger::getInternal());

    for(auto func : functions) {
        systemNS.set(func.name, func.function);
    }

    return state;
}

void LuaProcessor::uploadScript(unsigned int id, std::string *script) {

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

//    objectScripts[new_id];

    return new_id;
}

unsigned int LuaProcessor::generateEntity(Entity* e, std::string* initScript) {
    auto e_id = newState();
    sol::state* state = &objectStates[e_id];
    objectScripts[e_id] = initScript;

    state->script(*objectScripts[e_id]);
    state->get<sol::function>("init")();

    state->set("self", e);

    return e_id;
}