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

#ifndef FLAPPY_SCREEN_GAME_H
#define FLAPPY_SCREEN_GAME_H

#define GROUND_Y (WINDOW_HEIGHT - 54)

#define PIPE_WIDTH 45
#define PIPE_GAP 85
#define PIPE_GAP_MIN_Y 150
#define PIPE_GAP_MAX_Y (WINDOW_HEIGHT - 150)
#define PIPE_SPEED -60
#define PIPE_SPAWN_TIME 2000
#define MAX_PIPES 5

#define BIRD_FLAP_VELOCITY -200
#define BIRD_GRAVITY 500
#define BIRD_SPAWN_X 70
#define BIRD_SPAWN_Y 100
#define BIRD_WIDTH 20
#define BIRD_HEIGHT 20

/** Start a new game
 * 
 * This function is separate from enter_game_screen because
 * the game screen needs to be able to be a "client" screen,
 * that is, other screens need to be able to draw it when
 * it isn't the current screen. */
void new_game();

/** Disable collisions in the game
 * 
 * This is used by the game over screen to allow the player
 * to fall in the background while the game over screen is
 * displayed */
void disable_game_collisions();

/** Enter game screen, set current screen */
void enter_game_screen();

/** Update and render one frame of the game screen */
void game_screen(float delta_time);

/** Draw the game screen */
void draw_game();

/** Get score of curren game */
int get_score();

/** Get the high score of all games played this session */
int get_high_score();

/** Set the score, update high score if necessary */
void set_score(int score);

/** Increment the score by amount, set high score if necessary */
void increment_score(int amount);

#endif // FLAPPY_SCREEN_GAME_H