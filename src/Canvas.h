#pragma once
#ifndef P2D_CANVAS_H
#define P2D_CANVAS_H

#include "TextureHandler.h"
#include "Canvas_LayerData.h"
#include <vector>
#include <string>
#include <libs/json/include/nlohmann/json.hpp>
#include <fstream>

namespace CanvasSystem {
    class Canvas {
        //TODO: Implement a tiling method
    public:
        Canvas();

/** createCanvasItem
         * \brief Will paint a static rectangle with texture to the screen, for building scenes
         *
         * \param layer - The layer that the item will be 'painted' to
         * \param textureFileName - The path to the texture file
         * \param texSizeX - The width of the texture
         * \param texSizeY - The height of the texture
         * \param posX - Desired x position on screen
         * \param posY - Desired y position on screen
         *
         * Setting the following will enable tiling, which instead creates a rectangle filled with the texture
         * \param fillSizeX default=0 - The width of the box to tiling-fill with texture
         * \param fillSizeY default=0 - The height of the box to tiling-fill with texture
         *
         * Setting the following will offset the src rect
         * \param offsetX - Amount to offset the X-axis on the image source (For grabbing a different frame to the 'right' or 'left')
         * \param offsetY - Amount to offset the y-axis on the image source (For grabbing a different frame from 'up' or 'down')
         *
         * \return An integer identifier of the item added for referencing later
         *
         * */
        int createCanvasItem(int layer, std::string textureFileName, int texSizeX, int texSizeY, int posX, int posY,
                             int fillSizeX = 0, int fillSizeY = 0, bool ignoreOverlap = false,
                             int offsetX = 0, int offsetY = 0);

        /** removeFromCanvas
         * \brief Will remove the item from the canvas
         * \param textureInstanceId - The id of the texture to be removed */
        void removeFromCanvas(int textureInstanceId);

        /** draw
         *\brief Draws the elements in the canvas to the screen for render*/
        void draw();

        /** genCanvasFromLevel
         * \brief generate a canvas from a level JSON file
         * \param *path - The path to the level JSON file */
        void genCanvasFromLevel(const char *path);

        /** Add texture for use with maps*/
        void addTexture(const char* path);

        //All of the layers available
        enum layers {
            FRONT = 3,
            MIDDLE_FRONT = 2,
            MIDDLE_BACK = 1,
            BACKGROUND = 0
        };

    private:


        const int maxTexturesPerLayer = 100;
        int canvasItemUID = -1;
        //Last to be processed is rendered 'above'
        std::vector<Canvas_LayerData *> layerArray[4] = {
                std::vector<Canvas_LayerData *>(),   //Background
                std::vector<Canvas_LayerData *>(),   //MiddleBack
                std::vector<Canvas_LayerData *>(),   //MiddleFront
                std::vector<Canvas_LayerData *>()    //Front
        };


        /** convertStringToLayer
         * \brief Returns an integer corresponding to the layers enum for the name given
         * \param input - String that should be converted to enum value */
        static int convertStringToLayer(std::string &input);

    };


#endif //P2D_CANVAS_H

}