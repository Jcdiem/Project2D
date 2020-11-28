#ifndef PROJECT2DTD_LEVELLOADER_H
#define PROJECT2DTD_LEVELLOADER_H
#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "TextureHandler.h"
#include "ECS/Components.h"

class JParser {
public:
    explicit JParser(Manager *manager);
    static void genLevelList();
    void genObjs(const char* levelPath);
    static const char* getLevel(int levelNum);
private:
    void objFromJson(const char* path);
    Manager *eManager;
    static std::vector<std::string> levelList;
};

#endif //PROJECT2DTD_LEVELLOADER_H
