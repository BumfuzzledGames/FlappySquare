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

#include "util.h"

static Uint64 random_state;

void random_mixstate(int seed) {
    random_state += seed;
}

static int rand31(void) {
    random_state = random_state*0x3243f6a8885a308dULL + 1;
    return random_state >> 33;
}

float ticks_to_seconds(Uint64 ticks) {
    return (float)ticks / SDL_GetPerformanceFrequency();
}

int random_in_range(int min, int max) {
    return rand31() % (max - min) + min;
}
