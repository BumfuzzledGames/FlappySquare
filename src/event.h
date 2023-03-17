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

#ifndef FLAPPY_EVENT_H
#define FLAPPY_EVENT_H
#include <SDL.h>

/** User event IDs */
enum UserEvents {
    PIPE_SPAWN_EVENT = SDL_USEREVENT,
    GAME_OVER_DELAY_EVENT,
};

/** A timer callback that pushes its param to the event
 *  queue.
 * @param interval Timer interval
 * @param param The event to push
 * @returns 0 if the timer should be removed
*/
unsigned int reflect_event(Uint32 interval, void *param);

#endif // FLAPPY_EVENT_H