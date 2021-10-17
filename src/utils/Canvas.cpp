#include "Canvas.h"

void Canvas::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(auto layerPair : layers) {
        auto layer = layerPair.second;

        for(auto sprite : layer) {
            target.draw(*sprite, states);
        }
    }
}

void Canvas::addSprite(int layer, sf::Drawable* sprite) {
    layers[layer].push_back(sprite);
}

void Canvas::addSprite(int layer, Sprite* sprite) {
    layers[layer].push_back(sprite);
}
