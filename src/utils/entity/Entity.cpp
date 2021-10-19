#include "Entity.h"

void Entity::update() {
    for(Component &component: components) {
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

void Entity::orphan() {
    orphaned = true;
}

void Entity::active(bool set) {
    activated = set;
}

bool Entity::active() const {
    return activated;
}
