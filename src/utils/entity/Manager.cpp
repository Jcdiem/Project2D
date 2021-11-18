#include "Manager.h"

void Manager::initialize() {
    LuaProcessor::registerFunction("newEntity", newEntity);
    cacheEntities();
}

void Manager::newEntity(const std::string& type) {
    try {
        std::string* initScript = &cachedEntityScripts.at(type);

        auto newEntity = entities.emplace_back();

        unsigned int objID = LuaProcessor::generateEntity(&newEntity, initScript);
        newEntity.getData()->type = type;
        newEntity.getData()->objID = objID;
    } catch (std::out_of_range& e) {
        Logger::print(ERROR, "Attempted to create entity of id ", type,
                      " which does not exist, or hasn't been cached yet...");
    }
}

void Manager::cacheEntities() {
    std::filesystem::path objectDir = "assets/objects/";

    for(auto& item : std::filesystem::recursive_directory_iterator(objectDir)) {
        //Iterate over all paths in the directory specified above, recursively.

        if(!item.is_directory()) { //We only care about items that aren't directories.
            std::string ext = item.path().extension();
            std::string stem = item.path().stem();

            if(item.file_size() > 128000000) {
                Logger::print(ERROR, "Script larger than 128 MB (", item.path(), ") it will be ignored...");
            } else if(ext == ".lua") {
                std::ifstream t(objectDir);
                std::stringstream buffer;
                buffer << t.rdbuf();

                cachedEntityScripts[stem] = buffer.str(); //ID is the name of the file, and the script is
                                                          //that file's contents. As long as the file's extension
                                                          //is .lua it will be added. Don't feed it huge files.
                                                          //that would make me sad...
            }
        }
    }
}
