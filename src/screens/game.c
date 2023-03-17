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

#include "game.h"
#include "game_over.h"
#include "../screen.h"
#include "../event.h"
#include "../font.h"
#include "../draw.h"
#include "../util.h"
#include "../window.h"

typedef struct Pipe {
    SDL_FRect top;
    SDL_FRect bottom;
    SDL_FRect trigger;
} Pipe;

typedef struct Bird {
    SDL_bool alive;
    SDL_FRect rect;
    SDL_FPoint velocity;
} Bird;

static Pipe pipes[MAX_PIPES];
static SDL_TimerID pipe_spawn_timer;
static SDL_Event pipe_spawn_event = {PIPE_SPAWN_EVENT};

static Bird bird;

static int score;
static int high_score;

static const SDL_Color clear_color = {32, 32, 32, 255};
static const SDL_Color background_color = {100, 100, 255, 255};
static const SDL_Color ground_color = {0, 128, 0, 255};
static const SDL_Color pipe_color = {0, 200, 0, 255};
static const SDL_Color bird_color = {200, 200, 200, 255};
static const SDL_Color trigger_color = {255, 0, 0, 128};
static const SDL_Color text_color = {200, 200, 200, 255};

const SDL_FRect ground = {
    .x = 0,
    .y = GROUND_Y,
    .w = WINDOW_WIDTH,
    .h = WINDOW_HEIGHT - GROUND_Y,
};

int get_score() {
    return score;
}

int get_high_score() {
    return high_score;
}

void set_score(int score_) {
    score = score_;
    if(score > high_score)
        high_score = score;
}

void increment_score(int amount) {
    set_score(score + amount);
}

/** Create a new pipe
 * 
 * New pipes are always created at the head of the list, so
 * the newest pipe is always index 0 and the oldest pipe
 * is always the last index. */
static void new_pipe() {
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
static void move_pipes(float delta_time) {
    for(int pipe = 0; pipe < MAX_PIPES; pipe++) {
        pipes[pipe].top.x += PIPE_SPEED * delta_time;
        pipes[pipe].bottom.x += PIPE_SPEED * delta_time;
        pipes[pipe].trigger.x += PIPE_SPEED * delta_time;
    }
}

/** Draw the pipes */
static void draw_pipes() {
    for(int pipe = 0; pipe < MAX_PIPES; pipe++) {
        draw_rect(&pipes[pipe].top, &pipe_color);
        draw_rect(&pipes[pipe].bottom, &pipe_color);

        // Draw the triggers in debug builds
        #ifndef NDEBUG
        draw_rect(&pipes[pipe].trigger, &trigger_color);
        #endif // NDEBUG
    }
}

/** Create a new bird */
static void new_bird() {
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
static void flap() {
    if(bird.alive)
        bird.velocity.y = BIRD_FLAP_VELOCITY;
}

/** Move the bird */
static void move_bird(float delta_time) {
    bird.velocity.y += BIRD_GRAVITY * delta_time;
    bird.rect.y += bird.velocity.y * delta_time;
}

/** Draw the bird */
static void draw_bird() {
    draw_rect(&bird.rect, &bird_color);
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

/** Start a new game, initializing all game state */
void new_game() {
    score = 0;
    SDL_memset(&pipes, 0, sizeof(pipes));
    new_pipe();
    new_bird();
}

void enter_game_screen() {
    // If the pipe spawn timer is active, kill it
    SDL_RemoveTimer(pipe_spawn_timer);
    // Start the pipe spawn timer
    pipe_spawn_timer = SDL_AddTimer(
        PIPE_SPAWN_TIME,
        reflect_event,
        &pipe_spawn_event);

    // Start the game with a flap
    flap();

    set_current_screen(game_screen);
}

void game_screen(float delta_time) {
    // Process events
    for(SDL_Event event; SDL_PollEvent(&event);) {
        switch (event.type) {
        case SDL_QUIT:
            exit(EXIT_SUCCESS);
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
    move_pipes(delta_time);
    move_bird(delta_time);

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
        enter_game_over_screen();
        game_over_screen(delta_time);
        return;
    }

    // Render game
    draw_game();
    SDL_RenderPresent(renderer);
}