#include "engine.h"

#include "flagger.h"
#include "json.h"

int main(int argc, char *argv[]) {
    json::initDefaultFlags("assets/conf.json");
    flagger::parse(argc, argv);
    flagger::printFlags();

    return 0;
}