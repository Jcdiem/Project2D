#include "Canvas_LayerData.h"

Canvas_LayerData::Canvas_LayerData(SDL_Texture* texture_ptr, int sizeX, int sizeY, int posX, int posY, int xOffset, int yOffset){

    srcRect.w = sizeX;
    srcRect.h = sizeY;
    destRect.w = sizeX;
    destRect.h = sizeY;

    srcRect.x = xOffset;
    srcRect.y = yOffset;

    destRect.x = 10;
    destRect.y = 20;

    savedTexture = texture_ptr;
}

Canvas_LayerData::~Canvas_LayerData(){
    //Delete the texture after it is done being used
    SDL_DestroyTexture(savedTexture);
}

SDL_Rect Canvas_LayerData::getSrcRect() {
    return srcRect;
}

SDL_Texture* Canvas_LayerData::getTexturePtr() {
    return savedTexture;
}


const SDL_Rect &Canvas_LayerData::getDestRect() const {
    return destRect;
}
