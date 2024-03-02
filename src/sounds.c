#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "main.h"
#include "status.h"
#include "menu.h"
#include "map.h"
#include "sounds.h"
#include "enemies.h"
#include "interface.h"

Mix_Chunk *jumpSound = NULL;
Mix_Chunk *clickSound = NULL;
Mix_Chunk *scrollSound = NULL;
Mix_Chunk *menuSound = NULL;
Mix_Music *menuMusic = NULL;
Mix_Music *menuRoflMusic = NULL;
Mix_Music *gameNormalMusic = NULL;
Mix_Music *gameBossMusic = NULL;
Mix_Chunk *gameBgSound = NULL;
Mix_Chunk *damageSound = NULL;
Mix_Chunk *dieSound = NULL;


bool soundsLoaded = false;

void InitSounds()
{
    if( SDL_Init( SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }

    if( Mix_OpenAudio( 44100, AUDIO_S16SYS, 1, 16324) < 0 )
    {
         printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    // if(isRoflMode())
    // {
    //     menuSound = Mix_LoadWAV("resource/sounds/Twene4-My-heart-bleeds.wav");
    //     if (menuSound == NULL) {
    //         printf("Failed to load click sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    //         exit(1);
    //     }
    // }
    // else
    // {
    //     menuSound = Mix_LoadWAV("resource/sounds/menu.wav");
    //     if (menuSound == NULL) {
    //         printf("Failed to load click sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    //         exit(1);
    //     }
    // }

    // gameBgSound = Mix_LoadWAV("resource/sounds/underdrop.wav");
    // if (gameBgSound == NULL) {
    //     printf("Failed to load click sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    //     exit(1);
    // }

    // Load click
    clickSound = Mix_LoadWAV("resource/sounds/click.wav");
    if (clickSound == NULL) {
        printf("Failed to load click sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }

    scrollSound = Mix_LoadWAV("resource/sounds/scroll.wav");
    if (scrollSound == NULL) {
        printf("Failed to load click sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }


    // Load sounds
    jumpSound = Mix_LoadWAV("resource/sounds/jump.wav");
    if (jumpSound == NULL) {
        printf("Failed to load jump sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }

    damageSound = Mix_LoadWAV("resource/sounds/damage.wav");
    if (damageSound == NULL) {
        printf("Failed to load jump sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }

    dieSound = Mix_LoadWAV("resource/sounds/die.wav");
    if (dieSound == NULL) {
        printf("Failed to load jump sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }

    menuRoflMusic = Mix_LoadMUS("resource/sounds/Twene4-My-heart-bleeds.wav");
    if (menuRoflMusic == NULL) {
        printf("Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }
    
     menuMusic = Mix_LoadMUS("resource/sounds/menumusic.wav");
    if (menuMusic == NULL) {
        printf("Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }

    if(isRoflMode())
    {
        gameNormalMusic = Mix_LoadMUS("resource/sounds/Twene4-My-heart-bleeds.wav");
        if (gameNormalMusic == NULL) {
            printf("Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError());
            exit(1);
        }
    }
    else
    {
        gameNormalMusic = Mix_LoadMUS("resource/sounds/Underdrop.wav");
        if (gameNormalMusic == NULL) {
             printf("Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError());
             exit(1);
        }
    }

    

    gameBossMusic = Mix_LoadMUS("resource/sounds/Underdroptrap.wav");
    if (gameBossMusic == NULL) {
         printf("Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError());
         exit(1);
    }
    
    //MAX 128 MIN 0
    Mix_Volume(-1, 64);
    soundsLoaded = true;
}

void playMenuSound(Mix_Chunk *soundToPlay) {
    if(!soundsLoaded) return;
    if( Mix_Playing(2) == 0 )
    {
        Mix_PlayChannel( 2, soundToPlay, 0 );
    }
}


void playSound(Mix_Chunk *soundToPlay) {
    if(!soundsLoaded) return;
    Mix_PlayChannel( 1, soundToPlay, 0 );
}

void playMusic(Mix_Music *musicToPlay)
{
    if(!soundsLoaded) return;
    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic( musicToPlay, -1 );
    }
    else{
        Mix_HaltMusic();
        Mix_PlayMusic( musicToPlay, -1 );
    }
}

void close_sounds() {
    // Free loaded sounds
    Mix_FreeChunk(jumpSound);
    Mix_FreeChunk(clickSound);
    Mix_FreeChunk(scrollSound);
    Mix_FreeChunk(damageSound);
    Mix_FreeChunk(dieSound);

    // Free loaded music
    Mix_FreeChunk(menuSound);

    // Quit SDL_mixer
    Mix_CloseAudio();
}
