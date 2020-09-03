#include "Entity.h"

int engineW = 800;
int engineH = 600;//TODO: take in screen size somehow

//TODO: Separate out different entities with interface
int dvdSpeedX = 1;
int dvdSpeedY = 1;

Entity::Entity(const char* spriteSheet, SDL_Renderer* renderer, int height, int width, int x, int y) {
    Entity::renderer = renderer;
    Entity::entTexture = TextureHandler::loadTexture(spriteSheet, renderer);
    Entity::spriteHeight = height;
    Entity::spriteWidth = width;
    Entity::xPos = x;
    Entity::yPos = y;
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
    else if(xPos >= (engineH - spriteHeight)){
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
void Entity::render() {
    SDL_RenderCopy(renderer, entTexture, &srcRect, &destRect);
}