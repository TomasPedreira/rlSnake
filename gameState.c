#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include "gameState.h"

#ifndef DEFAULT_GAME_SPEED
    #define DEFAULT_GAME_SPEED 2.5
#endif // DEFAULT_GAME_SPEED

void restart_game(GameState *game_state){
    game_state->current_page = GAME;
    game_state->snake_length = 1;
    game_state->snake_pos[0] = (Vector2){0,0};
    game_state->snake_dir = (Vector2){1,0};
    game_state->snake_last_dir = (Vector2){1,0};
    game_state->score = 0;
    game_state->time_since_update = 0.0;
    game_state->lost = false;
    game_state->has_apple = false;
    game_state->paused = false;
    game_state->game_speed = DEFAULT_GAME_SPEED;
}