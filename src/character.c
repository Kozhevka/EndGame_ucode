#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "character.h"
#include "main.h"
#include "imageTool.h"



void playerMove(Man *player, float gameSpeed, int direction)
{
    player->dx += 0.1 * gameSpeed * direction;

    int directionDelta = direction * 3; 

    if (player->dx < directionDelta * gameSpeed) 
    {
        player->dx = directionDelta * gameSpeed;
    }

    
    player->facingLeft = direction > 0 ? 0 : 1;
    player->slowingDown = 0;
}

void playerIdle(Man *player, float gameSpeed)
{
    player->animFrame = 0;
    player->dx *= 0.1f * gameSpeed;
    player->slowingDown = 1;

    if (fabsf(player->dx) < 0.1f)
    {
        player->dx = 0;
    }
}

void playerJump(Man *player, float jumpForce)
{
    player->dy -= 0.003f * getStaleY() * jumpForce;
}
void playerAttack(Man *player)
{

}
void playerGotHit(Man *player, int attackerDirection)
{

}

void playerMoveAnimationStep(Man *player)
{
    int currentAnimationStep = player->animFrame;

    currentAnimationStep++;
    if (currentAnimationStep > 4)
    {
        currentAnimationStep = 0;
    }
    player->animFrame = currentAnimationStep;
}


void enemyMove(Enemy *enemy, int direction){}
void enemyAttack(Enemy *enemy){}


