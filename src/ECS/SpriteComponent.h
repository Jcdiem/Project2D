#pragma once
#ifndef PROJECT2DTD_SPRITECOMPONENT_H
#define PROJECT2DTD_SPRITECOMPONENT_H

#include "SDL2/SDL.h"
#include "EntityComponentSystem.h"
#include "AnimStruct.h"

#include <chrono>

class SpriteComponent : public Component{
public:
    SpriteComponent(std::vector<animToolkit::animation*> anims){
        this->anims = anims;

        srcRect.y = 0;
        curAnim = anims[0];
        curFrame = lastFrame = 0;
    }

    void init() override{
        data = &entity->getComponent<DataComponent>();
        playAnim(0, -1);

        data->w = curAnim->dwidth;
        data->h = curAnim->dheight;
    }

    void playAnim(int animId, int loops) {
        curAnim = anims[animId];
        restartTimers();

        modPoint = int((float(curAnim->frames) / float(curAnim->framerate)) * 1000);

        animDur = modPoint * loops;

//      flipPoint = (float(1) / float(curAnim->frames)) * (1000 * animDur);
//      ^^ Unsimplified version of equation below, I don't get how the simplified one works. I only __made__ it :shrug:
        flipPoint = float(1000) / float(curAnim->framerate);
    }

    void update() override{
        srcRect.w = curAnim->width;
        srcRect.h = curAnim->height;

        data->realX = data->x;
        data->realY = data->y;

        try {
            Entity* parent = this->entity->getParent();
            if(parent) {
                DataComponent* parentData = &parent->getComponent<DataComponent>();
                if(parentData) {
                    data->realX += parentData->x;
                    data->realY += parentData->y;
                }
            }
        } catch(...){}

        destRect.x = int(data->realX);
        destRect.y = int(data->realY);
        destRect.w = int(data->w);
        destRect.h = int(data->h);

        flipStatus = SDL_FLIP_NONE;

        if(data->hflip) flipStatus = (SDL_RendererFlip)(flipStatus | SDL_FLIP_HORIZONTAL);
        if(data->vflip) flipStatus = (SDL_RendererFlip)(flipStatus | SDL_FLIP_VERTICAL);

        rotPoint.x = int(data->rotX);
        rotPoint.y = int(data->rotY);

        std::chrono::time_point<std::chrono::steady_clock> curTime = std::chrono::steady_clock::now();
        int timeSince = std::chrono::duration_cast<std::chrono::milliseconds>(curTime-animTimer).count();

        if(animDur > -1 && animDur < timeSince) {
            playAnim(0, -1);
        }
    }

    void draw() override{
        std::chrono::time_point<std::chrono::steady_clock> curTime = std::chrono::steady_clock::now();
        int timeSince = std::chrono::duration_cast<std::chrono::milliseconds>(curTime-frameTimer).count();
        timeSince %= modPoint;

        lastFrame = curFrame;
        curFrame = timeSince / flipPoint;

//        if(curFrame - lastFrame > 1) {
//            std::cout << "Uh oh, animation cycles can't keep up! Framerate too low?" << std::endl;
//        }
//        Enable for warnings about animation cycling, not really needed most of the time.

        srcRect.x = curFrame * curAnim->width;

        if(!data->hidden) {
            TextureHandler::Draw(curAnim->texture, srcRect, destRect, data->rot, rotPoint, flipStatus);
        }
    }
private:
    void restartTimers() {
        frameTimer = animTimer = std::chrono::steady_clock::now();
    }

    std::vector<animToolkit::animation*> anims;

    animToolkit::animation* curAnim;

    int modPoint;
    float flipPoint;

    int lastFrame;
    int curFrame;


    SDL_RendererFlip flipStatus;
    SDL_Point rotPoint;

    DataComponent* data;

    std::chrono::time_point<std::chrono::steady_clock> frameTimer;
    std::chrono::time_point<std::chrono::steady_clock> animTimer;

    int animDur;

    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
};


#endif //PROJECT2DTD_SPRITECOMPONENT_H
