#ifndef PROJECT2DTD_TEXTUREHANDLER_H
#define PROJECT2DTD_TEXTUREHANDLER_H
#include "Engine.h"

class TextureHandler {
public:
    static SDL_Texture* loadTexture(const char* filename, SDL_Renderer* renderer);


};


#endif //PROJECT2DTD_TEXTUREHANDLER_H
