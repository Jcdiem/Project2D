cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(P2D VERSION 0.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(FetchContent)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

FetchContent_Declare(SDL2
        GIT_REPOSITORY "https://github.com/SDL-mirror/SDL.git"
        GIT_TAG        "76468465a94b59f0dde4791846bc2476be4f245f")

FetchContent_Declare(SDL2_image
        GIT_REPOSITORY "https://github.com/SDL-mirror/SDL_image"
        GIT_TAG        "b4f28c1fc9ab2f91ae594fc3e86622c5c13ffbbb")

FetchContent_Declare(JSON
        GIT_REPOSITORY "https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git"
        GIT_TAG        "391786c6c3abdd3eeb993a3154f1f2a4cfe137a0")

FetchContent_Declare(CHAISCRIPT
        GIT_REPOSITORY "https://github.com/ChaiScript/ChaiScript.git"
        GIT_TAG        "ac0d7ce94925f8eac367533b276d9d7db13a77ae")

FetchContent_GetProperties(SDL2)
FetchContent_GetProperties(SDL2_image)
FetchContent_GetProperties(JSON)
FetchContent_GetProperties(CHAISCRIPT)

if(NOT SDL2_POPULATED)
    FetchContent_Populate(SDL2)
    add_subdirectory(${sdl2_SOURCE_DIR} ${sdl2_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

if(NOT SDL2_image_POPULATED)
    FetchContent_Populate(SDL2_image)
    include_directories(${sdl2_image_SOURCE_DIR} ${sdl2_image_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

if(NOT JSON_POPULATED)
    FetchContent_Populate(JSON)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

if(NOT CHAISCRIPT_POPULATED)
    FetchContent_Populate(CHAISCRIPT)
    add_subdirectory(${chaiscript_SOURCE_DIR} ${chaiscript_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

set(SOURCE_FILES
        src/ECS/Components.h
        src/ECS/EntityComponentSystem.h
        src/ECS/PositionComponent.h
        src/ECS/SpriteComponent.h
        src/ECS/ChaiEngine.h
        src/Engine.h
        src/JParser.h
        src/TextureHandler.h
        src/TextureMap.h
        src/Engine.cpp
        src/JParser.cpp
        src/TextureHandler.cpp
        src/TextureMap.cpp)

add_executable(P2D ${SOURCE_FILES} src/main.cpp)

#Add the libraries
target_link_libraries(P2D PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${CMAKE_DL_LIBS} nlohmann_json::nlohmann_json)