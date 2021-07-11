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
#include "../Logger.h"
#include "../Flagger.h"
#include "../Json.h"

#define uintTrio unsigned int, unsigned int, unsigned int

class AtlasIndex;

class Atlas {
private:
    friend class AtlasIndex;

    explicit Atlas(const std::filesystem::path& path) : Atlas(path, true) {};
    Atlas(const std::filesystem::path& path, bool recursive);

    sf::Texture& getAtlasTex();

    //Tuple is formatted as follows, 0: vertical offset, 1: width, 2: height
    std::map<std::string, std::tuple<uintTrio>> offsets;

    sf::Image atlasImg;
    sf::Texture atlasTex;
};


#endif //BUILD_ATLAS_H
