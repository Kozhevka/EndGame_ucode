#include "menu.h"
#include "main.h"
#include <stdbool.h>

MainMenuButtonReferences menuButtonReferences;
SelectedButtonReference selectedMenuButton;
CurrentScene *sceneChangerReference;
int selectedButtonInteger;

int currentMenuCategory;



void loadMenu(MenuResources *resources)
{
    SDL_Surface *surface = NULL;

    resources->font = TTF_OpenFont("assets/fonts/ARCADECLASSIC.TTF", 48);
    if (!resources->font)
    {
        printf("cannot find font\n\n");
        SDL_Quit();
        exit(1);
    }
    resources->isLoaded = 1;
    resources->menuLabel = NULL;
}

void init_menu(MenuResources *resources) {
    // Загрузка текстур для меню
    // SDL_Surface *menuBackgroundSurface = IMG_Load("../assets/images/menu_background.png");
    // if (menuBackgroundSurface == NULL) {
    //     printf("Cannot find menu_background.png\n");
    //     SDL_Quit();
    //     exit(1);
    // }

    // game->menuBackground = SDL_CreateTextureFromSurface(game->renderer, menuBackgroundSurface);
    // SDL_FreeSurface(menuBackgroundSurface);

    // Установка параметров менm

    /*{
        resources->gameNameText.menuText = "name of game";
        SDL_Color white = {255, 255, 255, 255};
        SDL_Surface *tmp = TTF_RenderText_Blended(resources->font, resources->gameNameText.menuText, white);
        resources->gameNameText.menuLabel = SDL_CreateTextureFromSurface(resources->renderer, tmp);
        SDL_FreeSurface(tmp);

        resources->gameNameText.menuLabelW = tmp->w;
        resources->gameNameText.menuLabelH = tmp->h;

        resources->gameNameText.menuX = (1980 - resources->gameNameText.menuLabelW) / 2;
        resources->gameNameText.menuY = 150;//starts from up

        SDL_DestroyTexture(resources->gameNameText.menuLabel);
        resources->gameNameText.menuLabel = NULL;
    }*/
    currentMenuCategory = MENU_MAINMENU;
    SetTextParameters(resources, &resources->gameNameText, "Unnamed", 0, 150, MENUBUTTONPURPOSE_UNASSIGNED);

    SetTextParameters(resources, &resources->playText, "Play", 0, 400, MENUBUTTONPURPOSE_PLAY);
    menuButtonReferences.playButton = &resources->playText;

    SetTextParameters(resources, &resources->settingsText, "Settings", 0, 500, MENUBUTTONPURPOSE_SETTINGS);
    menuButtonReferences.settingsButton = &resources->settingsText;

    SetTextParameters(resources, &resources->developersText, "Developers", 0, 600, MENUBUTTONPURPOSE_DEVELOPERS);
    menuButtonReferences.developersButton = &resources->developersText;

    SetTextParameters(resources, &resources->quitText, "Quit", 0, 700, MENUBUTTONPURPOSE_QUIT);
    menuButtonReferences.quitButton = &resources->quitText;

    SetTextParameters(resources, &resources->developersMenuText, "Developers", 0, 150, MENUBUTTONPURPOSE_UNASSIGNED);
    SetTextParameters(resources, &resources->andreyKlText, "Andrii   Kalashnikov", 0, 250, MENUBUTTONPURPOSE_UNASSIGNED);
    SetTextParameters(resources, &resources->bogdanText, "Bohdan   Yakilevskyi", 0, 350, MENUBUTTONPURPOSE_UNASSIGNED);
    SetTextParameters(resources, &resources->iliaText, "Illia   Kozhevnikov", 0, 450, MENUBUTTONPURPOSE_UNASSIGNED);
    SetTextParameters(resources, &resources->sergeyText, "Serhii   Ivashchuk", 0, 550, MENUBUTTONPURPOSE_UNASSIGNED);
    SetTextParameters(resources, &resources->yuriyText, "Yurii   Kryvoruchka", 0, 650, MENUBUTTONPURPOSE_UNASSIGNED);
    SetTextParameters(resources, &resources->andreyKuText, "Andrii   Kubik", 0, 750, MENUBUTTONPURPOSE_UNASSIGNED);
    SetTextParameters(resources, &resources->leaveDevelopersMenuText, "Leave", 0, 850, MENUBUTTONPURPOSE_LEAVEDEVELOPERSMENU);
    menuButtonReferences.leaveDevelopersButton = &resources->leaveDevelopersMenuText;

    SetElementSelected(menuButtonReferences.playButton);
}

void SetTextParameters(MenuResources *resources, 
MenuTextElement *targetText, 
char* textToSet,
int xPos,
int yPos, int purposeToSet)
{
    targetText->menuText = textToSet;
    targetText->isSelected = 0;
    targetText->purpose = purposeToSet;
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *tmp = TTF_RenderText_Blended(resources->font, targetText->menuText, white);
    targetText->menuLabel = SDL_CreateTextureFromSurface(resources->renderer, tmp);
    SDL_FreeSurface(tmp);

    

    targetText->menuLabelW = tmp->w;
    targetText->menuLabelH = tmp->h;

    targetText->menuX = (1980 - targetText->menuLabelW) / 2;
    targetText->menuY = yPos;//starts from up

    SDL_DestroyTexture(targetText->menuLabel);
    targetText->menuLabel = NULL;
}

void SetElementSelected(MenuTextElement *targetText)
{
    selectedMenuButton.selectedButton = targetText;
    targetText->isSelected = 1;
}



void renderMenu(SDL_Renderer *renderer, MenuResources *resources) 
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if(currentMenuCategory == MENU_MAINMENU)
    {
    drawText(renderer, resources, &resources->gameNameText);
    drawText(renderer, resources, &resources->playText);
    drawText(renderer, resources, &resources->settingsText);
    drawText(renderer, resources, &resources->developersText);
    drawText(renderer, resources, &resources->quitText);
    }
    else if(currentMenuCategory == MENU_SETTINGS)
    {

    }
    else if(currentMenuCategory == MENU_DEVELOPERS)
    {
        drawText(renderer, resources, &resources->developersMenuText);
        drawText(renderer, resources, &resources->andreyKlText);
        drawText(renderer, resources, &resources->bogdanText);
        drawText(renderer, resources, &resources->iliaText);
        drawText(renderer, resources, &resources->sergeyText);
        drawText(renderer, resources, &resources->yuriyText);
        drawText(renderer, resources, &resources->andreyKuText);
        drawText(renderer, resources, &resources->leaveDevelopersMenuText);
    }



    SDL_RenderPresent(renderer);
}

void drawText(SDL_Renderer *renderer, MenuResources *resources, MenuTextElement *textProperties)
{
    SDL_Color colorToSet = {255, 255, 255, 255};
    if(textProperties->isSelected == 1)
    {
        colorToSet.r = 255;
        colorToSet.g = 0;
        colorToSet.b = 0;
    }
    else
    {
        colorToSet.r = 255;
        colorToSet.g = 255;
        colorToSet.b = 255;
    }

    SDL_Surface *tmp = TTF_RenderText_Blended(resources->font, textProperties->menuText, colorToSet);
    SDL_Texture *label = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);

    int centerX = 1980 / 2;
    int centerY = 1080 / 2;

    int textX = textProperties->menuX;
    int textY = textProperties->menuY;

    int textW = textProperties->menuLabelW;
    int textH = textProperties->menuLabelH;
    SDL_QueryTexture(label, NULL, NULL, &textW, &textH);

    SDL_Rect textRect = {textX, textY, textW, textH};
    SDL_RenderCopy(renderer, label, NULL, &textRect);

    SDL_DestroyTexture(label);

    
}

void SetupSceneChanger(CurrentScene *sceneData)
{
    sceneChangerReference = sceneData;
}

//==============================RESOURCES===========================

void initResourceManagement(MenuResources *menuResources, GameState *gameResources)
{
    menuResources->isLoaded = 0;
    gameResources->isLoaded = 0;

}

void unloadMenuResources(MenuResources *resources)
{
    if(resources->isLoaded == 0) return;

    if(resources->menuLabel != NULL)
    {
        SDL_DestroyTexture(resources->menuLabel);
        TTF_CloseFont(resources->font);
    }
}

void unloadGameResources(GameState *resources)
{
    if(resources->isLoaded == 0) return;

    SDL_DestroyTexture(resources->enemy);
    SDL_DestroyTexture(resources->manFrames[0]);
    SDL_DestroyTexture(resources->manFrames[1]);
    SDL_DestroyTexture(resources->brick);

    //if (gameState.label != NULL)
    SDL_DestroyTexture(resources->label);
    TTF_CloseFont(resources->font);

}

//===================================================================

//=================================INPUT==================================

int processInputInMenu(SDL_Window *window, CurrentScene *currentScene) {
    SDL_Event event;
    int done = 0;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_WINDOWEVENT_CLOSE:
                if (window) {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    done = 1;
                }
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        done = 1;
                        break;
                    case SDLK_SPACE:
                        // Переключение на игровую сцену
                        currentScene->sceneInteger = SCENE_GAME;
                        break;
                    case SDLK_UP:
                        ChangeSelectedButton(false);
                    break;

                    case SDLK_DOWN:
                        ChangeSelectedButton(true);
                    break;
                    case SDLK_RETURN:
                        OnMenuButtonPressed(selectedMenuButton.selectedButton);
                    break;
                }
                break;

            

            case SDL_QUIT:
                done = 1;
                break;
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if(state[SDL_SCANCODE_UP]){
        
    }
    if(state[SDL_SCANCODE_DOWN]){
    }
    if(state[SDL_SCANCODE_RETURN]){
        
    }

    return done;
}

void ChangeSelectedButton(bool state)
{
    if(currentMenuCategory == MENU_MAINMENU)
    {
        ClearMainMenuButtons();
        if(state)
        {
            selectedButtonInteger++;
        }
        else
        {
            selectedButtonInteger--;
        }
        if(selectedButtonInteger > 3) selectedButtonInteger = 0;
        if(selectedButtonInteger < 0) selectedButtonInteger = 3;

        switch(selectedButtonInteger)
        {
            case 0:
                SetElementSelected(menuButtonReferences.playButton);
            break;
            case 1:
                SetElementSelected(menuButtonReferences.settingsButton);
            break;
            case 2:
                SetElementSelected(menuButtonReferences.developersButton);
            break;
            case 3:
                SetElementSelected(menuButtonReferences.quitButton);
            break;
        }
    }
}

void ClearMainMenuButtons()
{
    menuButtonReferences.playButton->isSelected = 0;
    menuButtonReferences.settingsButton->isSelected = 0;
    menuButtonReferences.developersButton->isSelected = 0;
    menuButtonReferences.quitButton->isSelected = 0;
}

void OnMenuButtonPressed(MenuTextElement *menuButton)
{
    if(menuButton->purpose == MENUBUTTONPURPOSE_UNASSIGNED) return;

    switch(menuButton->purpose)
    {
        case MENUBUTTONPURPOSE_PLAY:
            sceneChangerReference->sceneInteger = SCENE_GAME;
        break;
        case MENUBUTTONPURPOSE_SETTINGS:
            //currentMenuCategory = MENU_SETTINGS;
        break;
        case MENUBUTTONPURPOSE_DEVELOPERS:
            currentMenuCategory = MENU_DEVELOPERS;
            SetElementSelected(menuButtonReferences.leaveDevelopersButton);
        break;
        case MENUBUTTONPURPOSE_QUIT:
            sceneChangerReference->sceneInteger = QUITGAME;
        break;
        case MENUBUTTONPURPOSE_LEAVEDEVELOPERSMENU:
            currentMenuCategory = MENU_MAINMENU;
            SetElementSelected(menuButtonReferences.developersButton);
        break;
    }
}

//======================================================================
