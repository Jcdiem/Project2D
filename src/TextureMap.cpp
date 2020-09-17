#include "TextureMap.h"

//Explanation of terribleness:
//0 = Tex0 | 1 = Tex1 | 2 = Tex2
int start[20][25]={ //TODO: load texture maps through XML or something
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

TextureMap::TextureMap() {
    mapTextureName0 = TextureHandler::loadTexture("assets/textures/mapTex0.png");
    mapTextureName1 = TextureHandler::loadTexture("assets/textures/mapTex1.png");
    mapTextureName2 = TextureHandler::loadTexture("assets/textures/mapTex2.png");

    loadMap(start);

    src.x = src.y = 0;
    src.w = src.h = dest.h = dest.w = 32; //NOTE: all texture maps should be 32x32 pixels

    dest.x = dest.y = 0;
}

void TextureMap::loadMap(int array[textureMapRows][textureMapCols]) {
    for(int row = 0; row < textureMapRows; row++){
        for(int col = 0; col < textureMapCols; col++){
            textureMap[row][col] = array[row][col];
        }
    }
}

void TextureMap::drawMap() {
    int type = 0;

    for(int row = 0; row < textureMapRows; row++){
        for(int col = 0; col < textureMapCols; col++){
            type = textureMap[row][col];
            dest.x = col * 32;
            dest.y = row * 32;

            switch (type) {
                case 0: //Draw texture map 0
                    TextureHandler::Draw(mapTextureName0, src, dest);
                    break;
                case 1: //Draw texture map 0
                    TextureHandler::Draw(mapTextureName1, src, dest);
//                    printf("Drew a %d on tilemap \n",type);
                    break;
                case 2: //Draw texture map 0
                    TextureHandler::Draw(mapTextureName2, src, dest);
//                    printf("Drew a %d on tilemap \n",type);
                    break;
                default:
                    printf("WARNING: Got %d for map type when only possible cases are 0, 1, 2 \n"
                           "    Location %d, %d (row,col)\n",type,row,col);
                    break;
            }
        }
    }
}