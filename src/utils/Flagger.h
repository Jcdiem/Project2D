#pragma once
#ifndef PROJECT2D_FLAGGER_H
#define PROJECT2D_FLAGGER_H

#include <map>
#include <string>

#include "Logger.h"

class Flagger {
public:
    Flagger() = delete; //Remove constructor and destructor
    ~Flagger() = delete;

    static void parse(int argc, char *argv[]);
    static int find(const std::string& flag);
    static void set(const std::string& flag, int value);
    static std::map<std::string, int>* getInternal();

private:
    static int parseString(std::string number);
    static std::map<std::string, int> flags;
};


#endif //PROJECT2D_FLAGGER_H
