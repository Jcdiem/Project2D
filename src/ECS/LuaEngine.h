#pragma once
#ifndef PROJECT2D_LUAENGINE_H
#define PROJECT2D_LUAENGINE_H

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

//Singleton stolen gracefully from here: https://stackoverflow.com/questions/1008019/c-singleton-design-pattern

class LuaEngine
{
public:
    LuaEngine();

    void initScript(const std::string& script);
    void runScript();
    void updScript(const std::string& script);

    sol::state* gLu();

    template<typename type>
    void newVar(std::string name, type value) {
        lua[name] = value;
    }

private:
    sol::state lua;
};


#endif //PROJECT2D_LUAENGINE_H
