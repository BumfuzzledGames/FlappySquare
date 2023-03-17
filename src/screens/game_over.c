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
#include "game_over.h"
#include "game.h"
#include "start.h"
#include "../screen.h"
#include "../event.h"
#include "../font.h"
#include "../window.h"
#include <SDL.h>

static SDL_TimerID delay_timer;
static SDL_Event delay_event = {GAME_OVER_DELAY_EVENT};
static SDL_bool display_message;

static const SDL_Color game_over_text_color = {0, 0, 0, 255};

void enter_game_over_screen() {
    SDL_RemoveTimer(delay_timer);
    delay_timer = SDL_AddTimer(
        GAME_OVER_DELAY,
        reflect_event,
        &delay_event);
    display_message = SDL_FALSE;
    set_current_screen(game_over_screen);
}

/** Display the game over screen */
void game_over_screen(float delta_time) {
    // Process events
    for(SDL_Event event; SDL_PollEvent(&event);) {
        switch(event.type) {
        case GAME_OVER_DELAY_EVENT:
            display_message = SDL_TRUE;
            SDL_RemoveTimer(delay_timer);
            delay_timer = 0;
            break;
        case SDL_KEYDOWN:
        case SDL_MOUSEBUTTONDOWN:
            if(display_message) {
                enter_start_screen();
                start_screen(delta_time);
                return;
            }
            break;
        case SDL_QUIT:
            exit(EXIT_SUCCESS);
        }
    }

    // Draw the game and the game over overlay
    draw_game();

    const char *message = "";
    if(display_message)
        message = "\nClick to\nplay again";
    draw_string_centered(
        0, WINDOW_WIDTH,
        (WINDOW_HEIGHT / 2) - FONT_CHARACTER_HEIGHT * FONT_DISPLAY_SCALE,
        &game_over_text_color,
        "WASTED\n%s",
        message);

    SDL_RenderPresent(renderer);
}
