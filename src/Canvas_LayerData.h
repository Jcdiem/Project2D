#pragma once
#ifndef P2D_CANVAS_LAYERDATA_H
#define P2D_CANVAS_LAYERDATA_H

#include "TextureHandler.h"

namespace CanvasSystem {
    class Canvas_LayerData {
    public:
        //    TODO: add the ability for animated backgrounds
        Canvas_LayerData(SDL_Texture *texture_ptr, int sizeX, int sizeY, int posX, int posY,
                         int fillSizeX = 0, int fillSizeY = 0, bool ignoreOverlap = false,
                         int xOffset = 0, int yOffset = 0);

        ~Canvas_LayerData();

        SDL_Rect getSrcRect();

        SDL_Texture *getTexturePtr();

        Uint32 getPixelFormat() const;

        /*Get the x position for screen placement
         * @return - The requested x-axis position of this element */
        int getPosX() const;

        /*Get the y position for screen placement
         * @return - The requested y-axis position of this element */
        int getPosY() const;

        const SDL_Rect &getDestRect() const;

        SDL_Texture *getTextureMap() const;

    private:
        SDL_Rect srcRect;
        SDL_Rect destRect;
    public:
        Uint16 getFillW() const;

        Uint16 getFillH() const;

    private:
        SDL_Texture *savedTexture;
        Uint32 pixelFormat;
        SDL_Texture *textureMap;
        //When screen size becomes 65K, we're done for
        Uint16 fillW;
        Uint16 fillH;
    };

}


#endif //P2D_CANVAS_LAYERDATA_H
