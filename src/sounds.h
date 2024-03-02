#ifndef SOUNDS_H
#define SOUNDS_H

#include <SDL2/SDL_mixer.h>

extern Mix_Chunk *jumpSound;
extern Mix_Chunk *clickSound;
extern Mix_Chunk *menuSound;
extern Mix_Chunk *gameBgSound;
extern Mix_Music *menuMusic;
extern Mix_Music *gameNormalMusic;
extern Mix_Music *gameBossMusic;
extern Mix_Chunk *damageSound;
extern Mix_Chunk *scrollSound;
extern Mix_Chunk *dieSound;

// void init_sounds();
// void playJumpSound();
// void playClickSound();
// void playMenuMusic();
// void close_sounds();

void InitSounds();

void playMenuSound(Mix_Chunk *soundToPlay);
void playSound(Mix_Chunk *soundToPlay);
void playMusic(Mix_Music *musicToPlay);

void close_sounds();

#endif /* SOUNDS_H */
