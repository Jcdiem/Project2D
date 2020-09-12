#include "EntityType.h"

int engineW;
int engineH;

//TODO: Separate out different entities with interface
int dvdSpeedX = 1;
int dvdSpeedY = 1;

EntityType::EntityType(const char* spriteSheet, int width, int height, int x, int y) {
    entTexture = TextureHandler::loadTexture(spriteSheet);
    spriteHeight = height;
    spriteWidth = width;
    xPos = x;
    yPos = y;
    engineW = Engine::getEngineWidth();
    engineH = Engine::getEngineHeight();
}

void EntityType::update() {
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

void EntityType::render() {
    SDL_RenderCopy(Engine::getRenderer(), entTexture, nullptr, &destRect);
}