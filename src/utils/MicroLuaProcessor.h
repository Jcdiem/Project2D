#pragma once
#ifndef BUILD_MICROLUAPROCESSOR_H
#define BUILD_MICROLUAPROCESSOR_H

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

namespace MicroLuaProcessor {
    namespace { //Private parts of the MicroLuaProcessor kept here. Compiler seems to also think they go unused, that's not true...
        [[maybe_unused]] sol::state dirtyRunner; //Used for things that shouldnt affect the system, namely fetching values.
    }

    void initialize();
    void destroy();

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

#endif //BUILD_MICROLUAPROCESSOR_H
