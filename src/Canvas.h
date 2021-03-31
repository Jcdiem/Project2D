#pragma once
#ifndef P2D_CANVAS_H
#define P2D_CANVAS_H
#include "TextureHandler.h"
#include "Canvas_LayerData.h"
#include <vector>

class Canvas {
    //TODO: Implement a tiling method
public:
    /* paintToCanvas
     * Will paint a static texture to the canvas, for building scenes
     *
     * @param layer - The layer that the item will be 'painted' to
     * @param *textureFileName - The
     * @return An integer identifier of the item added for referencing later
     * */
    int paintToCanvas(int layer, std::string textureFileName, int sizeX, int sizeY, int posX, int posY, int offsetX=0, int offsetY=0);

    /* removeFromCanvas
     * Will remove the item from the canvas
     * @param textureInstanceId - The id of the texture to be removed */
    void removeFromCanvas(int textureInstanceId);

    /*draw
     *Draws the elements in the canvas to the screen for render*/
    void draw();

    /* genCanvasFromLevel
     * generate a canvas from a level JSON file
     * @param *path - The path to the level JSON file */
    void genCanvasFromLevel(const char * path);

    //All of the layers available
    enum layers{
        FRONT=0,
        MIDDLE_FRONT=1,
        MIDDLE_BACK=2,
        BACKGROUND=3
    };

private:


    const int maxTexturesPerLayer = 100;
    int canvasItemUID = -1;
    std::vector<Canvas_LayerData*> layerArray[4] = {
            std::vector<Canvas_LayerData*>(),   //Front
            std::vector<Canvas_LayerData*>(),   //MiddleFront
            std::vector<Canvas_LayerData*>(),   //MiddleBack
            std::vector<Canvas_LayerData*>()    //Background
    };

    /*convertStringToLayer
     * Returns an integer corresponding to the layers enum for the name given
     * @param input - String that should be converted to enum value */
    static int convertStringToLayer(std::string &input);

};


#endif //P2D_CANVAS_H
