#include <iostream>
#include "objectFactory.h"
using json = nlohmann::json;

std::vector<char*> objectFactory::objList;

void objectFactory::genObjList() {
    auto file = json::parse(std::fstream("assets/objects/objectList.json"))["objects"];
    for(int i = 0; i != file.size(); ++i) {
        auto path = file[i]["path"].get<std::string>();
        objList.emplace_back(&path[0]);
    }
}