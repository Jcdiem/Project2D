#pragma once
#ifndef BUILD_JSON_H
#define BUILD_JSON_H

#include <nlohmann/json.hpp>
#include <fstream>
#include <map>

#include "Flagger.h"
#include "Logger.h"

namespace Json {
    void fetchFlags(const std::string& filePath);

    std::map<std::string, int> jsonToMap(const std::string& path);
    void mapToJson(const std::map<std::string, int>& map, const std::string& path);

    template <typename... types>
    std::map<std::string, std::tuple<types...>> jsonToMap(const std::string& path) {
        try {
            nlohmann::json file = nlohmann::json::parse(std::fstream(path), nullptr, true, true);
            std::map<std::string, std::tuple<types...>> output;

            for(auto& [key, value] : file.items()) {
                output[key] = value;
            }

            return output;
        } catch(std::exception& e) {
            Logger::print(Level::ERROR, "Failed to convert json file \"", path, "\" to a map: ", e.what());
            throw e;
        }
    }

    template <typename... types>
    void mapToJson(std::map<std::string, std::tuple<types...>> map, const std::string& path) {
        nlohmann::json json;

        for(const auto& elem : map) {
            json[elem.first] = elem.second;
        }

        std::ofstream file(path);
        file << json;
    }

    //Various json helpers, based on the fist one here.
    template <typename Type>
    Type getValue(const std::string& filePath, const std::string& value) {
        try {
            return getValue<Type>(std::fstream(filePath), value);
        } catch(std::exception &e) {
            Logger::print(Level::ERROR, "JSON error: " + std::string(e.what()));
        }

        return Type();
    }

    template <typename Type>
    Type getValue(std::fstream filePath, const std::string& value) {
        try {
            return getValue<Type>(nlohmann::json::parse(filePath, nullptr, true, true), value);
        } catch(std::exception &e) {
            Logger::print(Level::ERROR, "JSON error: " + std::string(e.what()));
        }

        return Type();
    }

    template <typename Type>
    Type getValue(nlohmann::json file, const std::string& value) {
        try {
            return file[value].get<Type>();
        } catch(std::exception &e) {
            Logger::print(Level::ERROR, "JSON error: " + std::string(e.what()));
        }

        return Type();
    }
};


#endif //BUILD_JSON_H
