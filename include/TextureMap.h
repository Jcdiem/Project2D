#ifndef PROJECT2DTD_TEXTUREMAP_H
#define PROJECT2DTD_TEXTUREMAP_H

#include <vector>
#include "SDL2/SDL.h"

class TextureMap {
public:
    TextureMap();
    ~TextureMap();

    void loadMap(int inArray[20][25]);
    int getMap()[20][25];
    const char* getTexturePath(int textureID);
    void populateTexturePath(std::vector<const char*> fileNames);


private:
    static const int textureMapRows = 20;
    static const int textureMapCols = 25;
    SDL_Rect src, dest;

    SDL_Texture* mapTextureName0;
    SDL_Texture* mapTextureName1;
    SDL_Texture* mapTextureName2;

    int textureMap[textureMapRows][textureMapCols];

    std::vector<const char*> texturePaths;
};


#endif //PROJECT2DTD_TEXTUREMAP_H
