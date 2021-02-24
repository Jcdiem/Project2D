#ifndef PROJECT2DTD_POSITIONCOMPONENT_H
#define PROJECT2DTD_POSITIONCOMPONENT_H

#include <string>
#include <fstream>
#include <streambuf>

#include "EntityComponentSystem.h"
#include "LuaEngine.h"

class ScriptComponent : public Component{
public:
    ScriptComponent(Manager* manager, char* path) {
        xPos = 0;
        yPos = 0;
        this->path = path;
        this->manager = manager;
        engineW = manager->getWW();
        engineH = manager->getWH();

        std::ifstream t(path);

        //Finding the end of file
        t.seekg(0, std::ios::end);
        script.reserve(t.tellg());
        t.seekg(0, std::ios::beg);
        //Finding the end of file

        script.assign((std::istreambuf_iterator<char>(t)),
                      std::istreambuf_iterator<char>());
    }

    ScriptComponent(Manager* manager, char* path, int x, int y) {
        xPos = x;
        yPos = y;
        this->path = path;
        this->manager = manager;
        engineW = manager->getWW();
        engineH = manager->getWH();

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
        lua.gLu()->set_function("x", &ScriptComponent::x, this);
        lua.gLu()->set_function("y", &ScriptComponent::y, this);
        lua.gLu()->set_function("setX", &ScriptComponent::setX, this);
        lua.gLu()->set_function("setY", &ScriptComponent::setY, this);
        lua.gLu()->set_function("EW", &ScriptComponent::getEW, this);
        lua.gLu()->set_function("EH", &ScriptComponent::getEH, this);

        lua.initScript(script);
    }

    float x() {
        return xPos;
    }

    float y() {
        return yPos;
    }

    int getEW() {
        return engineW;
    }

    int getEH() {
        return engineH;
    }

    void setPos(float x, float y) {
        xPos = x;
        yPos = y;
    }

    void setX(float x) {
        xPos = x;
    }

    void setY(float y) {
        yPos = y;
    }

    void update() {
        lua.runScript();
    }

private:
    float xPos;
    float yPos;
    int engineW;
    int engineH;

    char* path;

    LuaEngine lua;
    Manager* manager;
    std::string script;
};


#endif //PROJECT2DTD_POSITIONCOMPONENT_H
