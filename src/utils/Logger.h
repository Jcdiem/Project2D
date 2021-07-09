#pragma once
#ifndef BUILD_LOGGER_H
#define BUILD_LOGGER_H

#include <iostream>
#include <cstdarg>
#include <string>

//TODO: Automatically send all output to log files
enum Level {
    INFO,
    WARN,
    ERROR
};

namespace Logger {
    template<typename... Details>
    void print(Level lvl, Details... details)  {
        switch(lvl){ //HERE BE MAGIC, see here: https://stackoverflow.com/a/49435122
            case INFO:
                std::cout << "[INFO]: ";
                (std::cout << ... << details) << std::endl;
                break;
            case WARN:
                std::clog << "[WARN]: ";
                (std::clog << ... << details) << std::endl;
                break;
            case ERROR:
                std::cerr << "[ERROR]: ";
                (std::cerr << ... << details) << std::endl;
                break;
        }
    }
};


#endif //BUILD_LOGGER_H
