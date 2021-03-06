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
}

std::map<std::string, int> Json::jsonToMap(const std::string &path) {
    try {
        nlohmann::json file = nlohmann::json::parse(std::fstream(path), nullptr, true, true);
        std::map<std::string, int> output;

        for(auto& [key, value] : file.items()) {
            output[key] = value;
        }

        return output;
    } catch(std::exception& e) {
        Logger::print(Level::ERROR, "Failed to convert json file \"", path, "\" to a map: ", e.what());
        throw e;
    }
}

void Json::mapToJson(const std::map<std::string, int> &map, const std::string &path) {
    nlohmann::json json;
    for(const auto& elem : map) {
        json[elem.first] = elem.second;
    }

    std::ofstream file(path);
    file << json;
}
