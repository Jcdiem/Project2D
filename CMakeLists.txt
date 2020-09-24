cmake_minimum_required(VERSION 3.17)
project(Project2DTD)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(JSON_BuildTests OFF CACHE INTERNAL "")

INCLUDE(FindPkgConfig)
include(FetchContent)
include_directories(.)

add_subdirectory(nlohmann_json)

#Add the required libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

#Include the dependency directories
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(Project2DTD
        src/main.cpp
        src/Engine.cpp
        src/Engine.h
        src/TextureHandler.cpp
        src/TextureHandler.h
        src/ECS/EntityComponentSystem.h
        src/ECS/Components.h
        src/ECS/PositionComponent.h
        src/ECS/SpriteComponent.h
        src/TextureMap.cpp
        src/LevelLoader.cpp
        src/LevelLoader.h)

#Add the library
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} nlohmann_json::nlohmann_json)