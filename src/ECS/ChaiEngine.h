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

        chai.add(chaiscript::fun(&ChaiEngine::hello_world, this), "hello_world");
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

    //CHAI SYSTEM FUNCTIONS \/\/\/\/\/\/\/\/\/
    std::string hello_world() {
        return "Hello World!";
    }

    //TODO: Use the manager pointer to access other entities
    //CHAI SYSTEM FUNCTIONS /\/\/\/\/\/\/\/\/\

private:
    chaiscript::ChaiScript chai;
    Manager* manager;
    std::string script;
};


#endif //P2D_CHAIENGINE_H
