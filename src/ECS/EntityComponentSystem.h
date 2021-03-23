#pragma once
#ifndef PROJECT2DTD_ENTITYCOMPONENTSYSTEM_H
#define PROJECT2DTD_ENTITYCOMPONENTSYSTEM_H
#include <utility>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <iostream>
#include <thread>

#include "QueueingThread.h"

// Design pattern by Vittorio Romeo
// https://vittorioromeo.info/

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;

//Gives out an incrementing ID For each time ran
inline ComponentID getComponentTypeId(){
    static ComponentID  lastID = 0; //Store the last ID
    return lastID++; //Give out the next ID
}

template <typename type> inline ComponentID getComponentTypeId() noexcept{
    static ComponentID typeID = getComponentTypeId(); //Get an ID from the ticketing system
    return typeID;
}

constexpr std::size_t maxComponents = 32; //Max classes an entity can have

using componentBitSet = std::bitset<maxComponents>; //Sets the bitmask for Components
using componentArray = std::array<Component*,maxComponents>; //Array of pointers for Components






//interface for Component
class Component{
public:
    Entity* entity{};

    virtual void init(){}
    virtual void update(){}
    virtual void draw(){}

    virtual ~Component()= default;
};






//Entity interface
class Entity{
public:
    void update(){
        //iterate through all the Components and tell them to draw/update
        for (auto& component : componentList) component->update();
    }
    void draw(){
        for (auto& component : componentList) component->draw();
    }
    [[nodiscard]] bool isActive() const {
        return active;
    }
    void destroy(){
        active = false;
    }

    template<typename type> [[nodiscard]] bool hasComponent() const{
        return compBitSet[getComponentTypeId < type >]; //Return : Does entity have type component?
    }

    template <typename type, typename... TypeArgs> //Follows to next line
    type& addComponent(TypeArgs&&... mArgs){
        type* component( //Make a component type
                new type(std::forward<TypeArgs>(mArgs)...) //Give it arguments
        );
        component->entity = this; //Set the Components entity to this instance of an entity
        std::unique_ptr<Component> uniquePtr{component}; //Make a pointer for component
        componentList.emplace_back(std::move(uniquePtr));//Push the component to the back of the list of Components

        compArray[getComponentTypeId<type>()] = component; //Add component to array of related Components
        compBitSet[getComponentTypeId<type>()] = true; //Set the bit for this component being used with the entity (For masking)

        component->init();

        return *component;
    }

    template<typename type> type& getComponent() const{
        auto ptr(compArray[getComponentTypeId<type>()]); //Get the pointer of component in array
        return *static_cast<type*>(ptr); //return pointer of component
    }

    void setName(std::string name) {
        this->name = std::move(name);
    }

    std::string getName() {
        return name;
    }

    void setParent(Entity* parent) {
        this->parent = parent;
    }

    Entity* getParent() {
        return parent;
    }

    void addChild(Entity* child) {
        children.push_back(child);
    }

    std::vector<Entity*> getChildren() {
        return children;
    }

private:
    std::string name;
    Entity* parent;
    std::vector<Entity*> children;

    bool active = true;
    std::vector<std::unique_ptr<Component>> componentList;

    componentArray compArray{};
    componentBitSet compBitSet;
};

class Manager{
public:
    void multithreaded_update(int maxThreads){
        while(maxThreads < int(threads.size())) {
            threads.back()->halt();
            threads.pop_back();
        }
        while(maxThreads > int(threads.size())) {
            threads.push_back(new QueueingThread<Entity>(-1));
            //The higher the que size the higher the memory usage. -1 for no limit (Not recommended)
        }

        int perThread = int(entityList.size()) / maxThreads;

        int i = 0;
        int j = 0;
        for(; i < maxThreads - 1; i++) {
            for(; j - i*perThread < perThread; j++) {
                threads[i]->que(entityList[j].get());
            }
        }

        for(; j < int(entityList.size()); j++) {
            threads[i]->que(entityList[j].get());
        }
    }

    void update(){
        for (auto& entity : entityList) entity->update();
    }

    void draw(){
        for (auto& entity : entityList) entity->draw();
    }

    void refresh(){ //Delete inactive entities
        entityList.erase(std::remove_if(std::begin(entityList),std::end(entityList),
                                        [](const std::unique_ptr<Entity> &mEntity){
            return !mEntity->isActive();
        }),
               std::end(entityList));
    }

    std::vector<std::unique_ptr<Entity>>* getEntityList() {
        return &entityList;
    }

    Entity& addEntity(){
        unsigned int lastSize = entityList.size();
        auto* entityPtr = new Entity();
        std::unique_ptr<Entity> uniquePtr(entityPtr);
        entityList.emplace_back(std::move(uniquePtr));

        if(lastSize == entityList.size()) {
            std::throw_with_nested(std::runtime_error("Error creating entity"));
        }

        return *entityPtr;
    }

    void setWW(int width) {
        windowW = width;
    }

    void setWH(int height) {
        windowH = height;
    }

    int getWW() const {
        return windowW;
    }

    int getWH() const {
        return windowH;
    }

private:
    std::vector<std::unique_ptr<Entity>> entityList; //List of entity pointers
    std::vector<QueueingThread<Entity>*> threads;

    int windowW;
    int windowH;
};

#endif //PROJECT2DTD_ENTITYCOMPONENTSYSTEM_H
