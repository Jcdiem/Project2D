#pragma once
#ifndef BUILD_ATLAS_H
#define BUILD_ATLAS_H

#include <SFML/Graphics/Texture.hpp>
#include <filesystem>
#include <fstream>
#include <map>
#include <utility>

#include "EmbeddedSprites.h"
#include "../Logger.h"
#include "../Flagger.h"
#include "../Json.h"

class AtlasIndex {
public:
    static void stitchAtlases();

    class Atlas {
    public:
        explicit Atlas(const std::filesystem::path& path) : Atlas(path, true) {};
        Atlas(const std::filesystem::path& path, bool recursive);
    private:
        std::map<std::string, int> offsets;
        sf::Image atlasTex;
    };
private:
    static std::map<std::string, Atlas> atlasIndex;
};




#endif //BUILD_ATLAS_H
