#include "Sprite.h"

Sprite::Sprite(const std::string& atlasName, const std::string& spriteName, int dwidth, int dheight) {
    AtlasTex atlasTex = AtlasIndex::getTex(atlasName, spriteName);

    sprite.setTexture(atlasTex.texture);
}

Sprite::Sprite(const std::string& atlas, const std::string& sprite) {
    if(!texture.loadFromFile(atlas)) {
        texture.create(128, 128);
        texture.update(EmbeddedSprites::nullsprite);
        Logger::print(Level::ERROR, "Failed to load image at ", atlas);
    }

    texture.setSmooth(Flagger::getFlag("spriteSmoothing"));

    width = texture.getSize().x;
    height = texture.getSize().y;

    this->sprite.setTexture(texture);
}

void Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Sprite::setSize(int dwidth, int dheight) {
    sprite.setScale(float(dwidth) / width, float(dheight) / height);
}
