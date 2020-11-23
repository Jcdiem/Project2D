#ifndef PROJECT2DTD_POSITIONCOMPONENT_H
#define PROJECT2DTD_POSITIONCOMPONENT_H

#include <iostream>

#include "EntityComponentSystem.h"
#include "ChaiEngine.h"

class PositionComponent : public Component{
public:
    PositionComponent(Manager* manager, char* path){
        xPos = 0;
        yPos = 0;
        this->manager = manager;
        this->path = path;
        chai  = new ChaiEngine(manager, path);
    }
    PositionComponent(Manager* manager, char* path, int x, int y){
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
        tea->add(chaiscript::fun(&PositionComponent::setPos, this), "set_pos");
        tea->add(chaiscript::fun(&PositionComponent::setX, this), "set_x");
        tea->add(chaiscript::fun(&PositionComponent::setY, this), "set_y");
        tea->add(chaiscript::fun(&PositionComponent::x, this), "get_x");
        tea->add(chaiscript::fun(&PositionComponent::y, this), "get_y");
        tea->add(chaiscript::fun(&PositionComponent::getEH, this), "get_eh");
        tea->add(chaiscript::fun(&PositionComponent::getEW, this), "get_ew");
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
