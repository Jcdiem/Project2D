#ifndef PROJECT2DTD_POSITIONCOMPONENT_H
#define PROJECT2DTD_POSITIONCOMPONENT_H

#include <iostream>
#include "EntityComponentSystem.h"

class PositionComponent : public Component{
public:
    PositionComponent(){
        xPos = 0;
        yPos = 0;
    }
    PositionComponent(int x, int y){
        xPos = x;
        yPos = y;
    }


    int x() {
        return xPos;
    }
    int y(){
        return yPos;
    }
    void init() override{
        xPos = rand() % 800; //just for multi cd demo
        yPos = rand() % 640;
        dvdSpeedX = 1;
        dvdSpeedY = 1;
        engineH = 640;
        engineW = 800;
    }

    void setPos(int x, int y){
        xPos = x;
        yPos = y;
    }

    //TODO: Remove reference to just DVD Logic
    void update() override{
        //Has hit right side
        if(xPos >= (engineW - 200)){
            dvdSpeedX = -1;
        }
            //Has hit left side
        else if(xPos <= 0){
            dvdSpeedX = 1;
        }
            //has hit the bottom
        else if(yPos >= (engineH - 80)){
            dvdSpeedY = -1;
        }
            //Has hit the top
        else if(yPos <= 0){
            dvdSpeedY = 1;
        }

        //Checking for corner spasm
        if(yPos >= (engineH - 80) || yPos <= 0){
            if(xPos >= (engineW - 200) || xPos <= 0){
                std::cout << "Yes, that was actually the corner" << std::endl;
            }
        }
        xPos = (dvdSpeedX + xPos);
        yPos = (dvdSpeedY + yPos);
    }

private:
    int xPos;
    int yPos;
    int dvdSpeedX;
    int dvdSpeedY;
    int engineW;
    int engineH;
};


#endif //PROJECT2DTD_POSITIONCOMPONENT_H
