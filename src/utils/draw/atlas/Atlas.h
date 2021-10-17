#pragma once
#ifndef BUILD_ATLAS_H
#define BUILD_ATLAS_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <filesystem>
#include <fstream>
#include <map>
#include <utility>

#include "EmbeddedSprites.h"
#include "src/utils/Logger.h"
#include "src/utils/Flagger.h"
#include "src/utils/Json.h"

#define uintTrio unsigned int, unsigned int, unsigned int

class AtlasIndex;

struct AtlasTex {
    bool found;
    sf::Texture* texture;
    std::tuple<uintTrio> location;
};

class Atlas {
private:
    friend class AtlasMan;

    Atlas(const std::filesystem::path& path);

    template<typename... Specifiers>
    AtlasTex find(const std::string& specifier, Specifiers... specifiers) {
        return children.at(specifier).find(specifiers...);
    }
    
    AtlasTex find(const std::string& spriteName) {
        if(spriteName == "atlas") {
            return {true, &internalAtlasTex, {0, internalAtlasTex.getSize().x, internalAtlasTex.getSize().y}};
        }

        try {
            std::tuple<uintTrio> imgLoc = offsets.at(spriteName);

            return {true, &internalAtlasTex, imgLoc};

        } catch(std::exception& e) {
            return {false};
        }
    }

    std::map<std::string, Atlas> children;

    //Tuple is formatted as follows, 0: vertical offset, 1: width, 2: height
    std::map<std::string, std::tuple<uintTrio>> offsets;

    sf::Image atlasImg;
    sf::Texture internalAtlasTex;
};


#endif //BUILD_ATLAS_H
