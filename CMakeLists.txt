cmake_minimum_required(VERSION 3.0.0)
project(FlappySquare VERSION 0.0.1)
find_package(SDL2 REQUIRED)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c17 -Wall -Wextra -Wshadow -Werror -pedantic")

add_executable(FlappySquare main.c font.c)
target_link_libraries(FlappySquare SDL2::SDL2main SDL2::SDL2)

install(TARGETS FlappySquare RUNTIME DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin/FlappySquare")
install(FILES $<TARGET_RUNTIME_DLLS:FlappySquare> DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin/FlappySquare")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
