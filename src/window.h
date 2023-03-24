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

#ifndef FLAPPY_WINDOW_H
#define FLAPPY_WINDOW_H
#include "SDL.h"

#define WINDOW_TITLE "Flappy Square"
#define WINDOW_WIDTH (1080/4)
#define WINDOW_HEIGHT (1920/4)

/** The window */
extern SDL_Window *window;

/** The window's renderer */
extern SDL_Renderer *renderer;

/** Create the window and its renderer, exit on failure */
int create_window(void);

#endif // FLAPPY_WINDOW_H
