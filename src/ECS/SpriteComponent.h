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
    }

    void init() override{
        position = &entity->getComponent<ScriptComponent>();
        restartTimer();
    }

    void playAnim(int animId) {
        curAnim = animId;
        restartTimer();
    }

    void update() override{
        destRect.x = position->x();
        destRect.y = position->y();
        flipPoint = 1;
        flipPoint = (flipPoint / anims[curAnim]->framerate) * 1000;

        srcRect.w = destRect.w = anims[curAnim]->width;
        srcRect.h = destRect.h = anims[curAnim]->height;
    }

    void draw() override{
        std::chrono::time_point<std::chrono::steady_clock> curTime = std::chrono::steady_clock::now();
        int timeSince = std::chrono::duration_cast<std::chrono::milliseconds>(curTime-timer).count();
        timeSince = timeSince % 1000;

        int curFrame = timeSince / flipPoint;

        srcRect.x = curFrame * anims[curAnim]->width;

        TextureHandler::Draw(anims[curAnim]->texture, srcRect, destRect);
    }

    void restartTimer() {
        timer = std::chrono::steady_clock::now();
    }

private:
    std::vector<animToolkit::animation*> anims;

    int curAnim = 0;
    float flipPoint;

    std::chrono::time_point<std::chrono::steady_clock> timer;

    ScriptComponent *position;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
};


#endif //PROJECT2DTD_SPRITECOMPONENT_H
