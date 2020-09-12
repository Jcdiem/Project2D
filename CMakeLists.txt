cmake_minimum_required(VERSION 3.17)
project(Project2DTD)

set(CMAKE_CXX_STANDARD 14)

INCLUDE(FindPkgConfig)
include_directories(.)
include_directories(assets)

#Add the SDL2 and SDL_Image libraries
find_package(SDL2 REQUIRED)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

#Include the dependecy directories
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

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
        src/Sprite.h
        src/TextureHandler.cpp
        src/TextureHandler.h
        src/TextureMap.cpp
        src/TextureMap.h)

#Add the libraries
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})