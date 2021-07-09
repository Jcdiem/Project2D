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
typedef std::tuple<uintTrio> TextureLoc;

struct AtlasTex {
    sf::Texture& texture;
    TextureLoc location;
};

class AtlasIndex {
public:
    AtlasIndex() = delete;
    ~AtlasIndex() = delete;

    static void stitchAtlases();
    static AtlasTex getTex(const std::string& atlasName, const std::string& texName);

    class Atlas {
    public:
        explicit Atlas(const std::filesystem::path& path) : Atlas(path, true) {};
        Atlas(const std::filesystem::path& path, bool recursive);

        sf::Texture& getAtlasTex();

        //Tuple is formatted as follows, 0: offset, 1: width, 2: height
        std::map<std::string, TextureLoc> offsets;

    private:
        sf::Image atlasImg;
        sf::Texture atlasTex;
    };

private:
    static std::map<std::string, Atlas> atlasIndex;
    static sf::Image missingImg;
    static sf::Texture missingTex;
};




#endif //BUILD_ATLAS_H
