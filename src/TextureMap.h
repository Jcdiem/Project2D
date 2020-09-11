#ifndef PROJECT2DTD_TEXTUREMAP_H
#define PROJECT2DTD_TEXTUREMAP_H
#include "Engine.h"

class TextureMap {
public:
    TextureMap();
    ~TextureMap();

    void loadMap(int array[20][25]);
    void drawMap();


private:
    static const int textureMapRows = 20;
    static const int textureMapCols = 25;
    SDL_Rect src, dest;

    SDL_Texture* mapTextureName0;
    SDL_Texture* mapTextureName1;
    SDL_Texture* mapTextureName2;

    int textureMap[textureMapRows][textureMapCols];
};


#endif //PROJECT2DTD_TEXTUREMAP_H
