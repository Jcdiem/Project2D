#include "../include/Canvas.h"

int Canvas::PaintToCanvas(Canvas_LayerData layerData, int layer){

    return 0;
}

void Canvas::draw(){
    for(int curLayer = 0; curLayer < layerArray.length(); curLayer++){
        for(int curTexture = 0; curTexture < layerArray[0].length(); curTexture++){
            TextureHandler::Draw(layerArray[curLayer][curTexture].getTexture, layerArray[curLayer][curTexture].getSrcRect, nullptr);
        }
    }
}