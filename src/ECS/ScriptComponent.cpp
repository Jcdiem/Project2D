#include "ScriptComponent.h"

ScriptComponent::ScriptComponent(Manager* manager, char* path) {
    xPos = 0;
    yPos = 0;
    this->path = path;
    this->manager = manager;
    engineW = manager->getWW();
    engineH = manager->getWH();

    std::ifstream t(path);

    //Finding the end of file
    t.seekg(0, std::ios::end);
    script.reserve(t.tellg());
    t.seekg(0, std::ios::beg);
    //Finding the end of file

    script.assign((std::istreambuf_iterator<char>(t)),
                  std::istreambuf_iterator<char>());
}

ScriptComponent::ScriptComponent(Manager* manager, char* path, int x, int y) {
    xPos = x;
    yPos = y;
    this->path = path;
    this->manager = manager;
    engineW = manager->getWW();
    engineH = manager->getWH();

    std::ifstream t(path);

    //Finding the end of file
    t.seekg(0, std::ios::end);
    script.reserve(t.tellg());
    t.seekg(0, std::ios::beg);
    //Finding the end of file

    script.assign((std::istreambuf_iterator<char>(t)),
                  std::istreambuf_iterator<char>());
}

void ScriptComponent::init() {
    lua.gLu()->set_function("x", &ScriptComponent::x, this);
    lua.gLu()->set_function("y", &ScriptComponent::y, this);
    lua.gLu()->set_function("setX", &ScriptComponent::setX, this);
    lua.gLu()->set_function("setY", &ScriptComponent::setY, this);
    lua.gLu()->set_function("EW", &ScriptComponent::getEW, this);
    lua.gLu()->set_function("EH", &ScriptComponent::getEH, this);

    lua.initScript(script);
}

float ScriptComponent::x() {
    return xPos;
}

float ScriptComponent::y() {
    return yPos;
}

int ScriptComponent::getEW() {
    return engineW;
}

int ScriptComponent::getEH() {
    return engineH;
}

void ScriptComponent::setPos(float x, float y) {
    xPos = x;
    yPos = y;
}

void ScriptComponent::setX(float x) {
    xPos = x;
}

void ScriptComponent::setY(float y) {
    yPos = y;
}

void ScriptComponent::update() {
    lua.runScript();
}