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

#ifndef FLAPPY_UTIL_H
#define FLAPPY_UTIL_H
#include "SDL.h"

/** Mix entropy into the random number generator state.
 * @param seed Data to mix the state */
void random_mixstate(int seed);

/** Return a random number within a range
 * @param min The range start
 * @param max The range end */
int random_in_range(int min, int max);

/** Convert an amount of ticks to seconds
 * @param ticks The ticks
 * @return      The seconds */
float ticks_to_seconds(Uint64 ticks);


#endif // FLAPPY_UTIL_H