#include <iostream>
#include "objectFactory.h"
using json = nlohmann::json;

void objectFactory::genObjList() {
    auto file = json::parse(std::fstream("assets/objects/objectList.json"))["objects"];//[0]["path"]
    for(auto i = 0; i != file.size(); ++i) {
        auto path = file[i]["path"].get<std::string>();
        objList.emplace_back(path);
    }

    for(std::string string : objList){
        std::cout << string << std::endl;
    }
}