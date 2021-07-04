#include "flagger.h"

std::map<std::string, int> flagger::flags;

int flagger::parseString(std::string number) {
    if(number == "true") return 1;
    if(number == "false") return 0;

    try {
        return std::stoi(number);
    } catch(std::exception &e) {
        logger::print(level::WARN, "Can't parse \"" + number + "\"");
    }

    return -1;
}

void flagger::parse(int argc, char *argv[]) {
    for(int i = 2; i < argc; i += 2) { //First arg is always the executable name, so we skip it.
        flags[argv[i - 1] + 1] = parseString(argv[i]);
        //Addition here removes first character :)
    }
}

void flagger::newFlag(const std::string& flag, int value) {
    flags[flag] = value;
}

void flagger::newFlag(const std::string &flag, bool value) {
    flags[flag] = int(value);
}

void flagger::printFlags() {
    for(std::pair<std::string, int> flag : flags) {
        logger::print(level::INFO, flag.first, " : ", flag.second);
    }
}
