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

FetchContent_Declare(JSON
        GIT_REPOSITORY "https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git"
        GIT_TAG        "391786c6c3abdd3eeb993a3154f1f2a4cfe137a0")

FetchContent_GetProperties(JSON)
if(NOT JSON_POPULATED)
    FetchContent_Populate(JSON)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

set(SOURCE_FILES
        src/ECS/Components.h
        src/ECS/EntityComponentSystem.h
        src/ECS/PositionComponent.h
        src/ECS/SpriteComponent.h
        src/Engine.h
        src/LevelLoader.h
        src/TextureHandler.h
        src/TextureMap.h
        src/TEngine.h
        src/Engine.cpp
        src/LevelLoader.cpp
        src/TextureHandler.cpp
        src/TextureMap.cpp
        src/TEngine.cpp)

add_executable(P2D ${SOURCE_FILES} src/main.cpp)

#Add the libraries
target_link_libraries(P2D PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${CMAKE_DL_LIBS} nlohmann_json::nlohmann_json)