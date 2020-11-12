cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(P2D VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(SOURCE_FILES
        src/ECS/Components.h
        src/ECS/EntityComponentSystem.h
        src/ECS/PositionComponent.h
        src/ECS/SpriteComponent.h
        src/Engine.h
        src/LevelLoader.h
        src/LuaScripter.h
        src/TextureHandler.h
        src/TextureMap.h
        src/Engine.cpp
        src/LevelLoader.cpp
        src/TextureHandler.cpp
        src/TextureMap.cpp
)

add_executable(P2D ${SOURCE_FILES} src/main.cpp)

#Add the libraries
target_link_libraries(P2D PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})