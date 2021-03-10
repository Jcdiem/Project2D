#pragma once
#ifndef PROJECT2D_ENTITYDATA_H
#define PROJECT2D_ENTITYDATA_H

//Where entity data is stored, IE: Position Data, but any component can store things here if they want :)
struct EntityData : public Component {
//    engineSettings
    int windowWidth;
    int windowHeight;
//    engineSettings

//    positionData
    float x;
    float y;
//    positionData

//    animData
    bool updAnim = false;
    int animId;
    int loops = -1;
//    animData
};

#endif //PROJECT2D_ENTITYDATA_H
