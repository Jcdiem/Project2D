#pragma once
#ifndef P2D_CANVAS_H
#define P2D_CANVAS_H
#include "TextureHandler.h"
#include "Canvas_LayerData.h"
#include <vector>

class Canvas {
public:
    //TODO: will return a unique ID for removing textures
    int paintToCanvas(int layer, const char *fileName, int sizeX, int sizeY, int offsetX=0, int offsetY=0);
    void removeFromCanvas(int textureInstanceId);
    void draw();

private:

    enum layers{FRONT=0, MIDDLE_FRONT=1, MIDDLE_BACK=2, BACKGROUND=3};
    const int maxTexturesPerLayer = 100;
    std::vector<std::vector<Canvas_LayerData*>> layerVector;


};


#endif //P2D_CANVAS_H
