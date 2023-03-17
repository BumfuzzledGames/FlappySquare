cmake_minimum_required(VERSION 3.0.0)
project(FlappySquare VERSION 0.1.0)
find_package(SDL2 REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c17 -Wall -Wextra -Wshadow -Werror -pedantic")

add_executable(FlappySquare main.c font.c)
target_link_libraries(FlappySquare SDL2::SDL2main SDL2::SDL2)
