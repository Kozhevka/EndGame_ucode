#include <stdio.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include "sounds.h"

Mix_Chunk *jumpSound = NULL;
Mix_Chunk *landSound = NULL;
Mix_Music *bgMusic = NULL;

int initSounds() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return 0;
    }

    jumpSound = Mix_LoadWAV("jump.wav");
    if (jumpSound == NULL) {
        printf("Failed to load jump sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return 0;
    }

    landSound = Mix_LoadWAV("land.wav");
    if (landSound == NULL) {
        printf("Failed to load land sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return 0;
    }

    bgMusic = Mix_LoadMUS("underdrop.wav");
    if (bgMusic == NULL) {
        printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
        return 0;
    }

    SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);

    return 1;
}

void closeSounds() {
    Mix_FreeChunk(jumpSound);
    Mix_FreeChunk(landSound);
    Mix_FreeMusic(bgMusic);

    Mix_CloseAudio();
}

void playSound(Mix_Chunk* sound) {
    Mix_PlayChannel(-1, sound, 0);
}

void playWalkSound() {
    if (Mix_Playing(1) == 0) {
        Mix_PlayChannel(1, landSound, 0);
    }
}

void playJumpSound() {
    Mix_PlayChannel(-1, jumpSound, 0);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (!initSounds()) {
        return 1;
    }

    Mix_PlayMusic(bgMusic, -1);

    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_a:
                        case SDLK_d:
                            playWalkSound();
                            break;
                        case SDLK_SPACE:
                            playJumpSound();
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        // Update game logic and render here

        SDL_Delay(10); // Delay to reduce CPU usage
    }

    closeSounds();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
