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

#ifndef FLAPPY_SCREEN_H
#define FLAPPY_SCREEN_H

/** The delta_time will never exceed this value */
#define MAX_DELTA_TIME (1.0f / 30)

/** A screen function updates and renders a single frame */
typedef int (*Screen)(float delta_time);

/** Set the current screen to screen
 * @param screen The new current screen */
void set_current_screen(Screen screen);

/** Update and render a single frame of the current scene */
int run_current_screen();

#endif // FLAPPY_SCREEN_H