#include <iostream>
#include "../include/JParser.h"

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
        if(component.key() == "ScriptComponent") {
            auto chaiP = component.value()["path"].get<std::string>();
            int x = component.value()["X"].get<int>();
            int y = component.value()["Y"].get<int>();
            curObjPtr.addComponent<ScriptComponent>(eManager, &chaiP[0], x, y);
        }
        if(component.key() == "SpriteComponent") {
            std::vector<animToolkit::animation*> animArray;
            for(auto anim = component->begin(); anim != component->end(); anim++) {
                auto* curAnim = new animToolkit::animation;
                animToolkit::addByPath(curAnim, &anim.value()["path"].get<std::string>()[0]);
                curAnim->width = anim.value()["width"].get<int>();
                curAnim->height = anim.value()["height"].get<int>();
                curAnim->frames = anim.value()["frames"].get<int>();
                curAnim->framerate = anim.value()["framerate"].get<int>();
                animArray.emplace_back(curAnim);
            }
            curObjPtr.addComponent<SpriteComponent>(animArray);
        }
    }
}

const char* JParser::getLevel(int levelNum) {
    return &levelList[levelNum][0];
}

std::string JParser::getTitle() {
    nlohmann::json file = nlohmann::json::parse(std::fstream("assets/engineSettings.json"), nullptr, true, true);
    return file["Title"].get<std::string>();
}

int JParser::getXSize() {
    nlohmann::json file = nlohmann::json::parse(std::fstream("assets/engineSettings.json"), nullptr, true, true);
    return file["WindowXRes"].get<int>();
}

int JParser::getYSize() {
    nlohmann::json file = nlohmann::json::parse(std::fstream("assets/engineSettings.json"), nullptr, true, true);
    return file["WindowYRes"].get<int>();
}

bool JParser::getFullscreen() {
    nlohmann::json file = nlohmann::json::parse(std::fstream("assets/engineSettings.json"), nullptr, true, true);
    return file["Fullscreen"].get<bool>();
}

bool JParser::getResizable() {
    nlohmann::json file = nlohmann::json::parse(std::fstream("assets/engineSettings.json"), nullptr, true, true);
    return file["ForceResizable"].get<bool>();
}