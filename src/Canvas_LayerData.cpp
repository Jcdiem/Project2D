//
// Created by jzorld on 15/01/2021.
//

#include "../include/Canvas_LayerData.h"

Canvas_LayerData::Canvas_LayerData(SDL_Texture* texture_ptr, int sizeX, int sizeY, int xOffset=0, int yOffset=0){

    srcRect.w = sizeX;
    srcRect.h = sizeY;

    srcRect.x = xOffset;
    srcRect.y = yOffset;

    SavedTexturePtr = texture_ptr;
}

Canvas_LayerData::~Canvas_LayerData(){
    //Delete the texture after it is done being used
    SDL_DestroyTexture(texture_ptr);
}

SDL_Rect Canvas_LayerData::getSrcRect() {
    return srcRect;
}

SDL_Texture* Canvas_LayerData::getTexturePtr() {
    return savedTexture;
}


