#include "map.h"
#include <stdlib.h>
#include <stdio.h>

void initMap(GameState *game, float scaleX, float scaleY) {
    // Пример инициализации блоков
    for (int i = 0; i < 100; i++) {
        game->ledges[i].w = (int)(256 * scaleX);
        game->ledges[i].h = (int)(64 * scaleY);
        game->ledges[i].x = (int)(i * (252) * scaleX); 
        game->ledges[i].y = SCREEN_HEIGHT - game->ledges[i].h * 3; 
    }

    // Пример инициализации врагов
    for (int i = 0; i < NUM_ENEMIES; i++) {
        int randomBlock;
        do {
            // Выбираем случайный блок
            randomBlock = rand() % 100;
            // Проверяем, что блок не слишком близко к началу
        } while (game->ledges[randomBlock].x < 500 * scaleX);

        // Устанавливаем врага наверху выбранного блока
        game->enemies[i].x = game->ledges[randomBlock].x + game->ledges[randomBlock].w / 2 - 80 * scaleX / 2;
        game->enemies[i].y = game->ledges[randomBlock].y - 140 * scaleY;
    }
}

void renderMap(SDL_Renderer *renderer, GameState *game) {
    float scaleX = (float)SCREEN_WIDTH / 1980.0f;
    float scaleY = (float)SCREEN_HEIGHT / 1080.0f;

    // Пример отрисовки блоков
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < 100; i++) {
        SDL_Rect ledgeRect = {game->scrollX + game->ledges[i].x, game->ledges[i].y, game->ledges[i].w, game->ledges[i].h};
        SDL_RenderCopy(renderer, game->brick, NULL, &ledgeRect);
    }

    // Пример отрисовки врагов
    for (int i = 0; i < NUM_ENEMIES; i++) {
        SDL_Rect enemyRect = {game->scrollX + game->enemies[i].x, game->enemies[i].y, 160 * scaleX, 140 * scaleY};
        SDL_RenderCopy(renderer, game->enemy, NULL, &enemyRect);
    }
}
