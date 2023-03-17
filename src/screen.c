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

#include "screen.h"
#include "util.h"
#include "draw.h"
#include "window.h"
#include <SDL.h>

static SDL_bool first_frame = SDL_TRUE;
static Uint64 last_frame;

static void no_screen(float delta_time) { (void)delta_time; }

static Screen current_screen = no_screen;
static const SDL_Color clear_color = {32, 32, 32, 255};

void set_current_screen(Screen screen) {
    current_screen = screen;
}

void run_current_screen() {
    if(first_frame) {
        last_frame = SDL_GetPerformanceCounter();
        first_frame = SDL_FALSE;
    }

    Uint64 this_frame = SDL_GetPerformanceCounter();
    float delta_time = ticks_to_seconds(this_frame - last_frame);
    last_frame = this_frame;

    set_draw_color(&clear_color);
    SDL_RenderClear(renderer);
    current_screen(delta_time);
    SDL_RenderPresent(renderer);
}