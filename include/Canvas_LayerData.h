#ifndef P2D_CANVAS_LAYERDATA_H
#define P2D_CANVAS_LAYERDATA_H
#include "TextureHandler.h"

class Canvas_LayerData {

//    TODO: add the ability for animated backgrounds
    Canvas_LayerData();
    ~Canvas_LayerData();

    SDL_Rect getSrcRect();
    SDL_Texture* getTexturePtr();

private:
    SDL_Rect srcRect;
    SDL_Texture* savedTexture;

};


#endif //P2D_CANVAS_LAYERDATA_H
