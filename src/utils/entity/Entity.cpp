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
