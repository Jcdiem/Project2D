#pragma once
#ifndef PROJECT2D_QUEUEINGTHREAD_H
#define PROJECT2D_QUEUEINGTHREAD_H

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Logger.h"

class QueueingThread {
public:
    QueueingThread(int maxQue) {
        thread = std::thread(&QueueingThread::taskRunner, this);
        this->maxQue = maxQue;
    }

    void halt() { //Shouldn't be needed? Default destructor should join the thread
        run = false;
        thread.join();
    }

    void que(void (*function)()) {
        if(int(queue.size()) < maxQue || maxQue == -1) {
            queue.push(function);
            empty.notify_all();
        } else {
            Logger::print(Level::WARN, "Thread que is too long, are you lagging? dropping items... (", maxQue, ")");
        }
    }

private:
    void taskRunner() {
        while(run) {
            if(queue.empty()) {
                std::unique_lock<std::mutex> lck(mtx);
                empty.wait(lck);
            } else {
                queue.front()();
                queue.pop();
            }
        }
    }

    int maxQue;

    bool run = true;

    std::mutex mtx;
    std::condition_variable empty;

    std::thread thread;
    std::queue<void (*)()> queue;
};

#endif //PROJECT2D_QUEUEINGTHREAD_H
