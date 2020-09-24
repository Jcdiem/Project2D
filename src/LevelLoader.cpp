#include <iostream>
#include "LevelLoader.h"

using json = nlohmann::json;

std::vector<std::string> LevelLoader::levelList;

const char *nullLevel = "assets/levels/null.json";
const char *nullObj = "assets/objects/null.json";

LevelLoader::LevelLoader(Manager *manager) {
    eManager = manager;
}

void LevelLoader::genLevelList() {
    json file;
    try {
        file = json::parse(std::fstream("assets/levels/levelList.json"), nullptr, true, true)["levels"];
    }
    catch(json::exception &e) {
        std::throw_with_nested(std::runtime_error("Level list could not be found or it was improperly formatted."));
    }

    for (auto level = file.begin(); level != file.end(); ++level)
    {
        try{
            levelList.emplace_back(std::string(level.value()));
        }
        catch(...) {
            std::cout << "Failed to get object path, does it exist?" << std::endl;
            levelList.emplace_back(std::string(nullLevel));
        }
    }
}

void LevelLoader::genObjs(const char* levelPath) {
    json file;
    try {
        file = json::parse(std::fstream(levelPath), nullptr, true, true)["objects"];
    }
    catch(json::exception &e) {
        std::throw_with_nested(std::runtime_error("Level file could not be found or it was improperly formatted."));
    }

    for (auto obj = file.begin(); obj != file.end(); ++obj)
    {

        objFromJson(&std::string(obj.value())[0]);
        try{
        }
        catch(...) {
            std::cout << "Failed to get object path, does it exist?" << std::endl;
            objFromJson(nullObj);
        }
    }
}

void LevelLoader::objFromJson(const char* path) {
    auto &curObjPtr(eManager->addEntity());
    json file;

    try {
        file = json::parse(std::fstream(path), nullptr, true, true).front()["components"];
    }
    catch(json::exception &e) {
        std::throw_with_nested(std::runtime_error(std::string(path).append(" could not be found...")));
    }

    for (auto component = file.begin(); component != file.end(); ++component)
    {
        if(component.key() == "PositionComponent") {
            curObjPtr.addComponent<PositionComponent>();
        }
        if(component.key() == "SpriteComponent") {
            auto sprP = component.value()["path"].get<std::string>();
            int sprW = component.value()["width"];
            int sprH = component.value()["height"].get<int>();
            int sprF = component.value()["frames"].get<int>();
            curObjPtr.addComponent<SpriteComponent>(&sprP[0], sprW, sprH, sprF);
        }
    }
}

const char* LevelLoader::getLevel(int levelNum) {
    return &levelList[levelNum][0];
}