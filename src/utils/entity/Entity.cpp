#include "Entity.h"

void Entity::removeComponent(unsigned int id) {
    for(auto compIDPair : components) {
        if(compIDPair.first == id) {
            delete compIDPair.second;
            return;
        }
    }
}

void Entity::update() {
    if(!data.active) {
        return; //Don't update if the entity is marked as inactive.
    }

    if(!data.parent || data.parent->killedStatus()) { //Check if parent has died
        data.orphaned = true;
        data.parent = nullptr;
    }

    for(auto childIter = data.children.begin(); childIter != data.children.end(); childIter++) {
        if(!(*childIter) || (*childIter)->killedStatus()) data.children.erase(childIter);
        //Remove children that are null pointers or marked as dead.
    }

    for(auto &componentIDPair : components) { //Run through and update all components!
        componentIDPair.second->update();
    }
}

void Entity::draw() {
    if(!data.active) {
        return; //Don't do draw actions if the entity is marked as inactive.
    }

    for(auto componentIDPair : components) {
        componentIDPair.second->draw();
    }
}

void Entity::kill() {
    data.dead = true;
    for(auto child : data.children) {
        if(child) {
            child->orphan();
        }
    }
}

bool Entity::killedStatus() const {
    return data.dead;
}

void Entity::orphan() {
    data.orphaned = true;
}

bool Entity::orphanedStatus() const {
    return data.orphaned;
}

void Entity::setActive(bool set) {
    data.active = set;
}

bool Entity::activeStatus() const {
    return data.active;
}

EntityData *Entity::getData() {
    return &data;
}

void Entity::setParent(Entity* e) {
    data.parent = e;

    if(!data.parent) { //If you give me a dead parent, I become an orphan.
        data.orphaned = true;
    } else {
        data.orphaned = false;

        for(auto child : e->getChildren()) {
            if(child == this) return; //Ensure we aren't already in the list of children before adding ourselves.
        }

        data.parent->addChild(this);
    }
}

Entity* Entity::getParent() const {
    return data.parent;
}

void Entity::addChild(Entity *e) {
    if(e && !e->killedStatus()) {
        data.children.push_back(e);

        if(e->getParent() != this) { //Ensure we aren't already their parent to avoid infinite loops.
            e->setParent(this);
        }
    }
}

std::vector<Entity*> Entity::getChildren() const {
    return data.children;
}
