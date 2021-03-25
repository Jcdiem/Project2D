#pragma once
#ifndef BUILD_ENTITYWRAPPER_H
#define BUILD_ENTITYWRAPPER_H

#include "InputManager.h"

#include "EntityComponentSystem.h"
#include "DataComponent.h"
#include "SpriteComponent.h"

//Add methods for all possible components!
class EntityWrapper {
public:
    EntityWrapper();
    EntityWrapper(Entity* entity);

    void setEntity(Entity* entity);

    //Setters
    void setX(float x);
    void setY(float y);
    void setRealX(float x);
    void setRealY(float y);
    void setW(float width);
    void setH(float height);
    void setRot(float rotation);
    void setRotX(float rotationX);
    void setRotY(float rotationY);
    void setHFlip(bool b);
    void setVFlip(bool b);
    void setHidden(bool b);

    //Getters
    float getX();
    float getY();
    float getRealX();
    float getRealY();
    float getW();
    float getH();
    float getRot();
    float getRotX();
    float getRotY();
    bool getHFlip();
    bool getVFlip();
    bool getHidden();

    //SpriteComponent helpers
    void resetRotPos();
    void playAnim(int animId, int ms);

    //InputManager helpers
    void addBinding(std::string action);
    bool isPressed(std::string action);
    void refreshBindings();

    //General Entity Helpers
    void kill();
    EntityWrapper getParent();
    void setParent(EntityWrapper entity);
    std::vector<EntityWrapper> getChildren();
    void addChild(EntityWrapper entity);
    Entity* getPtr();
    Manager* getMan();

private:
    Entity* entity;
    DataComponent* dataPtr;
    SpriteComponent* spritePtr;
    InputManager inputManager;
};


#endif //BUILD_ENTITYWRAPPER_H
