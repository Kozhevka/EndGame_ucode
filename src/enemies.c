#include "main.h"
#include "enemies.h"

void updateEnemies(GameState *game) {
    // Просто для примера, можно добавить свою логику
    if (game->time % 600 == 0) {
        // Изменяем направление врага каждые 6 секунд
        for (int i = 0; i < NUM_ENEMIES; i++) {
            game->enemies[i].facingLeft = !game->enemies[i].facingLeft;
        }
    }

    for (int i = 0; i < NUM_ENEMIES; i++) {
        // Изменяем координаты врага в зависимости от направления
        if (game->enemies[i].facingLeft) {
            game->enemies[i].x -= 1 * getScaleX();
            // Устанавливаем facingLeft в 1, чтобы текстура была перевернута
            game->enemies[i].facingLeftTexture = 1;
        } else {
            game->enemies[i].x += 1 * getScaleX();
            // Устанавливаем facingLeft в 0, чтобы текстура не была перевернута
            game->enemies[i].facingLeftTexture = 0;
        }

        // Обновляем кадр анимации в каждом кадре
        if (game->enemies[i].state == ENEMY_STATE_IDLE) {
            game->enemies[i].animFrame = 0; // Кадр покоя
        } else {
            // Изменяем текстуру каждые 100 кадров
            if (game->time % 50 == 0) {
                game->enemies[i].animFrame = 1 - game->enemies[i].animFrame; // Переключаем между 0 и 1
            }
        }
    }
}