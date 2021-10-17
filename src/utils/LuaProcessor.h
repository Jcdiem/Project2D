#pragma once
#ifndef BUILD_LUAPROCESSOR_H
#define BUILD_LUAPROCESSOR_H

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include <fstream>
#include <vector>

#include "Flagger.h"
#include "Logger.h"

namespace LuaProcessor {
    namespace { //Private parts of the LuaProcessor kept here.
        sol::state* systemControl;
        std::map<unsigned int, sol::state*> objectStates;
        std::map<unsigned int, std::string*> objectScripts;

        sol::state* initState() {
            auto* state = new sol::state;
            //Basic lua libraries aren't included by default, if you want them you'll have to change that here!
            (*state).open_libraries(sol::lib::base);

            return state;
        }
        sol::state* initState(sol::state* state) {
            //Basic lua libraries aren't included by default, if you want them you'll have to change that here!
            (*state).open_libraries(sol::lib::base);

            return state;
        }
    }

    void initialize();
    void destroy();

    unsigned int newState();
    void uploadScript(unsigned int id, std::string* script);

    void fetchFlags(std::string filePath);
};

#endif //BUILD_LUAPROCESSOR_H
