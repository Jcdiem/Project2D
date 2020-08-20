#include "Physics.h"
#include <iostream>

void Physics::applyForce(int power, int direction, Sprite sprite) {
    int quad;
    int xForce;
    int yForce;
    
    direction %= 360;
    
    quad = 0;
    if(direction > 90) {
        quad = 1;
        direction %= 90;
    }
    if(direction > 180) {
        quad = 2;
        direction %= 90;
    }
    if(direction > 270) {
        quad = 3;
        direction %= 90;
    }
    
    xForce = power * sin(direction);
    yForce = power * cos(direction);
    
    switch(quad){
        case(0):
            break;
            
        case(1):
            yForce = -yForce;
            break;
        case(2):
            xForce = -xForce;
            yForce = -yForce;
            break;
            
        case(3):
            xForce = -xForce;
            break;
            
        default:
            break;
    }
    
    sprite.setXSpeed(xForce);
    std::cout << sprite.getXSpeed() << std::endl;
    sprite.setYSpeed(yForce);
}

void Physics::spriteTick(Sprite sprite) {
    std::cout << sprite.getXSpeed() << std::endl;
    sprite.setX(sprite.getX() + sprite.getXSpeed());
    sprite.setY(sprite.getY() + sprite.getYSpeed());
}