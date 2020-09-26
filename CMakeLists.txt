cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(Project2DTD)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(JSON_BuildTests OFF CACHE INTERNAL "")

include(FetchContent)
include_directories(src)

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY "https://github.com/SDL-mirror/SDL.git"
        GIT_TAG        "76468465a94b59f0dde4791846bc2476be4f245f"
)
FetchContent_Declare(
        SDL_image
        GIT_REPOSITORY "https://github.com/SDL-mirror/SDL_image"
        GIT_TAG        "b4f28c1fc9ab2f91ae594fc3e86622c5c13ffbbb"
)
FetchContent_Declare(
        LUA
        GIT_REPOSITORY "https://github.com/LuaDist/lua.git"
        GIT_TAG        "fcdc5efb13f0d6c03d2868b7476b73e63a291ed3"
)
FetchContent_Declare(
        JSON
        GIT_REPOSITORY "https://github.com/nlohmann/json.git"
        GIT_TAG        "db78ac1d7716f56fc9f1b030b715f872f93964e4"
)

FetchContent_MakeAvailable(SDL2 SDL_image LUA JSON)

include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

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
target_link_libraries(${PROJECT_NAME} SDL2 SDL_image LUA nlohmann_json::nlohmann_json)