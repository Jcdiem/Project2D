#ifndef P2D_CHAIENGINE_H
#define P2D_CHAIENGINE_H

#include <chaiscript/chaiscript.hpp>

#include "EntityComponentSystem.h"

class ChaiEngine {
public:
    ChaiEngine(Manager* manager) {
        this->manager = manager;
        chai.add(chaiscript::fun(&ChaiEngine::hello_world, this), "hello_world");
    }

    void run(const char* path) {
        try {
            chai.eval_file(path);
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
};


#endif //P2D_CHAIENGINE_H
