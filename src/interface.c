#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "status.h"
#include "interface.h"


void renderHealth(GameState *game) {
    // Преобразование значения здоровья в строку
    char healthText[20];
    snprintf(healthText, sizeof(healthText), "HP %d", game->man.health);

    // Создание поверхности текста
    SDL_Color textColor = {255, 255, 255}; // Белый цвет текста
    SDL_Surface* textSurface = TTF_RenderText_Solid(game->font, healthText, textColor);
    if (!textSurface) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        // Создание текстовой текстуры из поверхности
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(game->renderer, textSurface);
        if (!textTexture) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        } else {
            // Отображение текстовой текстуры в верхнем правом углу экрана
            int textWidth = textSurface->w;
            int textHeight = textSurface->h;
            SDL_Rect dstRect = {250 - textWidth - 10, 10, textWidth, textHeight};
            SDL_RenderCopy(game->renderer, textTexture, NULL, &dstRect);
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
        }
    }
}