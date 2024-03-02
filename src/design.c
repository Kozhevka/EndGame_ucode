#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "main.h"
#include "resourceTool.h"

//void initializeMainHero(AnimationMainHeroHolder *animationHolder, SDL_Renderer *renderer);
//void initializeEnemy(AnimationEnemyHolder *animationHolder, SDL_Renderer *renderer);
//void initializeLocationTexture(LocationTextures *locationTextures, SDL_Renderer *renderer);
//void initializeParticleTexture(ParticlesTextures *particleTextures, SDL_Renderer *renderer);

void initializeLocationTextures(LocationTextures *locationTextures, SDL_Renderer *renderer)
{
    const char* imageLocations = "assets/images/location/";

    const char* brick = "brick.png";
    const char* chandelier = "chandelier.png";
    const char* door = "door.png";
    const char* flag = "flag.png";
    const char* grave = "grave.png";
    const char* scull = "scull.png";
    const char* wall = "wall.png";
    const char* window = "window.png";

    locationTextures->brick = GetTexture(imageLocations, brick, renderer);
    locationTextures->chandelier = GetTexture(imageLocations, chandelier, renderer);
    locationTextures->door = GetTexture(imageLocations, door, renderer);
    locationTextures->flag = GetTexture(imageLocations, flag, renderer);
    locationTextures->grave = GetTexture(imageLocations, grave, renderer);
    locationTextures->scull = GetTexture(imageLocations, scull, renderer);
    locationTextures->wall = GetTexture(imageLocations, wall, renderer);
    locationTextures->window = GetTexture(imageLocations, window, renderer);
}

void initializeParticleTextures(ParticlesTextures *particleTextures, SDL_Renderer *renderer)
{
    const char* imageLocations = "assets/images/particles/";

    const char* blood = "dead-effect.png";
    particleTextures->blood = GetTexture(imageLocations, blood, renderer);
}

void initializeMainHeroTextures(AnimationMainHeroHolder *animationHolder, SDL_Renderer *renderer)
{
    const char* imageLocations = "assets/images/mainHero/";
    
    const char* flyIdle = "gg_flyIdle.png";
    const char* gotHit = "gg_gotHit.png";
    const char* idle = "gg_idle.png";
    const char* jump = "gg_jump.png";

    const char* runImg0 = "gg_run0.png";
    const char* runImg1 = "gg_run1.png";
    const char* runImg2 = "gg_run2.png";
    const char* runImg3 = "gg_run3.png";

    
    const char* hit_accumulate_0 = "hit_accumulate_0.png";
    const char* hit_accumulate_1 = "hit_accumulate_1.png";
    const char* hit_accumulate_2 = "hit_accumulate_2.png";
    const char* hit_perform = "hit_perform.png";

    animationHolder->flyIdle = GetTexture(imageLocations, flyIdle, renderer);
    animationHolder->gotHit = GetTexture(imageLocations, gotHit, renderer);
    animationHolder->idle = GetTexture(imageLocations, idle, renderer);
    animationHolder->jump = GetTexture(imageLocations, jump, renderer);
    animationHolder->run[0] = GetTexture(imageLocations, runImg0, renderer);
    animationHolder->run[1] = GetTexture(imageLocations, runImg1, renderer);
    animationHolder->run[2] = GetTexture(imageLocations, runImg2, renderer);
    animationHolder->run[3] = GetTexture(imageLocations, runImg3, renderer);
    animationHolder->hit_accumulate_0 = GetTexture(imageLocations, hit_accumulate_0, renderer);
    animationHolder->hit_accumulate_1 = GetTexture(imageLocations, hit_accumulate_1, renderer);
    animationHolder->hit_accumulate_2 = GetTexture(imageLocations, hit_accumulate_2, renderer);
    animationHolder->hit_perform = GetTexture(imageLocations, hit_perform, renderer);

}

void initializeEnemyTextures(AnimationEnemyHolder *animationHolder, SDL_Renderer *renderer)
{
    const char* imageLocations = "assets/images/enemy/";

    const char* attackStart = "enemy_attack_start.png";
    const char* attackEnd = "enemy_attacked_end.png";
    const char* attack = "enemy_attacked.png";
    const char* idle = "enemy_idle.png";
    const char* walk = "enemy_walk.png";

    animationHolder->attackStart = GetTexture(imageLocations, attackStart, renderer);
    animationHolder->attackedContinue = GetTexture(imageLocations, attack, renderer);
    animationHolder->attackedEnd = GetTexture(imageLocations, attackEnd, renderer);
    animationHolder->idle = GetTexture(imageLocations, idle, renderer);
    animationHolder->walk = GetTexture(imageLocations, walk, renderer);
}