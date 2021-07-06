#include "Json.h"

void Json::initDefaultFlags(std::string filePath) {
    nlohmann::json file = nlohmann::json::parse(std::fstream(filePath), nullptr, true, true);

    for(auto& [setting, value] : file.items()) {
        try {
            Flagger::setFlag(setting, int(value));
        } catch(std::exception& e) {
            Logger::print(Level::ERROR, "Option in conf.json \"", setting, "\" holds invalid type, ", e.what());
        }
    }

    //HARDCODED FLAGS BELOW!!!
    //None for now, things like threads and such would go here
}
