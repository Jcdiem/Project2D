#include "Sprite.h"

void Sprite::setX(int x) {
    spriteRect->x = x;
}

void Sprite::setXSpeed(int speed) {
    xSpeed = speed;
}

void Sprite::setY(int y) {
    spriteRect->y = y;
}

void Sprite::setYSpeed(int speed) {
    ySpeed = speed;
}

void Sprite::setH(int h) {
    spriteRect->h = h;
}

void Sprite::setW(int w) {
    spriteRect->w = w;
}

//Getters
const char * Sprite::getFile() {
    return filePath;
}

SDL_Rect* Sprite::getRect() {
    return spriteRect.get();
}

int Sprite::getX() {
    return spriteRect->x;
}

int Sprite::getXSpeed() {
    return xSpeed;
}

int Sprite::getY() {
    return spriteRect->y;
}

int Sprite::getYSpeed() {
    return ySpeed;
}

int Sprite::getH() {
    return spriteRect->h;
}

int Sprite::getW() {
    return spriteRect->w;
}