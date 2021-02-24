#include "Canvas.h"

int Canvas::paintToCanvas(int layer, const char *fileName, int sizeX, int sizeY, int offsetX, int offsetY){
    layerVector.at(layer).push_back(new Canvas_LayerData(TextureHandler::loadTexture(fileName),sizeX,sizeY,offsetY,offsetX));
    //TODO: Return a unique ID
    return -1;
}

void Canvas::draw(){
    for(unsigned int curLayer = 0; curLayer < layerVector.size(); curLayer++){
        for(unsigned int curTexture = 0; curTexture < layerVector.at(0).size(); curTexture++){
            TextureHandler::Draw(layerVector.at(curLayer).at(curTexture)->getTexturePtr(), layerVector.at(curLayer).at(curTexture)->getSrcRect(), layerVector.at(curLayer).at(curTexture)->getSrcRect());
        }
    }
}