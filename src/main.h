#ifndef sdl2_game_main_h
#define sdl2_game_main_h

#define STATUS_STATE_LIVES 0
#define STATUS_STATE_GAME 1
#define STATUS_STATE_GAMEOVER 2

#define NUM_ENEMIES 30
#define NUM_SCULLS 1000
#define NUM_LADGES 100
#define NUM_WINDOWS 500


// #define SCREEN_WIDTH 1920
// #define SCREEN_HEIGHT 1080

// 2560 1440
// 1920 1080
// 1360 768
// 1280 720
// 1024 768
// 800 600

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
    int x, y, w, h;
} Ceiling;

typedef struct
{
    int x, y, w, h;
} Wall;

typedef struct
{
    int x, y, w, h;
} Door;

typedef struct
{
    int x, y, w, h, random;
} Window;

typedef struct
{
    int x, y, w, h, random;
} Scull;

typedef struct
{
    int isLoaded;

    float scrollX;

    Man man;

    Enemy enemies[NUM_ENEMIES];

    Ledge ledges[NUM_LADGES];
    Ceiling ceilings[NUM_LADGES];
    Wall walls[NUM_LADGES];
    Door doors;
    Window windows[NUM_WINDOWS];
    Scull sculls[NUM_SCULLS];

    SDL_Texture *scull;
    SDL_Texture *window;
    SDL_Texture *door;
    SDL_Texture *wall;
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

    MenuTextElement* resolutionButton;
    MenuTextElement* fullscreenButton;
    MenuTextElement* leaveSettingsButton;

    MenuTextElement* leaveDevelopersButton;

}   MainMenuButtonReferences;

typedef struct
{
    int isLoaded;

    TTF_Font *font;

//==========MAINMENUCATEGORY

    MenuTextElement gameNameText;
    MenuTextElement playText;
    MenuTextElement settingsText;
    MenuTextElement developersText;
    MenuTextElement quitText;

//==============================

//==========SETTINGSCATEGORY
    
    MenuTextElement settingsCaptionText;
    MenuTextElement resolutionText;
    MenuTextElement fullscreenText;
    MenuTextElement leaveSettingsText;

//==============================


//==========DEVELOPERSCATEGORY

    MenuTextElement developersMenuText;
    MenuTextElement andreyKlText;
    MenuTextElement bogdanText;
    MenuTextElement iliaText;
    MenuTextElement sergeyText;
    MenuTextElement yuriyText;
    MenuTextElement andreyKuText;
    MenuTextElement leaveDevelopersMenuText;

//==============================

    char* menuText;
    SDL_Texture* menuLabel;
    int menuLabelW, menuLabelH;
    int menuX, menuY;

    SDL_Texture *menuBackground;

    SDL_Window *applicationWindow;
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
    MENUBUTTONPURPOSE_LEAVEDEVELOPERSMENU,
    MENUBUTTONPURPOSE_CLOSESETTINGS,
    MENUBUTTONPURPOSE_TOGGLEFULLSCREEN,
    MENUBUTTONPURPOSE_TOGGLERESOLUTION,
};

enum {
    MENU_MAINMENU,
    MENU_SETTINGS,
    MENU_DEVELOPERS,
};

enum {
    RESOLUTION_DEFAULT,
    RESOLUTION_SVGA,
    RESOLUTION_XGA,
    RESOLUTION_HD,
    RESOLUTION_FHD,
    RESOLUTION_QHD,
};

//====================================================================================

void doRender(SDL_Renderer *renderer, GameState *game);
void init_game_over(GameState *game);
float getStaleX();
float getStaleY();
#endif


