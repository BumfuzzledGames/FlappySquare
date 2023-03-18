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

#ifndef FLAPPY_FONT_H
#define FLAPPY_FONT_H
#include "SDL.h"

// Note: @ is actually the copyright symbol
#define FONT_CHARSET                                       \
    " !\"#$%&'()*+,-./0123456789:;<=>?"                    \
    "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"                    \
    "$abcdefghijklmnopqrstuvwxyz{|}~@"

#define FONT_CHARACTERS_PER_ROW 32
#define FONT_CHARACTER_ROWS 3
#define FONT_CHARACTER_WIDTH 8
#define FONT_CHARACTER_HEIGHT 8
#define FONT_TEXTURE_SCALE 4
#define FONT_DISPLAY_SCALE 2

/** Load the font resources
 * 
 * This must be called after the window and its renderer
 * have been created */
int load_font();

/** Draw a string on the screen
 * @param x The x coordinate of the top left of the string
 * @param y The y coordinate of the top right of the string
 * @param color The color of the string
 * @param format The string format, as with printf */
void draw_string(
    int x, int y,
    const SDL_Color *color,
    const char *format, ...);

/** Draw a centered string on the screen
 * @param minx The left side of the centered area
 * @param maxx The right side of the centered area
 * @param y The y coordinate of the top right of the string
 * @param color The color of the string
 * @param format The string format, as with printf */
void draw_string_centered(
    int minx, int maxx,
    int y,
    const SDL_Color *color,
    const char *format, ...);

#endif // FLAPPY_FONT_H
