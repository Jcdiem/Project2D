#pragma once
#ifndef PROJECT2D_COMPONENT_H
#define PROJECT2D_COMPONENT_H

#include "EntityData.h"

class Component {
public:
    virtual void init(){}; //Called once at the creation of the component.
    virtual void update(){}; //Called every time the engine updates, determined by engine settings.
    virtual void draw(){}; //Called every time the engine draws, determined by engine settings.
    virtual void destroy(){}; //Called once at the destruction of the object.

    virtual ~Component() = default;

protected:
    explicit Component(EntityData &data) : data(data){};

    EntityData& data;
};

#endif //PROJECT2D_COMPONENT_H
