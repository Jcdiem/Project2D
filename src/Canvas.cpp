#include "../include/Canvas.h"

int Canvas::PaintToCanvas(int layer, const char *fileName, int sizeX, int sizeY, int offsetX=0, int offsetY=0){
    layerArray[layer].push_back(new Canvas_LayerData(TextureHandler::LoadTexture(fileName),sizeX,sizeY,offsetY,offsetX,offsetY));
    //TODO: Return a unique ID
    return -1;
}

void Canvas::draw(){
    for(int curLayer = 0; curLayer < layerArray.length(); curLayer++){
        for(int curTexture = 0; curTexture < layerArray[0].length(); curTexture++){
            TextureHandler::Draw(layerArray[curLayer][curTexture].getTexture, layerArray[curLayer][curTexture].getSrcRect, layerArray[curLayer][curTexture].getSrcRect);
        }
    }
}

void Canvas::importTexMap(int texMap[20][25], vector<const char*> filePaths){
    const int TEX_MAP_LAYER = 4;
    const int TEX_MAP_SIZE = 32;
    const int TEX_MAP_ROW = 20;
    const int TEX_MAP_COL = 25;

    int type = 0;

    for(int row = 0; row < TEX_MAP_ROW; row++){
        for(int col = 0; col < TEX_MAP_COL; col++){
            int type = texMap[row][col];
            SDL_Rect *dest = new SDL_Rect();
            dest -> h = dest -> w = 32;
            dest -> x = col * 32;
            dest -> y = row * 32;

            SDL_Texture *curTexture = TextureHandler::loadTexture(filePaths[texMap[row][col]]);

            layerArray[TEX_MAP_LAYER].push_back(
                    Canvas_LayerData(&curTexture, TEX_MAP_SIZE, TEX_MAP_SIZE)
                    );
        }
    }
}