#pragma once
#ifndef BUILD_ENTITY_H
#define BUILD_ENTITY_H

#include <vector>
#include "EntityData.h"
#include "Components.h"

class Entity {
public:
    template <class Comp, class = typename std::enable_if<std::is_base_of<Component, Comp>::value>::type>
    void addComponent() {
        Comp comp = Comp(data);
        comp.init();

        components.emplace_back(std::move(comp));
    }

    void update();
    void draw();
    void kill();
    void orphan();
    void active(bool set);
    [[nodiscard]] bool active() const;
private:
    bool orphaned;
    bool dead;
    bool activated;
    Entity* parent;
    std::vector<Entity*> children;
    std::vector<Component> components;
    EntityData data;
};

#endif //BUILD_ENTITY_H
