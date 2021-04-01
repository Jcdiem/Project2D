cmake_minimum_required(VERSION 3.6)

project(P2D)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(${nlohmann_json_source}
        libs/json)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)


file(GLOB SOURCES
    src/Main.cpp
    src/Engine.cpp
)

add_executable(P2D ${SOURCES})
target_link_libraries(P2D sfml-graphics sfml-audio)

target_link_libraries(P2D nlohmann_json::nlohmann_json)