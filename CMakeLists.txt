cmake_minimum_required(VERSION 3.29)

project(renderer)

find_package(SDL2 CONFIG REQUIRED)

add_executable(renderer renderer.c)
target_link_libraries(renderer SDL2::SDL2)
