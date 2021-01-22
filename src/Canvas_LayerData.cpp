#include "../include/Canvas_LayerData.h"

Canvas_LayerData::Canvas_LayerData(SDL_Texture* texture_ptr, int sizeX, int sizeY, int xOffset, int yOffset){

    srcRect.w = sizeX;
    srcRect.h = sizeY;

    srcRect.x = xOffset;
    srcRect.y = yOffset;

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


