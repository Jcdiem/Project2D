#include "InputManager.h"

const std::string configFile = "assets/keybinds.json";

InputManager::InputManager():keystate(SDL_GetKeyboardState(NULL)){}

void InputManager::addBinding(std::string action) {
    actionList.emplace_back(action);
}

bool InputManager::isPressed(std::string action) {
    for(int key : keybinds[action]) {
        if(!keystate[key]) {
            return false;
        }
    }
    return true;
}

void InputManager::refreshBindings() {
    for(std::string action : actionList) {
        std::vector<int> keyList;
        nlohmann::json arr = getValue<nlohmann::json>(configFile, action);

        for(auto item : arr) {
            keyList.emplace_back(item.get<int>());
        }

        keybinds[action] = keyList;
    }
}