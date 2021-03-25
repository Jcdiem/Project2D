#include "EntityWrapper.h"

#include <utility>

EntityWrapper::EntityWrapper() = default;

EntityWrapper::EntityWrapper(Entity* entity) {
    this->entity = entity;
    dataPtr = &entity->getComponent<DataComponent>();
    spritePtr = &entity->getComponent<SpriteComponent>();
}

void EntityWrapper::setEntity(Entity* entity) {
    this->entity = entity;
    dataPtr = &entity->getComponent<DataComponent>();
    spritePtr = &entity->getComponent<SpriteComponent>();
}

void EntityWrapper::setX(float x) {
    if(dataPtr) {
        dataPtr->x = x;
    }
}

void EntityWrapper::setY(float y) {
    if(dataPtr) {
        dataPtr->y = y;
    }
}

void EntityWrapper::setRealX(float x) {
    if(dataPtr) {
        dataPtr->realX = x;
    }
}

void EntityWrapper::setRealY(float y) {
    if(dataPtr) {
        dataPtr->realY = y;
    }
}

void EntityWrapper::setW(float width) {
    if(dataPtr) {
        dataPtr->w = width;
    }
}

void EntityWrapper::setH(float height) {
    if(dataPtr) {
        dataPtr->h = height;
    }
}

void EntityWrapper::setRot(float rotation) {
    if(dataPtr) {
        dataPtr->rot = rotation;
    }
}

void EntityWrapper::setRotX(float rotationX) {
    if(dataPtr) {
        dataPtr->rotX = rotationX;
    }
}

void EntityWrapper::setRotY(float rotationY) {
    if(dataPtr) {
        dataPtr->rotY = rotationY;
    }
}

void EntityWrapper::setHFlip(bool b) {
    if(dataPtr) {
        dataPtr->hflip = b;
    }
}

void EntityWrapper::setVFlip(bool b) {
    if(dataPtr) {
        dataPtr->vflip = b;
    }
}

void EntityWrapper::setHidden(bool b) {
    if(dataPtr) {
        dataPtr->hidden = b;
    }
}

float EntityWrapper::getX() {
    if(dataPtr) {
        return dataPtr->x;
    }
    return 0;
}

float EntityWrapper::getY() {
    if(dataPtr) {
        return dataPtr->y;
    }
    return 0;
}

float EntityWrapper::getRealX() {
    if(dataPtr) {
        return dataPtr->realX;
    }
    return 0;
}

float EntityWrapper::getRealY() {
    if(dataPtr) {
        return dataPtr->realY;
    }
    return 0;
}

float EntityWrapper::getW() {
    if(dataPtr) {
        return dataPtr->w;
    }
    return 0;
}

float EntityWrapper::getH() {
    if(dataPtr) {
        return dataPtr->h;
    }
    return 0;
}

float EntityWrapper::getRot() {
    if(dataPtr) {
        return dataPtr->rot;
    }
    return 0;
}

float EntityWrapper::getRotX() {
    if(dataPtr) {
        return dataPtr->rotX;
    }
    return 0;
}

float EntityWrapper::getRotY() {
    if(dataPtr) {
        return dataPtr->rotY;
    }
    return 0;
}

bool EntityWrapper::getHFlip() {
    if(dataPtr) {
        return dataPtr->hflip;
    }
    return false;
}

bool EntityWrapper::getVFlip() {
    if(dataPtr) {
        return dataPtr->vflip;
    }
    return false;
}

bool EntityWrapper::getHidden() {
    if(dataPtr) {
        return dataPtr->hidden;
    }
    return false;
}

void EntityWrapper::resetRotPos() {
    if(dataPtr) {
        dataPtr->rotX = dataPtr->w / float(2);
        dataPtr->rotY = dataPtr->h / float(2);
    }
}

void EntityWrapper::playAnim(int animId, int ms) {
    if(spritePtr) {
        spritePtr->playAnim(animId, ms);
    }
}

void EntityWrapper::addBinding(std::string action) {
    inputManager.addBinding(std::move(action));
}

bool EntityWrapper::isPressed(std::string action) {
    return inputManager.isPressed(std::move(action));
}

void EntityWrapper::refreshBindings() {
    inputManager.refreshBindings();
}

void EntityWrapper::kill() {
    entity->destroy();
}

EntityWrapper EntityWrapper::getParent() {
    return EntityWrapper(entity->getParent());
}

void EntityWrapper::setParent(EntityWrapper entity) {
    this->entity->setParent(entity.getPtr());
}

std::vector<EntityWrapper> EntityWrapper::getChildren() {
    std::vector<EntityWrapper> entVec;
    for(Entity* child : *entity->getChildren()) {
        entVec.emplace_back(child);
    }

    return entVec;
}

void EntityWrapper::addChild(EntityWrapper entity) {
    this->entity->addChild(entity.getPtr());
}

Entity* EntityWrapper::getPtr() {
    return entity;
}

Manager *EntityWrapper::getMan() {
    return entity->manager;
}
