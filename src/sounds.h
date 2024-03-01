#ifndef SOUNDS_H
#define SOUNDS_H

#include <SDL2/SDL_mixer.h>

// extern Mix_Chunk *jumpSound;
// extern Mix_Chunk *clickSound;
// extern Mix_Music *menuMusic;

// void init_sounds();
// void playJumpSound();
// void playClickSound();
// void playMenuMusic();
// void close_sounds();

void playSound(const char* filename);

#endif /* SOUNDS_H */
