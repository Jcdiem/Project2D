#ifndef P2D_ANIMSTRUCT_H
#define P2D_ANIMSTRUCT_H

#include "../TextureHandler.h"

namespace animToolkit {
    struct animation {
        SDL_Texture* texture{};
        int width;
        int height;
        int dwidth;
        int dheight;
        int frames;
        int framerate;

        void addByPath(char* path) {
            texture = TextureHandler::loadTexture(path);
        }
    };
}
#endif //P2D_ANIMSTRUCT_H
