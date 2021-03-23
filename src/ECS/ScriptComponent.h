#pragma once
#ifndef PROJECT2DTD_POSITIONCOMPONENT_H
#define PROJECT2DTD_POSITIONCOMPONENT_H

#include <string>
#include <fstream>
#include <streambuf>

#include "EntityComponentSystem.h"
#include "LuaEngine.h"
#include "InputManager.h"

class ScriptComponent : public Component{
public:
    ScriptComponent(char* path) {
        this->path = path;

        std::ifstream t(path);

        //Finding the end of file
        t.seekg(0, std::ios::end);
        script.reserve(t.tellg());
        t.seekg(0, std::ios::beg);
        //Finding the end of file

        script.assign((std::istreambuf_iterator<char>(t)),
                      std::istreambuf_iterator<char>());
    }

    void init() override {
        data = &entity->getComponent<EntityData>();

        sol::usertype<EntityData> entity_data =
                lua.gLu()->new_usertype<EntityData>("data", sol::no_constructor);

        entity_data["EW"] = &EntityData::windowWidth;
        entity_data["EH"] = &EntityData::windowHeight;
        entity_data["x"] = &EntityData::x;
        entity_data["y"] = &EntityData::y;
        entity_data["realX"] = sol::readonly(&EntityData::realX);
        entity_data["realY"] = sol::readonly(&EntityData::realY);
        entity_data["w"] = &EntityData::w;
        entity_data["h"] = &EntityData::h;
        entity_data["rot"] = &EntityData::rot;
        entity_data["rotX"] = &EntityData::rotX;
        entity_data["rotY"] = &EntityData::rotY;
        entity_data["vflip"] = &EntityData::vflip;
        entity_data["hflip"] = &EntityData::hflip;

        lua.newVar<EntityData*>("self", data);

        Entity* parent = this->entity->getParent();
        if(parent) {
            EntityData* parentData = &parent->getComponent<EntityData>();
            if(parentData) {
                lua.newVar<EntityData*>("parent", parentData);
            }
        }

        //Get children
        lua.newVar("children", entity->getChildren());

        lua.gLu()->set_function("playAnim", &ScriptComponent::playAnim, this);
        lua.gLu()->set_function("resetRotPos", &ScriptComponent::resetRotPos, this);
        lua.gLu()->set_function("addBinding", &InputManager::addBinding, inputManager);
        lua.gLu()->set_function("refreshBindings", &InputManager::refreshBindings, inputManager);
        lua.gLu()->set_function("isPressed", &InputManager::isPressed, inputManager);

        lua.initScript(script);

        inputManager->refreshBindings();
    }

    void update() override {
        lua.runScript();
    }

    void playAnim(int animId, int ms) {
        try {
            entity->getComponent<SpriteComponent>().playAnim(animId, ms);
        } catch(...) {}
    }

    void resetRotPos() {
        try {
            data->rotX = data->w / 2.0;
            data->rotY = data->h / 2.0;
        } catch(...) {}
    }
private:
    EntityData* data;
    InputManager* inputManager = new InputManager();

    char* path;

    LuaEngine lua;
    std::string script;
};


#endif //PROJECT2DTD_POSITIONCOMPONENT_H
