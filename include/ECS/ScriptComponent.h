#ifndef PROJECT2DTD_POSITIONCOMPONENT_H
#define PROJECT2DTD_POSITIONCOMPONENT_H

#include <string>
#include <fstream>
#include <streambuf>

#include "EntityComponentSystem.h"
#include "LuaEngine.h"

class ScriptComponent : public Component{
public:
    ScriptComponent(Manager* manager, char* path){
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
    ScriptComponent(Manager* manager, char* path, int x, int y){
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

    void init() override{
        lua.gLu()->set_function("x", &ScriptComponent::x, this);
        lua.gLu()->set_function("y", &ScriptComponent::y, this);
        lua.gLu()->set_function("setX", &ScriptComponent::setX, this);
        lua.gLu()->set_function("setY", &ScriptComponent::setY, this);
        lua.gLu()->set_function("EW", &ScriptComponent::getEW, this);
        lua.gLu()->set_function("EH", &ScriptComponent::getEH, this);

        lua.initScript(script);
    }

    [[nodiscard]] int x() const {
        return xPos;
    }

    [[nodiscard]] int y() const{
        return yPos;
    }

    int getEW(){
        return engineW;
    }

    int getEH(){
        return engineH;
    }

    void setPos(int x, int y){
        xPos = x;
        yPos = y;
    }

    void setX(int x){
        xPos = x;
    }

    void setY(int y){
        yPos = y;
    }

    void update() override{
        lua.runScript();
    }

private:
    int xPos;
    int yPos;
    int engineW;
    int engineH;

    char* path;

    LuaEngine lua;
    Manager* manager;
    std::string script;
};


#endif //PROJECT2DTD_POSITIONCOMPONENT_H
