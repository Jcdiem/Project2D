#ifndef PROJECT2D_LUAENGINE_H
#define PROJECT2D_LUAENGINE_H

//#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

//Singleton stolen gracefully from here: https://stackoverflow.com/questions/1008019/c-singleton-design-pattern

class LuaEngine
{
public:
    LuaEngine();

    void initScript(std::string script);
    void runScript();
    void updScript(std::string script);

    sol::state* gLu();

private:
    sol::state lua;
};


#endif //PROJECT2D_LUAENGINE_H
