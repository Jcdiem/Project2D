#ifndef PROJECT2DTD_SPRITECOMPONENT_H
#define PROJECT2DTD_SPRITECOMPONENT_H

#include "SDL.h"
#include "src/ECS/EntityComponentSystem.h"


class SpriteComponent : public Component{
public:

    SpriteComponent() = default;
    SpriteComponent(const char* path,int sizeW,int sizeH){
        texture = TextureHandler::loadTexture(path);
        spriteHeight = sizeH;
        spriteWidth = sizeW;
    }

    void init() override{
        position = &entity->getComponent<PositionComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = destRect.w = spriteWidth;
        srcRect.h = destRect.h = spriteHeight;
    }

    void update() override{
        destRect.x = position->x();
        destRect.y = position->y();
    }

    void draw() override{
        TextureHandler::Draw(texture,srcRect,destRect);
    }

private:
    int spriteHeight;
    int spriteWidth;
    PositionComponent *position;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

};


#endif //PROJECT2DTD_SPRITECOMPONENT_H
