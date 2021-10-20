#include "LuaProcessor.h"

void LuaProcessor::initialize() {
    initState(&systemControl);
    initState(&dirtyRunner);

    systemControl["flags"] = Flagger::getInternal();
}

void LuaProcessor::destroy() {
    for(auto &object : objectStates) {
        auto script = objectScripts[object.first];

        delete script;
    }
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

    objectStates[new_id] = initState();
    objectScripts[new_id] = new std::string;

    return new_id;
}

void LuaProcessor::fetchFlags(std::string filePath) {
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

void LuaProcessor::generateEntity(Entity* e, const std::string& initScript) {
    dirtyRunner["new_entity"] = e;

    dirtyRunner.script(initScript);
}
