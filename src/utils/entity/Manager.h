#ifndef BUILD_MANAGER_H
#define BUILD_MANAGER_H

#include "Entity.h"
#include "../QueueingThread.h"

#include <vector>

namespace Manager {
    namespace {
        std::vector<Entity> entities;
        QueueingThread thread = QueueingThread(255);
    }

    void cacheEntities();
}


#endif //BUILD_MANAGER_H
