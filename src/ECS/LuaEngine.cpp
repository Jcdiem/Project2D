#include "LuaEngine.h"

LuaEngine::LuaEngine() {
    lua.open_libraries(sol::lib::base);
}

void LuaEngine::initScript(std::string script) {
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
        std::cout << "an expected error has occurred:\n" << e.what() << std::endl;
    }
}

void LuaEngine::updScript(std::string script) {
    lua.script(script, &sol::script_default_on_error);
}

sol::state *LuaEngine::gLu() {
    return &lua;
}