#pragma once
#ifndef PROJECT2D_SPRITECOMPONENT_H
#define PROJECT2D_SPRITECOMPONENT_H

#include "Component.h"

class SpriteComponent : public Component {
public:
    explicit SpriteComponent(EntityData &data) : Component(data){}

    void init() override;
    void update() override;
    void draw() override;
};


#endif //PROJECT2D_SPRITECOMPONENT_H
