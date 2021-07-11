#pragma once
#ifndef BUILD_SPRITE_H
#define BUILD_SPRITE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <map>

#include "AtlasIndex.h"
#include "../Logger.h"
#include "../Flagger.h"

class Sprite : public sf::Drawable {
public:
    Sprite(const std::string& atlas, const std::string& sprite, int dwidth, int dheight);
    Sprite(const std::string& atlas, const std::string& sprite);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setSize(int dwidth, int dheight);

private:
    unsigned int width;
    unsigned int height;

    std::tuple<uintTrio> texLoc;
    sf::Texture texture;
    sf::Sprite sprite;
};


#endif //BUILD_SPRITE_H
