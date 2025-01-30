#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include "gameState.h"
#include "mouseEvents.h"



void mouse_events_game(GameState *game_state){
    Vector2 mouse_pos = GetMousePosition();
    if (
        (mouse_pos.x >= game_state->buttons[STOP].start.x) && 
        (mouse_pos.y >= game_state->buttons[STOP].start.y) && 
        (mouse_pos.x <= game_state->buttons[STOP].start.x+game_state->buttons[STOP].width) && 
        (mouse_pos.y <= game_state->buttons[STOP].start.y+game_state->buttons[STOP].height)
    ){
        game_state->buttons[STOP].hovering = true;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            game_state->current_page = ENDGAME;
            game_state->lost = true;
        }
    }else{
        game_state->buttons[STOP].hovering = false;
    }
}
void mouse_events_end(GameState *game_state){
    Vector2 mouse_pos = GetMousePosition();
    if (
        (mouse_pos.x >= game_state->buttons[QUIT].start.x) && 
        (mouse_pos.y >= game_state->buttons[QUIT].start.y) && 
        (mouse_pos.x <= game_state->buttons[QUIT].start.x+game_state->buttons[QUIT].width) && 
        (mouse_pos.y <= game_state->buttons[QUIT].start.y+game_state->buttons[QUIT].height)
    ){
        game_state->buttons[QUIT].hovering = true;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            game_state->running = false;
        }
    }else{
        game_state->buttons[QUIT].hovering = false;
    }
    if (
        (mouse_pos.x >= game_state->buttons[RESTART].start.x) && 
        (mouse_pos.y >= game_state->buttons[RESTART].start.y) && 
        (mouse_pos.x <= game_state->buttons[RESTART].start.x+game_state->buttons[RESTART].width) && 
        (mouse_pos.y <= game_state->buttons[RESTART].start.y+game_state->buttons[RESTART].height)
        ){
        game_state->buttons[RESTART].hovering = true;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            restart_game(game_state);
        }
    }else{
        game_state->buttons[RESTART].hovering = false;
    }
}