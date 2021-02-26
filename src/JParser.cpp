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
        file = nlohmann::json::parse(std::fstream(path), nullptr, true, true).front();
    }
    catch(nlohmann::json::exception &e) {
        std::throw_with_nested(std::runtime_error(std::string(path).append(" could not be found...")));
    }

    nlohmann::json components = file["components"];
    nlohmann::json values = file["values"];

    curObjPtr.addComponent<EntityData>();
    EntityData* eData = &curObjPtr.getComponent<EntityData>();

    for(auto kvPair = values.begin(); kvPair != values.end(); ++kvPair) {
        if(kvPair.key() == "x") {
            eData->x = kvPair.value().get<float>();
        }
        if(kvPair.key() == "y") {
            eData->y = kvPair.value().get<float>();
        }
    }

    for(auto component = components.begin(); component != components.end(); ++component)
    {
        if(component.key() == "ScriptComponent") {
            auto scriptPath = component.value()["path"].get<std::string>();
            curObjPtr.addComponent<ScriptComponent>(&scriptPath[0]);
        }
        if(component.key() == "SpriteComponent") {
            std::vector<animToolkit::animation*> animArray;
            for(auto anim = component->begin(); anim != component->end(); anim++) {
                auto* curAnim = new animToolkit::animation;

                //Req'd properties
                curAnim->addByPath(&anim.value()["path"].get<std::string>()[0]);
                curAnim->width = anim.value()["width"].get<int>();
                curAnim->height = anim.value()["height"].get<int>();


                //Optional properties
                if(anim.value().contains("frames")) {
                    curAnim->frames = anim.value()["frames"].get<int>();
                } else {
                    curAnim->frames = 1;
                }
                if(anim.value().contains("framerate")) {
                    curAnim->framerate = anim.value()["framerate"].get<int>();
                } else {
                    curAnim->framerate = 1;
                }
                if(anim.value().contains("dwidth")) {
                    curAnim->dwidth = anim.value()["dwidth"].get<int>();
                } else {
                    curAnim->dwidth = curAnim->width;
                }
                if(anim.value().contains("dheight")) {
                    curAnim->dheight = anim.value()["dheight"].get<int>();
                } else {
                    curAnim->dheight = curAnim->height;
                }

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

int JParser::getTPS() {
    nlohmann::json file = nlohmann::json::parse(std::fstream("assets/engineSettings.json"), nullptr, true, true);
    return file["Tickrate"].get<int>();
}

int JParser::getFPS() {
    nlohmann::json file = nlohmann::json::parse(std::fstream("assets/engineSettings.json"), nullptr, true, true);
    return file["Framerate"].get<int>();
}