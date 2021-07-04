#include "json.h"

void json::initDefaultFlags(std::string filePath) {
    nlohmann::json file = nlohmann::json::parse(std::fstream(filePath), nullptr, true, true);

    std::string settings[] = {"xRes",
                              "yRes",
                              "framerate",
                              "fullscreen"};

    for(std::string setting : settings) {
        flagger::newFlag(setting, getValue<int>(file, setting));
    }

    //HARDCODED FLAGS BELOW!!!
    //None for now, things like threads and such would go here
}
