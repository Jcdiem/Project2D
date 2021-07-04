#pragma once
#ifndef BUILD_FLAGGER_H
#define BUILD_FLAGGER_H

#include <map>
#include <string>

#include "logger.h"

class flagger {
public:
    flagger() = delete; //Remove constructor and destructor
    ~flagger() = delete;

    static void parse(int argc, char *argv[]);
    static void newFlag(const std::string& flag, int value);
    static void newFlag(const std::string& flag, bool value);
    static void printFlags();
    static std::map<std::string, int> flags;

private:
    static int parseString(std::string number);
};


#endif //BUILD_FLAGGER_H
