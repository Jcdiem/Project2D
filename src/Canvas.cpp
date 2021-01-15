#include "../include/Canvas.h"

int Canvas::findFirstEmptySpace(int workingLayer){
    prtinf("Finding first empty space in layer %d ...",workingLayer);
    for(int curPtr = 0; curPtr < layerArray[workingLayer].length(); curPtr++){
        if(layerArray[workingLayer][curPtr] != nullptr) {
            printf("First empty space found at index %d!",curPtr)
            return curPtr;
        }
        else if(curPtr == layerArray[0].length() - 1) {
            std::throw(std::runtime_error(std::string("Too many items in layer #").append(workingLayer)))
            return -1;
        }
    }
}

int Canvas::PaintToCanvas(int layer, const char *fileName, sizeX, sizeY, offsetX=0, offsetY=0){
    TextureHandler::LoadTexture(fileName)
    return 0;
}

void Canvas::draw(){
    for(int curLayer = 0; curLayer < layerArray.length(); curLayer++){
        for(int curTexture = 0; curTexture < layerArray[0].length(); curTexture++){
            TextureHandler::Draw(layerArray[curLayer][curTexture].getTexture, layerArray[curLayer][curTexture].getSrcRect, layerArray[curLayer][curTexture].getSrcRect);
        }
    }
}

void Canvas::importTexMap(int[20][25] texMap, vector<const char*> filePaths){
    const TEX_MAP_LAYER = 4;
    const TEX_MAP_SIZE = 32;
    const TEX_MAP_ROW = 20;
    const TEX_MAP_COL = 25;

    int type = 0;

    for(int row = 0; row < TEX_MAP_ROW; row++){
        for(int col = 0; col < TEX_MAP_COL; col++){
            int type = textureMap[row][col];
            SDL_Rect dest = new SDL_Rect();
            dest.h = dest.w = 32
            dest.x = col * 32;
            dest.y = row * 32;

            SDL_Texture *curTexture = TextureHandler::loadTexture(filePaths[texMap[row][col]]);
            int itemNo = findFirstEmptySpace(TEX_MAP_LAYER);

            layerArray[TEX_MAP_LAYER][itemNo] = new Canvas_LayerData(currentTexture, TEX_MAP_SIZE, TEX_MAP_SIZE);
        }
    }
}