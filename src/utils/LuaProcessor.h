#pragma once
#ifndef BUILD_LUAPROCESSOR_H
#define BUILD_LUAPROCESSOR_H

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include <fstream>
#include <vector>
#include <list>

#include "Flagger.h"
#include "Logger.h"
#include "entity/Entity.h"

namespace LuaProcessor {
    namespace { //Private parts of the LuaProcessor kept here. Compiler seems to also think they go unused, that's not true...
        [[maybe_unused]] sol::state systemControl; //Used for scripts that need to affect the system.
        [[maybe_unused]] sol::state dirtyRunner; //Used for one time scripts that shouldn't be run multiple times, or affect the system
        [[maybe_unused]] std::map<unsigned int, sol::state> objectStates; //Used for instances of individual object, separate for each.
        [[maybe_unused]] std::map<unsigned int, std::string*> objectScripts;

        [[maybe_unused]] void initState(sol::state* state) {
            //Basic lua libraries aren't included by default, if you want them you'll have to change that here!
            (*state).open_libraries(sol::lib::base);

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
            );
        }

        [[maybe_unused]] sol::state initState() {
            auto state = sol::state();
            //Basic lua libraries aren't included by default, if you want them you'll have to change that here!
            initState(&state);

            return state;
        }
    }

    void initialize();
    void destroy();

    unsigned int newState();
    void uploadScript(unsigned int id, std::string* script);

    void fetchFlags(std::string filePath);

    template <typename T, std::size_t S>
    void mapToLuaConf(std::map<std::string, std::array<T, S>> map, const std::string& path, std::string name) {
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
    std::map<std::string, std::array<T, S>> luaConfToMap(const std::string& path, std::string name) {
        std::map<std::string, std::array<T, S>> result;

        dirtyRunner[name] = &result;

        dirtyRunner.script_file(path);

        return result;
    }

    void generateEntity(Entity* e, const std::string &initScript);
}

#endif //BUILD_LUAPROCESSOR_H
