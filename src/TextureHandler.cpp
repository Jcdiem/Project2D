#include "../include/TextureHandler.h"
#include <cstdio>

SDL_Renderer* TextureHandler::renderer = nullptr;

SDL_Texture* TextureHandler::loadTexture(const char *filename) {
    SDL_Surface* tempSurface = IMG_Load(filename);

    //Detect error in image loading.
    if(!tempSurface) {
        printf("IMG_Load: %s\n", IMG_GetError());
        printf("Loading fallback image...\n");
        tempSurface = IMG_Load("assets/textures/null.png");
    }

    SDL_Texture* retTex = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return retTex;
}

void TextureHandler::Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(renderer, texture, &src, &dest);
}

void TextureHandler::setRenderer(SDL_Renderer *ren) {
    renderer = ren;
}
