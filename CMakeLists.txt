cmake_minimum_required(VERSION 3.6)

project(P2D)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(P2D src/Main.cpp)
target_link_libraries(P2D sfml-graphics sfml-audio)
