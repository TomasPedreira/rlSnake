#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_


enum current_page{
    MAIN_MENU,
    GAME,
    ENDGAME
};
enum buttons{
    START,
    QUIT,
    RESTART,
    STOP,
};

typedef struct _Button {
    Vector2 start;
    size_t width;
    size_t height;
    Color color;
    Vector2 text_pos;
    char* text;
    bool hovering;
    bool clicked;
    size_t font_size;
} Button;
typedef struct _GameState {
    size_t snake_length;
    Vector2* snake_pos;
    Vector2 snake_dir;
    Vector2 food_pos;
    Vector2 snake_last_dir;
    size_t score;
    float time_since_update;
    bool running;
    bool has_apple;
    int current_page;
    bool lost;
    Button buttons[4]; // 0-start, 1-quit, 2-restart, 3-stop
    float game_speed;
} GameState;

void restart_game(GameState *game_state);

#endif //_GAME_STATE_H_ 