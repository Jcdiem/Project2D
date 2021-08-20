#pragma once
#ifndef BUILD_SPRITE_H
#define BUILD_SPRITE_H

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
    Sprite(int dwidth, int dheight, Specifiers... specifiers) {
        AtlasTex atlasTex = AtlasMan::getTex(specifiers...);
        texture = atlasTex.texture;
        texLoc = atlasTex.location;

        textRect.top = std::get<0>(texLoc);
        textRect.left = 0;
        textRect.width = std::get<1>(texLoc);
        textRect.height = std::get<2>(texLoc);

        spriteScalar.x = float(dwidth) / textRect.width;
        spriteScalar.y = float(dheight) / textRect.height;

        sprite.setTexture(texture);
        sprite.setTextureRect(textRect);
        sprite.setScale(spriteScalar);
    }

    template<typename... Specifiers>
    Sprite(Specifiers... specifiers) {
        AtlasTex atlasTex = AtlasMan::getTex(specifiers...);
        texture = atlasTex.texture;
        texLoc = atlasTex.location;

        textRect.top = std::get<0>(texLoc);
        textRect.left = 0;
        textRect.width = std::get<1>(texLoc);
        textRect.height = std::get<2>(texLoc);

        spriteScalar.x = 1;
        spriteScalar.y = 1;

        sprite.setTexture(texture);
        sprite.setTextureRect(textRect);
        sprite.setScale(spriteScalar);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setSize(int dwidth, int dheight);

private:
    float width;
    float height;

    std::tuple<uintTrio> texLoc;
    sf::Vector2f spriteScalar;

    sf::Texture texture;
    sf::IntRect textRect;
    sf::Sprite sprite;
};


#endif //BUILD_SPRITE_H
