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

#include "start.h"
#include "game.h"
#include "../screen.h"
#include "../font.h"
#include "../window.h"

static const SDL_Color text_color = {192, 255, 192, 255};

void start_screen(float delta_time) {
    // Process events
    for(SDL_Event event; SDL_PollEvent(&event);) {
        switch(event.type) {
        case SDL_QUIT:
            exit(EXIT_SUCCESS);
        case SDL_KEYDOWN:
        case SDL_MOUSEBUTTONDOWN:
            enter_game_screen();
            game_screen(delta_time);
            return;
        }
    }

    // Draw the game with the game start overlay
    draw_game();
    draw_string_centered(
        0, WINDOW_WIDTH,
        WINDOW_HEIGHT / 2,
        &text_color,
        "Click to flap");
    SDL_RenderPresent(renderer);
}

void enter_start_screen() {
    // Initialize game state and set current screen
    new_game();
    set_current_screen(start_screen);
}