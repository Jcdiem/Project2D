#pragma once
#ifndef PROJECT2D_ENTITYDATA_H
#define PROJECT2D_ENTITYDATA_H

#include <string>
#include <vector>

class Entity; //Predef for pointers!

struct EntityData {
    bool orphaned = false; //Indicates weather the entity is an orphan.
    bool dead = false; //Indicates weather the entity is dead, if it is, expect the object to be destroyed soon.
    bool active = true; //Indicates weather an object is active or now,
                        // it won't receive updates or get drawn while inactive
    Entity* parent = nullptr; //A pointer to the parent object.
    std::vector<Entity*> children; //A vector full of pointers to child objects.

    unsigned int objID; //ID assigned at runtime, used to access an instance of a type.
    std::string type; //Describes the type of the object.
    bool isScripted; //Used to determine if lua is needed to update the object. Most will, but there may be exceptions.
};

#endif //PROJECT2D_ENTITYDATA_H
