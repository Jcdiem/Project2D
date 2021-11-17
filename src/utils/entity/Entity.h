#pragma once
#ifndef PROJECT2D_ENTITY_H
#define PROJECT2D_ENTITY_H

#include <vector>
#include <utility>

#include "EntityData.h"
#include "Components.h"
#include "../Logger.h"

class Entity {
public:
    Entity() = default;

    template <class Comp, class = typename std::enable_if<std::is_base_of<Component, Comp>::value>::type>
    long unsigned int addComponent() { //In order for lua to be able to add a new component,
                          //you can do that at src/utils/LuaProcessor.cpp around line 26.



        for(long unsigned int i = 0; i < std::size(components); i++) {
            if(components[i].second == nullptr) {//Find first component slot that resolves to a nullptr (IE: is empty)
                Comp* comp = new Comp(data);
                comp->init();

                components[i].second = comp;
                return i;
            }
        }

        Logger::print(ERROR, "Attempted to add component to already full entity (", data.objID, ")");
        return -1;
    }

    void removeComponent(unsigned int id);

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
    EntityData data;
    std::pair<unsigned int, Component*> components[10] = {
            {0, nullptr},
            {1, nullptr},
            {2, nullptr},
            {3, nullptr},
            {4, nullptr},
            {5, nullptr},
            {6, nullptr},
            {7, nullptr},
            {8, nullptr},
            {9, nullptr}
    }; //Max components allowed! 10 is probably more than is needed
};

#endif //PROJECT2D_ENTITY_H
