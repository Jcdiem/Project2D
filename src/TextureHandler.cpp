#include "TextureHandler.h"

SDL_Texture* TextureHandler::loadTexture(const char *filename, SDL_Renderer *renderer) {
    SDL_Surface* tempSurface = IMG_Load(filename);
    SDL_Texture* retTex = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return retTex;
}