#ifndef sdl2_game_map_h
#define sdl2_game_map_h

#include "main.h"

void initMap(GameState *game, float scaleX, float scaleY);
void renderMap(SDL_Renderer *renderer, GameState *game);
void updateBoss(GameState *game);  // Добавлено объявление
void renderBoss(SDL_Renderer *renderer, GameState *game);

#endif