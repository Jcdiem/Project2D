#ifndef PROJECT2DTD_PHYSICS_H
#define PROJECT2DTD_PHYSICS_H
#include <vector>
#include "Sprite.h"


class Physics {
public:
    Physics(int gravity, int gravDir, std::vector<Sprite> rigidList) {
        Physics::gravity = gravity;
        Physics::gravDir = gravDir;
        Physics::rigidList = rigidList;
    }
    
    void applyForce(int power, int direction, Sprite sprite);
    void spriteTick(Sprite sprite);
private:
    int gravity;
    int gravDir;
    std::vector<Sprite> rigidList;
};


#endif //PROJECT2DTD_PHYSICS_H
