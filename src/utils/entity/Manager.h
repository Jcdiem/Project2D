#pragma once
#ifndef PROJECT2D_MANAGER_H
#define PROJECT2D_MANAGER_H

#include "Entity.h"
#include "../LuaProcessor.h"
#include "../QueueingThread.h"

#include <vector>
#include <map>

namespace Manager {
    namespace {
        std::vector<Entity> entities;
        std::map<std::string, std::string> cachedEntityScripts;
    }

    void initialize();

    void newEntity(const std::string& type);
    void newEntity(const std::string& type);

    void cacheEntities();
}


#endif //PROJECT2D_MANAGER_H
