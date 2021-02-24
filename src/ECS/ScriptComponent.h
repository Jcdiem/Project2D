#ifndef PROJECT2DTD_POSITIONCOMPONENT_H
#define PROJECT2DTD_POSITIONCOMPONENT_H

#include <string>
#include <fstream>
#include <streambuf>

#include "EntityComponentSystem.h"
#include "LuaEngine.h"

class ScriptComponent : public Component{
public:
    ScriptComponent(Manager* manager, char* path);
    ScriptComponent(Manager* manager, char* path, int x, int y);

    void init() override;
    float x();
    float y();
    int getEW();
    int getEH();
    void setPos(float x, float y);
    void setX(float x);
    void setY(float y);
    void update() override;

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
