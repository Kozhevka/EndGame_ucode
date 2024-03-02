#ifndef sdl2_enemies_h
#define sdl2_enemies_h

#include "main.h"  


#define MOVING_LEFT 0
#define MOVING_RIGHT 1

void initBoss(GameState *game, float scaleX, float scaleY);
void updateEnemies(GameState *game, SDL_Renderer *renderer);
void renderBoss(SDL_Renderer *renderer, GameState *game);


#endif