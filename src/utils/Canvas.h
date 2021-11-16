#pragma once
#ifndef PROJECT2D_CANVAS_H
#define PROJECT2D_CANVAS_H

#include "draw/Sprite.h"
#include "Logger.h"

#include <map>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>


class Canvas : public sf::Drawable {
public:
    /*!
     * @brief Standard inheritable function used by sfml to allow for nice syntax on drawn objects
     *        Objects are drawn from lowest layer to highest layer,
     *        meaning an object with a larger layer number gets drawn on top.
     * @param You shouldn't need to worry about it :D
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    /*!
     * @brief Fill a layer of the canvas with items to print
     * @param layer, The layer to be drawn on, can be any number as long as it's an int
     * @param sprite, A drawable object, according to sfml, inherits from sf::Drawable
     */
    void addSprite(int layer, sf::Drawable* sprite);

    /*!
     * @brief Fill a layer of the canvas with items to print
     * @param layer, The layer to be drawn on, can be any number as long as it's an int
     * @param sprite, A drawable object, according to sfml, inherits from sf::Drawable
     */
    void addSprite(int layer, Sprite* sprite);

private:
    std::map<int, std::vector<sf::Drawable*>> layers;
};


#endif //PROJECT2D_CANVAS_H
