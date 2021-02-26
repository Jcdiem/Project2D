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
        data = &entity->getComponent<EntityData>();

        playAnim(0);
    }

    void playAnim(int animId) {
        curAnim = anims[animId];
        restartTimer();

        modPoint = (float(curAnim->frames) / float(curAnim->framerate)) * 1000;

//      flipPoint = (float(1) / float(curAnim->frames)) * (1000 * animDur);
//      ^^ Unsimplified version of equation below, I don't get how the simplified one works. I only __made__ it :shrug:
        flipPoint = float(1000) / float(curAnim->framerate);
    }

    void update() override{
        srcRect.w = curAnim->width;
        srcRect.h = curAnim->height;
        destRect.w = curAnim->dwidth;
        destRect.h = curAnim->dheight;
        destRect.x = int(data->x);
        destRect.y = int(data->y);
    }

    void draw() override{
        std::chrono::time_point<std::chrono::steady_clock> curTime = std::chrono::steady_clock::now();
        int timeSince = std::chrono::duration_cast<std::chrono::milliseconds>(curTime-timer).count();
        timeSince %= modPoint;

        lastFrame = curFrame;
        curFrame = timeSince / flipPoint;

        if(curFrame - lastFrame > 1) {
            std::cout << "Uh oh, animation cycles can't keep up! Framerate too low?" << std::endl;
        }

        srcRect.x = curFrame * curAnim->width;

        TextureHandler::Draw(curAnim->texture, srcRect, destRect);
    }

    void restartTimer() {
        timer = std::chrono::steady_clock::now();
    }

private:
    std::vector<animToolkit::animation*> anims;

    animToolkit::animation* curAnim;

    int modPoint;
    float flipPoint;

    int lastFrame;
    int curFrame;

    EntityData* data;

    std::chrono::time_point<std::chrono::steady_clock> timer;

    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
};


#endif //PROJECT2DTD_SPRITECOMPONENT_H
