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

#include "draw.h"
#include "window.h"

static const SDL_Color stroke_color = {32, 32, 32, 255};

void set_draw_color(const SDL_Color *color) {
    SDL_SetRenderDrawColor(
        renderer,
        color->r, color->g, color->b, color->a);
    if(color->a == 255)
        SDL_SetRenderDrawBlendMode(
            renderer,
            SDL_BLENDMODE_NONE);
    else
        SDL_SetRenderDrawBlendMode(
            renderer,
            SDL_BLENDMODE_BLEND);
}

void draw_rect(const SDL_FRect *rect, const SDL_Color *color) {
    set_draw_color(color);
    SDL_RenderFillRectF(renderer, rect);
    set_draw_color(&stroke_color);
    SDL_RenderDrawRectF(renderer, rect);
}