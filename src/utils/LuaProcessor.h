#pragma once
#ifndef PROJECT2D_LUAPROCESSOR_H
#define PROJECT2D_LUAPROCESSOR_H

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
        struct ambiguous_function {
            std::string name;
            sol::function function;
        };

        [[maybe_unused]] sol::state functionHolder; //Holds a collection of pointers to functions used by many a thing!
        [[maybe_unused]] std::vector<ambiguous_function> functions;

        [[maybe_unused]] sol::state systemControl; //Used for scripts that need to affect the system.
                                                   //Currently not refreshed between uses, maybe later it will be if
                                                   //it's needed.
        [[maybe_unused]] sol::state dirtyRunner; //Used for things that shouldn't affect the system, namely fetching values.

        [[maybe_unused]] std::map<unsigned int, sol::state> objectStates; //Used for instances of individual object, separate for each.
        [[maybe_unused]] std::map<unsigned int, std::string*> objectScripts;

    }

    void initialize();
    void destroy();

    void fetchFlags(const std::string& filePath);

    sol::state* initState(sol::state* state);

    unsigned int newState(); //TODO: This needs a better implementation that won't leave lingering lua states.
    void uploadScript(unsigned int id, std::string* script);

    template <typename Return, typename ...Args>
    void registerFunction(std::string funcName ,Return (*funcPtr)(Args...)) {
        functionHolder.set(funcName, funcPtr); //Register the shared function in the function holder object
        functions.emplace_back(funcName, functionHolder[funcName]); //Create what is essentially
        // a pointer to the function, but without a signature. Somehow sol2 is able to store the types ambiguously without losing them.
        // This is probably not the intended way to use this, and can definitely be done more efficiently, but it should
        // **JUST WORK** TODO: Make better implementation

        auto sysCtlSysNS = systemControl["sys"].get_or_create<sol::table>();
        sysCtlSysNS.set(funcName, funcPtr);

        for(auto &statePair : objectStates) {
            auto systemNS = (*&statePair.second)["sys"].get_or_create<sol::table>();

            systemNS.set(funcName, funcPtr);
        }
    }

    template <typename T, std::size_t S>
    void mapToLuaConf(std::map<std::string, std::array<T, S>> map, const std::string& path, const std::string& name) {
        std::string result;

        for(auto pair : map) {
            result += name + "." + pair.first + "={";

            for(auto item : pair.second) {
                result += std::to_string(item);
                result += ",";
            }

            result += "};";
        }

        std::ofstream file(path);
        file << result;
    }

    template <typename T, std::size_t S>
    std::map<std::string, std::array<T, S>> luaConfToMap(const std::string& path, const std::string& name) {
        std::map<std::string, std::array<T, S>> result;

        dirtyRunner.set(name, &result);

        dirtyRunner.script_file(path);

        return result;
    }

    unsigned int generateEntity(Entity* e, std::string* initScript);
}

#endif //PROJECT2D_LUAPROCESSOR_H
