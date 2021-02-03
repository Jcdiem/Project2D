#ifndef P2D_CHAIENGINE_H
#define P2D_CHAIENGINE_H

#include <chaiscript/chaiscript.hpp>
#include <fstream>
#include <string>

#include "EntityComponentSystem.h"

class ChaiEngine {
public:
    ChaiEngine(Manager* manager, char* path) {
        this->manager = manager;

        std::ifstream file(path);
        if(file) {
            std::ostringstream fileContent;
            fileContent << file.rdbuf(); // reading data
            script = fileContent.str();
        }
    }

    void run() {
        try {
            chai.eval(script);
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    chaiscript::ChaiScript* brew() {
        return &chai;
    }

private:
    chaiscript::ChaiScript chai;
    Manager* manager;
    std::string script;
};


#endif //P2D_CHAIENGINE_H
