#ifndef PROJECT2DTD_POSITIONCOMPONENT_H
#define PROJECT2DTD_POSITIONCOMPONENT_H

#include <iostream>

#include "EntityComponentSystem.h"
#include "ChaiEngine.h"

class ScriptComponent : public Component{
public:
    ScriptComponent(Manager* manager, char* path){
        xPos = 0;
        yPos = 0;
        this->manager = manager;
        this->path = path;
        chai  = new ChaiEngine(manager, path);
    }
    ScriptComponent(Manager* manager, char* path, int x, int y){
        xPos = x;
        yPos = y;
        this->manager = manager;
        this->path = path;
        chai  = new ChaiEngine(manager, path);
    }


    int x() {
        return xPos;
    }

    int y(){
        return yPos;
    }

    int getEW(){
        return engineW;
    }

    int getEH(){
        return engineH;
    }


    void init() override{
        xPos = rand() % 800; //just for multi cd demo
        yPos = rand() % 640;
        engineH = 640;
        engineW = 800;
        chaiscript::ChaiScript* tea = chai->brew();
        tea->add(chaiscript::fun(&ScriptComponent::setPos, this), "set_pos");
        tea->add(chaiscript::fun(&ScriptComponent::setX, this), "set_x");
        tea->add(chaiscript::fun(&ScriptComponent::setY, this), "set_y");
        tea->add(chaiscript::fun(&ScriptComponent::x, this), "get_x");
        tea->add(chaiscript::fun(&ScriptComponent::y, this), "get_y");
        tea->add(chaiscript::fun(&ScriptComponent::getEH, this), "get_eh");
        tea->add(chaiscript::fun(&ScriptComponent::getEW, this), "get_ew");
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
        chai->run();
    }

private:
    int xPos;
    int yPos;
    int engineW;
    int engineH;

    Manager* manager;
    ChaiEngine* chai;
    std::string path;
};


#endif //PROJECT2DTD_POSITIONCOMPONENT_H
