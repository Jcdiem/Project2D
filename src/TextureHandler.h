#ifndef PROJECT2DTD_TEXTUREHANDLER_H
#define PROJECT2DTD_TEXTUREHANDLER_H
#include "Engine.h"

class TextureHandler {
public:
    static SDL_Texture* loadTexture(const char* filename);
    static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);

};


#endif //PROJECT2DTD_TEXTUREHANDLER_H
