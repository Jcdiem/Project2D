#ifndef PROJECT2DTD_SPRITE_H
#define PROJECT2DTD_SPRITE_H
#include "Engine.h"
#include <memory>
#include <iostream>


class Sprite {
public:
    Sprite(int width, int height, SDL_Texture* texture){
        Sprite::spriteRect->h = height;
        Sprite::spriteRect->w = width;
        Sprite::spriteRect->x = 0;
        Sprite::spriteRect->y = 0;
        Sprite::spriteTex = texture;
    }

    void setX(int x);
    void setXSpeed(int speed);
    void setY(int y);
    void setYSpeed(int speed);
    void setH(int h);
    void setW(int w);


    SDL_Texture* getTex();
    SDL_Rect* getRect();
    int getX();
    int getXSpeed();
    int getY();
    int getYSpeed();
    int getH();
    int getW();

private:
    SDL_Texture* spriteTex;
//    const char *filePath;
    std::shared_ptr<SDL_Rect> spriteRect = std::make_shared<SDL_Rect>();
};


#endif //PROJECT2DTD_SPRITE_H
