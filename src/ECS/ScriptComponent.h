#pragma once
#ifndef PROJECT2DTD_POSITIONCOMPONENT_H
#define PROJECT2DTD_POSITIONCOMPONENT_H

#include <string>
#include <fstream>
#include <streambuf>
#include <utility>

#include "EntityComponentSystem.h"
#include "EntityWrapper.h"
#include "LuaEngine.h"
#include "Components.h"

class ScriptComponent : public Component {
public:
    explicit ScriptComponent(const std::string &path) {
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
        entity_data["hidden"] = sol::property(&EntityWrapper::getHidden, &EntityWrapper::setHidden);

        //Methods
        entity_data["resetRotPos"] = &EntityWrapper::resetRotPos;
        entity_data["playAnim"] = &EntityWrapper::playAnim;
        entity_data["addBinding"] = &EntityWrapper::addBinding;
        entity_data["isPressed"] = &EntityWrapper::isPressed;
        entity_data["refreshBindings"] = &EntityWrapper::refreshBindings;
        entity_data["kill"] = &EntityWrapper::kill;
        entity_data["getParent"] = &EntityWrapper::getParent;
        entity_data["setParent"] = &EntityWrapper::setParent;
        entity_data["getChildren"] = &EntityWrapper::getChildren;
        entity_data["addChild"] = &EntityWrapper::addChild;

        lua.newVar("EW", self.getMan()->getWW());
        lua.newVar("EH", self.getMan()->getWH());

        lua.newVar<EntityWrapper>("self", self);

        if (entity->getParent()) {
            lua.newVar<EntityWrapper>("parent", self.getParent());
        }

        lua.newVar("children", self.getChildren());

        lua.gLu()->set_function("search", &ScriptComponent::search, this);

        lua.initScript(script);
    }

    void update() override {
        //Update family before running script
        if (entity->getParent()) {
            lua.newVar<EntityWrapper>("parent", self.getParent());
        }
        lua.newVar("children", self.getChildren());

        lua.runScript();
    }

    std::vector<EntityWrapper> search(std::string name) {
        std::vector<EntityWrapper> result;
        for(Entity* entity : self.getMan()->search(std::move(name))) {
            result.emplace_back(entity);
        }
        return result;
    }

private:
    EntityWrapper self;
    EntityWrapper parent;

    std::string path;

    LuaEngine lua;
    std::string script;
};


#endif //PROJECT2DTD_POSITIONCOMPONENT_H
