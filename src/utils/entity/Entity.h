#pragma once
#ifndef BUILD_ENTITY_H
#define BUILD_ENTITY_H

#include <vector>
#include "EntityData.h"
#include "Components.h"

class Entity {
public:
    template<class Comp>
    void addComponent() {
        Comp comp = Comp();
        comp.init();

        components.emplace_back(std::move(comp));
    }

    void update();
    void draw();
private:
    Entity* parent;
    std::vector<Entity*> children;
    std::vector<Component> components;
    EntityData data;
};

#endif //BUILD_ENTITY_H
