#ifndef P2D_CANVAS_H
#define P2D_CANVAS_H
#include "../include/TextureHandler.h"
#include "../include/Canvas_LayerData.h"


class Canvas {
public:

private:

    enum layers{FRONT=0, MIDDLE_FRONT=1, MIDDLE_BACK=2, BACKGROUND=3};
    const maxTexturesPerLayer = 100;
    Canvas_LayerData layerArray[3][maxTexturesPerLayer];

    //TODO: will return a unique ID for removing textures
    int paintToCanvas(Canvas_LayerData layerData, int layer);

    void removeFromCanvas(int textureInstanceId);


};


#endif //P2D_CANVAS_H
