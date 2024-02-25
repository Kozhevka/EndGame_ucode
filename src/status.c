#include <stdio.h>
#include "main.h"


void init_status_lives(GameState *game) {
    char str[128] = "";

    sprintf(str, "x %d", (int)game->man.lives);

    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Surface *tmp = TTF_RenderText_Blended(game->font, str, white); 
    game->labelW = tmp->w;
    game->labelH = tmp->h;
    game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);
    SDL_FreeSurface(tmp);
}
void draw_status_lives(GameState *game)
{
    SDL_Renderer *renderer = game->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Рассчитываем координаты для персонажа и текста
    int centerX = 1980 / 2; // середина по горизонтали
    int centerY = 1080 / 2; // середина по вертикали

    int characterX = centerX - 110; // координаты для персонажа
    int characterY = centerY - 60;
    SDL_Rect rect = {characterX, characterY, 80, 120};
    SDL_RenderCopyEx(renderer, game->manFrames[0], NULL, &rect, 0, NULL, (game->man.facingLeft == 0));

    // Рассчитываем координаты для текста
    int textX = centerX - game->labelW / 2 + 20; // координаты для текста
    int textY = centerY + 10 - game->labelH / 2;
    SDL_Rect textRect = {textX, textY, game->labelW, game->labelH};
    SDL_RenderCopy(renderer, game->label, NULL, &textRect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}
void shutdown_status_lives (GameState *game) {
    SDL_DestroyTexture(game->label);
    game->label = NULL;
}

void init_game_over(GameState *game)
{
    SDL_Renderer *renderer = game->renderer;

    // Отображение могилы
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int centerX = 1980 / 2; // середина по горизонтали
    int centerY = 1080 / 2; // середина по вертикали

    int graveX = centerX - 20; // координаты для могилы
    int graveY = centerY + 10;
    SDL_Rect graveRect = {graveX, graveY, 80, 120};
    SDL_RenderCopyEx(renderer, game->graveTexture, NULL, &graveRect, 0, NULL, SDL_FLIP_NONE);

    // Отображение надписи "gameover"
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *tmp = TTF_RenderText_Blended(game->font, "Game Over", white);
    game->labelW = tmp->w;
    game->labelH = tmp->h;
    game->label = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);

    int textX = centerX - game->labelW / 2 + 20; // координаты для текста
    int textY = centerY - game->labelH / 2 - 50;
    SDL_Rect textRect = {textX, textY, game->labelW, game->labelH};
    SDL_RenderCopy(renderer, game->label, NULL, &textRect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}




