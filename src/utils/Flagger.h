#pragma once
#ifndef BUILD_FLAGGER_H
#define BUILD_FLAGGER_H

#include <map>
#include <string>

#include "Logger.h"

class Flagger {
public:
    Flagger() = delete; //Remove constructor and destructor
    ~Flagger() = delete;

    static void parse(int argc, char *argv[]);
    static int getFlag(const std::string& flag);
    static void setFlag(const std::string& flag, int value);
    static void printFlags();

private:
    static int parseString(std::string number);
    static std::map<std::string, int> flags;
};


#endif //BUILD_FLAGGER_H
