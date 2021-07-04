#pragma once
#ifndef PROJECT2DTD_LEVELLOADER_H
#define PROJECT2DTD_LEVELLOADER_H
#include <vector>
#include <string>
#include <fstream>
#include "../libs/json/include/nlohmann/json.hpp"

//#include "ECS/Components.h"
//#include "ECS/AnimStruct.h"

namespace ObjectBuilder {
    //Used to generate objects and levels
    std::vector<std::string> genLevelList();
//    void genObjs(Manager* man, std::string levelPath);
//    void genCanvas(Manager *man, std::string levelPath);
//    Entity* recurseChildren(Manager* man, auto root, Entity* parent);
//    Entity* objFromJson(Manager* man, std::string path, std::string name, Entity* parent);

    template<typename T>
    T getValue(const std::string& filePath, const std::string& value) {
        nlohmann::json file = nlohmann::json::parse(std::fstream(filePath), nullptr, true, true);
        return file[value].get<T>();
    }
}

#endif //PROJECT2DTD_LEVELLOADER_H
