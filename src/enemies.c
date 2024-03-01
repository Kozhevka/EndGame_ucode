#include "main.h"
#include "enemies.h"



void updateEnemies(GameState *game, SDL_Renderer *renderer) {
    
    // Просто для примера, можно добавить свою логику
    if (game->time % 600 == 0) {
        // Изменяем направление врага каждые 6 секунд
        for (int i = 0; i < NUM_ENEMIES; i++) {
            game->enemies[i].facingLeft = !game->enemies[i].facingLeft;
        }
    }

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

        

        // Добавим новые переменные для удобства
        int attackRange = 300;  // Дистанция, на которой враг начнет атаковать
        int stopRange = 50;     // Дистанция, на которой враг остановится перед атакой

        // Добавим переменную для удобства
        int direction = (game->man.x < game->enemies[i].x) ? -1 : 1;

        float distance = sqrt(pow(game->man.x - game->enemies[i].x, 2) + pow(game->man.y - game->enemies[i].y, 2));

        // Изменяем координаты врага в зависимости от направления
        if (distance < 400 && abs(game->man.x - game->enemies[i].x) < 400) { // Проверяем и расстояние, и положение по X
            if (game->man.x < game->enemies[i].x) {
                game->enemies[i].x -= 1 * getStaleX();
                game->enemies[i].facingLeftTexture = 1;
            } else {
                game->enemies[i].x += 2 * getStaleX();
                game->enemies[i].facingLeftTexture = 0;
            }
        } else if (game->enemies[i].facingLeft) {
            game->enemies[i].x -= 1 * getStaleX();
            // Устанавливаем facingLeft в 1, чтобы текстура была перевернута
            game->enemies[i].facingLeftTexture = 1;
        } else {
            game->enemies[i].x += 1.3 * getStaleX();
            // Устанавливаем facingLeft в 0, чтобы текстура не была перевернута
            game->enemies[i].facingLeftTexture = 0;
        }

        // Изменяем состояние врага в зависимости от его движения
        if (game->enemies[i].x > game->enemies[i].initialX + 100 * getStaleX() ||
            game->enemies[i].x < game->enemies[i].initialX - 100 * getStaleX()) {
            // Если враг двигается влево или вправо, считаем его идущим
            game->enemies[i].state = ENEMY_STATE_WALKING;
        } else {
            // Иначе считаем его в состоянии покоя
            game->enemies[i].state = ENEMY_STATE_IDLE;
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

        // Добавим логику атаки
        if (distance < attackRange) {
            // Враг останавливается перед атакой
            if (distance > stopRange) {
                game->enemies[i].x += direction * getStaleX();
            }

            // Обработка состояния атаки
            if (game->enemies[i].attackTimer <= 0) {
                // Сбрасываем состояние атаки
                game->enemies[i].attackState = 0;
                // Задаем таймер атаки
                game->enemies[i].attackTimer = 300;  // Устанавливаем таймер в 300 кадров (60 кадров в секунду * 5 секунд)
            }

            if (game->enemies[i].attackState == 0) {
                // Начало атаки
                currentEnemyTexture = game->enemyAttackStart;
            } else if (game->enemies[i].attackState == 1) {
                // Атака
                currentEnemyTexture = game->enemyAttacked;
            } else if (game->enemies[i].attackState == 2) {
                // Завершение атаки
                currentEnemyTexture = game->enemyAttackedEnd;
            } else {
                // Исходное положение
                currentEnemyTexture = game->enemyReturn;
            }

            // Уменьшаем таймер атаки
            game->enemies[i].attackTimer -= 1;
            // Переход к следующему состоянию атаки каждые 100 кадров
            if (game->time % 100 == 0) {
                game->enemies[i].attackState = (game->enemies[i].attackState + 1) % 4;
            }
        }
        SDL_Rect enemyRect = {game->scrollX + game->enemies[i].x, game->enemies[i].y, 160 * getStaleX(), 140 * getStaleY()};
        SDL_RenderCopyEx(renderer, currentEnemyTexture, NULL, &enemyRect, 0, NULL, flip);
    }
}