#ifndef DESIGN_H
#define DESIGN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "main.h"

typedef struct
{
    SDL_Texture *brick;
    SDL_Texture *grave;
    SDL_Texture *wall;
    SDL_Texture *door;
    SDL_Texture *window;
    SDL_Texture *scull;
    SDL_Texture *chandelier;
    SDL_Texture *flag;

} LocationTextures;

typedef struct
{
    SDL_Texture *blood;
} ParticlesTextures;


typedef struct
{
    SDL_Texture *idle;
    SDL_Texture *run[4];
    SDL_Texture *jump;
    SDL_Texture *flyIdle;
    SDL_Texture *attack;
    SDL_Texture *gotHit;
    SDL_Texture *dead;
    SDL_Texture *hit_accumulate_0;
    SDL_Texture *hit_accumulate_1;
    SDL_Texture *hit_accumulate_2;
    SDL_Texture *hit_perform;

} AnimationMainHeroHolder;

typedef struct
{
    SDL_Texture *attackStart;
    SDL_Texture *attackedContinue;
    SDL_Texture *attackedEnd;
    SDL_Texture *idle;
    SDL_Texture *walk;

} AnimationEnemyHolder;

void initializeMainHeroTextures(AnimationMainHeroHolder *animationHolder, SDL_Renderer *renderer);
void initializeEnemyTextures(AnimationEnemyHolder *animationHolder, SDL_Renderer *renderer);
void initializeLocationTextures(LocationTextures *locationTextures, SDL_Renderer *renderer);
void initializeParticleTextures(ParticlesTextures *particleTextures, SDL_Renderer *renderer);

void disposeMainHeroTextures(AnimationMainHeroHolder *animationHolder);
void disposeEnemyTextures(AnimationEnemyHolder *animationHolder);
void disposeLocationTextures(LocationTextures *locationTextures);
void disposeParticleTextures(ParticlesTextures *particleTextures);

#endif // DESIGN_H