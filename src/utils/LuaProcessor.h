#pragma once
#ifndef BUILD_LUAPROCESSOR_H
#define BUILD_LUAPROCESSOR_H

#ifndef SOL_ALL_SAFETIES_ON
#define SOL_ALL_SAFETIES_ON 1
#endif //SOL_ALL_SAFETIES_ON

#include <sol/sol.hpp>
#include <fstream>
#include <vector>
#include <list>

#include "Flagger.h"
#include "Logger.h"
#include "entity/Entity.h"
#include "entity/Manager.h"

namespace LuaProcessor {
    namespace { //Private parts of the LuaProcessor kept here. Compiler seems to also think they go unused, that's not true...
        [[maybe_unused]] sol::state systemControl; //Used for scripts that need to affect the system.
        [[maybe_unused]] std::map<unsigned int, sol::state> objectStates; //Used for instances of individual object, separate for each.
        [[maybe_unused]] std::map<unsigned int, std::string*> objectScripts;

    }

    void initialize();
    void destroy();

    void fetchFlags(const std::string& filePath);

    void initState(sol::state* state);
    sol::state initState();

    unsigned int newState();
    void uploadScript(unsigned int id, std::string* script);
}

#endif //BUILD_LUAPROCESSOR_H
