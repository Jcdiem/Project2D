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
        std::map<int, std::string> cachedInitScripts;
        QueueingThread qthread = QueueingThread(255);
    }

    void initialize();

    void newEntity(int id);

    void cacheEntities();
}


#endif //PROJECT2D_MANAGER_H
