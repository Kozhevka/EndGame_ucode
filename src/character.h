#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "main.h"

void playerMove(Man *player, float gameSpeed, int direction);
void playerIdle(Man *player, float gameSpeed);
void playerJump(Man *player, float jumpForce);
void playerAttack(Man *player);
void playerGotHit(Man *player, int attackerDirection);
void playerMoveAnimationStep(Man *player);

void enemyMove(Enemy *enemy, int direction);
void enemyAttack(Enemy *enemy);

