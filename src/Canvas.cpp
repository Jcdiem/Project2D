#include "../include/Canvas.h"

int Canvas::paintToCanvas(int layer, const char *fileName, int sizeX, int sizeY, int offsetX, int offsetY){
    layerVector.at(layer).push_back(new Canvas_LayerData(TextureHandler::loadTexture(fileName),sizeX,sizeY,offsetY,offsetX));
    //TODO: Return a unique ID
    return -1;
}

void Canvas::draw(){
    for(unsigned int curLayer = 0; curLayer < layerVector.size(); curLayer++){
        for(int curTexture = 0; curTexture < layerVector.at(0).size(); curTexture++){
            TextureHandler::Draw(layerVector.at(curLayer).at(curTexture)->getTexturePtr(), layerVector.at(curLayer).at(curTexture)->getSrcRect(), layerVector.at(curLayer).at(curTexture)->getSrcRect());
        }
    }
}

void Canvas::importTexMap(int texMap[20][25], vector<const char*> filePaths){
    //Can't use constant because that would require constant as an input
    //Apparently c++ sees constant as a variable type :)
    int TEX_MAP_LAYER = 4;
    int TEX_MAP_ROW = 20;
    int TEX_MAP_COL = 25;

    int type = 0;

    for(int row = 0; row < TEX_MAP_ROW; row++){
        for(int col = 0; col < TEX_MAP_COL; col++){
            int type = texMap[row][col];
            SDL_Rect *dest = new SDL_Rect();
            dest -> h = dest -> w = 32;
            dest -> x = col * 32;
            dest -> y = row * 32;

            SDL_Texture *curTexture = TextureHandler::loadTexture(filePaths[texMap[row][col]]);

            layerVector[TEX_MAP_LAYER].push_back(
                    //Template:
                    //Canvas_LayerData(Texture for bg, sizeX, sizeY, offset, offset)
                    //This is currently set up for importing texture maps
                    //and shouldn't need to change unless texture maps are changed
                    Canvas_LayerData(curTexture, 32, 32)
                    );
        }
    }
}