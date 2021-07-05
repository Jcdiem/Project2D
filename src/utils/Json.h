#pragma once
#ifndef BUILD_JSON_H
#define BUILD_JSON_H

#include <nlohmann/json.hpp>
#include <fstream>

#include "Flagger.h"
#include "Logger.h"

namespace Json {
    void initDefaultFlags(std::string filePath);

    //Various json helpers, based on the fist one here.
    template <typename Type>
    Type getValue(const std::string& filePath, const std::string& value) {
        try {
            nlohmann::json file = nlohmann::json::parse(std::fstream(filePath), nullptr, true, true);
            return file[value].get<Type>();
        } catch(std::exception &e) {
            Logger::print(Level::ERROR, "JSON error: " + std::string(e.what()));
        }
    }

    template <typename Type>
    Type getValue(std::fstream filePath, const std::string& value) {
        try {
            nlohmann::json file = nlohmann::json::parse(filePath, nullptr, true, true);
            return file[value].get<Type>();
        } catch(std::exception &e) {
            Logger::print(Level::ERROR, "JSON error: " + std::string(e.what()));
        }
    }

    template <typename Type>
    Type getValue(nlohmann::json file, const std::string& value) {
        try {
            return file[value].get<Type>();
        } catch(std::exception &e) {
            Logger::print(Level::ERROR, "JSON error: " + std::string(e.what()));
        }
    }
};


#endif //BUILD_JSON_H
