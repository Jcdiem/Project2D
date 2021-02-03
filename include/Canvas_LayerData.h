#ifndef P2D_CANVAS_LAYERDATA_H
#define P2D_CANVAS_LAYERDATA_H
#include "TextureHandler.h"

class Canvas_LayerData {
public:
//    TODO: add the ability for animated backgrounds
    //TODO: Fix constructor default values not working
    Canvas_LayerData(SDL_Texture* texture_ptr, int sizeX, int sizeY, int xOffset=0, int yOffset=0);
    ~Canvas_LayerData();

    SDL_Rect getSrcRect();
    SDL_Texture* getTexturePtr();

private:
    SDL_Rect srcRect;
    SDL_Texture* savedTexture;
};


#endif //P2D_CANVAS_LAYERDATA_H
