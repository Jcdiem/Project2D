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
        engineW = manager->getWW();
        engineH = manager->getWH();
    }
    ScriptComponent(Manager* manager, char* path, int x, int y){
        xPos = x;
        yPos = y;
        this->manager = manager;
        this->path = path;
        chai  = new ChaiEngine(manager, path);
        engineW = manager->getWW();
        engineH = manager->getWH();
    }

    void init() override{
        chaiscript::ChaiScript* tea = chai->brew();
        tea->add(chaiscript::fun(&ScriptComponent::setPos, this), "set_pos");
        tea->add(chaiscript::fun(&ScriptComponent::setX, this), "set_x");
        tea->add(chaiscript::fun(&ScriptComponent::setY, this), "set_y");
        tea->add(chaiscript::fun(&ScriptComponent::x, this), "get_x");
        tea->add(chaiscript::fun(&ScriptComponent::y, this), "get_y");
        tea->add(chaiscript::fun(&ScriptComponent::getEH, this), "get_eh");
        tea->add(chaiscript::fun(&ScriptComponent::getEW, this), "get_ew");
        tea->add(chaiscript::fun(&Manager::getEntityList, this->manager), "get_elist");
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
