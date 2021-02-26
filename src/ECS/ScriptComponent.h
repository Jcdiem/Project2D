#ifndef PROJECT2DTD_POSITIONCOMPONENT_H
#define PROJECT2DTD_POSITIONCOMPONENT_H

#include <string>
#include <fstream>
#include <streambuf>

#include "EntityComponentSystem.h"
#include "LuaEngine.h"

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

        lua.initScript(script);
    }

    float getX() {
        return data->x;
    }

    float getY() {
        return data->y;
    }

    int getEW() {
        return engineW;
    }

    int getEH() {
        return engineH;
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

    void playAnim(int animId, int loops) {
        data->updAnim = true;
        data->animId = animId;
        data->loops = loops + 1;
    }

private:
    int engineW = 640;
    int engineH = 480;

    EntityData* data;

    char* path;

    LuaEngine lua;
    std::string script;
};


#endif //PROJECT2DTD_POSITIONCOMPONENT_H
