#include "Atlas.h"

Atlas::Atlas(const std::filesystem::path &path, bool recursive) {
    if(std::filesystem::exists(path.string() + "/atlas.png")) {
        if(!Flagger::getFlag("regenAtlas")) {
            try {
                if(!atlasTex.loadFromFile(path.string() + "/atlas.png")) {
                    throw std::exception();
                }

                atlasTex.generateMipmap();
                atlasTex.setSmooth(Flagger::getFlag("spriteSmoothing"));

                offsets = Json::jsonToMap<uintTrio>(path.string() + "/atlas.json");
                return; //We already have an atlas, and we want to keep it :)
            } catch(std::exception& e) {
                Logger::print(Level::WARN, "Something is wrong with one of the cached atlases!");
            }
        }

        std::filesystem::remove(path.string() + "/atlas.png");
        std::filesystem::remove(path.string() + "/atlas.json");
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
                    Logger::print(Level::ERROR, "Failed to load image, consider remaking your atlas next launch: ", file.path());
                    images.pop_back();
                    break;
                }
                images.back().second = file.path().stem();
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

    atlasImg.create(width, height, sf::Color::Transparent);

    unsigned int curOffset = 0;
    for(const auto& image : images) {
        atlasImg.copy(image.first, 0, curOffset);
        std::get<0>(offsets[image.second]) = curOffset;
        std::get<1>(offsets[image.second]) = image.first.getSize().x;
        std::get<2>(offsets[image.second]) = image.first.getSize().y;
        curOffset += image.first.getSize().y;
    }

    Json::mapToJson(offsets, path.string() + "/atlas.json");
    atlasImg.saveToFile(path.string() + "/atlas.png");

    atlasTex.loadFromImage(atlasImg);
    atlasTex.generateMipmap();
    atlasTex.setSmooth(Flagger::getFlag("spriteSmoothing"));
}

sf::Texture &Atlas::getAtlasTex() {
    return atlasTex;
}
