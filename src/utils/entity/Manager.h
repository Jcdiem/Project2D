#pragma once
#ifndef BUILD_MANAGER_H
#define BUILD_MANAGER_H

#include "Entity.h"
#include "../MicroLuaProcessor.h"
#include "../QueueingThread.h"

#include <vector>
#include <map>

namespace Manager {
    namespace {
        std::vector<Entity> entities;
        std::map<int, std::string> cachedInitScripts;
        QueueingThread qthread = QueueingThread(255);
    }

    void initialize();

    void newEntity(int id);

    void cacheEntities();
}


#endif //BUILD_MANAGER_H
