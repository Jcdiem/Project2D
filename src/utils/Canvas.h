#include "draw/Sprite.h"
#include "Logger.h"
#include <stdexcept>
#include <list>
#include <SFML/Graphics/RenderWindow.hpp>

#ifndef BUILD_CANVAS_H
#define BUILD_CANVAS_H


class Canvas : public sf::Drawable {
public:
    /*!
     * @brief Standard inheritable function used by sfml to allow for nice syntax on drawn objects
     * @param You shouldn't need to worry about it :D
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    /*!
     * @brief Fill a layer of the canvas with items to print
     * @param spriteListToAdd A list containing sprites aligned to the screen to be drawn
     * @param layer The layer to draw the sprites on (0 is back, 5 is front)
     */
    void fillCanvasLayer(const std::list<Sprite>& spriteListToAdd, int layer);

private:
    std::vector<Sprite*> canvasLayers[5];
};


#endif //BUILD_CANVAS_H
