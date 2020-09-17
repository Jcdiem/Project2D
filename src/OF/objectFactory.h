#ifndef PROJECT2DTD_OBJECTFACTORY_H
#define PROJECT2DTD_OBJECTFACTORY_H
#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

class objectFactory {
public:
    static void genObjList();
private:
    static std::vector<std::string> > objList;
};

#endif //PROJECT2DTD_OBJECTFACTORY_H
