#include "map.h"
#include "menu.h"
#include <stdlib.h>
#include <stdio.h>

void renderMap(SDL_Renderer *renderer, GameState *game);

void initMap(GameState *game, float scaleX, float scaleY) {
    // Пример инициализации блоков
    for (int i = 0; i < 100; i++) {
        game->ledges[i].w = (int)(256 * scaleX);
        game->ledges[i].h = (int)(64 * scaleY);
        game->ledges[i].x = (int)(i * (252) * scaleX); 
        game->ledges[i].y = getHeight() - game->ledges[i].h * 3; 
    }

    // Пример инициализации врагов
    for (int i = 0; i < NUM_ENEMIES; i++) {
        int randomBlock;
        game->enemies[i].speed = 0.2 * scaleX;
        do {
            // Выбираем случайный блок
            randomBlock = rand() % 100;
            // Проверяем, что блок не слишком близко к началу
        } while (game->ledges[randomBlock].x < 500 * scaleX);

        // Устанавливаем врага наверху выбранного блока
        game->enemies[i].x = game->ledges[randomBlock].x + game->ledges[randomBlock].w / 2 - 80 * scaleX / 2;
        game->enemies[i].y = game->ledges[randomBlock].y - 140 * scaleY;
        game->enemies[i].animFrame = 0;
        game->enemies[i].facingLeft = 1;
        game->enemies[i].speed = 0.2 * scaleX;
    }
}

void renderMap(SDL_Renderer *renderer, GameState *game) {

    // Пример отрисовки блоков
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < 100; i++) {
        SDL_Rect ledgeRect = {game->scrollX + game->ledges[i].x, game->ledges[i].y, game->ledges[i].w, game->ledges[i].h};
        SDL_RenderCopy(renderer, game->brick, NULL, &ledgeRect);
    }

    // Пример отрисовки врагов
    for (int i = 0; i < NUM_ENEMIES; i++) {
        SDL_RendererFlip flip = game->enemies[i].facingLeftTexture ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        SDL_Texture *currentEnemyTexture;

        if (game->enemies[i].state == ENEMY_STATE_IDLE) {
            currentEnemyTexture = game->enemy;
        } else {
            // Чтобы чередовать между game->enemy и game->enemyGo, используйте game->enemies[i].animFrame
            if (game->enemies[i].animFrame == 0) {
                currentEnemyTexture = game->enemy;
            } else {
                currentEnemyTexture = game->enemyGo;
            }
        }

        SDL_Rect enemyRect = {game->scrollX + game->enemies[i].x, game->enemies[i].y, 160 * getStaleX(), 140 * getStaleY()};
        SDL_RenderCopyEx(renderer, currentEnemyTexture, NULL, &enemyRect, 0, NULL, flip);
    }
}
