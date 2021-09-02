#include "draw/Sprite.h"
#include <stdexcept>
#include <list>

#ifndef BUILD_CANVAS_H
#define BUILD_CANVAS_H


class Canvas {
public:
    Canvas();

    /*!
     * @brief Will draw the canvas members to the screen
     * @param window The RenderWindow to draw to
     */
    void drawCanvas(sf::RenderWindow *window);

    /*!
     * @brief Fill a layer of the canvas with items to print
     * @param spriteListToAdd A list containing sprites aligned to the screen to be drawn
     * @param layer The layer to draw the sprites on (0 is back, 5 is front)
     */
    void fillCanvasLayer(std::list<Sprite> spriteListToAdd, int layer){
        if (layer >= mainCanvas->size() || layer < 0) throw std::invalid_argument("Incorrect layer number given");
        for (Sprite toAdd : spriteListToAdd) mainCanvas[layer].push_back(toAdd);
    }

private:
    std::list<Sprite> mainCanvas [5]; //Add 5 layers behind/back
};


#endif //BUILD_CANVAS_H
