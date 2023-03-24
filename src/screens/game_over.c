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
#include "../font.h"
#include "../window.h"
#include "../draw.h"
#include "SDL.h"

#define DELAY_TIME 1
#define GAME_SCREEN_SLOWDOWN 10

static float screen_time;

static const SDL_Color overlay_color = {64, 0, 0, 192};

void enter_game_over_screen(void) {
    screen_time = 0;
    disable_game_collisions();
    set_current_screen(game_over_screen);
}

/** Display the game over screen */
int game_over_screen(float delta_time) {
    screen_time += delta_time;

    // Process events
    for(SDL_Event event; SDL_PollEvent(&event);) {
        switch(event.type) {
        case SDL_KEYDOWN:
        case SDL_MOUSEBUTTONDOWN:
            if(screen_time > DELAY_TIME) {
                enter_start_screen();
                start_screen(delta_time);
                return 1;
            }
            break;
        case SDL_QUIT:
            return 0;
        }
    }

    // Keep updating and drawing the game in slow motion
    // enter_game_over disabled collision, though
    game_screen(delta_time / GAME_SCREEN_SLOWDOWN);

    set_draw_color(&overlay_color);
    SDL_RenderFillRect(
        renderer,
        0);

    // Draw the message
    const char *message = "";
    if(screen_time > DELAY_TIME)
        message = "\nClick to\nplay again";
    static const SDL_Color text_color = {255, 255, 255, 255};
    draw_string_centered(
        0, WINDOW_WIDTH,
        (WINDOW_HEIGHT / 2) - FONT_CHARACTER_HEIGHT * FONT_DISPLAY_SCALE,
        &text_color,
        "WASTED\n%s",
        message);
    return 1;
}
