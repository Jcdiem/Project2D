#include "ObjectBuilder.h"

const char *nullLevel = "assets/levels/null.json";
const char *nullObj = "assets/objects/null.json";

std::vector<std::string> ObjectBuilder::genLevelList() {
    std::vector<std::string> levelList;
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

    return levelList;
}

void ObjectBuilder::genObjs(Manager* man, std::string levelPath) {
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
            objFromJson(man, &std::string(obj.value())[0]);
        }
        catch(...) {
            std::cout << "Failed to create object from " << obj.value() << ", either object is malformed or does not exist." << std::endl;
            objFromJson(man, nullObj);
        }
    }
}

void ObjectBuilder::objFromJson(Manager* man, const char* path) {
    auto &curObjPtr(man->addEntity());
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

    eData->windowWidth = man->getWW();
    eData->windowHeight = man->getWH();

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