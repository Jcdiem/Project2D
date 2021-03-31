#pragma once
#ifndef P2D_CANVAS_LAYERDATA_H
#define P2D_CANVAS_LAYERDATA_H
#include "TextureHandler.h"

class Canvas_LayerData {
public:
//    TODO: add the ability for animated backgrounds
    //TODO: Fix constructor default values not working
    Canvas_LayerData(SDL_Texture* texture_ptr, int sizeX, int sizeY, int posX, int posY, int xOffset=0, int yOffset=0);
    ~Canvas_LayerData();

    SDL_Rect getSrcRect();
    SDL_Texture* getTexturePtr();

    /*Get the x position for screen placement
     * @return - The requested x-axis position of this element */
    int getPosX() const;

    /*Get the y position for screen placement
     * @return - The requested y-axis position of this element */
    int getPosY() const;

    const SDL_Rect &getDestRect() const;

private:
    SDL_Rect srcRect;
    SDL_Rect destRect;
    SDL_Texture* savedTexture;
};


#endif //P2D_CANVAS_LAYERDATA_H
