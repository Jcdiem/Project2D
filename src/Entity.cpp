#include "Entity.h"

int engineW = 800;
int engineH = 640;//TODO: take in screen size somehow

//TODO: Separate out different entities with interface
int dvdSpeedX = 1;
int dvdSpeedY = 1;

Entity::Entity(const char* spriteSheet, int width, int height, int x, int y, Engine engine) {
    entTexture = TextureHandler::loadTexture(spriteSheet);
    spriteHeight = height;
    spriteWidth = width;
    xPos = x;
    yPos = y;
}

void Entity::init(){
}

void Entity::update() {
    srcRect.h = spriteHeight;
    srcRect.w = spriteWidth;

    //Has hit right side
    if(xPos >= (engineW - spriteWidth)){
        dvdSpeedX = -1;
    }
        //Has hit left side
    else if(xPos <= 0){
        dvdSpeedX = 1;
    }
        //has hit the bottom
    else if(yPos >= (engineH - spriteHeight)){
        dvdSpeedY = -1;
    }
        //Has hit the top
    else if(yPos <= 0){
        dvdSpeedY = 1;
    }
//    std::cout << "dvdx is " << xPos << std::endl;
    //Checking for corner spasm
    if(yPos >= (engineH - spriteHeight) || yPos <= 0){
        if(xPos >= (engineW - spriteWidth) || xPos <= 0){
            std::cout << "Yes, that was actually the corner" << std::endl;
        }
    }
    xPos = (dvdSpeedX + xPos);
    yPos = (dvdSpeedY + yPos);


    //This should stay the same without specifics
    destRect.x = xPos;
    destRect.y = yPos;
    destRect.w = spriteWidth;
    destRect.h = spriteHeight;
}
void Entity::render() {
    SDL_RenderCopy(Engine::renderer, entTexture, nullptr, &destRect);
}