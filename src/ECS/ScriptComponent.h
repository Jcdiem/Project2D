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

    void init() {
        data = &entity->getComponent<EntityData>();

        lua.gLu()->set_function("x", &ScriptComponent::getX, this);
        lua.gLu()->set_function("y", &ScriptComponent::getY, this);
        lua.gLu()->set_function("setX", &ScriptComponent::setX, this);
        lua.gLu()->set_function("setY", &ScriptComponent::setY, this);
        lua.gLu()->set_function("EW", &ScriptComponent::getEW, this);
        lua.gLu()->set_function("EH", &ScriptComponent::getEH, this);
        lua.gLu()->set_function("playAnim", &ScriptComponent::playAnim, this);
        lua.gLu()->set_function("addBinding", &InputManager::addBinding, inputManager);
        lua.gLu()->set_function("refreshBindings", &InputManager::refreshBindings, inputManager);
        lua.gLu()->set_function("isPressed", &InputManager::isPressed, inputManager);

        lua.initScript(script);

        inputManager->refreshBindings();
    }

    float getX() {
        return data->x;
    }

    float getY() {
        return data->y;
    }

    int getEW() {
        return data->windowWidth;
    }

    int getEH() {
        return data->windowHeight;
    }

    void setPos(float x, float y) {
        data->x = x;
        data->y = y;
    }

    void setX(float x) {
        data->x = x;
    }

    void setY(float y) {
        data->y = y;
    }

    void update() {
        lua.runScript();
    }

    void playAnim(int animId, int ms) {
        entity->getComponent<SpriteComponent>().playAnim(animId, ms);
    }

private:
    EntityData* data;
    InputManager* inputManager = new InputManager();

    char* path;

    LuaEngine lua;
    std::string script;
};


#endif //PROJECT2DTD_POSITIONCOMPONENT_H
