#include <SFML/Graphics/RenderTexture.hpp>
#include "Atlas.h"

std::map<std::string, AtlasIndex::Atlas> AtlasIndex::atlasIndex;

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
}

AtlasIndex::Atlas::Atlas(const std::filesystem::path& path, bool recursive) {
    if(std::filesystem::exists(path.string() + "/atlas.png")) {
        if(!Flagger::getFlag("regenAtlas")) {
            try {
                if(!atlasTex.loadFromFile(path.string() + "/atlas.png")) {
                    throw std::exception();
                }
                offsets = Json::jsonToMap(path.string() + "/atlas.json");
                return; //We already have an atlas, and we want to keep it :)
            } catch(std::exception& e) {
                Logger::print(Level::WARN, "Something is wrong with one of the cached atlases!");
            }
        }

        std::filesystem::remove(path.string() + "/atlas.png");
        //We already have an atlas, but we want/need a new one /:
    }

    auto fs_iter = std::filesystem::recursive_directory_iterator(path);
    std::vector<std::pair<sf::Image, std::string>> images;


    for(const auto& file : fs_iter) {
        if(!recursive) fs_iter.disable_recursion_pending();

        if(!file.is_directory() && file.path().filename() != "atlas.json") {
            std::string ext = file.path().extension();
            //The supported image formats are bmp, png, tga, jpg, gif, psd, hdr and pic.
            if(ext == ".bmp" || ext == ".png" || ext == ".tga" ||
               ext == ".jpg" || ext == ".jpeg"|| ext == ".gif" ||
               ext == ".psd" || ext == ".hdr" || ext == ".pic") {
                images.emplace_back();
                if(!images.back().first.loadFromFile(file.path())) {
                    images.back().first.create(128, 128, EmbeddedSprites::nullsprite);
                    Logger::print(Level::ERROR, "Failed to load image at ", file.path());
                }
                images.back().second = file.path().filename();
            }
        }
    }

    unsigned int width = 0;
    unsigned int height = 0;
    for(const auto& image : images) {
        auto size = image.first.getSize();
        width = std::max(width, size.x);
        height += size.y;
    }
    atlasTex.create(width, height, sf::Color::Transparent);

    int curOffset = 0;
    for(const auto& image : images) {
        atlasTex.copy(image.first, 0, curOffset);
        offsets[image.second] = curOffset;
        curOffset += image.first.getSize().y;
    }

    Json::mapToJson(offsets, path.string() + "/atlas.json");
    atlasTex.saveToFile(path.string() + "/atlas.png");
}
