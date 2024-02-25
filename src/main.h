#ifndef sdl2_game_main_h
#define sdl2_game_main_h

#define STATUS_STATE_LIVES 0
#define STATUS_STATE_GAME 1
#define STATUS_STATE_GAMEOVER 2

#define NUM_ENEMIES 100

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

typedef struct
{
    float x, y;
    float dy, dx;
    short lives;
    char *name;
    int onLedge, isDead;

    int animFrame, facingLeft, slowingDown;

} Man;

typedef struct
{
    int x, y;
} Enemy;

typedef struct
{
    int x, y, w, h;
} Ledge;

typedef struct
{

    float scrollX;

    Man man;

    Enemy enemies[NUM_ENEMIES];

    Ledge ledges[100];

    SDL_Texture *enemy;
    SDL_Texture *manFrames[4];
    SDL_Texture *brick;
    SDL_Texture *deadEffect;
    SDL_Texture *label;
    SDL_Texture *graveTexture;
    int labelW, labelH;

    TTF_Font *font;

    int time , deathCountdown;
    int statusState;


    SDL_Renderer *renderer;
} GameState;


void doRender(SDL_Renderer *renderer, GameState *game);
void init_game_over(GameState *game);

#endif


