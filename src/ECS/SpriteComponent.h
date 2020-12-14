#ifndef PROJECT2DTD_SPRITECOMPONENT_H
#define PROJECT2DTD_SPRITECOMPONENT_H

#include "SDL2/SDL.h"
#include "EntityComponentSystem.h"
#include "AnimStruct.h"


class SpriteComponent : public Component{
public:

    SpriteComponent() = default;
    SpriteComponent(std::vector<animToolkit::animation*> anims){
        this->anims = anims;
        srcRect.y = 0;
        curAnim = anims[0];
        curFrame = lastFrame = 0;
    }

    void init() override{
        position = &entity->getComponent<ScriptComponent>();
        restartTimer();

        modPoint = (curAnim->frames / curAnim->framerate) * 1000;

//      flipPoint = (float(1) / float(curAnim->frames)) * (1000 * animDur);
//      ^^ Unsimplified version of equation below, I don't get how the simplified one works. I only __made__ it :shrug:
        flipPoint = float(1000) / float(curAnim->framerate);
    }

    void playAnim(int animId) {
        curAnim = anims[animId];
        restartTimer();

        modPoint = (curAnim->frames / curAnim->framerate) * 1000;

//      flipPoint = (float(1) / float(curAnim->frames)) * (1000 * animDur);
//      ^^ Unsimplified version of equation below, I don't get how the simplified one works. I only __made__ it :shrug:
        flipPoint = float(1000) / float(curAnim->framerate);
    }

    void update() override{
        destRect.x = position->x();
        destRect.y = position->y();

        srcRect.w = destRect.w = curAnim->width;
        srcRect.h = destRect.h = curAnim->height;
    }

    void draw() override{
        std::chrono::time_point<std::chrono::steady_clock> curTime = std::chrono::steady_clock::now();
        int timeSince = std::chrono::duration_cast<std::chrono::milliseconds>(curTime-timer).count();
        timeSince %= modPoint;

        lastFrame = curFrame;
        curFrame = timeSince / flipPoint;

        if(curFrame - lastFrame > 1) {
            printf("Uh oh, animation cycles can't keep up!");
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

    std::chrono::time_point<std::chrono::steady_clock> timer;

    ScriptComponent *position;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
};


#endif //PROJECT2DTD_SPRITECOMPONENT_H
