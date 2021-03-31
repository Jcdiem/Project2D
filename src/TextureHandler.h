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
    static void Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest, double angle);
    static void Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest, double angle, SDL_RendererFlip flip);
    static void Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest, double angle, SDL_Point center, SDL_RendererFlip flip);

    //tilemaps
    static SDL_Texture *loadBigTexture(Uint32 pixelFormat, int width, int height);
    static void focusBigTexture(SDL_Texture* bigTexture);
    static void releaseRendererFocus();
private:
    static SDL_Renderer* renderer;
};


#endif //PROJECT2DTD_TEXTUREHANDLER_H
