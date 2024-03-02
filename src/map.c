#include "map.h"
#include "enemies.h"
#include "menu.h"
#include <stdlib.h>
#include <stdio.h>

void initMap(GameState *game, float scaleX, float scaleY) {
    for (int i = 0; i < NUM_LADGES; i++) {
        game->ledges[i].w = (int)(256 * scaleX);
        game->ledges[i].h = (int)(64 * scaleY);
        game->ledges[i].x = (int)(i * 252 * scaleX);
        game->ledges[i].y = getHeight() - game->ledges[i].h * 3;
    }

    for (int i = 0; i < NUM_LADGES + NUM_BOSSPLATFORM - 1; i++) {
        game->ceilings[i].w = (int)(256 * scaleX);
        game->ceilings[i].h = (int)(64 * scaleY);
        game->ceilings[i].x = (int)(i * 252 * scaleX);
        game->ceilings[i].y = getHeight() - game->ceilings[i].h * 10;
    }
    for (int i = 0; i < NUM_BOSSPLATFORM; i++) {
        game->bossplatform[i].w = (int)(256 * scaleX);
        game->bossplatform[i].h = (int)(64 * scaleY);
        game->bossplatform[i].x = (int)(i * 252 * scaleX + game->ledges[NUM_LADGES-1].x);
        game->bossplatform[i].y = getHeight() - game->bossplatform[i].h * 3;
    }

    for (int i = 0; i < NUM_WALLS; i++) {
        game->walls[i].w = (int)(405 * scaleX);
        game->walls[i].h = (int)(395 * scaleY - 10);
        game->walls[i].x = (int)(i * 400 * scaleX);
        game->walls[i].y = getHeight() - game->ceilings[i].h * 9;
    }

    for (int i = 0; i < NUM_COLONAS; i++) {
        if(i == 0){
        game->colonas[i].w = (int)(64 * scaleX);
        game->colonas[i].h = (int)(270 * scaleY);
        game->colonas[i].x = (int)(i * 300 * scaleX + game->ledges[NUM_LADGES-1].x+247);
        game->colonas[i].y = getHeight() - game->colonas[i].h * 3 + 160;
        }
        else if (i == 1){
        game->colonas[i].w = (int)(64 * scaleX);
        game->colonas[i].h = (int)(600 * scaleY);
        game->colonas[i].x = (int)(i * 300 * scaleX + game->bossplatform[NUM_BOSSPLATFORM-1].x - 100);
        game->colonas[i].y = getHeight() - game->colonas[i].h * 3 + 1000;
        }
    }
    

    game->doors.w = (int)(256 * scaleX);
    game->doors.h = (int)(258 * scaleY);
    game->doors.x = (int)((game->man.x - 210) * scaleX);
    game->doors.y = getHeight() - game->ledges[1].h * 6 - 12;

    game->bossskeletons.w = (int)(128 * scaleX);
    game->bossskeletons.h = (int)(128 * scaleY);
    game->bossskeletons.x = (int)(game->bossplatform[3].x);
    game->bossskeletons.y = getHeight() - game->ledges[1].h * 5 + 15;


    for (int i = 1; i < NUM_WINDOWS; i++) {
       if ((int)(i * 252 * scaleX) > game->ledges[NUM_LADGES-1].x)
            {
                break;
            }
        if (rand() % 2 == 1) {
            game->windows[i].random = 1;
            game->windows[i].w = (int)(160 * scaleX);
            game->windows[i].h = (int)(160 * scaleY);
            game->windows[i].x = (int)(i * 252 * scaleX);
            game->windows[i].y = getHeight() - game->ledges[i].h * 6;
        } else {
            i++;
        }

    }

        for (int i = 1; i < NUM_FLAGS; i++) {
        if (rand() % 2 == 1 && game->windows[i].random != 1) {
            if ((int)(i * 252 * scaleX) > game->ledges[NUM_LADGES-1].x)
            {
                break;
            }
            game->flags[i].random = 1;
            game->flags[i].w = (int)(200 * scaleX);
            game->flags[i].h = (int)(320 * scaleY);
            game->flags[i].x = (int)(i * 252 * scaleX);
            game->flags[i].y = getHeight() - game->ledges[i].h * 8;
        } else {
            i++;
        }
    }

    for (int i = 1; i < NUM_SCULLS; i++) {
        if (rand() % 10 == 1) {
            if ((int)(i * 70 * scaleX) > game->ledges[NUM_LADGES-1].x)
            {
                break;
            }
            game->sculls[i].random = 1;
            game->sculls[i].w = (int)(100 * scaleX);
            game->sculls[i].h = (int)(100 * scaleY);
            game->sculls[i].x = (int)(i * 70 * scaleX);
            game->sculls[i].y = getHeight() - game->ledges[i].h * 4;
        } else {
            i++;
        }
    }

    for (int i = 0; i < NUM_CHANDELIERS; i++) {
            if ((int)(i * 700 * scaleX) > game->ledges[NUM_LADGES-1].x)
            {
                break;
            }
        game->chandeliers[i].w = (int)(128 * scaleX);
        game->chandeliers[i].h = (int)(128 * scaleY);
        game->chandeliers[i].x = (int)(i * 700 * scaleX);
        game->chandeliers[i].y = getHeight() - game->chandeliers[i].h * 4 - 60;
    }


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
        game->enemies[i].y = game->ledges[randomBlock].y - 120 * scaleY;
        game->enemies[i].animFrame = 0;
        game->enemies[i].facingLeft = 1;
        game->enemies[i].speed = 0.2 * scaleX;
    }

    game->boss.texture = game->bossStand;  // Замените это на соответствующую текстуру
    game->boss.x = game->bossplatform[4].x * scaleX;  // Установите начальные координаты босса
    game->boss.y = 750 * scaleY;  // Установите начальные координаты босса
    game->boss.speed = BOSS_SPEED * scaleX;  // Установите скорость босса


}

void renderMap(SDL_Renderer *renderer, GameState *game) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < NUM_LADGES; i++) {
        SDL_Rect ledgeRect = {game->scrollX + game->ledges[i].x, game->ledges[i].y, game->ledges[i].w, game->ledges[i].h};
        SDL_RenderCopy(renderer, game->brick, NULL, &ledgeRect);
    }
    for (int i = 0; i < NUM_BOSSPLATFORM; i++) {
        SDL_Rect bossplatformRect = {game->scrollX + game->bossplatform[i].x, game->bossplatform[i].y, game->bossplatform[i].w, game->bossplatform[i].h};
        SDL_RenderCopy(renderer, game->brick, NULL, &bossplatformRect);
    }
    for (int i = 0; i < NUM_LADGES + NUM_BOSSPLATFORM - 1; i++) {
        SDL_Rect ceilingRect = {game->scrollX + game->ceilings[i].x, game->ceilings[i].y, game->ceilings[i].w, game->ceilings[i].h};
        SDL_RenderCopy(renderer, game->ceiling, NULL, &ceilingRect);
    }

    for (int i = 0; i < NUM_WALLS; i++) {
        SDL_Rect wallsRect = {game->scrollX + game->walls[i].x, game->walls[i].y, game->walls[i].w, game->walls[i].h};
        SDL_RenderCopy(renderer, game->wall, NULL, &wallsRect);
    }

    for (int i = 0; i < NUM_COLONAS; i++) {
        SDL_Rect colonaRect = {game->scrollX + game->colonas[i].x, game->colonas[i].y, game->colonas[i].w, game->colonas[i].h};
        SDL_RenderCopy(renderer, game->brick, NULL, &colonaRect);
    }


    for (int i = 1; i < NUM_WINDOWS; i++) {
        if (game->windows[i].random == 1) {
            SDL_Rect windowsRect = {game->scrollX + game->windows[i].x, game->windows[i].y, game->windows[i].w, game->windows[i].h};
            SDL_RenderCopy(renderer, game->window, NULL, &windowsRect);
        } else {
            i++;
        }
    }

    for (int i = 1; i < NUM_FLAGS; i++) {
        if (game->flags[i].random == 1) {
            SDL_Rect flagsRect = {game->scrollX + game->flags[i].x, game->flags[i].y, game->flags[i].w, game->flags[i].h};
            SDL_RenderCopy(renderer, game->flag, NULL, &flagsRect);
        } else {
            i++;
        }
    }

    for (int i = 1; i < NUM_SCULLS; i++) {
        if (game->sculls[i].random == 1) {
            SDL_Rect scullsRect = {game->scrollX + game->sculls[i].x, game->sculls[i].y, game->sculls[i].w, game->sculls[i].h};
            SDL_RenderCopy(renderer, game->scull, NULL, &scullsRect);
        } else {
            i++;
        }
    }

    for (int i = 0; i < NUM_CHANDELIERS; i++) {
        SDL_Rect chandelierRect = {game->scrollX + game->chandeliers[i].x, game->chandeliers[i].y, game->chandeliers[i].w, game->chandeliers[i].h};
        SDL_RenderCopy(renderer, game->chandelier, NULL, &chandelierRect);
    }

    SDL_Rect doorRect = {game->scrollX + game->doors.x, game->doors.y, game->doors.w, game->doors.h};
    SDL_RenderCopy(renderer, game->door, NULL, &doorRect);

    updateEnemies(game, renderer);

    updateBoss(game, renderer);

    SDL_Rect bossskeletonRect = {game->scrollX + game->bossskeletons.x, game->bossskeletons.y, game->bossskeletons.w, game->bossskeletons.h};
    SDL_RenderCopy(renderer, game->bossskeleton, NULL, &bossskeletonRect);

}