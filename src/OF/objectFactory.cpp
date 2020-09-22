#include <iostream>
#include "objectFactory.h"
using json = nlohmann::json;

std::vector<const char*> objectFactory::objList;

const char *nullObj = "src/assets/objects/null.json";

void objectFactory::genObjList() {
    json file;
    try {
        file = json::parse(std::fstream("assets/objects/objectList.json"), nullptr, true, true)["objects"][0];
    }
    catch(json::exception &e) {
        std::throw_with_nested(std::runtime_error("Object list could not be found or it was improperly formatted."));
    }

    for (auto obj = file.begin(); obj != file.end(); ++obj)
    {
        try{
            objList.emplace_back(&std::string(obj.value())[0]);
        }
        catch(...) {
            std::cout << "Failed to get object path, does it exist?" << std::endl;
            objList.emplace_back(nullObj);
        }
    }
}