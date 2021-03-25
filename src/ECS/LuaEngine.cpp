#include "LuaEngine.h"

LuaEngine::LuaEngine() {
    lua.open_libraries(sol::lib::base);
    lua.open_libraries(sol::lib::math);
}

void LuaEngine::initScript(const std::string& script) {
    updScript(script);

    try {
        lua.unsafe_script("init()");
    }
    catch (const sol::error &e) {
        std::cout << "An unexpected error has occurred:\n    " << e.what() << std::endl;
    }
}

void LuaEngine::runScript() {
    try {
        lua.unsafe_script("main()");
    }
    catch (const sol::error &e) {
        std::cout << "an unexpected error has occurred:\n" << e.what() << std::endl;
    }
}

void LuaEngine::updScript(const std::string& script) {
    lua.script(script, &sol::script_default_on_error);
}

sol::state *LuaEngine::gLu() {
    return &lua;
}