#include "TEngine.h"

TEngine::TEngine() = default;
TEngine::~TEngine() = default;

int TEngine::run(const char* file) {
    chai.eval_file(file);
    chai.eval_file("assets/scripts/test1.chai")
    return 0;
}