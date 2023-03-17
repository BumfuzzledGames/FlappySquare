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

#ifndef FLAPPY_SCREEN_GAME_OVER_H
#define FLAPPY_SCREEN_GAME_OVER_H

#define GAME_OVER_DELAY 1000

/** Enter the game over screen, set current screen */
void enter_game_over_screen();

/** Update and render one frame of the game over screen */
void game_over_screen(float delta_time);

#endif // FLAPPY_SCREEN_GAME_OVER_H