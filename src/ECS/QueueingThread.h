#pragma once
#ifndef PROJECT2D_QUEUEINGTHREAD_H
#define PROJECT2D_QUEUEINGTHREAD_H

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template<typename type>
class QueueingThread {
public:
    QueueingThread(int maxQue) {
        thread = std::thread(&QueueingThread<type>::taskRunner, this);
        this->maxQue = maxQue;
    }

    void halt() { //Shouldn't be needed? Default destructor should join the thread
        run = false;
        thread.join();
    }

    void que(type* entity) {
        if(int(queue.size()) < maxQue || maxQue == -1) {
            queue.push(entity);

            if(locked) {
                empty.notify_all();
            }
        } else {
            std::cout << "Thread que is too long, are you lagging? dropping items... (" << maxQue << ")" << std::endl;
        }
    }

private:
    void taskRunner() {
        while(run) {
            if(queue.empty()) {
                locked = true;
                std::unique_lock<std::mutex> lck(mtx);
                empty.wait(lck);
            }

            queue.front()->update();
            queue.pop();
        }
    }

    int maxQue;

    bool run = true;
    bool locked = false;

    std::mutex mtx;
    std::condition_variable empty;

    std::thread thread;
    std::queue<type*> queue;
};

#endif //PROJECT2D_QUEUEINGTHREAD_H
