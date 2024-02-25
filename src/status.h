#ifndef sdl2_game_status_h
#define sdl2_game_status_h


#include <stdio.h>
#include "main.h"

void init_status_lives(GameState *game);
void draw_status_lives(GameState *game);
void shutdown_status_lives (GameState *game);
void init_game_over(GameState *game);

#endif