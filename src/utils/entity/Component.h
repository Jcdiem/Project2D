#pragma once
#ifndef BUILD_COMPONENT_H
#define BUILD_COMPONENT_H

#include "EntityData.h"

class Component {
public:
    virtual void init(){};
    virtual void update(){};
    virtual void draw(){};

    virtual ~Component() = default;
private:
    EntityData* data;
};

#endif //BUILD_COMPONENT_H
