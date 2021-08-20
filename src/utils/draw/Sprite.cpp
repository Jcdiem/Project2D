#include "Sprite.h"

void Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Sprite::setSize(int dwidth, int dheight) {
    sprite.setScale(float(dwidth) / width, float(dheight) / height);
}
