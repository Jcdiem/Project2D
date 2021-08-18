#include "AtlasIndex.h"

sf::Image AtlasIndex::missingImg;
sf::Texture AtlasIndex::missingTex;
std::map<std::string, Atlas> AtlasIndex::atlasIndex;

void AtlasIndex::stitchAtlases() {
    atlasIndex.insert_or_assign("root", Atlas("assets/textures", false));

    for(const auto & file : std::filesystem::directory_iterator("assets/textures")) {
        if(std::filesystem::is_directory(file) && !file.path().empty()) {
            atlasIndex.insert_or_assign(file.path().stem().string(), Atlas(file.path()));
        }
    }

    for(auto& atlas : atlasIndex) {
        Logger::print(Level::INFO, "ATLAS NAME: ", atlas.first);
    }

    missingImg.create(128, 128, EmbeddedSprites::nullsprite);
    missingTex.loadFromImage(missingImg);
    missingTex.setRepeated(true);
    missingTex.setSmooth(Flagger::getFlag("spriteSmoothing"));
}

AtlasTex AtlasIndex::getTex(const std::string &atlasName, const std::string &texName) {
    try {
        Atlas atlas = atlasIndex.at(atlasName);

        try {
            std::tuple<uintTrio> imgLoc = atlas.offsets.at(texName);

            return {sf::Texture(atlas.getAtlasTex()), imgLoc};

        } catch(std::exception& e) {
            Logger::print(Level::ERROR, "Texture \"", texName, "\" not found in atlas \"", atlasName);
        }
    } catch(std::exception& e) {
        Logger::print(Level::ERROR, "Atlas \"", atlasName, "\" not found");
    }

    return {sf::Texture(missingTex), {0, 128, 128}};
}