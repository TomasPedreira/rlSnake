#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <stdio.h>
#include "gameState.h"
#include "keyEvents.h"




void key_events_game(GameState *game_state){
    switch(GetKeyPressed()){
        case KEY_A:
            if (game_state->snake_last_dir.x != 1){
                game_state->snake_dir.x = -1;
                game_state->snake_dir.y = 0;
            }
            break;
        case KEY_D:
            if (game_state->snake_last_dir.x != -1){
                game_state->snake_dir.x = 1;
                game_state->snake_dir.y = 0;
            }
            break;
        case KEY_W:
            if (game_state->snake_last_dir.y != 1){
                game_state->snake_dir.x = 0;
                game_state->snake_dir.y = -1;
            }
            break;
        case KEY_S:
            if (game_state->snake_last_dir.y != -1){
                game_state->snake_dir.x = 0;
                game_state->snake_dir.y = 1;
            }
            break;
        case KEY_P:
            if(game_state->paused){
                game_state->paused = false;
            } else {
                game_state->paused = true;
            }
            break;
        case KEY_Q:
            game_state->game_speed -= 0.5;
            if (game_state->game_speed < 0.5){
                game_state->game_speed = 0.5;
            }
            break;
        case KEY_E:
            game_state->game_speed += 0.5;
            if (game_state->game_speed > 10.0){
                game_state->game_speed = 10.0;
            }
            break;
    }
}
void key_events_end(GameState *game_state){
    if (IsKeyPressed(KEY_Q)){
        game_state->running = false;
    }
    if (IsKeyPressed(KEY_R)){
        go_to_game_page(game_state);
        restart_game(game_state);
    }
}
