#ifndef P2D_TENGINE_H
#define P2D_TENGINE_H

#include <chaiscript/chaiscript.hpp>

class TEngine {
public:
    TEngine();
    ~TEngine();

    int run(const char* file);

private:
    chaiscript::ChaiScript chai;
};


#endif //P2D_TENGINE_H
