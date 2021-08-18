#include "Sprite.h"

Sprite::Sprite(const std::string& atlasName, const std::string& spriteName, int dwidth, int dheight) {
    AtlasTex atlasTex = AtlasIndex::getTex(atlasName, spriteName);
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

Sprite::Sprite(const std::string& atlasName, const std::string& spriteName) {
    AtlasTex atlasTex = AtlasIndex::getTex(atlasName, spriteName);
    texture = atlasTex.texture;
    texLoc = atlasTex.location;

    textRect.top = std::get<0>(texLoc);
    textRect.left = 0;
    textRect.width = std::get<1>(texLoc);
    textRect.height = std::get<2>(texLoc);

    sprite.setTexture(texture);
    sprite.setTextureRect(textRect);
    sprite.setScale(spriteScalar);
}

void Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Sprite::setSize(int dwidth, int dheight) {
    sprite.setScale(float(dwidth) / width, float(dheight) / height);
}
