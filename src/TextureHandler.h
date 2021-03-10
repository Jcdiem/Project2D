#pragma once
#ifndef PROJECT2DTD_TEXTUREHANDLER_H
#define PROJECT2DTD_TEXTUREHANDLER_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class TextureHandler {
public:
    static void setRenderer(SDL_Renderer* ren);
    static SDL_Texture* loadTexture(const char* filename);
    static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
private:
    static SDL_Renderer* renderer;
};


#endif //PROJECT2DTD_TEXTUREHANDLER_H
