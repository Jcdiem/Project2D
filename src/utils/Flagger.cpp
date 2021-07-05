#include "Flagger.h"

std::map<std::string, int> Flagger::flags;

int Flagger::parseString(std::string number) {
    if(number == "true") return 1;
    if(number == "false") return 0;

    try {
        return std::stoi(number);
    } catch(std::exception &e) {
        Logger::print(Level::WARN, "Can't parse \"" + number + "\"");
    }

    return -1;
}

void Flagger::parse(int argc, char *argv[]) {
    for(int i = 2; i < argc; i += 2) { //First arg is always the executable name, so we skip it.
        flags[argv[i - 1] + 1] = parseString(argv[i]);
        //Addition here removes first character :)
    }
}

int Flagger::getFlag(const std::string &flag) {
    try {
        return flags[flag];
    } catch(std::exception& e) {
        Logger::print(Level::WARN, "Unset flag: ", flag);
        return 0;
    }
}

void Flagger::newFlag(const std::string& flag, int value) {
    flags[flag] = value;
}

void Flagger::newFlag(const std::string &flag, bool value) {
    flags[flag] = int(value);
}

void Flagger::printFlags() {
    for(const auto& flag : flags) {
        Logger::print(Level::INFO, flag.first, " : ", flag.second);
    }
}

