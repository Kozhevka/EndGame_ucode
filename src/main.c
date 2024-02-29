#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "status.h"
#include "menu.h"
#include "map.h"
#include "interface.h"

float scaleX = (float)SCREEN_WIDTH / 1980.0f;
float scaleY = (float)SCREEN_HEIGHT / 1080.0f;

float gravity = 0.03f;
float speed = 0;
int koff = 100;
int addToJump = 1;


int closeApplication = 0;

void loadGame(GameState *game)
{
    SDL_Surface *surface = NULL;

    surface = IMG_Load("assets/images/enemy.png");
    if (surface == NULL)
    {
        printf("cannot find enemy.png");
        SDL_Quit();
        exit(1);
    }
    game->enemy = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("assets/images/gg-run.png");
    if (surface == NULL)
    {
        printf("cannot find gg-stand.png");
        SDL_Quit();
        exit(1);
    }
    game->manFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("assets/images/gg-stand.png");
    if (surface == NULL)
    {
        printf("cannot find gg-run.png");
        SDL_Quit();
        exit(1);
    }
    game->manFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("assets/images/brick.png");
    game->brick = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("assets/images/dead-effect.png");
    game->deadEffect = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    game->font = TTF_OpenFont("assets/fonts/ARCADECLASSIC.TTF", 48);
    if (!game->font)
    {
        printf("cannot find font\n\n");
        SDL_Quit();
        exit(1);
    }

    surface = IMG_Load("assets/images/grave.png");
    if (surface == NULL)
    {
        printf("cannot find grave.png");
        SDL_Quit();
        exit(1);
    }
    game->graveTexture = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    game->label = NULL;

    // Адаптация размеров персонажей и объектов под экран
    game->man.x = 200 * scaleX - 40;
    game->man.y = 240 * scaleY - 40;
    game->man.dy = 0;
    game->man.onLedge = 0;
    game->man.animFrame = 0;
    game->man.facingLeft = 1;
    game->man.slowingDown = 0;
    game->man.lives = 3;
    game->man.isDead = 0;
    game->man.health = 100;
    game->statusState = STATUS_STATE_LIVES;

    init_status_lives(game);

    game->time = 0;
    game->scrollX = 0;
    game->deathCountdown = -1;

    

    game->isLoaded = 1;
}

void process(GameState *game)
{
    game->time++;

    if (game->man.health < 1)
    {
        game->man.isDead = 1;
    }
    if (game->time > 120)
    {
        shutdown_status_lives(game);
        if (game->statusState != STATUS_STATE_GAME)
        {
            SDL_Delay(2000);
            game->statusState = STATUS_STATE_GAME;
        }
    }

    if (game->statusState == STATUS_STATE_GAME)
    {
        if(!game->man.isDead){
        Man *man = &game->man;
        man->x += man->dx;
        man->y += man->dy;

        if (man->dx != 0 && man->onLedge && !man->slowingDown)
        {
            if (game->time % koff == 0)
            {
                if (man->animFrame == 0)
                {
                    man->animFrame = 1;
                }
                else
                {
                    man->animFrame = 0;
                }
            }
        }

        man->dy += gravity; 
        }

        if (game->man.isDead && game->deathCountdown < 0)
{
    // Проверка перед уменьшением количества жизней
    if (game->man.lives > 0)
    {
        game->man.lives--;
        SDL_Delay(2000);

        // Обновляем экран с количеством жизней
        init_status_lives(game);
        game->statusState = STATUS_STATE_LIVES;
        game->time = 0;

        game->man.isDead = 0;
        game->man.health = 100;
        game->man.x = 200 - 40;
        game->man.y = 240 - 40;
        game->man.dx = 0;
        game->man.dy = 0;
        game->man.onLedge = 0;
    }

    if (game->man.lives == 0)
    {
        // Если жизни закончились, переходим к экрану Game Over
        init_game_over(game);
        game->statusState = STATUS_STATE_GAMEOVER;
        game->time = 0;
    }
}
    }

    game->scrollX = -game->man.x + 500;
    if (game->scrollX > 0)
    {
        game->scrollX = 0;
    }
}

int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2){
    return !((x1 > (x2 + wt2 * scaleX)) || (x2 > (x1 + wt1 * scaleX)) || (y1 > (y2 + ht2 * scaleY)) || (y2 > (y1 + ht1 * scaleY)));
}

void colissionDetect(GameState *game)
{
    for (int i = 0; i < NUM_ENEMIES; i++)
    {

        if(collide2d(game->man.x, game->man.y, game->enemies[i].x,game->enemies[i].y, 48, 48, 64, 64))
        {
            game->man.health -= 25;
            if (game->man.x < game->enemies[i].x) {
                game->man.dx  = -5;
            } else {
                game->man.dx = 5;
            }
                        if (game->man.y < game->enemies[i].y) {
                game->man.dy  = -3;
            } else {
                game->man.dy = 3;
            }
        }
    }

    for (int i = 0; i < 100; i++)
    {
        float mw = 90 * scaleX, mh = 108 * scaleY;
        float mx = game->man.x, my = game->man.y;
        float bx = game->ledges[i].x, by = game->ledges[i].y, bw = game->ledges[i].w, bh = game->ledges[i].h;

        if (mx + mw / 2 > bx && mx + mw / 2 < bx + bw)
        {
            if (my < by + bh && my > by && game->man.dy < 0)
            {
                game->man.y = by + bh;
                my = by + bh;
                game->man.dy = 0;
                game->man.onLedge = 1;
            }
        }
        if (mx + mw > bx && mx < bx + bw)
        {
            if (my + mh > by && my < by && game->man.dy > 0)
            {
                game->man.y = by - mh;
                my = by - mh;
                game->man.dy = 0;
                game->man.onLedge = 1;
            }
        }

        if (my + mh > by && my < by + bh)
        {
            if (mx < bx + bw && mx + mw > bx + bw && game->man.dx < 0)
            {
                game->man.x = bx + bw;
                mx = bx + bw;
                game->man.dx = 0;
            }
            else if (mx + mw > bx && mx < bx && game->man.dx > 0)
            {
                game->man.x = bx - mw;
                mx = bx - mw;
                game->man.dx = 0;
            }
        }
    }
}

int processEvents(SDL_Window *window, GameState *game)
{
    

    SDL_Event event;
    int done = 0;
    while (SDL_PollEvent(&event))
    {
        switch (event.type) 
        {
        case SDL_WINDOWEVENT_CLOSE:
            if (window)
            {
                SDL_DestroyWindow(window);
                window = NULL;
                done = 1;
            }
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                done = 1;
                break;
            case SDLK_SPACE:
                if (game->man.dy == game->man.dy)
                {
                    game->man.dy = -3 * scaleY;
                    game->man.onLedge = 0;
                }
                break;
            }
            break;

        case SDL_QUIT:
            done = 1;
            break;
        }
    }


    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if(state[SDL_SCANCODE_SPACE]){
        game->man.dy -= 0.003f * scaleY * addToJump;
    }

    if (state[SDL_SCANCODE_A]) {
    game->man.dx -= 0.1 * speed;
    if (game->man.dx < -3 * speed) {
        game->man.dx = -3 * speed;
    }
    game->man.facingLeft = 0;
    game->man.slowingDown = 0;
    } else if (state[SDL_SCANCODE_D]) {
    game->man.dx += 0.1 * speed;
    if (game->man.dx > 3 * speed) {
        game->man.dx = 3 * speed;
    }
    game->man.facingLeft = 1;
    game->man.slowingDown = 0;
    }
    else
    {
        game->man.animFrame = 0;
        game->man.dx *= 0.1f * speed;
        game->man.slowingDown = 1;
        if (fabsf(game->man.dx) < 0.1f)
        {
            game->man.dx = 0;
        }
    }

    return done;
}

void doRender(SDL_Renderer *renderer, GameState *game)
{
    if (game->statusState == STATUS_STATE_LIVES)
    {
        draw_status_lives(game);
    }
    else if(game->statusState == STATUS_STATE_GAME){



        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        renderMap(renderer, game);
        
        renderHealth(game);

        SDL_Rect rect = {game->scrollX + game->man.x, game->man.y, 80 * scaleX, 120 * scaleY};
        SDL_RenderCopyEx(renderer, game->manFrames[game->man.animFrame], NULL, &rect, 0, NULL, (game->man.facingLeft == 0));

        if (game->man.isDead)
        {
            SDL_Rect rect = {game->scrollX + game->man.x - 24 * scaleX - 18 / 2, game->man.y - 24 * scaleY - 10 / 2, 140 * scaleX, 180 * scaleY};
            SDL_RenderCopyEx(renderer, game->deadEffect, NULL, &rect, 0, NULL, (game->time % 20 == 10));
        }

    }
    else if (game->statusState == STATUS_STATE_GAMEOVER)
    {
        init_game_over(game);
    }
    SDL_RenderPresent(renderer);
}

void changeScene(CurrentScene *currentSceneData, int sceneInt)
{
    currentSceneData->sceneInteger = sceneInt;
}




int main(int argc, char *argv[])
{
    if(SCREEN_WIDTH <= 800){
    speed = 0.06;
    gravity = 0.01f;
    koff = 100;
    } else if(SCREEN_WIDTH <= 1024){
        speed = 0.1;
        gravity = 0.013f;
        koff = 70;
    } else if(SCREEN_WIDTH <= 1280){
        speed = 0.16;
        gravity = 0.01f;
        koff = 50;
    } else if(SCREEN_WIDTH <= 1360){
        speed = 0.2;
        gravity = 0.01f;
        koff = 50;
    }else if(SCREEN_WIDTH <= 1920){
        speed = 0.9;
        gravity = 0.02f;
        koff = 30;
    }else if(SCREEN_WIDTH <= 2560 || SCREEN_WIDTH >= 2560){
        speed = 2;
        gravity = 0.05f;
        koff = 20;
        addToJump = 20;
    }

    GameState gameState;
    MenuResources menuResources;
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Init(SDL_INIT_VIDEO);
    srandom((int)time(NULL));

    window = SDL_CreateWindow("Game Window",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          SCREEN_WIDTH,
                          SCREEN_HEIGHT,
                          0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    gameState.renderer = renderer;
    menuResources.renderer = renderer;
    menuResources.applicationWindow = window;

    TTF_Init();

    initResourceManagement(&menuResources, &gameState);

    loadMenu(&menuResources);

    int done = 0;
    int gameLoaded = 0;
    CurrentScene currentScene;
    currentScene.sceneInteger = SCENE_MENU;
    SetupSceneChanger(&currentScene);

    init_menu(&menuResources);

    while (!done) {
        if (currentScene.sceneInteger == QUITGAME) done = 1;

        if (currentScene.sceneInteger == SCENE_MENU) {
            done = processInputInMenu(window, &currentScene);
            renderMenu(renderer, &menuResources);
        } else if(currentScene.sceneInteger == SCENE_GAME) {
            if (gameLoaded == 0) {
                // Загрузка ресурсов для игры
                loadGame(&gameState);
                initMap(&gameState, scaleX, scaleY);
                gameLoaded = 1;
            }

            // Обработка игровых событий
            done = processEvents(window, &gameState);

            // Обновление состояния игры
            process(&gameState);

            // Детекция коллизий
            colissionDetect(&gameState);

            // Рендеринг игры
            doRender(renderer, &gameState);
        }
    }

    // Очистка ресурсов
    unloadMenuResources(&menuResources);
    unloadGameResources(&gameState);
    

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();

    return 0;
}

