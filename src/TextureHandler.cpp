#include "TextureHandler.h"

SDL_Texture* TextureHandler::loadTexture(const char *filename) {
    SDL_Surface* tempSurface = IMG_Load(filename);
    SDL_Texture* retTex = SDL_CreateTextureFromSurface(Engine::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return retTex;
}

void TextureHandler::Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(Engine::renderer, texture, &src, &dest);
}
