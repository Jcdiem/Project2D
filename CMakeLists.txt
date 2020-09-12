cmake_minimum_required(VERSION 3.17)
project(Project2DTD)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


INCLUDE(FindPkgConfig)
include_directories(.)
include_directories(assets)

#Add the SDL2 and SDL_Image libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

#Include the dependecy directories
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(Project2DTD
        src/assets/dvd.png
        src/assets/dvdbe.png
        src/assets/mapTex0.png
        src/assets/mapTex1.png
        src/assets/mapTex2.png
        src/Engine.cpp
        src/Engine.h
        src/EntityType.cpp
        src/EntityType.h
        src/main.cpp
        src/TextureHandler.cpp
        src/TextureHandler.h
        src/TextureMap.cpp
        src/TextureMap.h)

#Add the libraries
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})