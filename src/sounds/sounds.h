#ifndef sdl2_game_sounds_h
#define sdl2_game_sounds_h

#include <SDL_mixer.h>
#include "main.h"

extern Mix_Chunk *jumpSound;
extern Mix_Chunk *landSound;
extern Mix_Chunk *doubleJumpSound;
extern Mix_Chunk *dieSound;
extern Mix_Chunk *damageSound;
extern Mix_Chunk *swordSound;
extern Mix_Chunk *bowSound;
extern Mix_Chunk *clickSound;
extern Mix_Chunk *scrollSound;

extern Mix_Music *bgMusic;
extern Mix_Music *bossfightMusic;
extern Mix_Music *menuMusic;

int initSounds();
void closeSounds();
Mix_Chunk* loadSound(char* path);
void playSound(Mix_Chunk* sound);

#endif
