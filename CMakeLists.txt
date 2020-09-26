cmake_minimum_required(VERSION 3.17)
project(Project2DTD)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(JSON_BuildTests OFF CACHE INTERNAL "")

include(FindPkgConfig)
include(FetchContent)
include_directories(src)

add_subdirectory(nlohmann_json)

#SDL2
FetchContent_Declare(
        SDL2
        GIT_REPOSITORY "https://github.com/SDL-mirror/SDL.git"
        GIT_TAG        "release-2.0.12"
)
FetchContent_Declare(
        SDL_IMAGE
        GIT_REPOSITORY "https://github.com/SDL-mirror/SDL_image.git"
        GIT_TAG        "release-2.0.5"
)
FetchContent_Declare(
        LUA
        GIT_REPOSITORY "https://github.com/LuaDist/lua.git"
        GIT_TAG        "5.3.2"
)
FetchContent_MakeAvailable(SDL2 SDL_IMAGE LUA)

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
        src/LevelLoader.h
        src/lua.h)

#Add the library
target_link_libraries(${PROJECT_NAME} SDL2 SDL_IMAGE LUA nlohmann_json::nlohmann_json)