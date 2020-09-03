#ifndef PROJECT2DTD_ENGINE_H
#define PROJECT2DTD_ENGINE_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Sprite.h"
#include <thread>
#include <time.h>
#include <iostream>
#include <vector>

class Engine {
public:
    Engine();
    ~Engine();


    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void loadSprite(Sprite sprite);
    Sprite getSprite(int spriteNum);

    void pushTexture(SDL_Texture* texture);
    SDL_Texture* getTexture(int texNum);

    void handleEvents();
    void update();
    void render();
    void clean();
    int dt();
    bool running() {
        return isRunning;
    }
    int winW;
    int winH;

private:
    std::vector<Sprite> spriteCollection;
    std::vector<SDL_Texture*> texturesInUse;
    int dvdSpeedX = 1;
    int dvdSpeedY = 1;
    int nsec;
    int nsecced;
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer  *renderer;

};

#endif //PROJECT2DTD_ENGINE_H
