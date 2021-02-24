#ifndef PROJECT2DTD_LEVELLOADER_H
#define PROJECT2DTD_LEVELLOADER_H
#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "TextureHandler.h"
#include "ECS/Components.h"
#include "ECS/AnimStruct.h"

class JParser {
public:
    explicit JParser(Manager *manager);

    //Used to generate objects and levels
    static void genLevelList();
    void genObjs(const char* levelPath);
    static const char* getLevel(int levelNum);


    //Used for engine settings
    static std::string getTitle();
    static int getXSize();
    static int getYSize();
    static bool getFullscreen();
    static bool getResizable();
    static int getTPS();
    static int getFPS();
private:
    void objFromJson(const char* path);
    Manager *eManager;
    static std::vector<std::string> levelList;
};

#endif //PROJECT2DTD_LEVELLOADER_H
