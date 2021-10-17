#include "Sprite.h"

Sprite::Sprite() {
    AtlasTex atlasTex = AtlasMan::getTex("missingTex");
    texture = atlasTex.texture;
    texLoc = atlasTex.location;

    texRect.top = std::get<0>(texLoc);
    texRect.left = 0;
    texRect.width = std::get<1>(texLoc);
    texRect.height = std::get<2>(texLoc);

    spriteScalar.x = 1;
    spriteScalar.y = 1;

    sprite.move(0, 0);
    sprite.setTexture(*texture);
    sprite.setTextureRect(texRect);
    sprite.setScale(spriteScalar);
}

void Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Sprite::setSize(float dwidth, float dheight) {
    sprite.setScale(dwidth / texRect.width, dheight / texRect.height);
}
