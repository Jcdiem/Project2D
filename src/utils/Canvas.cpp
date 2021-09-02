#include "Canvas.h"

Canvas::Canvas() {}

void Canvas::drawCanvas(sf::RenderWindow *window){
    for(std::list canvasLayer : mainCanvas){
        for(Sprite canvasItem : canvasLayer){
            window->draw(canvasItem);
        }
    }
}