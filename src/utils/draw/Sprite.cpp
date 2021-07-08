#include "Sprite.h"

Sprite::Sprite(const std::string& path, int dwidth, int dheight) {
    if(!texture.loadFromFile(path)) {
        texture.create(128, 128);
        texture.update(EmbeddedSprites::nullsprite);
        Logger::print(Level::ERROR, "Failed to load image at ", path);
    }

    texture.setSmooth(Flagger::getFlag("spriteSmoothing"));

    width = texture.getSize().x;
    height = texture.getSize().y;

    sprite.setScale(float(dwidth) / width, float(dheight) / height);

    sprite.setTexture(texture);
}

Sprite::Sprite(const std::string& path) {
    if(!texture.loadFromFile(path)) {
        texture.create(128, 128);
        texture.update(EmbeddedSprites::nullsprite);
        Logger::print(Level::ERROR, "Failed to load image at ", path);
    }

    texture.setSmooth(Flagger::getFlag("spriteSmoothing"));

    width = texture.getSize().x;
    height = texture.getSize().y;

    sprite.setTexture(texture);
}

void Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Sprite::setSize(int dwidth, int dheight) {
    sprite.setScale(float(dwidth) / width, float(dheight) / height);
}
