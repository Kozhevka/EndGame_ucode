#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "main.h"
#include "imageTool.h"

//void initializeMainHero(AnimationMainHeroHolder *animationHolder, SDL_Renderer *renderer);
//void initializeEnemy(AnimationEnemyHolder *animationHolder, SDL_Renderer *renderer);
//void initializeLocationTexture(LocationTextures *locationTextures, SDL_Renderer *renderer);
//void initializeParticleTexture(ParticlesTextures *particleTextures, SDL_Renderer *renderer);

void initializeLocationTexture(LocationTextures *locationTextures, SDL_Renderer *renderer)
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

    AssignTexture(locationTextures->brick, (char *)imageLocations, brick, renderer);
    AssignTexture(locationTextures->chandelier, (char *)imageLocations, chandelier, renderer);
    AssignTexture(locationTextures->door, (char *)imageLocations, door, renderer);
    AssignTexture(locationTextures->flag, (char *)imageLocations, flag, renderer);
    AssignTexture(locationTextures->grave, (char *)imageLocations, grave, renderer);
    AssignTexture(locationTextures->scull, (char *)imageLocations, scull, renderer);
    AssignTexture(locationTextures->wall, (char *)imageLocations, wall, renderer);
    AssignTexture(locationTextures->window, (char *)imageLocations, window, renderer);
}

void initializeParticleTexture(ParticlesTextures *particleTextures, SDL_Renderer *renderer)
{
    const char* imageLocations = "assets/images/particles/";

    const char* blood = "dead-effect.png";
    AssignTexture(particleTextures->blood, imageLocations, blood, renderer);
}

void initializeMainHero(AnimationMainHeroHolder *animationHolder, SDL_Renderer *renderer)
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

    AssignTexture(animationHolder->flyIdle, (char *)imageLocations, flyIdle, renderer);
    AssignTexture(animationHolder->gotHit, (char *)imageLocations, gotHit, renderer);
    AssignTexture(animationHolder->idle, (char *)imageLocations, idle, renderer);
    AssignTexture(animationHolder->jump, (char *)imageLocations, jump, renderer);
    AssignTexture(animationHolder->run[0], (char *)imageLocations, runImg0, renderer);
    AssignTexture(animationHolder->run[1], (char *)imageLocations, runImg1, renderer);
    AssignTexture(animationHolder->run[2], (char *)imageLocations, runImg2, renderer);
    AssignTexture(animationHolder->run[3], (char *)imageLocations, runImg3, renderer);

    
    AssignTexture(animationHolder->hit_accumulate_0, (char *)imageLocations, hit_accumulate_0, renderer);
    AssignTexture(animationHolder->hit_accumulate_1, (char *)imageLocations, hit_accumulate_1, renderer);
    AssignTexture(animationHolder->hit_accumulate_2, (char *)imageLocations, hit_accumulate_2, renderer);
    AssignTexture(animationHolder->hit_perform, (char *)imageLocations, hit_perform, renderer);

}

void initializeEnemy(AnimationEnemyHolder *animationHolder, SDL_Renderer *renderer)
{
    const char* imageLocations = "assets/images/enemy/";

    const char* attackStart = "enemy_attack_start.png";
    const char* attackEnd = "enemy_attacked_end.png";
    const char* attack = "enemy_attacked.png";
    const char* idle = "enemy_idle.png";
    const char* walk = "enemy_walk.png";

    AssignTexture(animationHolder->attackStart, (char *)imageLocations, attackStart, renderer);
    AssignTexture(animationHolder->attackedContinue, (char *)imageLocations, attack, renderer);
    AssignTexture(animationHolder->attackedEnd, (char *)imageLocations, attackEnd, renderer);
    AssignTexture(animationHolder->idle, (char *)imageLocations, idle, renderer);
    AssignTexture(animationHolder->walk, (char *)imageLocations, walk, renderer);
}