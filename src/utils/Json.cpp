#include "Json.h"

void Json::initDefaultFlags(const std::string& path) {
    nlohmann::json file = nlohmann::json::parse(std::fstream(path), nullptr, true, true);

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

std::map<std::string, int> Json::jsonToMap(const std::string &path) {
    nlohmann::json file = nlohmann::json::parse(std::fstream(path), nullptr, true, true);
    std::map<std::string, int> output;

    for(auto& [key, value] : file.items()) {
        try {
            output[key] = value;
        } catch(std::exception& e) {
            Logger::print(Level::ERROR, "Failed to convert json file \"", path, "\" to a map: ", e.what());
        }
    }

    return output;
}

void Json::mapToJson(const std::map<std::string, int> &map, const std::string &path) {
    nlohmann::json json;
    for(const auto& elem : map) {
        json[elem.first] = elem.second;
    }

    std::ofstream file(path);
    file << json;
}
