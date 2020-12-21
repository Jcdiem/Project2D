#ifndef P2D_ANIMSTRUCT_H
#define P2D_ANIMSTRUCT_H

#include "../TextureHandler.h"

namespace animToolkit {
    struct animation {
        SDL_Texture* texture{};
        int width{};
        int height{};
        int frames = 1;
        int framerate = 1;
    };

    static void addByPath(animation* anim, char* path) {
        anim->texture = TextureHandler::loadTexture(path);
    }
}
#endif //P2D_ANIMSTRUCT_H
