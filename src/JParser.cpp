#include <iostream>
#include "JParser.h"

std::vector<std::string> JParser::levelList;

const char *nullLevel = "assets/levels/null.json";
const char *nullObj = "assets/objects/null.json";

JParser::JParser(Manager *manager) {
    eManager = manager;
}

void JParser::genLevelList() {
    nlohmann::json file;
    try {
        file = nlohmann::json::parse(std::fstream("assets/levels/levelList.json"), nullptr, true, true)["levels"];
    }
    catch(nlohmann::json::exception &e) {
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

void JParser::genObjs(const char* levelPath) {
    nlohmann::json file;
    try {
        file = nlohmann::json::parse(std::fstream(levelPath), nullptr, true, true)["objects"];
    }
    catch(nlohmann::json::exception &e) {
        std::throw_with_nested(std::runtime_error("Level file could not be found or it was improperly formatted."));
    }

    for (auto obj = file.begin(); obj != file.end(); ++obj)
    {
        try{
            objFromJson(&std::string(obj.value())[0]);
        }
        catch(...) {
            std::cout << "Failed to create object from " << obj.value() << ", either object is malformed or does not exist." << std::endl;
            objFromJson(nullObj);
        }
    }
}

void JParser::objFromJson(const char* path) {
    auto &curObjPtr(eManager->addEntity());
    nlohmann::json file;

    try {
        file = nlohmann::json::parse(std::fstream(path), nullptr, true, true).front()["components"];
    }
    catch(nlohmann::json::exception &e) {
        std::throw_with_nested(std::runtime_error(std::string(path).append(" could not be found...")));
    }

    for (auto component = file.begin(); component != file.end(); ++component)
    {
        if(component.key() == "PositionComponent") {
            auto chaiP = component.value()["path"].get<std::string>();
            curObjPtr.addComponent<PositionComponent>(eManager, &chaiP[0]);
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

const char* JParser::getLevel(int levelNum) {
    return &levelList[levelNum][0];
}