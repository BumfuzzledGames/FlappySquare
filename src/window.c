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

#include "window.h"

SDL_Window *window;
SDL_Renderer *renderer;

void create_window() {
    // Create the window and renderer
    window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE);
    if(window == NULL) {
        SDL_Log("SDL_CreateWindow: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL) {
        SDL_Log("SDL_CreateRenderer: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Set the draw blend mode so shapes can be translucent
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // Set the minimum and logical sizes so the game window
    // is easily resized
    SDL_RenderSetLogicalSize(
        renderer,
        WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_SetWindowMinimumSize(
        window,
        WINDOW_WIDTH, WINDOW_HEIGHT);
}