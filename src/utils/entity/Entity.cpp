#include "Entity.h"

Entity::Entity() {

}

void Entity::update() {
    if(!parent || parent->killedStatus()) { //Check if parent has died
        orphaned = true;
        parent = nullptr;
    }

    for(auto childIter = children.begin(); childIter != children.end(); childIter++) {
        if(!(*childIter) || (*childIter)->killedStatus()) children.erase(childIter);
        //Remove children that are null pointers or marked as dead.
    }

    for(Component &component: components) { //Run through and update all components!
        component.update();
    }
}

void Entity::draw() {
    for(Component &component: components) {
        component.draw();
    }
}

void Entity::kill() {
    dead = true;
    for(auto child : children) {
        if(child) {
            child->orphan();
        }
    }
}

bool Entity::killedStatus() const {
    return dead;
}

void Entity::orphan() {
    orphaned = true;
}

bool Entity::orphanedStatus() const {
    return orphaned;
}

void Entity::setActive(bool set) {
    active = set;
}

bool Entity::activeStatus() const {
    return active;
}

EntityData *Entity::getData() {
    return &data;
}

void Entity::setParent(Entity* e) {
    parent = e;

    if(!parent || parent->killedStatus()) { //If you give me a pointer to null, or a dead parent, I become an orphan.
        orphaned = true;
    } else {
        orphaned = false;

        for(auto child : e->getChildren()) {
            if(child == this) return; //Ensure we aren't already in the list of children before adding ourselves.
        }

        parent->addChild(this);
    }
}

Entity* Entity::getParent() const {
    return parent;
}

void Entity::addChild(Entity *e) {
    if(e || !e->killedStatus()) {
        children.push_back(e);

        if(e->getParent() != this) { //Ensure we aren't already their parent to avoid infinite loops.
            e->setParent(this);
        }
    }
}

std::vector<Entity*> Entity::getChildren() const {
    return children;
}
