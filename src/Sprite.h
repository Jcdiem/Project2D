#ifndef PROJECT2DTD_SPRITE_H
#define PROJECT2DTD_SPRITE_H
#include <list>
#include <SDL2/SDL.h>
#include <memory>
#include <iostream>


class Sprite {
public:
    Sprite(int width, int height, const char *file){
        Sprite::spriteRect->h = height;
        Sprite::spriteRect->w = width;
        Sprite::spriteRect->x = 0;
        Sprite::spriteRect->y = 0;
        Sprite::filePath = file;
    }

    void setX(int x);
    void setXSpeed(int speed);
    void setY(int y);
    void setYSpeed(int speed);
    void setH(int h);
    void setW(int w);

    const char * getFile();
    SDL_Rect* getRect();
    int getX();
    int getXSpeed();
    int getY();
    int getYSpeed();
    int getH();
    int getW();

private:
    const char *filePath;
    int xSpeed = 0;
    int ySpeed = 0;
    std::shared_ptr<SDL_Rect> spriteRect = std::make_shared<SDL_Rect>();
};


#endif //PROJECT2DTD_SPRITE_H
