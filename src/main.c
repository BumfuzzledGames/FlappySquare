/***********************************************************
 * Flappy Square 
 * (C) 2023 Bumfuzzled Games <bumfuzzled.games@gmail.com>
 *
 * This program is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, see
 * <https://www.gnu.org/licenses/>.
 **********************************************************/
#include <SDL.h>
#include <time.h>
#include "font.h"
#include "screen.h"
#include "screens/start.h"
#include "window.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif // __EMSCRIPTEN__

int main(int argc, char *argv[]) { (void)argc; (void)argv;
    // Seed PRNG
    srand(time(0));

    // Initialize SDL, create window and renderer, load font.
    // Exit program if any of them fail
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
        SDL_Log("SDL_Init: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    create_window();
    load_font();

    enter_start_screen();

    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(run_current_screen, 0, 1);
    #else // __EMSCRIPTEN__
    while(1) { run_current_screen(); }
    #endif // __EMSCRIPTEN__

    return 0;
}