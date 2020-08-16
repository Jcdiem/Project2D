#ifndef PROJECT2DTD_SPRITE_H
#define PROJECT2DTD_SPRITE_H
#include <list>
#include <SDL2/SDL.h>
#include <memory>


class Sprite {
public:
    Sprite(int width, int height, const char *file){
        Sprite::spriteRect->h = height;
        Sprite::spriteRect->w = width;
        Sprite::spriteRect->x = 0;
        Sprite::spriteRect->y = 0;
        Sprite::filePath = file;
    }


    void setY(int y);
    void setX(int x);
    void setH(int h);
    void setW(int w);

    const char * getFile();
    SDL_Rect* getRect();
    int getX();
    int getY();
    int getH();
    int getW();

private:
    const char *filePath;
    std::shared_ptr<SDL_Rect> spriteRect;
};


#endif //PROJECT2DTD_SPRITE_H
