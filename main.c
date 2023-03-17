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
#include <SDL.h>
#include "font.h"

#define WINDOW_TITLE "Flappy Square"
#define WINDOW_WIDTH (1080/4)
#define WINDOW_HEIGHT (1920/4)

#define GROUND_Y (WINDOW_HEIGHT - 54)

#define PIPE_WIDTH 45
#define PIPE_GAP 85
#define PIPE_GAP_MIN_Y 150
#define PIPE_GAP_MAX_Y (WINDOW_HEIGHT - 150)
#define PIPE_SPEED -60
#define PIPE_SPAWN_TIME 2000
#define MAX_PIPES 5

#define BIRD_FLAP_VELOCITY -200
#define BIRD_GRAVITY 500
#define BIRD_SPAWN_X 70
#define BIRD_SPAWN_Y 100
#define BIRD_WIDTH 20
#define BIRD_HEIGHT 20

#define GAME_OVER_DELAY 1000

/** SDL user events */
enum UserEvents {
    PIPE_SPAWN_EVENT = SDL_USEREVENT,
    GAME_OVER_DELAY_EVENT,
};

/** A pipe */
typedef struct Pipe Pipe;
struct Pipe {
    SDL_FRect top;
    SDL_FRect bottom;
    SDL_FRect trigger;
};

/** A bird, for flapping */
typedef struct Bird Bird;
struct Bird {
    SDL_bool alive;
    SDL_FRect rect;
    SDL_FPoint velocity;
};

/** Set to true if this is a debug build */
#ifndef NDEBUG
const SDL_bool debug_build = 1;
#else
const SDL_bool debug_build = 0;
#endif

/** The window and its renderer */
SDL_Window *window;
SDL_Renderer *renderer;

/** Time */
float delta_time;

/** Score */
int score;
int high_score;

/** Pipes */
Pipe pipes[MAX_PIPES];
SDL_TimerID pipe_spawn_timer;
SDL_Event pipe_spawn_event = {PIPE_SPAWN_EVENT};

/** Game over screen */
SDL_TimerID game_over_delay_timer;
SDL_Event game_over_delay_event = {GAME_OVER_DELAY_EVENT};

/** The ground */
const SDL_FRect ground = {
    .x = 0,
    .y = GROUND_Y,
    .w = WINDOW_WIDTH,
    .h = WINDOW_HEIGHT - GROUND_Y,
};

/** The bird */
Bird bird;

/** Colors of various things */
const SDL_Color clear_color = {32, 32, 32, 255};
const SDL_Color background_color = {100, 100, 255, 255};
const SDL_Color ground_color = {0, 128, 0, 255};
const SDL_Color stroke_color = {32, 32, 32, 255};
const SDL_Color pipe_color = {0, 200, 0, 255};
const SDL_Color bird_color = {200, 200, 200, 255};
const SDL_Color trigger_color = {255, 0, 0, 128};
const SDL_Color text_color = {200, 200, 200, 255};
const SDL_Color game_over_text_color = {0, 0, 0, 255};
const SDL_Color game_start_text_color = {192, 255, 192, 255};

/** Convert an amount of ticks to seconds
 * @param ticks The ticks
 * @return      The seconds */
float ticks_to_seconds(Uint64 ticks) {
    return (float)ticks / SDL_GetPerformanceFrequency();
}

/** A timer callback that pushes its param to the event
 *  queue.
 * @param interval Timer interval
 * @param param The event to push
 * @returns 0 if the timer should be removed
*/
unsigned int reflect_event(Uint32 interval, void *param) {
    SDL_PushEvent(param);
    return interval;
}

/** Set the render draw color from an SDL_Color
 * @param color The color to set */
void set_draw_color(const SDL_Color *color) {
    SDL_SetRenderDrawColor(
        renderer,
        color->r, color->g, color->b, color->a);
}

/** Return a random number within a range
 * @param min The range start
 * @param max The range end */
int random_in_range(int min, int max) {
    return rand() % (max - min) + min;
}

/** Draw a rect and its outline */
void draw_rect(const SDL_FRect *rect, const SDL_Color *color) {
    set_draw_color(color);
    SDL_RenderFillRectF(renderer, rect);
    set_draw_color(&stroke_color);
    SDL_RenderDrawRectF(renderer, rect);
}

/** Create a new pipe
 * 
 * New pipes are always created at the head of the list, so
 * the newest pipe is always index 0 and the oldest pipe
 * is always the last index. */
void new_pipe() {
    // Move the pipes over in the array, erasing the
    // oldest pipe which should be off screen by now.
    SDL_memmove(
        &pipes[1], &pipes[0],
        sizeof(Pipe) * (MAX_PIPES - 1));

    // Get the Y coordinate of the gap
    float gap_y = (float)random_in_range(
        PIPE_GAP_MIN_Y,
        PIPE_GAP_MAX_Y);
    
    // Create the new pipe top and bottom
    pipes[0].top = (SDL_FRect) {
        .x = WINDOW_WIDTH + 1,
        .y = gap_y - PIPE_GAP / 2 - WINDOW_HEIGHT,
        .w = PIPE_WIDTH,
        .h = WINDOW_HEIGHT
    };

    pipes[0].bottom = (SDL_FRect) {
        .x = WINDOW_WIDTH + 1,
        .y = gap_y + PIPE_GAP / 2,
        .w = PIPE_WIDTH,
        .h = WINDOW_HEIGHT
    };

    // Create the trigger, which is the right half of the gap
    pipes[0].trigger = (SDL_FRect) {
        .x = WINDOW_WIDTH + 1 + PIPE_WIDTH / 2,
        .y = gap_y - PIPE_GAP / 2,
        .w = PIPE_WIDTH / 2,
        .h = PIPE_GAP,
    };
}

/** Move the pipes to the left */
void move_pipes() {
    for(int pipe = 0; pipe < MAX_PIPES; pipe++) {
        pipes[pipe].top.x += PIPE_SPEED * delta_time;
        pipes[pipe].bottom.x += PIPE_SPEED * delta_time;
        pipes[pipe].trigger.x += PIPE_SPEED * delta_time;
    }
}

/** Draw the pipes */
void draw_pipes() {
    for(int pipe = 0; pipe < MAX_PIPES; pipe++) {
        draw_rect(&pipes[pipe].top, &pipe_color);
        draw_rect(&pipes[pipe].bottom, &pipe_color);

        // Draw the triggers in debug builds
        if(debug_build)
            draw_rect(&pipes[pipe].trigger, &trigger_color);
    }
}

/** Create a new bird */
void new_bird() {
    bird = (Bird) {
        .alive = SDL_TRUE,
        .rect = (SDL_FRect) {
            .x = BIRD_SPAWN_X,
            .y = BIRD_SPAWN_Y,
            .w = BIRD_WIDTH,
            .h = BIRD_HEIGHT
        },
        .velocity = {0},
    };
}

/** Flappy flappy */
void flap() {
    if(bird.alive)
        bird.velocity.y = BIRD_FLAP_VELOCITY;
}

/** Move the bird */
void move_bird() {
    bird.velocity.y += BIRD_GRAVITY * delta_time;
    bird.rect.y += bird.velocity.y * delta_time;
}

/** Draw the bird */
void draw_bird() {
    draw_rect(&bird.rect, &bird_color);
}

/** Start a new game, initializing all game state */
void new_game() {
    score = 0;
    SDL_memset(&pipes, 0, sizeof(pipes));
    new_pipe();
    new_bird();
}

/** Clear the screen and draw the game */
void draw_game() {
    // Clear everything, including the window outside
    // the game area
    set_draw_color(&clear_color);
    SDL_RenderClear(renderer);
    // Clear the game area
    set_draw_color(&background_color);
    SDL_RenderFillRect(renderer, NULL);

    draw_pipes();
    draw_bird();
    draw_rect(&ground, &ground_color);
    draw_string_centered(
        0, WINDOW_WIDTH,
        GROUND_Y + 2,
        &text_color,
        "Score: %d\n"
        "High score: %d\n"
        "%s",
        score,
        high_score,
        WINDOW_TITLE);
}

/** Display the game over screen
 * @returns SDL_TRUE if another game should be played,
 *          otherwise SDL_FALSE */
SDL_bool game_over_screen() {
    SDL_RemoveTimer(game_over_delay_timer);
    game_over_delay_timer = SDL_AddTimer(
        GAME_OVER_DELAY,
        reflect_event,
        &game_over_delay_event);
    SDL_bool message_enabled = SDL_FALSE;
    while(1) {
        // Process events
        for(SDL_Event event; SDL_PollEvent(&event);) {
            if(event.type == GAME_OVER_DELAY_EVENT)
                message_enabled = SDL_TRUE;
            switch(event.type) {
            case SDL_KEYDOWN:
            case SDL_MOUSEBUTTONDOWN:
                if(message_enabled)
                    return SDL_TRUE;
                break;
            case SDL_QUIT:
                return SDL_FALSE;
            }
        }

        // Draw the game and the game over overlay
        draw_game();

        const char *message = "";
        if(message_enabled)
            message = "\nClick to\nplay again";
        draw_string_centered(
            0, WINDOW_WIDTH,
            (WINDOW_HEIGHT / 2) - FONT_CHARACTER_HEIGHT * FONT_DISPLAY_SCALE,
            &game_over_text_color,
            "WASTED\n%s",
            message);
        SDL_RenderPresent(renderer);
    }
}

/** Display the game start screen
 * @returns SDL_TRUE if the game should start, or SDL_FALSE
 *          if the game should quit */
SDL_bool game_start_screen() {
    while(1) {
        // Process events
        for(SDL_Event event; SDL_PollEvent(&event);) {
            switch(event.type) {
            case SDL_QUIT:
                return SDL_FALSE;
            case SDL_KEYDOWN:
            case SDL_MOUSEBUTTONDOWN:
                return SDL_TRUE;
            }
        }

        // Draw the game with the game start overlay
        draw_game();
        draw_string_centered(
            0, WINDOW_WIDTH,
            WINDOW_HEIGHT / 2,
            &game_start_text_color,
            "Click to flap");
        SDL_RenderPresent(renderer);
    }
}

/** Run a game from start screen to game over screen
 * @returns SDL_TRUE if another game should be played,
 *          otherwise SDL_FALSE */
SDL_bool run_game() {
    // Initialize game state
    new_game();

    // Show the game start screen, return false if
    // an SDL_QUIT event was received
    if(!game_start_screen())
        return SDL_FALSE;
    
    // If the pipe spawn timer is active, kill it
    // and start again
    SDL_RemoveTimer(pipe_spawn_timer);
    pipe_spawn_timer = SDL_AddTimer(
        PIPE_SPAWN_TIME,
        reflect_event,
        &pipe_spawn_event);

    // Start the game with a flap
    flap();

    // Track frame time in ticks to calculate delta_time
    Uint64 last_frame = SDL_GetPerformanceCounter();
    while(1) {
        // Get the tick count for the start of this frame
        // and use it to calculate delta_time
        Uint64 this_frame = SDL_GetPerformanceCounter();
        delta_time = ticks_to_seconds(this_frame - last_frame);
        last_frame = this_frame;

        // Process events
        for(SDL_Event event; SDL_PollEvent(&event);) {
            switch (event.type) {
            case SDL_QUIT:
                return SDL_FALSE;
            // Spawn a pipe
            case PIPE_SPAWN_EVENT:
                new_pipe();
                break;
            // Flap on key
            case SDL_KEYDOWN:
                if(event.key.repeat)
                    break;
                // Fallthrough
            // Or on mouse button
            case SDL_MOUSEBUTTONDOWN:
                flap();
                break;
            default:
                break;
            }
        }

        // Update game
        move_pipes();
        move_bird();

        // Bird hit trigger?
        for(int pipe = 0; pipe < MAX_PIPES; pipe++) {
            if(SDL_HasIntersectionF(&pipes[pipe].trigger, &bird.rect)) {
                // Hit a trigger, increment score and disable
                // the trigger
                pipes[pipe].trigger = (SDL_FRect){0};
                score++;
                if(score > high_score)
                    high_score++;
            }
        }

        // Game over?
        SDL_bool game_over = SDL_FALSE;
        game_over |= SDL_HasIntersectionF(&ground, &bird.rect);
        for(int pipe = 0; !game_over && pipe < MAX_PIPES; pipe++) {
            game_over |= SDL_HasIntersectionF(&pipes[pipe].top, &bird.rect);
            game_over |= SDL_HasIntersectionF(&pipes[pipe].bottom, &bird.rect);
        }
        if(game_over) {
            return game_over_screen();
        }

        // Render game
        draw_game();
        SDL_RenderPresent(renderer);
    }
}

int main(int argc, char *argv[]) {
    // Unused
    (void)argc;
    (void)argv;

    // Seed PRNG
    srand((unsigned int)SDL_GetPerformanceCounter());

    // Initialize SDL, create window and create renderer.
    // Exit program if any of them fail
    if(SDL_Init(SDL_INIT_EVERYTHING)) {
        SDL_Log("SDL_Init: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

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

    // Initialize font
    load_font();

    // Set the minimum and logical sizes so the game window
    // is easily resized
    SDL_RenderSetLogicalSize(
        renderer,
        WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_SetWindowMinimumSize(
        window,
        WINDOW_WIDTH, WINDOW_HEIGHT);
    
    // Run the game until run_game returns false
    while(run_game()) {}

    // Flapping has ceased, exit
    SDL_Quit();
    return 0;
}