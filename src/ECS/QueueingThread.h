#pragma once
#ifndef PROJECT2D_QUEINGTHREAD_H
#define PROJECT2D_QUEINGTHREAD_H

#include <queue>
#include <thread>

template<typename type>
class QueueingThread {
public:
    QueueingThread() {
        thread = std::thread(&QueueingThread<type>::taskRunner, this);
    }

    void halt() { //Shouldn't be needed? Default destructor should join the thread
        run = false;
        thread.join();
    }

    void que(type* entity) {
        queue.push(entity);
    }
private:
    void taskRunner() {
        while(run) {
            if(!queue.empty()) {
                queue.front()->update();
                queue.pop();
            }
        }
    }

    bool run = true;

    std::thread thread;
    std::queue<type*> queue;
};

#endif //PROJECT2D_QUEINGTHREAD_H
