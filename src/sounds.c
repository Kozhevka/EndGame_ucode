#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "status.h"
#include "menu.h"
#include "map.h"
#include "sounds.h"
#include "enemies.h"
#include "interface.h"

void playSound(const char* filename) {
    SDL_Init(SDL_INIT_AUDIO);

    // Полный путь к файлу
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "resource/sounds/%s", filename);

    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8* wavBuffer;

    SDL_LoadWAV(fullPath, &wavSpec, &wavBuffer, &wavLength);

    wavSpec.callback = NULL;
    wavSpec.userdata = NULL;

    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);  // Разрешить воспроизведение звука

    // Ожидание завершения воспроизведения
    while (SDL_GetQueuedAudioSize(deviceId) > 0) {
        SDL_Delay(100);
    }

    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
}


// Mix_Chunk *jumpSound = NULL;
// Mix_Chunk *clickSound = NULL;

// Mix_Music *menuMusic = NULL;

// void init_sounds() {
//     // Initialize SDL_mixer
    
//     if (Mix_Init(0) == 0) {
//         printf("Failed to initialize SDL_mixer: %s\n", Mix_GetError());
//         exit(1);
//     }
    
//     if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
//         printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
//         exit(1);
//     }

//     // Load click
//     clickSound = Mix_LoadWAV("resource/sounds/click.wav");
//     if (clickSound == NULL) {
//         printf("Failed to load click sound effect! SDL_mixer Error: %s\n", Mix_GetError());
//         exit(1);
//     }

//     // Load sounds
//     jumpSound = Mix_LoadWAV("resource/sounds/jump.wav");
//     if (jumpSound == NULL) {
//         printf("Failed to load jump sound effect! SDL_mixer Error: %s\n", Mix_GetError());
//         exit(1);
//     }

//     // Load music
//     menuMusic = Mix_LoadMUS("resource/sounds/menu.wav");
//     if (menuMusic == NULL) {
//         printf("Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError());
//         exit(1);
//     }
// }

// void playJumpSound() {
//     Mix_PlayChannel(-1, jumpSound, 0);
// }

// void playClickSound() {
//     Mix_PlayChannel(-1, clickSound, 0);
// }


// void playMenuMusic() {
//     Mix_PlayMusic(menuMusic, 0);
// }

// void close_sounds() {
//     // Free loaded sounds
//     Mix_FreeChunk(jumpSound);
//     Mix_FreeChunk(clickSound);

//     // Free loaded music
//     Mix_FreeMusic(menuMusic);

//     // Quit SDL_mixer
//     Mix_CloseAudio();
// }
