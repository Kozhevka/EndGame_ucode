#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "character.h"

void initializeMainHero(AnimationMainHeroHolder *animationHolder, SDL_Renderer *renderer);
void initializeEnemy(AnimationEnemyHolder *animationHolder, SDL_Renderer *renderer);
void initializeLocationTexture(LocationTextures *locationTextures, SDL_Renderer *renderer);
void initializeParticleTexture(ParticlesTextures *particleTextures, SDL_Renderer *renderer);

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
} ParticlesTextur;

