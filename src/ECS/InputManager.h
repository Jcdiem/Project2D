#pragma once
#ifndef PROJECT2D_INPUTMANAGER_H
#define PROJECT2D_INPUTMANAGER_H

#include <SDL2/SDL.h>
#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

class InputManager {
public:
    InputManager();

    void addBinding(std::string action);
    bool isPressed(std::string action);
    void refreshBindings();
private:
    std::map<std::string, std::vector<int>> keybinds;
    std::vector<std::string> actionList;

    //Basic function to get json values.
    template<typename type>
    type getValue(std::string filePath, std::string key) {
        nlohmann::json file = nlohmann::json::parse(std::fstream(filePath), nullptr, true, true);
        return file[key].get<type>();
    }

    const Uint8 *keystate;
};

#endif //PROJECT2D_INPUTMANAGER_H
