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

#ifndef FLAPPY_DRAW_H
#define FLAPPY_DRAW_H
#include "SDL.h"

/** Set the render draw color from an SDL_Color
 * @param color The color to set */
void set_draw_color(const SDL_Color *color);

/** Draw a rect and its outline
 * @param rect The rect
 * @param rect Fill color of the rect */
void draw_rect(const SDL_FRect *rect, const SDL_Color *color);

#endif // FLAPPY_DRAW_H