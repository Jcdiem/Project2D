#include "InputManager.h"

const std::string configFile = "assets/keybinds.json";

InputManager::InputManager():keystate(SDL_GetKeyboardState(NULL)){}

void InputManager::addBinding(std::string action) {
    actionList.emplace_back(action);
}

bool InputManager::isPressed(std::string action) {
    return keystate[keybinds[action]];
}

void InputManager::refreshBindings() {
    for(std::string action : actionList) {
        keybinds[action] = getValue<int>(configFile, action);
    }
}