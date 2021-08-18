#pragma once
#ifndef BUILD_ATLASINDEX_H
#define BUILD_ATLASINDEX_H

#include "Atlas.h"

struct AtlasTex {
    sf::Texture texture;
    std::tuple<uintTrio> location;
};

class AtlasIndex{
public:
    AtlasIndex() = delete;
    ~AtlasIndex() = delete;

    static void stitchAtlases();
    static AtlasTex getTex(const std::string& atlasName, const std::string& texName);

private:
    static std::map<std::string, Atlas> atlasIndex;
    static sf::Image missingImg;
    static sf::Texture missingTex;
};


#endif //BUILD_ATLASINDEX_H
