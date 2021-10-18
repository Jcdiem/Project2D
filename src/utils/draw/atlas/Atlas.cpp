#include "Atlas.h"

Atlas::Atlas(const std::filesystem::path &path) {
    if(std::filesystem::exists(path.string() + "/atlas.png")) {
        if(!Flagger::find("regenAtlas")) {
            try {
                if(!internalAtlasTex.loadFromFile(path.string() + "/atlas.png")) {
                    throw std::exception();
                }

                internalAtlasTex.generateMipmap();
                internalAtlasTex.setSmooth(Flagger::find("spriteSmoothing"));

                offsets = LuaProcessor::luaConfToMap<unsigned int, 3>(path.string() + "/atlas.lua", "atlas");

                return; //We already have an atlas, and we want to keep it :)
            } catch(std::exception& e) {
                Logger::print(Level::WARN, "Something is wrong with one of the cached atlases!");
            }
        } else {
            Logger::print(Level::WARN, "Forcibly rebuilding atlases...");
        }

        std::filesystem::remove(path.string() + "/atlas.png");
        std::filesystem::remove(path.string() + "/atlas.lua");
        //We already have an atlas, but we want/need a new one /:
    }

    std::vector<std::pair<sf::Image, std::string>> images;
    std::vector<std::filesystem::path> subdirs;

    for(const auto& item : std::filesystem::directory_iterator(path)) {
        if(item.is_directory()) {
            subdirs.push_back(item);
        } else {
            std::string ext = item.path().extension();
            //The supported image formats are bmp, png, tga, jpg, gif, psd, hdr and pic.
            if(ext == ".bmp" || ext == ".png" || ext == ".tga" ||
               ext == ".jpg" || ext == ".jpeg"|| ext == ".gif" ||
               ext == ".psd" || ext == ".hdr" || ext == ".pic") {
                images.emplace_back();
                if(!images.back().first.loadFromFile(item.path())) {
                    Logger::print(Level::ERROR, "Failed to load image, consider remaking your atlas next launch: ", item.path());
                    images.pop_back();
                    break;
                }
                images.back().second = "_" + item.path().stem().string();
            }
        }
    }

    for(std::filesystem::path dir : subdirs) {
        if(!std::filesystem::is_empty(dir)) {
            children.insert_or_assign(dir.filename(), Atlas(dir));
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

    LuaProcessor::mapToLuaConf(offsets, path.string() + "/atlas.lua", "atlas");
    atlasImg.saveToFile(path.string() + "/atlas.png");

    internalAtlasTex.loadFromImage(atlasImg);
    internalAtlasTex.generateMipmap();
    internalAtlasTex.setSmooth(Flagger::find("spriteSmoothing"));
}
