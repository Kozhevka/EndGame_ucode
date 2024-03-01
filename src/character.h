#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void playerMove(Man *player, float gameSpeed, int direction);
void playerIdle(Man *player, float gameSpeed);
void playerJump(Man *player, float jumpForce);
void playerAttack(Man *player);
void playerGotHit(Man *player, int attackerDirection);
void playerMoveAnimationStep(Man *player);

void enemyMove(Enemy *enemy, int direction);
void enemyAttack(Enemy *enemy);

typedef struct
{
    SDL_Texture *idle;
    SDL_Texture *run[4];
    SDL_Texture *jump;
    SDL_Texture *flyIdle;
    SDL_Texture *attack;
    SDL_Texture *gotHit;
    SDL_Texture *dead;
    SDL_Texture *hit_accumulate_0;
    SDL_Texture *hit_accumulate_1;
    SDL_Texture *hit_accumulate_2;
    SDL_Texture *hit_perform;

} AnimationMainHeroHolder;

typedef struct
{
    SDL_Texture *attackStart;
    SDL_Texture *attackedContinue;
    SDL_Texture *attackedEnd;
    SDL_Texture *idle;
    SDL_Texture *walk;

} AnimationEnemyHolder;
