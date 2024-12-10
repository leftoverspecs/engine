cmake_minimum_required(VERSION 3.30)
project(engine CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_net REQUIRED CONFIG)

add_library(engine STATIC
    networking/client.hpp
    networking/client.cpp
    networking/server.hpp
    networking/server.cpp
    networking/transmit.hpp
    networking/transmit.cpp)
target_link_libraries(engine PUBLIC SDL2::SDL2 SDL2_net::SDL2_net)