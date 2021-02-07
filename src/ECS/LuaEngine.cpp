#include "../../include/ECS/LuaEngine.h"

LuaEngine::LuaEngine() {
    lua.open_libraries(sol::lib::base);
}

void LuaEngine::initScript(std::string script) {
    lua.script(script, &sol::script_default_on_error);
    lua["init"]();
}

void LuaEngine::runScript() {
    lua["main"]();
}

void LuaEngine::updScript(std::string script) {
    lua.script(script, &sol::script_default_on_error);
}

sol::state* LuaEngine::gLu() {
    return &lua;
}