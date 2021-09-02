#include "Canvas.h"

void Canvas::drawCanvas(sf::RenderWindow *window){
    for(std::list canvasLayer : mainCanvas){
        for(Sprite canvasItem : canvasLayer){
            window->draw(canvasItem);
        }
    }
}

void Canvas::fillCanvasLayer(std::list<Sprite> spriteListToAdd, long unsigned int layer){
    if (layer >= mainCanvas->size() || layer < 0) throw std::invalid_argument("Incorrect layer number given");
    for (Sprite toAdd : spriteListToAdd) mainCanvas[layer].push_back(toAdd);
}