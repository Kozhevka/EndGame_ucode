#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "status.h"
#include "menu.h"
#include "map.h"
#include "enemies.h"
#include "interface.h"
#include "character.h"
#include "design.h"



float gravity = 0.03f;
float speed = 1;
int koff = 100;
int addToJump = 1;


int closeApplication = 0;


float getScaleX(){
    float scaleX = (float)getScreenWidht() / 1980;
    return scaleX;
}
float getScaleY(){
    float scaleY = (float)getScreenHeight() / 1080;
    return scaleY;
}

void loadGame(GameState *game)
{
    initializeMainHeroTextures(&(game->playerAnimations), game->renderer);

    for (size_t i = 0; i < NUM_ENEMIES; i++)
    {
        initializeEnemyTextures(&(game->enemyAnimations), game-> renderer);
    }
    
    initializeLocationTextures(&(game->locationTextures), game-> renderer);
    initializeParticleTextures(&(game->particlesTextures), game-> renderer);



    game->font = TTF_OpenFont("assets/fonts/ARCADECLASSIC.TTF", 48);
    if (!game->font)
    {
        printf("cannot find font\n\n");
        SDL_Quit();
        exit(1);
    }

    game->label = NULL;

    // Адаптация размеров персонажей и объектов под экран
    game->man.x = 200 * getScaleX() - 40;
    game->man.y = 800 * getScaleY() - 40;
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
                playerMoveAnimationStep(man);
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
    return !((x1 > (x2 + wt2 * getScaleX())) || (x2 > (x1 + wt1 * getScaleX())) || (y1 > (y2 + ht2 * getScaleY())) || (y2 > (y1 + ht1 * getScaleY())));
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
        float mw = 90 * getScaleX(), mh = 108 * getScaleY();
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

        for (int i = 0; i < 100; i++)
    {
        float mw = 90 * getScaleX(), mh = 108 * getScaleY();
        float mx = game->man.x, my = game->man.y;
        float bx = game->ceilings[i].x, by = game->ceilings[i].y, bw = game->ceilings[i].w, bh = game->ceilings[i].h;

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
                    game->man.dy = -3 * getScaleY();
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

    if(state[SDL_SCANCODE_SPACE] && game->man.isGrounded == 1)
    {
        playerJump(&game->man, addToJump);
    }

    if (state[SDL_SCANCODE_A]) 
    {
        playerMove(&game->man, speed, -1);
    } 
    else if (state[SDL_SCANCODE_D]) 
    {
        playerMove(&game->man, speed, 1);
    }
    else
    {
        playerIdle(&game->man, speed);
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



        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        renderMap(renderer, game);
        
        renderHealth(game);
        SDL_Rect rect = {game->scrollX + game->man.x, game->man.y, 80 * getScaleX(), 120 * getScaleY()};
        SDL_RenderCopyEx(renderer, game->playerAnimations->run[game->man.animFrame], NULL, &rect, 0, NULL, (game->man.facingLeft == 0));

        if (game->man.isDead)
        {
            SDL_Rect rect = {game->scrollX + game->man.x - 24 * getScaleX() - 18 / 2, game->man.y - 24 * getScaleY() - 10 / 2, 140 * getScaleX(), 180 * getScaleY()};
            SDL_RenderCopyEx(renderer, game->playerAnimations->dead, NULL, &rect, 0, NULL, (game->time % 20 == 10));
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

int setPhysics(){
    int width = getScreenWidht();
    if(width <= 800){
    speed = 0.06;
    gravity = 0.01f;
    koff = 100;
    } else if(width <= 1024){
        speed = 0.1;
        gravity = 0.013f;
        koff = 70;
    } else if(width <= 1280){
        speed = 0.16;
        gravity = 0.01f;
        koff = 50;
    } else if(width <= 1360){
        speed = 0.2;
        gravity = 0.01f;
        koff = 50;
    }else if(width <= 1920){
        speed = 2;
        gravity = 0.06f;
        koff = 100;
    }else if(width <= 2560 || width >= 2560){
        speed = 2;
        gravity = 0.05f;
        koff = 20;
        addToJump = 20;
    }

}


int main(int argc, char *argv[])
{
    

    GameState gameState;
    MenuResources menuResources;
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Init(SDL_INIT_VIDEO);
    srandom((int)time(NULL));


    window = SDL_CreateWindow(GetGameName(),
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          getScaleX(),
                          getScaleY(),
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
                setPhysics();
                // Загрузка ресурсов для игры
                loadGame(&gameState);
                initMap(&gameState, getScaleX(), getScaleY());
                updateEnemies(&gameState);
                gameLoaded = 1;
            }

            // Обработка игровых событий
            done = processEvents(window, &gameState);

            // Обновление состояния игры
            process(&gameState);

            updateEnemies(&gameState);

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

