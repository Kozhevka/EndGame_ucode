#ifndef sdl2_game_main_h
#define sdl2_game_main_h

#define STATUS_STATE_LIVES 0
#define STATUS_STATE_GAME 1
#define STATUS_STATE_GAMEOVER 2

#define NUM_ENEMIES 100

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

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
    int isLoaded;

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

//=================================================================================

typedef struct
{
    int isSelected;
    int purpose;
    
    char* menuText;
    SDL_Texture* menuLabel;
    int menuLabelW, menuLabelH;
    int menuX, menuY;

} MenuTextElement;

typedef struct
{
    MenuTextElement* selectedButton;
}   SelectedButtonReference;

typedef struct
{

    MenuTextElement* playButton;
    MenuTextElement* settingsButton;
    MenuTextElement* developersButton;
    MenuTextElement* quitButton;

}   MainMenuButtonReferences;

typedef struct
{
    int isLoaded;

    TTF_Font *font;

    MenuTextElement gameNameText;
    MenuTextElement playText;
    MenuTextElement settingsText;
    MenuTextElement developersText;
    MenuTextElement quitText;

    char* menuText;
    SDL_Texture* menuLabel;
    int menuLabelW, menuLabelH;
    int menuX, menuY;

    SDL_Renderer *renderer;

} MenuResources;

typedef struct
{
    
    int sceneInteger;

} CurrentScene;

enum {
    SCENE_MENU,
    SCENE_GAME,
    QUITGAME,
};

enum {
    MENUBUTTONPURPOSE_UNASSIGNED,
    MENUBUTTONPURPOSE_PLAY,
    MENUBUTTONPURPOSE_SETTINGS,
    MENUBUTTONPURPOSE_DEVELOPERS,
    MENUBUTTONPURPOSE_QUIT,
};

//====================================================================================

void doRender(SDL_Renderer *renderer, GameState *game);
void init_game_over(GameState *game);

#endif


