#include "ObjectBuilder.h"

#include <utility>

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
        recurseChildren(man, obj, nullptr);
    }
}

Entity* ObjectBuilder::recurseChildren(Manager* man, auto root, Entity* parent) {
    try {
        auto entity = objFromJson(man, root.value()["self"], root.key(), parent);

        if(root->contains("children")) {
            for (auto child = root.value()["children"].begin(); child != root.value()["children"].end(); ++child) {
                try {
                    auto childEntity = recurseChildren(man, child, entity);
                    entity->addChild(childEntity);
                } catch(...) {
                    std::cout << "Failed to create child of object: " << root.key() << std::endl;
                }
            }
        }

        entity->init();

        return entity;
    }
    catch(...) {
        std::cout << "Failed to create object from " << root.value() << ", either object is malformed or does not exist." << std::endl;
    }

    return nullptr;
}

Entity* ObjectBuilder::objFromJson(Manager* man, std::string path, std::string name, Entity* parent) {
    auto& curObj = man->addEntity();

    curObj.setName(std::move(name));

    if(parent) {
        curObj.setParent(parent);
    }

    nlohmann::json file;

    try {
        file = nlohmann::json::parse(std::fstream(path), nullptr, true, true).front();
    }
    catch(nlohmann::json::exception &e) {
        std::throw_with_nested(std::runtime_error(path.append(" could not be found...")));
    }

    nlohmann::json components = file["components"];
    nlohmann::json values = file["values"];

    curObj.addComponent<EntityData>();
    EntityData* eData = &curObj.getComponent<EntityData>();

    eData->windowWidth = man->getWW();
    eData->windowHeight = man->getWH();

    for(auto kvPair = values.begin(); kvPair != values.end(); ++kvPair) {
        if(kvPair.key() == "x") {
            eData->x = kvPair.value().get<float>();
        }
        if(kvPair.key() == "y") {
            eData->y = kvPair.value().get<float>();
        }
        if(kvPair.key() == "rotX") {
            eData->rotX = kvPair.value().get<float>();
        }
        if(kvPair.key() == "rotY") {
            eData->rotY = kvPair.value().get<float>();
        }
        if(kvPair.key() == "rot") {
            eData->rot = kvPair.value().get<float>();
        }
        if(kvPair.key() == "vflip") {
            eData->vflip = kvPair.value().get<bool>();
        }
        if(kvPair.key() == "hflip") {
            eData->hflip = kvPair.value().get<bool>();
        }
    }

    for(auto component = components.begin(); component != components.end(); ++component)
    {
        if(component.key() == "ScriptComponent") {
            auto scriptPath = component.value()["path"].get<std::string>();
            curObj.addComponent<ScriptComponent>(&scriptPath[0]);
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
            curObj.addComponent<SpriteComponent>(animArray);
        }
    }

    return &curObj;
}