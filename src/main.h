#ifndef MAIN_H
#define MAIN_H

#define STATUS_STATE_LIVES 0
#define STATUS_STATE_GAME 1
#define STATUS_STATE_GAMEOVER 2

#define NUM_ENEMIES 3
#define NUM_SCULLS 1000
#define NUM_LADGES 100
#define NUM_WINDOWS 500
#define NUM_CHANDELIERS 200
#define NUM_FLAGS 800
#define NUM_WALLS 68
#define NUM_BOSSPLATFORM 9
#define NUM_COLONAS 2

#define BOSS_ATTACK_RANGE 200
#define BOSS_WIDTH 100
#define BOSS_HEIGHT 150
#define BOSS_SPEED 1

#define BOSS_STATE_IDLE 0
#define BOSS_STATE_MOVING 1
#define BOSS_STATE_ATTACKING 2
#define BOSS_VISIBILITY_RANGE 400.0f 

// #define SCREEN_WIDTH 1920
// #define SCREEN_HEIGHT 1080

#define ENEMY_STATE_ATTACKING 2
#define ENEMY_SPEED 1.0

// 2560 1440
// 1920 1080
// 1360 768
// 1280 720
// 1024 768
// 800 600

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "design.h" 


typedef struct
{
    float x, y;
    float dy, dx;
    short lives;
    char *name;
    int health;
    int onLedge, isDead, isGrounded;
    int animFrame, facingLeft, slowingDown;
} Man;

typedef struct
{
    int x, y;
    int animFrame;   // Переменная для хранения текущего кадра анимации
    int facingLeft;  // Флаг направления врага (0 - вправо, 1 - влево)
    float distance;  // Переменная для отслеживания расстояния
    int leftBound, rightBound;
    int facingLeftTexture; // Флаг направления текстуры (0 - вправо, 1 - влево)
    int attackState;    // Состояние атаки (0 - нет атаки, 1 - начало атаки, 2 - атака, 3 - конец атаки)
    int attackTimer;    // Таймер для отслеживания времени атаки
    float attackTarget; // Координата, куда враг направлен в процессе атаки
    int state;
    float speed;
    float initialX;
    SDL_Texture *texture;
    
} Enemy;

typedef struct
{
    float x, y;
    float dy, dx;
    short lives;
    char *name;
    int health;
    int onLedge, isDead, isGrounded;
    int animFrame, facingLeft, slowingDown;

    // Добавленные поля для босса
    int attackState;    // Состояние атаки (0 - нет атаки, 1 - начало атаки, 2 - атака, 3 - конец атаки)
    int attackTimer;    // Таймер для отслеживания времени атаки
    float attackTarget; // Координата, куда босс направлен в процессе атаки
    int inAttackRange;  // Флаг, указывающий, находится ли игрок в зоне атаки
    int facingLeftTexture; // Флаг направления текстуры (0 - вправо, 1 - влево)
    int state;          // Состояние босса
    float speed;
    float initialX;
    SDL_Texture *texture;

} Boss;

enum {
    ENEMY_STATE_IDLE,
    ENEMY_STATE_WALKING,

};

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
    int x, y, w, h, random;
} Flag;

typedef struct
{
    int x, y, w, h;
} Chandelier;

typedef struct 
{
    int x, y, w, h;
} Boss_platform;

typedef struct
{
    int x, y, w, h;
} Bossskeleton;

typedef struct
{
    int x, y, w, h;
} Colona;


typedef struct
{
    int isLoaded;

    float scrollX;

    Man man;

    Enemy enemies[NUM_ENEMIES];

    Ledge ledges[NUM_LADGES];
    Ceiling ceilings[NUM_LADGES + NUM_BOSSPLATFORM - 1];
    Wall walls[NUM_WALLS];
    Door doors;
    Window windows[NUM_WINDOWS];
    Scull sculls[NUM_SCULLS];
    Chandelier chandeliers[NUM_CHANDELIERS];
    Flag flags[NUM_FLAGS];
    Boss_platform bossplatform[NUM_BOSSPLATFORM];
    Colona colonas[NUM_COLONAS];
    Bossskeleton bossskeletons;

    LocationTextures locationTextures;
    ParticlesTextures particlesTextures;
    AnimationEnemyHolder enemyAnimations;
    AnimationMainHeroHolder playerAnimations;

    SDL_Texture *label;
    SDL_Texture *bossskeleton;
    SDL_Texture *graveTexture;
    SDL_Texture *bossStand;
    SDL_Texture *bossAttackedStart;
    SDL_Texture *bossAttackedEnd;
    
    int labelW, labelH;

    TTF_Font *font;

    int time , deathCountdown;
    int statusState;


    Boss boss;

    SDL_Renderer *renderer;
}GameState;

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
float getScaleX();
float getScaleY();
#endif


