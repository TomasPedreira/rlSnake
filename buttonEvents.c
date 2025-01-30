#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include "gameState.h"
#include "buttonEvents.h"




void button_events_game(GameState *game_state){
    if (IsKeyPressed(KEY_Q)){
            game_state->game_speed -= 0.5;
            if (game_state->game_speed < 0.0){
                game_state->game_speed = 0.0;
            }
        }
        if (IsKeyPressed(KEY_E)){
            game_state->game_speed += 0.5;
            if (game_state->game_speed > 10.0){
                game_state->game_speed = 10.0;
            }
        }
        if (IsKeyPressed(KEY_A) && game_state->snake_last_dir.x != 1){
            game_state->snake_dir.x = -1;
            game_state->snake_dir.y = 0;
        }
        if (IsKeyPressed(KEY_D) && game_state->snake_last_dir.x != -1){
            game_state->snake_dir.x = 1;
            game_state->snake_dir.y = 0;

        }
        if (IsKeyPressed(KEY_W) && game_state->snake_last_dir.y != 1){
            game_state->snake_dir.x = 0;
            game_state->snake_dir.y = -1;
        }
        if (IsKeyPressed(KEY_S) && game_state->snake_last_dir.y != -1){
            game_state->snake_dir.x = 0;
            game_state->snake_dir.y = 1;
        }
}
void button_events_end(GameState *game_state){
    if (IsKeyPressed(KEY_Q)){
            game_state->running = false;
    }
    if (IsKeyPressed(KEY_R)){
        restart_game(game_state);
    }
}
