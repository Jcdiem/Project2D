#include <libs/json/include/nlohmann/json.hpp>
#include <fstream>
#include "Canvas.h"

int Canvas::paintToCanvas(int layer, std::string fileName, int sizeX, int sizeY, int posX, int posY, int offsetX, int offsetY){
    layerArray[layer].push_back(new Canvas_LayerData(TextureHandler::loadTexture(fileName.c_str()), sizeX, sizeY, offsetY, offsetX));
    this->canvasItemUID++; return this->canvasItemUID;

}

void Canvas::draw(){
    for(std::vector<Canvas_LayerData*> layer : layerArray){
        for(Canvas_LayerData * canvasItem : layer){
            TextureHandler::Draw(canvasItem->getTexturePtr(),
                                 canvasItem->getSrcRect(),
                                 canvasItem->getDestRect());
//            printf("SDL Error: %s \n",SDL_GetError());
        }
    }
}

void Canvas::genCanvasFromLevel(const char * path) {
    nlohmann::json json;
    try {
        json = nlohmann::json::parse(std::fstream(path), nullptr, true, true)["canvas"];
        for (auto canvasItem = json.begin(); canvasItem != json.end(); ++canvasItem){
            auto canvasLayer = canvasItem.value()["layer"].get<std::string>();
            auto canvasTexture = canvasItem.value()["texture"].get<std::string>();
            this->paintToCanvas(
                    convertStringToLayer(canvasLayer), //Layer
                    canvasTexture, //Texture
                    canvasItem.value()["width"].get<int>(),
                    canvasItem.value()["height"].get<int>(),
                    canvasItem.value()["x"].get<int>(),
                    canvasItem.value()["y"].get<int>()
            );

        }
    }
    catch(nlohmann::json::exception &e) {
        std::throw_with_nested(std::runtime_error("Level file could not be found or it was improperly formatted."));
    }

}

int Canvas::convertStringToLayer(std::string &input) {
    if(input == "front") return FRONT;
    else if(input == "background") return BACKGROUND;
    else if(input == "middle_front") return MIDDLE_FRONT;
    else if(input == "middle_back") return MIDDLE_BACK;
    else throw std::invalid_argument("Received invalid string " + input + " that could not be parsed");
}