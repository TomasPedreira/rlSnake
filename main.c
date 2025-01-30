#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include "gameState.h"
#include "keyEvents.h"
#include "mouseEvents.h"


#define WINDOW_WIDTH 16
#define WINDOW_HEIGHT 9
#define NUM_VERTICAL_CELLS 10
#define SCALING_FACTOR 100
#define CELL_SIZE WINDOW_HEIGHT*SCALING_FACTOR/NUM_VERTICAL_CELLS
#define EYE_SIZE CELL_SIZE/10


#ifndef DEFAULT_GAME_SPEED
#define DEFAULT_GAME_SPEED 2.5
#endif // DEFAULT_GAME_SPEED





size_t calculate_h_cells(){
    double aspect_ratio = (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT;
    const size_t default_num_horizontal_cells = NUM_VERTICAL_CELLS * aspect_ratio - 1;
    return default_num_horizontal_cells;
}

size_t max_cells(){
    return calculate_h_cells() * NUM_VERTICAL_CELLS;
}

size_t calculate_nav_width(){
    return WINDOW_WIDTH*SCALING_FACTOR - CELL_SIZE * calculate_h_cells();
}


// from 00 top left corner to wtv,wtv right bot corner
void paint_cell(size_t x, size_t y, Color color){
    const int board_start = calculate_nav_width();
    const int x_pos = board_start + CELL_SIZE * (x);
    DrawRectangle(x_pos, y*CELL_SIZE+1, CELL_SIZE-2, CELL_SIZE-2, color);
}

void draw_nav_bar(GameState game_state){
    const int board_start = calculate_nav_width() - 1;  
    const char* score_text = TextFormat("Score:\n   %zu", game_state.score);
    DrawRectangle(0,0,board_start, WINDOW_HEIGHT*SCALING_FACTOR, BLUE);
    DrawText("SNAKE\nGAME", board_start*0.1, WINDOW_HEIGHT*SCALING_FACTOR*0.05, SCALING_FACTOR*0.4, GREEN);
    DrawText(score_text, board_start*0.1, WINDOW_HEIGHT*SCALING_FACTOR*0.4, SCALING_FACTOR*0.4, GREEN);
    DrawRectangle(
        game_state.buttons[STOP].start.x, 
        game_state.buttons[STOP].start.y, 
        game_state.buttons[STOP].width, 
        game_state.buttons[STOP].height, 
        game_state.buttons[STOP].color
    );
    DrawText(
        game_state.buttons[STOP].text,
        game_state.buttons[STOP].text_pos.x, 
        game_state.buttons[STOP].text_pos.y, 
        game_state.buttons[STOP].font_size,
        WHITE
    );
}


void draw_grid(){
    const size_t num_horizontal_cells = calculate_h_cells();
    float bruh = WINDOW_WIDTH*SCALING_FACTOR - CELL_SIZE * num_horizontal_cells;
    int num = (int)bruh;
    // Vertical lines
    DrawLine(num,0,num,WINDOW_HEIGHT*SCALING_FACTOR, RAYWHITE);
    for (size_t i = 1; i < num_horizontal_cells + 1; i++)
    {
        DrawLine(num + CELL_SIZE*i-1,0,num + CELL_SIZE*i-1,WINDOW_HEIGHT*SCALING_FACTOR, RAYWHITE);

    }
    // Horizontal lines
    DrawLine(num,0,WINDOW_WIDTH*SCALING_FACTOR,0, RAYWHITE);
    for (size_t i = 1; i < NUM_VERTICAL_CELLS + 1 ; i++)
    {
        DrawLine(num, CELL_SIZE*i-1,WINDOW_WIDTH*SCALING_FACTOR,CELL_SIZE*i-1, RAYWHITE);
    }
}

void draw_snake_head(Vector2 snake_pos, Vector2 snake_dir){
    const int board_start = calculate_nav_width();
    const int x_pos = board_start + CELL_SIZE * (snake_pos.x);
    if (snake_dir.x == 1)
    {
        DrawRectangle(x_pos + CELL_SIZE*0.8 - EYE_SIZE/2, snake_pos.y*CELL_SIZE+CELL_SIZE*0.33 - EYE_SIZE/2, EYE_SIZE, EYE_SIZE, RED);
        DrawRectangle(x_pos + CELL_SIZE*0.8 - EYE_SIZE/2, snake_pos.y*CELL_SIZE+CELL_SIZE*0.66 - EYE_SIZE/2, EYE_SIZE, EYE_SIZE, RED);
    }
    else if (snake_dir.x == -1)
    {
        DrawRectangle(x_pos + CELL_SIZE*0.2 - EYE_SIZE/2, snake_pos.y*CELL_SIZE+CELL_SIZE*0.33 - EYE_SIZE/2, EYE_SIZE, EYE_SIZE, RED);
        DrawRectangle(x_pos + CELL_SIZE*0.2 - EYE_SIZE/2, snake_pos.y*CELL_SIZE+CELL_SIZE*0.66 - EYE_SIZE/2, EYE_SIZE, EYE_SIZE, RED);
    }
    else if (snake_dir.y == 1)
    {
        DrawRectangle(x_pos +CELL_SIZE*0.66 - EYE_SIZE/2, snake_pos.y*CELL_SIZE+CELL_SIZE*0.8 - EYE_SIZE/2, EYE_SIZE, EYE_SIZE, RED);
        DrawRectangle(x_pos +CELL_SIZE*0.33 - EYE_SIZE/2, snake_pos.y*CELL_SIZE+CELL_SIZE*0.8 - EYE_SIZE/2, EYE_SIZE, EYE_SIZE, RED);
    }
    else if (snake_dir.y == -1)
    {
        DrawRectangle(x_pos +CELL_SIZE*0.66 - EYE_SIZE/2, snake_pos.y*CELL_SIZE+CELL_SIZE*0.2 - EYE_SIZE/2, EYE_SIZE, EYE_SIZE, RED);
        DrawRectangle(x_pos +CELL_SIZE*0.33 - EYE_SIZE/2, snake_pos.y*CELL_SIZE+CELL_SIZE*0.2 - EYE_SIZE/2, EYE_SIZE, EYE_SIZE, RED);
    }
    
}

void draw_snake(Vector2* snake_pos, size_t snake_length, Vector2 snake_dir){
    for (size_t i = 0; i < snake_length; i++)
    {
        paint_cell(snake_pos[i].x, snake_pos[i].y, GREEN);
        if (i == 0)
        {
            draw_snake_head(snake_pos[i], snake_dir);
        }
    }
}
void draw_apples(GameState *game_state)
{
    paint_cell(game_state->food_pos.x, game_state->food_pos.y, RED);
}


void generate_apple(GameState *game_state){
    const size_t horizontal_cells = calculate_h_cells();
    size_t x;
    size_t y;
    bool valid = false;

    while(!valid){
        x = GetRandomValue(0, horizontal_cells-1);
        y = GetRandomValue(0, NUM_VERTICAL_CELLS-1);
        for (size_t i = 0; i < game_state->snake_length; i++)
        {
            if (game_state->snake_pos[i].x == x && game_state->snake_pos[i].y == y)
            {
                x = GetRandomValue(0, horizontal_cells-1);
                y = GetRandomValue(0, NUM_VERTICAL_CELLS-1);
                break;
            }

            // if youve not broken until now it means skane wasnt there
            if (i == game_state->snake_length-1)
            {
                valid = true;
                game_state->food_pos.x = x;
                game_state->food_pos.y = y;
                game_state->has_apple = true;
            }
        }
    }


}



void input(GameState *game_state)
{
    if (WindowShouldClose())
    {
        game_state->running = false;
    }
    if(game_state->current_page == GAME)
    {        
        key_events_game(game_state);
        mouse_events_game(game_state);
    }else if (game_state->current_page == ENDGAME){
        key_events_end(game_state);     
        mouse_events_end(game_state);   
    }
}

void update_game(GameState *game_state){
    
    if (!game_state->paused){
        game_state->time_since_update += GetFrameTime();
        if (game_state->time_since_update >= 1.0/game_state->game_speed)
        {
            game_state->time_since_update = 0.0;
            Vector2 last_pos_ass = game_state->snake_pos[game_state->snake_length-1];
            for (size_t i = game_state->snake_length-1; i > 0; i--)
            {
                game_state->snake_pos[i] = game_state->snake_pos[i-1];
            }
            
            game_state->snake_pos[0].x += game_state->snake_dir.x;
            game_state->snake_pos[0].y += game_state->snake_dir.y;
            if (game_state->snake_pos[0].x < 0)
            {
                game_state->snake_pos[0].x = calculate_h_cells()-1;
            }
            if (game_state->snake_pos[0].x == calculate_h_cells())
            {
                game_state->snake_pos[0].x = 0;
            }
            if (game_state->snake_pos[0].y < 0)
            {
                game_state->snake_pos[0].y = NUM_VERTICAL_CELLS-1;
            }
            if (game_state->snake_pos[0].y == NUM_VERTICAL_CELLS)
            {
                game_state->snake_pos[0].y = 0;
            }   
            if (game_state->snake_pos[0].x == game_state->food_pos.x && game_state->snake_pos[0].y == game_state->food_pos.y)
            {
                game_state->score++;
                game_state->snake_length++;
                game_state->has_apple = false;
                game_state->snake_pos[game_state->snake_length-1] = last_pos_ass;
            }
            game_state->snake_last_dir = game_state->snake_dir;
            for (size_t i = 0; i < game_state->snake_length-1;i++){
                for (size_t j = i+1; j < game_state->snake_length;j++){
                    if (game_state->snake_pos[i].x == game_state->snake_pos[j].x && game_state->snake_pos[i].y == game_state->snake_pos[j].y ){
                        game_state->lost = true;
                        game_state->current_page = ENDGAME;
                    }
                }
            }
            if (game_state->snake_length == max_cells()){
                game_state->lost = false;
                game_state->current_page = ENDGAME;
            }
        }
        if (!game_state->has_apple && game_state->snake_length < NUM_VERTICAL_CELLS*calculate_h_cells())
        {
            generate_apple(game_state);
        }
    } 
}
void update(GameState *game_state)
{
    if(game_state->current_page == GAME){

        update_game(game_state);
        game_state->buttons[STOP].color = game_state->buttons[STOP].hovering ? GRAY : BLACK;

    }else if (game_state->current_page == ENDGAME){
        
        game_state->buttons[RESTART].color = game_state->buttons[RESTART].hovering ? GRAY : BLACK;
        game_state->buttons[QUIT].color = game_state->buttons[QUIT].hovering ? GRAY : BLACK;

    } 
}

void endgame_page(GameState *game_state){

    ClearBackground(GREEN);
    if (game_state->lost){
        const char * losing_text = TextFormat("You Lost with %zu points", game_state->score);
        DrawText(losing_text,WINDOW_WIDTH*SCALING_FACTOR*0.33 - 0.33*SCALING_FACTOR*(sizeof losing_text), WINDOW_HEIGHT*SCALING_FACTOR*0.33, SCALING_FACTOR, BLACK);
    }else{
        const char winning_text[] = "YOU WON";
        DrawText(TextFormat("YOU WON", game_state->score),WINDOW_WIDTH*SCALING_FACTOR*0.33, WINDOW_HEIGHT*SCALING_FACTOR*0.33, SCALING_FACTOR, BLACK);
    }
    DrawRectangle(
        game_state->buttons[RESTART].start.x,
        game_state->buttons[RESTART].start.y, 
        game_state->buttons[RESTART].width, 
        game_state->buttons[RESTART].height, 
        game_state->buttons[RESTART].color
    );
    DrawText(
        game_state->buttons[RESTART].text,
        game_state->buttons[RESTART].text_pos.x, 
        game_state->buttons[RESTART].text_pos.y, 
        game_state->buttons[RESTART].font_size,
        WHITE
    );
    DrawRectangle( 
        game_state->buttons[QUIT].start.x,
        game_state->buttons[QUIT].start.y, 
        game_state->buttons[QUIT].width, 
        game_state->buttons[QUIT].height, 
        game_state->buttons[QUIT].color
    );
    DrawText(
        game_state->buttons[QUIT].text,
        game_state->buttons[QUIT].text_pos.x, 
        game_state->buttons[QUIT].text_pos.y, 
        game_state->buttons[QUIT].font_size,
        WHITE
    );
}
void render(GameState *game_state)
{
    const size_t num_horizontal_cells = calculate_h_cells();
    BeginDrawing();   
    if (game_state->current_page == ENDGAME){
        endgame_page(game_state);
    }else if (game_state->current_page == GAME){
        ClearBackground(BLACK);
        draw_grid(); 
        draw_nav_bar(*game_state); 
        draw_apples(game_state);
        draw_snake(game_state->snake_pos, game_state->snake_length, game_state->snake_dir);
    } 
    
    EndDrawing();
}

GameState init_game(){
    const size_t num_horizontal_cells = calculate_h_cells();
    
    GameState game_state;
    game_state.snake_length = 1;
    game_state.snake_pos = (Vector2*)malloc(sizeof(Vector2)*num_horizontal_cells*NUM_VERTICAL_CELLS);
    game_state.snake_pos[0] = (Vector2){3,3};
    game_state.snake_dir = (Vector2){1,0};
    game_state.snake_last_dir = (Vector2){1,0};
    game_state.score = 0;
    game_state.time_since_update = 0.0;
    game_state.running = true;
    game_state.has_apple = false;
    game_state.current_page = ENDGAME;
    game_state.lost = false;
    game_state.game_speed = DEFAULT_GAME_SPEED;
    game_state.paused = false;
    const size_t button_width = WINDOW_WIDTH*SCALING_FACTOR/4;
    const size_t button_height = WINDOW_HEIGHT*SCALING_FACTOR/8;
    const size_t quit_width = button_width*0.25;
    const size_t restart_width = button_width*0.50;
    const size_t quit_height = button_width*0.1;
    const size_t restart_height = button_width*0.10;

    // Restart button
    game_state.buttons[RESTART].clicked = false;
    game_state.buttons[RESTART].hovering = false;
    game_state.buttons[RESTART].start = (Vector2){WINDOW_WIDTH*SCALING_FACTOR*0.33 - button_width/2, WINDOW_HEIGHT*SCALING_FACTOR*0.8 - button_height/2};
    game_state.buttons[RESTART].width = button_width;
    game_state.buttons[RESTART].height = button_height;
    game_state.buttons[RESTART].color = BLACK;
    game_state.buttons[RESTART].text = "RESTART";
    game_state.buttons[RESTART].text_pos = (Vector2){WINDOW_WIDTH*SCALING_FACTOR*0.33 - restart_width/2, WINDOW_HEIGHT*SCALING_FACTOR*0.8 - restart_height/2};
    game_state.buttons[RESTART].font_size = SCALING_FACTOR*0.4;

    // Quit button
    game_state.buttons[QUIT].clicked = false;
    game_state.buttons[QUIT].hovering = false;
    game_state.buttons[QUIT].start = (Vector2){WINDOW_WIDTH*SCALING_FACTOR*0.66 - button_width/2, WINDOW_HEIGHT*SCALING_FACTOR*0.8 - button_height/2};
    game_state.buttons[QUIT].width = button_width;
    game_state.buttons[QUIT].height = button_height;
    game_state.buttons[QUIT].color = BLACK;
    game_state.buttons[QUIT].text = "QUIT";
    game_state.buttons[QUIT].text_pos = (Vector2){WINDOW_WIDTH*SCALING_FACTOR*0.66 - quit_width/2, WINDOW_HEIGHT*SCALING_FACTOR*0.8 - quit_height/2};
    game_state.buttons[QUIT].font_size = SCALING_FACTOR*0.4;

    // Stop button
    const size_t nav_width = calculate_nav_width();
    game_state.buttons[STOP].clicked = false;
    game_state.buttons[STOP].hovering = false;
    game_state.buttons[STOP].start = (Vector2){nav_width*0.1, WINDOW_HEIGHT*SCALING_FACTOR*0.8};
    game_state.buttons[STOP].width = nav_width*0.8;
    game_state.buttons[STOP].height = nav_width*0.8;
    game_state.buttons[STOP].color = BLACK;
    game_state.buttons[STOP].text = " End\nGame";
    game_state.buttons[STOP].text_pos = (Vector2){nav_width*0.2,WINDOW_HEIGHT*SCALING_FACTOR*0.8 + nav_width*0.8*0.2};
    game_state.buttons[STOP].font_size = SCALING_FACTOR*0.4;

    generate_apple(&game_state);
    return game_state;
}

int main(void)
{
    InitWindow(WINDOW_WIDTH*SCALING_FACTOR, WINDOW_HEIGHT*SCALING_FACTOR, "SNAKE GAME");
    GameState game_state = init_game();
    SetTargetFPS(60);
    SetExitKey(0);

    while (game_state.running)
    {
        input(&game_state);
        update(&game_state);
        render(&game_state);

    }
    free(game_state.snake_pos);
    CloseWindow();

    return 0;
}