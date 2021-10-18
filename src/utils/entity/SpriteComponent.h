#pragma once
#ifndef BUILD_SPRITECOMPONENT_H
#define BUILD_SPRITECOMPONENT_H

#include "Component.h"

class SpriteComponent : public Component {
public:
    explicit SpriteComponent(EntityData &data) : Component(data){}

    void init() override;
    void update() override;
    void draw() override;
};


#endif //BUILD_SPRITECOMPONENT_H
