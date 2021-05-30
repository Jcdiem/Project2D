#include "Canvas_LayerData.h"

namespace CanvasSystem {
    Canvas_LayerData::Canvas_LayerData(SDL_Texture* texture_ptr, int sizeX, int sizeY, int posX, int posY,
                                       int fillSizeX, int fillSizeY, bool ignoreOverlap, int offsetX, int offsetY){

        savedTexture = texture_ptr;

        //Is texture map
        if(fillSizeX > 0 && fillSizeY > 0){
            //Don't give this sizes, or it will change them to the image size (Breaks animation)
            //TODO: Create overload for simple textures that uses this method for info gathering
            //TODO: Add overlap check
            SDL_QueryTexture(texture_ptr, &pixelFormat, nullptr, nullptr, nullptr);
            textureMap = TextureHandler::loadBigTexture(pixelFormat, fillSizeX, fillSizeY);
        }


        srcRect.w = sizeX;
        srcRect.h = sizeY;
        destRect.w = sizeX;
        destRect.h = sizeY;

        srcRect.x = offsetX;
        srcRect.y = offsetY;

        destRect.x = posX;
        destRect.y = posY;
    }

    SDL_Texture *Canvas_LayerData::getTextureMap() const {
        return textureMap;
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

    Uint32 Canvas_LayerData::getPixelFormat() const {
        return pixelFormat;
    }

    Uint16 Canvas_LayerData::getFillW() const {
        return fillW;
    }

    Uint16 Canvas_LayerData::getFillH() const {
        return fillH;
    }
}