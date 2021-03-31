#include "Canvas.h"

int CanvasSystem::Canvas::createCanvasItem(int layer, std::string textureFileName, int texSizeX, int texSizeY, int posX, int posY,
                                           int fillSizeX, int fillSizeY, bool ignoreOverlap, int offsetX, int offsetY){
    layerArray[layer].push_back(new Canvas_LayerData(TextureHandler::loadTexture(textureFileName.c_str()), texSizeX, texSizeY, posX, posY, fillSizeX, fillSizeY, ignoreOverlap, offsetX, offsetY));
    this->canvasItemUID++;
    return this->canvasItemUID;

}

//Everything assumed to be a map
void CanvasSystem::Canvas::draw(){
    for(std::vector<Canvas_LayerData*> layer : layerArray){
        for(Canvas_LayerData * canvasItem : layer){
            //Render texture map
            if(canvasItem->getTextureMap() != nullptr){
                TextureHandler::focusBigTexture(canvasItem->getTextureMap());
                SDL_Rect fillRectDest;
                fillRectDest.w = canvasItem->getSrcRect().w;
                fillRectDest.h = canvasItem->getSrcRect().h;
                fillRectDest.x = 0;
                fillRectDest.y = 0;
                //STARTING IN TOP RIGHT CORNER OF TILE-MAP WILL FILL COLUMNS RIGHT->LEFT

                //Iterate over as many times as you can fit tile in x-axis, plus 1 (for good measure)
                for(int i = 1 + (int)(canvasItem->getFillW()/canvasItem->getSrcRect().w); i > 0; i--){
                    fillRectDest.x += canvasItem->getSrcRect().x;

                    //Iterate over as many times as you can fit tile in y-axis, plus 1 (for good measure)
                    for(int j = 1 + (int)(canvasItem->getFillH()/canvasItem->getSrcRect().y); j > 0; j--){
                        fillRectDest.y += canvasItem->getSrcRect().y;
                        TextureHandler::Draw(canvasItem->getTexturePtr(),canvasItem->getSrcRect(),fillRectDest);
                    }
                }
            }
            //Render simple object
            else{
                TextureHandler::Draw(canvasItem->getTexturePtr(),
                                     canvasItem->getSrcRect(),
                                     canvasItem->getDestRect());
            }

        }
    }
}

void CanvasSystem::Canvas::genCanvasFromLevel(const char * path) {
    nlohmann::json json;
    try {
        json = nlohmann::json::parse(std::fstream(path), nullptr, true, true)["canvas"];
        for (auto canvasItem = json.begin(); canvasItem != json.end(); ++canvasItem){
            auto canvasLayer = canvasItem.value()["layer"].get<std::string>();
            auto canvasTexture = canvasItem.value()["texture"].get<std::string>();
            this->createCanvasItem(
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

int CanvasSystem::Canvas::convertStringToLayer(std::string &input) {
    if(input == "front") return FRONT;
    else if(input == "background") return BACKGROUND;
    else if(input == "middle_front") return MIDDLE_FRONT;
    else if(input == "middle_back") return MIDDLE_BACK;
    else throw std::invalid_argument("Received invalid string " + input + " that could not be parsed");
}