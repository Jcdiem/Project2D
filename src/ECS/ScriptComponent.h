#pragma once
#ifndef PROJECT2DTD_POSITIONCOMPONENT_H
#define PROJECT2DTD_POSITIONCOMPONENT_H

#include <string>
#include <fstream>
#include <streambuf>

#include "EntityComponentSystem.h"
#include "EntityWrapper.h"
#include "LuaEngine.h"

class ScriptComponent : public Component{
public:
     explicit ScriptComponent(const std::string& path) {
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
        self = EntityWrapper(entity);
        if(entity->getParent()) {
            parent = EntityWrapper(entity->getParent());
        }

        for(Entity* child : *entity->getChildren()) {
            children.emplace_back(child);
        }

        sol::usertype<EntityWrapper> entity_data =
                lua.gLu()->new_usertype<EntityWrapper>("entity", sol::no_constructor);

        //Data Variables
        entity_data["x"] = sol::property(&EntityWrapper::getX, &EntityWrapper::setX);
        entity_data["y"] = sol::property(&EntityWrapper::getY, &EntityWrapper::setY);
        entity_data["realX"] = sol::property(&EntityWrapper::getRealX);
        entity_data["realY"] = sol::property(&EntityWrapper::getRealY);
        entity_data["w"] = sol::property(&EntityWrapper::getW, &EntityWrapper::setW);
        entity_data["h"] = sol::property(&EntityWrapper::getH, &EntityWrapper::setH);
        entity_data["rot"] = sol::property(&EntityWrapper::getRot, &EntityWrapper::setRot);
        entity_data["rotX"] = sol::property(&EntityWrapper::getRotX, &EntityWrapper::setRotX);
        entity_data["rotY"] = sol::property(&EntityWrapper::getRotY, &EntityWrapper::setRotY);
        entity_data["vflip"] = sol::property(&EntityWrapper::getVFlip, &EntityWrapper::setVFlip);
        entity_data["hflip"] = sol::property(&EntityWrapper::getHFlip, &EntityWrapper::setHFlip);

        //Methods
        entity_data["resetRotPos"] = &EntityWrapper::resetRotPos;
        entity_data["playAnim"] = &EntityWrapper::playAnim;
        entity_data["addBinding"] = &EntityWrapper::addBinding;
        entity_data["isPressed"] = &EntityWrapper::isPressed;
        entity_data["refreshBindings"] = &EntityWrapper::refreshBindings;

        lua.newVar("EW", entity->getComponent<DataComponent>().windowWidth);
        lua.newVar("EH", entity->getComponent<DataComponent>().windowHeight);

        lua.newVar<EntityWrapper>("self", self);

        if(entity->getParent()) {
            lua.newVar<EntityWrapper>("parent", parent);
        }

        lua.newVar("children", children);

        lua.initScript(script);
    }

    void update() override {
        lua.runScript();
    }
private:
    EntityWrapper self;
    EntityWrapper parent;
    std::vector<EntityWrapper> children;

    std::string path;

    LuaEngine lua;
    std::string script;
};


#endif //PROJECT2DTD_POSITIONCOMPONENT_H
