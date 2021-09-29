#include "Canvas.h"

void Canvas::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(const auto& layer : canvasLayers){
        for(const auto& sprite : layer){
            target.draw(*sprite);
        }
    }
}

void Canvas::fillCanvasLayer(const std::list<Sprite>& sprites, int layer){
    if (layer >= sizeof(canvasLayers) || layer < 0) throw std::invalid_argument("Invalid layer number given");

    for(Sprite sprite : sprites) canvasLayers[layer].push_back(&sprite);
}
