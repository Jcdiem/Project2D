#pragma once
#ifndef PROJECT2D_ENTITYDATA_H
#define PROJECT2D_ENTITYDATA_H

#include <string>

struct EntityData {
    unsigned int objID; //ID assigned at runtime, used to access an instance of a type.
    std::string type; //Describes the type of the object.
    bool isScripted; //Used to determine if lua is needed to update the object. Most will, but there may be exceptions.
};

#endif //PROJECT2D_ENTITYDATA_H
