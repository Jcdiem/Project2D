#ifndef PROJECT2DTD_ENTITY_H
#define PROJECT2DTD_ENTITY_H
#include "Engine.h"
#include "TextureHandler.h"

class Entity {
public:
    Entity(const char* spriteSheet, SDL_Renderer* renderer, int height, int width, int x, int y);
    ~Entity();

    void init();
    void update();
    void render();

private:
    int xPos;
    int yPos;

    //For use in next phase of sheet (current size + next)
    int spriteHeight;
    int spriteWidth;

    SDL_Texture* entTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;

};


#endif //PROJECT2DTD_ENTITY_H
