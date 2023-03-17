cmake_minimum_required(VERSION 3.0.0)
project(FlappySquare VERSION 0.0.2)
find_package(SDL2 REQUIRED)

set(
    SRC
    src/draw.c
    src/event.c
    src/font.c
    src/main.c
    src/screen.c
    src/util.c
    src/window.c
    src/screens/game_over.c
    src/screens/game.c
    src/screens/start.c
)

add_executable(FlappySquare ${SRC})
target_link_libraries(
    FlappySquare
    SDL2::SDL2main SDL2::SDL2
)

set(
    CFLAGS
    -std=c17
    -Wall -Wextra -Wshadow -Werror
    -pedantic
    -fanalyzer
)

target_compile_options(
    FlappySquare
    PUBLIC $<$<CONFIG:DEBUG>:${CFLAGS} -O0>
    PUBLIC $<$<CONFIG:RELEASE>:${CFLAGS}>
)

# Hide console on Windows release builds
if(WIN32)
    set_target_properties(
        FlappySquare
        PROPERTIES
        LINK_FLAGS_DEBUG "-mconsole"
        LINK_FLAGS_RELEASE "-mwindows"
        LINK_FLAGS_RELWITHDEBINFO "-mwindows"
        LINK_FLAGS_MINSIZEREL "-mwindows"
    )
endif(WIN32)


set(INSTALLDIR "${CMAKE_CURRENT_BINARY_DIR}/bin/FlappySquare")
install(
    TARGETS FlappySquare
    RUNTIME DESTINATION "${INSTALLDIR}"
)
install(
    FILES $<TARGET_RUNTIME_DLLS:FlappySquare>
    DESTINATION "${INSTALLDIR}"
)