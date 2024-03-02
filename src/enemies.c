#include "main.h"
#include "enemies.h"
#include "menu.h"


void updateEnemies(GameState *game, SDL_Renderer *renderer) {

    static Uint32 enemyMoveTimer = 0;

    static Uint32 textureChangeTimer = 0;

    if (SDL_GetTicks() - enemyMoveTimer > 6000) {
        for (int i = 0; i < NUM_ENEMIES; i++) {
            game->enemies[i].facingLeft = !game->enemies[i].facingLeft;
        }
        enemyMoveTimer = SDL_GetTicks();
    }

    if (SDL_GetTicks() - textureChangeTimer > 500) {
        for (int i = 0; i < NUM_ENEMIES; i++) {
            game->enemies[i].facingLeftTexture = !game->enemies[i].facingLeftTexture;
        }
        textureChangeTimer = SDL_GetTicks();
    }


    for (int i = 0; i < NUM_ENEMIES; i++) {

        float deltaX = game->enemies[i].facingLeft ? -ENEMY_SPEED * getStaleX() : ENEMY_SPEED * getStaleX(); 

        game->enemies[i].x += deltaX * getStaleX();

        if (deltaX != 0) {
            game->enemies[i].state = ENEMY_STATE_WALKING;
        } else {
            game->enemies[i].state = ENEMY_STATE_IDLE;
        }

        SDL_Texture *currentEnemyTexture;
        SDL_RendererFlip flip = game->enemies[i].facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        if (game->enemies[i].state == ENEMY_STATE_IDLE) {
            currentEnemyTexture = game->enemy;
        } else {
            if (game->enemies[i].facingLeftTexture) {
                currentEnemyTexture = game->enemyGo;
            } else {
                currentEnemyTexture = game->enemy; 
            }
        }


        float distanceToPlayer = fabs(game->man.x - game->enemies[i].x);

        if (distanceToPlayer < 400 * getStaleX() && game->enemies[i].attackTimer <= 0) {
            int directionToPlayer = (game->man.x < game->enemies[i].x) ? -1 : 1;

            game->enemies[i].x += directionToPlayer * getStaleX();

            game->enemies[i].facingLeft = (directionToPlayer == -1);

            game->enemies[i].state = ENEMY_STATE_WALKING;
        }

        if (game->enemies[i].state == ENEMY_STATE_IDLE) {
            game->enemies[i].animFrame = 0; 
        } else {
            if (game->time % 50 == 0) {
                game->enemies[i].animFrame = 1 - game->enemies[i].animFrame; 
            }
        }

        int attackRange = 300;  
        int stopRange = 50;     

        int direction = (game->man.x < game->enemies[i].x) ? -1 : 1;

        float distance = sqrt(pow(game->man.x - game->enemies[i].x, 2) + pow(game->man.y - game->enemies[i].y, 2));

        if (distance < 400 * getStaleX() && abs(game->man.x - game->enemies[i].x) < 400 * getStaleX()) { 
            if (game->man.x < game->enemies[i].x) {
                game->enemies[i].x -= 1 * getStaleX();
                game->enemies[i].facingLeftTexture = 1;
            } else {
                game->enemies[i].x += 2 * getStaleX();
                game->enemies[i].facingLeftTexture = 0;
            }
        } 

        if (game->enemies[i].x > game->enemies[i].initialX + 100 * getStaleX() ||
            game->enemies[i].x < game->enemies[i].initialX - 100 * getStaleX()) {
            game->enemies[i].state = ENEMY_STATE_WALKING;
        } else {
            game->enemies[i].state = ENEMY_STATE_IDLE;
        }

        if (game->enemies[i].state == ENEMY_STATE_IDLE) {
            game->enemies[i].animFrame = 0; 
        } else {
            if (game->time % 50 == 0) {
                game->enemies[i].animFrame = 1 - game->enemies[i].animFrame; 
            }
        }

        if (distance < attackRange) {
            if (distance > stopRange) {
                game->enemies[i].x += direction * getStaleX();
            }

            if (game->enemies[i].attackTimer <= 0) {
                game->enemies[i].attackState = 0;
                game->enemies[i].attackTimer = 300;  
            }

            if (game->enemies[i].attackState == 0) {

                currentEnemyTexture = game->enemyAttackStart;
            } else if (game->enemies[i].attackState == 1) {
                currentEnemyTexture = game->enemyAttacked;
            } else if (game->enemies[i].attackState == 2) {
                currentEnemyTexture = game->enemyAttackedEnd;
            } else {
                currentEnemyTexture = game->enemyReturn;
            }

            game->enemies[i].attackTimer -= 1;
            if (game->time % 100 == 0) {
                game->enemies[i].attackState = (game->enemies[i].attackState + 1) % 4;
            }
        }

        SDL_Rect enemyRect = {game->scrollX + game->enemies[i].x, game->enemies[i].y, 160 * getStaleX(), 140 * getStaleY()};
        SDL_RenderCopyEx(renderer, currentEnemyTexture, NULL, &enemyRect, 0, NULL, flip);
    }
}

void updateBoss(GameState *game, SDL_Renderer *renderer) {
    static Uint32 bossMoveTimer = 0;
    static Uint32 bossTextureChangeTimer = 0;

    if (SDL_GetTicks() - bossMoveTimer > 6000) {
        game->boss.facingLeft = !game->boss.facingLeft;
        bossMoveTimer = SDL_GetTicks();
    }

    if (SDL_GetTicks() - bossTextureChangeTimer > 500) {
        game->boss.facingLeftTexture = !game->boss.facingLeftTexture;
        bossTextureChangeTimer = SDL_GetTicks();
    }

    float distanceToPlayer = fabs(game->man.x - game->boss.x);

    if (distanceToPlayer * getStaleX() < BOSS_VISIBILITY_RANGE) {
        int bossDirectionToPlayer = (game->man.x < game->boss.x) ? -1 : 1;
        game->boss.x += bossDirectionToPlayer * BOSS_SPEED * getStaleX();

        game->boss.facingLeft = (bossDirectionToPlayer == -1);
        game->boss.facingLeftTexture = !game->boss.facingLeft;

        game->boss.state = BOSS_STATE_ATTACKING;

        game->boss.attackTimer = 300;  
    } else {
        float bossDeltaX = game->boss.facingLeft ? -BOSS_SPEED * getStaleX() : BOSS_SPEED * getStaleX();
        game->boss.x += bossDeltaX;
        game->boss.state = BOSS_STATE_MOVING;
    }

    SDL_Texture *currentBossTexture;

    if (game->boss.state == BOSS_STATE_ATTACKING) {
        if (game->boss.attackState == 0) {
            int bossDirectionToPlayer = (game->man.x < game->boss.x) ? -1 : 1;
            game->boss.x += bossDirectionToPlayer * BOSS_SPEED * 1.5 * getStaleX();
            currentBossTexture = game->bossAttackedStart;
        } else if (game->boss.attackState == 1) {
            int bossDirectionToPlayer = (game->man.x < game->boss.x) ? -1 : 1;
            game->boss.x += bossDirectionToPlayer * BOSS_SPEED * 1.2 * getStaleX();
            currentBossTexture = game->bossAttackedEnd;
        }
    } else {
        currentBossTexture = game->boss.texture;
    }

    SDL_Rect bossRect = {game->scrollX + game->boss.x, game->boss.y, BOSS_WIDTH * getStaleX(), BOSS_HEIGHT * getStaleY()};
    SDL_RendererFlip flip = game->boss.facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, currentBossTexture, NULL, &bossRect, 0, NULL, flip);

    if (game->boss.state == BOSS_STATE_ATTACKING) {
        if (distanceToPlayer < BOSS_ATTACK_RANGE && game->boss.attackTimer <= 0) {
            game->man.health -= 25;
            game->boss.attackTimer = 300;  
        }

        game->boss.attackTimer -= 1;

        if (game->time % 100 == 0) {
            game->boss.attackState = (game->boss.attackState + 1) % 2;
        }
    }
}