#pragma once
#ifndef PROJECT2D_SPRITE_H
#define PROJECT2D_SPRITE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <map>

#include "atlas/AtlasMan.h"
#include "../Logger.h"
#include "../Flagger.h"

class Sprite : public sf::Drawable {
public:
    template<typename... Specifiers>
    Sprite(int x, int y, int dwidth, int dheight, Specifiers... specifiers) {
        AtlasTex atlasTex = AtlasMan::getTex(specifiers...);
        texture = atlasTex.texture;
        texLoc = atlasTex.location;

        texRect.top = std::get<0>(texLoc);
        texRect.left = 0;
        texRect.width = std::get<1>(texLoc);
        texRect.height = std::get<2>(texLoc);

        spriteScalar.x = float(dwidth) / texRect.width;
        spriteScalar.y = float(dheight) / texRect.height;

        sprite.move(x, y);
        sprite.setTexture(*texture);
        sprite.setTextureRect(texRect);
        sprite.setScale(spriteScalar);
    }

    template<typename... Specifiers>
    Sprite(int x, int y, Specifiers... specifiers) {
        AtlasTex atlasTex = AtlasMan::getTex(specifiers...);
        texture = atlasTex.texture;
        texLoc = atlasTex.location;

        texRect.top = std::get<0>(texLoc);
        texRect.left = 0;
        texRect.width = std::get<1>(texLoc);
        texRect.height = std::get<2>(texLoc);

        spriteScalar.x = 1;
        spriteScalar.y = 1;

        sprite.move(x, y);
        sprite.setTexture(*texture);
        sprite.setTextureRect(texRect);
        sprite.setScale(spriteScalar);
    }

    Sprite();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setSize(float dwidth, float dheight);

private:
    std::array<unsigned int, 3> texLoc;
    sf::Vector2f spriteScalar;

    sf::Texture* texture;
    sf::IntRect texRect;
    sf::Sprite sprite;
};


#endif //PROJECT2D_SPRITE_H
