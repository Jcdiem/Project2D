#include "AtlasMan.h"

std::optional<Atlas> AtlasMan::rootAtlas;
sf::Image AtlasMan::missingImg;
sf::Texture AtlasMan::missingTex;

void AtlasMan::stitchAtlases() {
    rootAtlas = Atlas("assets/textures");

    //TODO: Create atlas printer for logger.

    missingImg.create(128, 128, EmbeddedSprites::nullsprite);
    missingTex.loadFromImage(missingImg);
    missingTex.setRepeated(true);
    missingTex.setSmooth(Flagger::getFlag("spriteSmoothing"));
}