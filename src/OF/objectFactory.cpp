#include <iostream>
#include "objectFactory.h"
using json = nlohmann::json;

std::vector<const char*> objectFactory::objList;

const char *nullObj = "src/assets/objects/null.json";

void objectFactory::genObjList() {
    json file;
    try {
        file = json::parse(std::fstream("assets/objects/objectList.json"), nullptr, true, true)["objects"];
    }
    catch(json::exception &e) {
        std::throw_with_nested(std::runtime_error("Object list could not be found or it was improperly formatted."));
    }

    for(int i = 0; i != file.size(); ++i) {
        try{
            auto path = file[i]["path"].get<std::string>();
            objList.emplace_back(&path[0]);
        }
        catch(...) {
            objList.emplace_back(nullObj);
        }
    }
}