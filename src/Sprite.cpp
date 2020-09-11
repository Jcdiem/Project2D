#include "Sprite.h"

void Sprite::setX(int x) {
    spriteRect->x = x;
}

void Sprite::setY(int y) {
    spriteRect->y = y;
}

void Sprite::setH(int h) {
    spriteRect->h = h;
}

void Sprite::setW(int w) {
    spriteRect->w = w;
}

//Getters
SDL_Texture* Sprite::getTex(){
    return Sprite::spriteTex;
}

SDL_Rect* Sprite::getRect() {
    return spriteRect.get();
}

int Sprite::getX() {
    return spriteRect->x;
}

int Sprite::getY() {
    return spriteRect->y;
}

int Sprite::getH() {
    return spriteRect->h;
}

int Sprite::getW() {
    return spriteRect->w;
}