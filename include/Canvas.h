#ifndef P2D_CANVAS_H
#define P2D_CANVAS_H
#include "../include/TextureHandler.h"
#include "../include/Canvas_LayerData.h"
#include "../include/TextureMap.h"

using std::vector;

class Canvas {
public:
    //TODO: will return a unique ID for removing textures
    int paintToCanvas(int layer, const char *fileName, int sizeX, int sizeY, int offsetX=0, int offsetY=0);
    void removeFromCanvas(int textureInstanceId);
    void draw();
    void importTexMap(int texMap[20][25], vector<const char*> filePaths);

private:

    enum layers{FRONT=0, MIDDLE_FRONT=1, MIDDLE_BACK=2, BACKGROUND=3};
    const int maxTexturesPerLayer = 100;
    vector<vector<Canvas_LayerData*>> layerVector;


};


#endif //P2D_CANVAS_H
