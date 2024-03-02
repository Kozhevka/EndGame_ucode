#include "main.h"
#include "enemies.h"
#include "menu.h"


void updateEnemies(GameState *game, SDL_Renderer *renderer) {
    // Переменная для отслеживания времени между изменениями направления движения врагов
    static Uint32 enemyMoveTimer = 0;
    // Переменная для отслеживания времени смены текстур
    static Uint32 textureChangeTimer = 0;

    // Если прошло больше 6 секунд, меняем направление врагов и сбрасываем таймер
    if (SDL_GetTicks() - enemyMoveTimer > 6000) {
        for (int i = 0; i < NUM_ENEMIES; i++) {
            game->enemies[i].facingLeft = !game->enemies[i].facingLeft;
        }
        enemyMoveTimer = SDL_GetTicks();
    }

    // Если прошло больше 1 секунды, меняем текстуры и сбрасываем таймер
    if (SDL_GetTicks() - textureChangeTimer > 500) {
        for (int i = 0; i < NUM_ENEMIES; i++) {
            game->enemies[i].facingLeftTexture = !game->enemies[i].facingLeftTexture;
        }
        textureChangeTimer = SDL_GetTicks();
    }

    // Обновляем положение и анимацию врагов в соответствии с их направлением
    for (int i = 0; i < NUM_ENEMIES; i++) {
        // Измените ENEMY_SPEED на значение, которое соответствует вашим требованиям
        float deltaX = game->enemies[i].facingLeft ? -ENEMY_SPEED * getStaleX() : ENEMY_SPEED * getStaleX(); 

        // Обновляем координаты врага
        game->enemies[i].x += deltaX * getStaleX();

        // Устанавливаем состояние врага в зависимости от его движения
        if (deltaX != 0) {
            game->enemies[i].state = ENEMY_STATE_WALKING;
        } else {
            game->enemies[i].state = ENEMY_STATE_IDLE;
        }

        // Выбираем текстуру в зависимости от состояния врага
        SDL_Texture *currentEnemyTexture;
        SDL_RendererFlip flip = game->enemies[i].facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        if (game->enemies[i].state == ENEMY_STATE_IDLE) {
            currentEnemyTexture = game->enemy;
        } else {
            // Используйте game->enemies[i].facingLeftTexture для определения текстуры
            if (game->enemies[i].facingLeftTexture) {
                currentEnemyTexture = game->enemyGo;
            } else {
                currentEnemyTexture = game->enemy;  // Поменяйте на game->enemyGo, если это нужно
            }
        }

        // Добавим переменные для удобства
        float distanceToPlayer = fabs(game->man.x - game->enemies[i].x);

        // Проверим, находится ли игрок достаточно близко
        if (distanceToPlayer < 400 * getStaleX() && game->enemies[i].attackTimer <= 0) {
            // Направление к игроку
            int directionToPlayer = (game->man.x < game->enemies[i].x) ? -1 : 1;

            // Изменяем координаты врага в сторону игрока
            game->enemies[i].x += directionToPlayer * getStaleX();

            // Устанавливаем facingLeft в зависимости от направления к игроку
            game->enemies[i].facingLeft = (directionToPlayer == -1);

            // Устанавливаем состояние врага в зависимости от его движения
            game->enemies[i].state = ENEMY_STATE_WALKING;
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

        int attackRange = 300;  // Дистанция, на которой враг начнет атаковать
        int stopRange = 50;     // Дистанция, на которой враг остановится перед атакой

        // Добавим переменную для удобства
        int direction = (game->man.x < game->enemies[i].x) ? -1 : 1;

        float distance = sqrt(pow(game->man.x - game->enemies[i].x, 2) + pow(game->man.y - game->enemies[i].y, 2));

        // Изменяем координаты врага в зависимости от направления
        if (distance < 400 * getStaleX() && abs(game->man.x - game->enemies[i].x) < 400 * getStaleX()) { // Проверяем и расстояние, и положение по X
            if (game->man.x < game->enemies[i].x) {
                game->enemies[i].x -= 1 * getStaleX();
                game->enemies[i].facingLeftTexture = 1;
            } else {
                game->enemies[i].x += 2 * getStaleX();
                game->enemies[i].facingLeftTexture = 0;
            }
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

void updateBoss(GameState *game, SDL_Renderer *renderer) {
    // Таймеры для движения и смены текстур
    static Uint32 bossMoveTimer = 0;
    static Uint32 bossTextureChangeTimer = 0;

    // Если прошло больше 6 секунд, меняем направление движения босса и сбрасываем таймер
    if (SDL_GetTicks() - bossMoveTimer > 6000) {
        game->boss.facingLeft = !game->boss.facingLeft;
        bossMoveTimer = SDL_GetTicks();
    }

    // Если прошло больше 1 секунды, меняем текстуры и сбрасываем таймер
    if (SDL_GetTicks() - bossTextureChangeTimer > 500) {
        game->boss.facingLeftTexture = !game->boss.facingLeftTexture;
        bossTextureChangeTimer = SDL_GetTicks();
    }

    // Расстояние до игрока
    float distanceToPlayer = fabs(game->man.x - game->boss.x);

    if (distanceToPlayer * getStaleX() < BOSS_VISIBILITY_RANGE) {
        // Если игрок близко, босс атакует
        int bossDirectionToPlayer = (game->man.x < game->boss.x) ? -1 : 1;
        game->boss.x += bossDirectionToPlayer * BOSS_SPEED * getStaleX();

        // Устанавливаем направление и текстуру босса в соответствии с направлением к игроку
        game->boss.facingLeft = (bossDirectionToPlayer == -1);
        game->boss.facingLeftTexture = !game->boss.facingLeft;

        // Устанавливаем состояние босса в атаку
        game->boss.state = BOSS_STATE_ATTACKING;

        // Задаем таймер атаки
        game->boss.attackTimer = 300;  // Устанавливаем таймер в 300 кадров (60 кадров в секунду * 5 секунд)
    } else {
        // Если игрок далеко, босс двигается туда-сюда
        float bossDeltaX = game->boss.facingLeft ? -BOSS_SPEED * getStaleX() : BOSS_SPEED * getStaleX();
        game->boss.x += bossDeltaX;
        game->boss.state = BOSS_STATE_MOVING;
    }

    // Выбор текстуры в зависимости от состояния и направления движения
    SDL_Texture *currentBossTexture;

    if (game->boss.state == BOSS_STATE_ATTACKING) {
        // Выбор текстуры атаки в зависимости от состояния атаки
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
        // Выбор обычной текстуры босса
        currentBossTexture = game->boss.texture;
    }

    // Отрисовка босса
    SDL_Rect bossRect = {game->scrollX + game->boss.x, game->boss.y, BOSS_WIDTH * getStaleX(), BOSS_HEIGHT * getStaleY()};
    SDL_RendererFlip flip = game->boss.facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, currentBossTexture, NULL, &bossRect, 0, NULL, flip);

    // Обработка атаки
    if (game->boss.state == BOSS_STATE_ATTACKING) {
        // Проверяем, попал ли игрок в атаку босса
        if (distanceToPlayer < BOSS_ATTACK_RANGE && game->boss.attackTimer <= 0) {
            // Здесь может быть логика урона для игрока
            game->man.health -= 25;
            // Задаем таймер атаки
            game->boss.attackTimer = 300;  // Таймер атаки
        }

        // Уменьшаем таймер атаки
        game->boss.attackTimer -= 1;

        // Переход к следующему состоянию атаки каждые 100 кадров
        if (game->time % 100 == 0) {
            game->boss.attackState = (game->boss.attackState + 1) % 2;
        }
    }
}