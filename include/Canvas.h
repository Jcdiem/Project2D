#ifndef P2D_CANVAS_H
#define P2D_CANVAS_H
#include "../include/TextureHandler.h"
#include "../include/Canvas_LayerData.h"


class Canvas {
public:
    //TODO: will return a unique ID for removing textures
    int paintToCanvas(Canvas_LayerData layerData, int layer);
    void removeFromCanvas(int textureInstanceId);
    void draw();

private:

    enum layers{FRONT=0, MIDDLE_FRONT=1, MIDDLE_BACK=2, BACKGROUND=3};
    const maxTexturesPerLayer = 100;
    Canvas_LayerData layerArray[3][maxTexturesPerLayer];



};


#endif //P2D_CANVAS_H
