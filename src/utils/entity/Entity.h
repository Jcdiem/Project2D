#pragma once
#ifndef BUILD_ENTITY_H
#define BUILD_ENTITY_H

#include <vector>
#include "EntityData.h"
#include "Components.h"

class Entity {
public:
    template <class Comp, class = typename std::enable_if<std::is_base_of<Component, Comp>::value>::type>
    void addComponent() { //In order for lua to be able to add a new component,
                          //you can do that at src/utils/LuaProcessor.cpp around line 26.
        Comp comp = Comp(data);
        comp.init();

        components.emplace_back(std::move(comp));
    }

    void update();
    void draw();

    void kill();
    void orphan();
    void setActive(bool set);
    void setParent(Entity* e);
    void addChild(Entity* e);

    EntityData* getData();
    [[nodiscard]] bool killedStatus() const;
    [[nodiscard]] bool orphanedStatus() const;
    [[nodiscard]] bool activeStatus() const;
    [[nodiscard]] Entity* getParent() const;
    [[nodiscard]] std::vector<Entity*> getChildren() const;
private:
    bool orphaned = false;
    bool dead = false;
    bool active = true;
    Entity* parent = nullptr;
    std::vector<Entity*> children;
    std::vector<Component> components;
    EntityData data;
};

#endif //BUILD_ENTITY_H
