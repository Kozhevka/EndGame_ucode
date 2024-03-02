#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "main.h"
#include "imageTool.h"

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

    AssignTexture(&locationTextures->brick, imageLocations, brick, renderer);
    AssignTexture(&locationTextures->chandelier, imageLocations, chandelier, renderer);
    AssignTexture(&locationTextures->door, imageLocations, door, renderer);
    AssignTexture(&locationTextures->flag, imageLocations, flag, renderer);
    AssignTexture(&locationTextures->grave, imageLocations, grave, renderer);
    AssignTexture(&locationTextures->scull, imageLocations, scull, renderer);
    AssignTexture(&locationTextures->wall, imageLocations, wall, renderer);
    AssignTexture(&locationTextures->window, imageLocations, window, renderer);
}

void initializeParticleTextures(ParticlesTextures *particleTextures, SDL_Renderer *renderer)
{
    const char* imageLocations = "assets/images/particles/";

    const char* blood = "dead-effect.png";
    AssignTexture(&particleTextures->blood, imageLocations, blood, renderer);
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

    AssignTexture(&animationHolder->flyIdle, (char *)imageLocations, flyIdle, renderer);
    AssignTexture(&animationHolder->gotHit, (char *)imageLocations, gotHit, renderer);
    AssignTexture(&animationHolder->idle, (char *)imageLocations, idle, renderer);
    AssignTexture(&animationHolder->jump, (char *)imageLocations, jump, renderer);
    AssignTexture(&animationHolder->run[0], (char *)imageLocations, runImg0, renderer);
    AssignTexture(&animationHolder->run[1], (char *)imageLocations, runImg1, renderer);
    AssignTexture(&animationHolder->run[2], (char *)imageLocations, runImg2, renderer);
    AssignTexture(&animationHolder->run[3], (char *)imageLocations, runImg3, renderer);
    AssignTexture(&animationHolder->hit_accumulate_0, (char *)imageLocations, hit_accumulate_0, renderer);
    AssignTexture(&animationHolder->hit_accumulate_1, (char *)imageLocations, hit_accumulate_1, renderer);
    AssignTexture(&animationHolder->hit_accumulate_2, (char *)imageLocations, hit_accumulate_2, renderer);
    AssignTexture(&animationHolder->hit_perform, (char *)imageLocations, hit_perform, renderer);

}

void initializeEnemyTextures(AnimationEnemyHolder *animationHolder, SDL_Renderer *renderer)
{
    const char* imageLocations = "assets/images/enemy/";

    const char* attackStart = "enemy_attack_start.png";
    const char* attackEnd = "enemy_attacked_end.png";
    const char* attack = "enemy_attacked.png";
    const char* idle = "enemy_idle.png";
    const char* walk = "enemy_walk.png";

    AssignTexture(&animationHolder->attackStart, (char *)imageLocations, attackStart, renderer);
    AssignTexture(&animationHolder->attackedContinue, (char *)imageLocations, attack, renderer);
    AssignTexture(&animationHolder->attackedEnd, (char *)imageLocations, attackEnd, renderer);
    AssignTexture(&animationHolder->idle, (char *)imageLocations, idle, renderer);
    AssignTexture(&animationHolder->walk, (char *)imageLocations, walk, renderer);
}


void disposeMainHeroTextures(AnimationMainHeroHolder *animationHolder)
{
    SDL_DestroyTexture(animationHolder->flyIdle);
    SDL_DestroyTexture(animationHolder->gotHit);
    SDL_DestroyTexture(animationHolder->idle);
    SDL_DestroyTexture(animationHolder->jump);
    SDL_DestroyTexture(animationHolder->run[0]);
    SDL_DestroyTexture(animationHolder->run[1]);
    SDL_DestroyTexture(animationHolder->run[2]);
    SDL_DestroyTexture(animationHolder->run[3]);
    SDL_DestroyTexture(animationHolder->hit_accumulate_0);
    SDL_DestroyTexture(animationHolder->hit_accumulate_1);
    SDL_DestroyTexture(animationHolder->hit_accumulate_2);
    SDL_DestroyTexture(animationHolder->hit_perform);
}

void disposeEnemyTextures(AnimationEnemyHolder *animationHolder)
{
    SDL_DestroyTexture(animationHolder->attackStart);
    SDL_DestroyTexture(animationHolder->attackedContinue);
    SDL_DestroyTexture(animationHolder->attackedEnd);
    SDL_DestroyTexture(animationHolder->idle);
    SDL_DestroyTexture(animationHolder->walk);
}

void disposeLocationTextures(LocationTextures *locationTextures)
{
    SDL_DestroyTexture(locationTextures->brick);
    SDL_DestroyTexture(locationTextures->chandelier);
    SDL_DestroyTexture(locationTextures->door);
    SDL_DestroyTexture(locationTextures->flag);
    SDL_DestroyTexture(locationTextures->grave);
    SDL_DestroyTexture(locationTextures->scull);
    SDL_DestroyTexture(locationTextures->wall);
    SDL_DestroyTexture(locationTextures->window);
}

void disposeParticleTextures(ParticlesTextures *particleTextures)
{
    SDL_DestroyTexture(particleTextures->blood);
}