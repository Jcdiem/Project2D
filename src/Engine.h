#pragma once
#ifndef PROJECT2DTD_ENGINE_H
#define PROJECT2DTD_ENGINE_H

#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

#include "utils/Flagger.h"

#include "utils/draw/Sprite.h" //TEMP
#include "utils/Canvas.h"

enum Systems {
    render,
    update,
    listen,
    all,
    bundled,
};

class Engine {
public:
    /*!
     * @brief Constructor for the game engine, that uses flags from utils/flagger
     */
    Engine();

    /*!
     * @brief Constructor for the game engine
     * @param title The name to present for the game/project
     * @param width Width in pixels of the window
     * @param height Height in pixels of the window
     * @param fullscreen True/False for whether to load fullscreen
     */
    Engine(const std::string& title, int width, int height, bool fullscreen, bool vsync);

    /*!
     * @brief Destructor used to destroy the sfml window and join any threads that need joining.
     */
    ~Engine();

    /*!
     * @brief Initializes the whole engine systems, should only be run once
     * @param system The systems to be initialized
     * @param tickrate the tickrate the engine should run at
     */
    void initSystem(Systems system, int tickrate); //Takes a enum to select which system to init

    /*!
     * @brief Used to handle various sfml events, currently only exits, but could be more!
     */
    void listen();

    /*!
     * @brief Update all manager calls
     */
    void update();

    /*!
     * @brief Call the rendering of all objects that need to be displayed
     */
    void render();

    /*!
     * @brief Call each of the system functions seen above in this order (Listen, Update, Render)
     */
    void bundledSystems();

    /*!
     * @brief Handles exit operations that need to be done before the destructor
     */
    void quit();

    /*!
     * @brief calls the engine function tickrate times per second, and attempts to account for lag.
     * @param system System to monitor with clock
     * @param tickrate How many times per second to call the engine function
     */
    void clockRunner(void (Engine::*system)(), int tickrate);
private:
    /*!
     * @brief Threads for each system (-1)
     */
    std::thread systems[2];

    /*!
     * @brief Bool for whether the application is meant to be running
     */
    bool isRunning;

    /*!
     * @brief Variable to hold the most recent SFML event
     */
    sf::Event event;

    /*!
     * @brief The application window itself
     */
    sf::RenderWindow* window;

    /*!
     * @brief The canvas used for rendering
     */
     Canvas canvas = Canvas();
};

#endif //PROJECT2DTD_ENGINE_H