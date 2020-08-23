#include "Sprite.h"

void Sprite::setX(int x) {
    Sprite::spriteRect->x = x;
}

void Sprite::setY(int y) {
    Sprite::spriteRect->y = y;
}

void Sprite::setH(int h) {
    Sprite::spriteRect->h = h;
}

void Sprite::setW(int w) {
    Sprite::spriteRect->w = w;
}

//Getters
const char * Sprite::getFile() {
    return Sprite::filePath;
}

SDL_Rect* Sprite::getRect() {
    return Sprite::spriteRect.get();
}

int Sprite::getX() {
    return Sprite::spriteRect->x;
}

int Sprite::getY() {
    return Sprite::spriteRect->y;
}

int Sprite::getH() {
    return Sprite::spriteRect->h;
}

int Sprite::getW() {
    return Sprite::spriteRect->w;
}