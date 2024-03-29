#pragma once
#ifndef PROJECT2D_ATLASMAN_H
#define PROJECT2D_ATLASMAN_H

#include <optional>
#include <sstream>
#include "Atlas.h"

class AtlasMan {
public:
    static void stitchAtlases();

    template<typename... Specifiers>
    static AtlasTex getTex(Specifiers... specifiers) {
        AtlasTex tex = rootAtlas->find(specifiers...);
        if(tex.found) {
            return tex;
        } else {
            return {false, &missingTex, {0, 128, 128}};
        }
    }

private:

    static std::optional<Atlas> rootAtlas;
    static sf::Image missingImg;
    static sf::Texture missingTex;
};


#endif //PROJECT2D_ATLASMAN_H
