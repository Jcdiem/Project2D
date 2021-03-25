#pragma once
#ifndef PROJECT2D_ENTITYDATA_H
#define PROJECT2D_ENTITYDATA_H

//Where entity data is stored, IE: Position Data, but any component can store things here if they want :)
struct DataComponent : public Component {
    float x;
    float realX; //Based on position of parents and self, do not write!
    float y;
    float realY; //Based on position of parents and self, do not write!
    float w;
    float h;
    float rotX;
    float rotY;
    float rot;
    bool vflip;
    bool hflip;
    bool hidden;
};

#endif //PROJECT2D_ENTITYDATA_H
