#include "menu.h"
#include "main.h"
#include "sounds.h"
#include <stdbool.h>

MainMenuButtonReferences menuButtonReferences;
SelectedButtonReference selectedMenuButton;
CurrentScene *sceneChangerReference;
SDL_Window *windowRef;
int selectedButtonInteger;
int selectedButtonSettingsMenu;

int currentMenuCategory;
int currentResolutionInteger = 0;

int currentScreenWidth;
int currentScreenHeight;

int roflMode = 0;

SDL_DisplayMode dm;

char* gameName = "HANNAH   OWO     SIMULATOR";


int getWidth(){
    return currentScreenWidth;
}
int getHeight(){
    return currentScreenHeight;
}

void loadMenu(MenuResources *resources)
{
    resources->font = TTF_OpenFont("assets/fonts/menuFont.ttf", 48);
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
    SetupWindowReference(resources->applicationWindow);  
    
    currentResolutionInteger = 0;
    ChangeResolution();
    //playMenuMusic();
    
    // background texture load
    SDL_Surface *surface = NULL;

    surface = IMG_Load("assets/images/menu_background.png");
    if (surface == NULL) {
        printf("Cannot find menu_background.png\n");
        SDL_Quit();
        exit(1);    
        
    }
    
    resources->menuBackground = SDL_CreateTextureFromSurface(resources->renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("assets/images/heroi.png");
    if (surface == NULL) {
        printf("Cannot find menu_background.png\n");
        SDL_Quit();
        exit(1);
    }

    resources->menuRoflBackground = SDL_CreateTextureFromSurface(resources->renderer, surface);
    SDL_FreeSurface(surface);


    // UI elements setting
//===================================MAINMENU==================================
    currentMenuCategory = MENU_MAINMENU;
    SetTextParameters(resources, &resources->gameNameText, GetGameName(), 0, 150, MENUBUTTONPURPOSE_UNASSIGNED);
    SetTextParameters(resources, &resources->playText, "Play", 0, 400, MENUBUTTONPURPOSE_PLAY);
    menuButtonReferences.playButton = &resources->playText;
    SetTextParameters(resources, &resources->settingsText, "Settings", 0, 500, MENUBUTTONPURPOSE_SETTINGS);
    menuButtonReferences.settingsButton = &resources->settingsText;
    SetTextParameters(resources, &resources->developersText, "Developers", 0, 600, MENUBUTTONPURPOSE_DEVELOPERS);
    menuButtonReferences.developersButton = &resources->developersText;
    SetTextParameters(resources, &resources->quitText, "Quit", 0, 700, MENUBUTTONPURPOSE_QUIT);
    menuButtonReferences.quitButton = &resources->quitText;
//================================================================================

//===============================SETTINGS=======================================

    SetTextParameters(resources, &resources->settingsCaptionText, "Settings", 0, 150, MENUBUTTONPURPOSE_UNASSIGNED);    
    SetTextParameters(resources, &resources->resolutionText, "Resolution", 0, 300, MENUBUTTONPURPOSE_TOGGLERESOLUTION);
    menuButtonReferences.resolutionButton = &resources->resolutionText;
    SetTextParameters(resources, &resources->fullscreenText, "Fullscreen", 0, 400, MENUBUTTONPURPOSE_TOGGLEFULLSCREEN);
    menuButtonReferences.fullscreenButton = &resources->fullscreenText;
    SetTextParameters(resources, &resources->toggleRoflModeText, "Sad Hamster Mode", 0, 500, MENUBUTTONPURPOSE_TOGGLEROFLMODE);
    menuButtonReferences.toggleRoflModeButton = &resources->toggleRoflModeText;
    SetTextParameters(resources, &resources->leaveSettingsText, "Leave", 0, 600, MENUBUTTONPURPOSE_CLOSESETTINGS);
    menuButtonReferences.leaveSettingsButton = &resources->leaveSettingsText;

//==============================================================================

//===============================DEVELOPERS==============================
    SetTextParameters(resources, &resources->developersMenuText, "Developers", 0, 150, MENUBUTTONPURPOSE_UNASSIGNED);
    SetTextParameters(resources, &resources->andreyKlText, "Andrii   Kalashnikov", 0, 250, MENUBUTTONPURPOSE_UNASSIGNED);
    SetTextParameters(resources, &resources->bogdanText, "Bohdan   Yakilevskyi", 0, 350, MENUBUTTONPURPOSE_UNASSIGNED);
    SetTextParameters(resources, &resources->iliaText, "Illia   Kozhevnikov", 0, 450, MENUBUTTONPURPOSE_UNASSIGNED);
    SetTextParameters(resources, &resources->sergeyText, "Serhii   Ivashchuk", 0, 550, MENUBUTTONPURPOSE_UNASSIGNED);
    SetTextParameters(resources, &resources->yuriyText, "Yurii   Kryvoruchka", 0, 650, MENUBUTTONPURPOSE_UNASSIGNED);
    SetTextParameters(resources, &resources->andreyKuText, "Andrii   Kubik", 0, 750, MENUBUTTONPURPOSE_UNASSIGNED);
    SetTextParameters(resources, &resources->leaveDevelopersMenuText, "Leave", 0, 850, MENUBUTTONPURPOSE_LEAVEDEVELOPERSMENU);
    menuButtonReferences.leaveDevelopersButton = &resources->leaveDevelopersMenuText;
//========================================================================
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
    if(isRoflMode()){
        SDL_RenderCopy(resources->renderer, resources->menuRoflBackground, NULL, NULL);   
    }
    else{
        SDL_RenderCopy(resources->renderer, resources->menuBackground, NULL, NULL);   
    }
    
    
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
        drawText(renderer, resources, &resources->settingsCaptionText);
        drawResolutionButtonText(renderer, resources, &resources->resolutionText);
        drawFullscreenButtonText(renderer, resources, &resources->fullscreenText);
        drawRoflModeButton(renderer, resources, &resources->toggleRoflModeText);
        drawText(renderer, resources, &resources->leaveSettingsText);
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
        colorToSet.g = 255;
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

    int centerX = currentScreenWidth;
    int centerY = 1080 / 2;

    int textX = textProperties->menuX;
    int textY = textProperties->menuY;

    int textW = textProperties->menuLabelW;
    int textH = textProperties->menuLabelH;
    SDL_QueryTexture(label, NULL, NULL, &textW, &textH);

    SDL_Rect textRect = {(centerX - GetRectWidth(textW)) / 2, GetRectYCoordinate(textY), GetRectWidth(textW), GetRectHeight(textH)};
    SDL_RenderCopy(renderer, label, NULL, &textRect);

    SDL_DestroyTexture(label);

    
}

void drawFullscreenButtonText(SDL_Renderer *renderer, MenuResources *resources, MenuTextElement *textProperties)
{
    SDL_Color colorToSet = {255, 255, 255, 255};
    if(textProperties->isSelected == 1)
    {
        colorToSet.r = 255;
        colorToSet.g = 255;
        colorToSet.b = 0;
    }
    else
    {
        colorToSet.r = 255;
        colorToSet.g = 255;
        colorToSet.b = 255;
    }
    bool isFullscreen = SDL_GetWindowFlags(windowRef) & SDL_WINDOW_FULLSCREEN;
    char* textToSet = "null";
    if(isFullscreen)
    {
        textToSet = "Fullscreen   mode      ON";
    }
    else
    {
        textToSet = "Fullscreen   mode      OFF";
    }
    

    SDL_Surface *tmp = TTF_RenderText_Blended(resources->font, textToSet, colorToSet);
    SDL_Texture *label = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);

    int centerX = currentScreenWidth;
    int centerY = 1080 / 2;

    int textX = textProperties->menuX;
    int textY = textProperties->menuY;

    int textW = textProperties->menuLabelW;
    int textH = textProperties->menuLabelH;
    SDL_QueryTexture(label, NULL, NULL, &textW, &textH);

    SDL_Rect textRect = {(centerX - GetRectWidth(textW)) / 2, GetRectYCoordinate(textY), GetRectWidth(textW), GetRectHeight(textH)};
    SDL_RenderCopy(renderer, label, NULL, &textRect);

    SDL_DestroyTexture(label);

    
}



void drawResolutionButtonText(SDL_Renderer *renderer, MenuResources *resources, MenuTextElement *textProperties)
{
    SDL_Color colorToSet = {255, 255, 255, 255};
    if(textProperties->isSelected == 1)
    {
        colorToSet.r = 255;
        colorToSet.g = 255;
        colorToSet.b = 0;
    }
    else
    {
        colorToSet.r = 255;
        colorToSet.g = 255;
        colorToSet.b = 255;
    }
    bool isFullscreen = SDL_GetWindowFlags(windowRef) & SDL_WINDOW_FULLSCREEN;
    char* textToSet = GetTextForResolutionButton();

    SDL_Surface *tmp = TTF_RenderText_Blended(resources->font, textToSet, colorToSet);
    SDL_Texture *label = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);

    int centerX = currentScreenWidth;
    int centerY = 1080 / 2;

    int textX = textProperties->menuX;
    int textY = textProperties->menuY;

    int textW = textProperties->menuLabelW;
    int textH = textProperties->menuLabelH;
    SDL_QueryTexture(label, NULL, NULL, &textW, &textH);

    SDL_Rect textRect = {(centerX - GetRectWidth(textW)) / 2, GetRectYCoordinate(textY), GetRectWidth(textW), GetRectHeight(textH)};
    SDL_RenderCopy(renderer, label, NULL, &textRect);

    SDL_DestroyTexture(label);

    
}

void drawRoflModeButton(SDL_Renderer *renderer, MenuResources *resources, MenuTextElement *textProperties)
{
    SDL_Color colorToSet = {255, 255, 255, 255};
    if(textProperties->isSelected == 1)
    {
        colorToSet.r = 255;
        colorToSet.g = 255;
        colorToSet.b = 0;
    }
    else
    {
        colorToSet.r = 255;
        colorToSet.g = 255;
        colorToSet.b = 255;
    }
    bool isFullscreen = SDL_GetWindowFlags(windowRef) & SDL_WINDOW_FULLSCREEN;
    char* textToSet = GetTextForRoflMode();

    SDL_Surface *tmp = TTF_RenderText_Blended(resources->font, textToSet, colorToSet);
    SDL_Texture *label = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);

    int centerX = currentScreenWidth;
    int centerY = 1080 / 2;

    int textX = textProperties->menuX;
    int textY = textProperties->menuY;

    int textW = textProperties->menuLabelW;
    int textH = textProperties->menuLabelH;
    SDL_QueryTexture(label, NULL, NULL, &textW, &textH);

    SDL_Rect textRect = {(centerX - GetRectWidth(textW)) / 2, GetRectYCoordinate(textY), GetRectWidth(textW), GetRectHeight(textH)};
    SDL_RenderCopy(renderer, label, NULL, &textRect);

    SDL_DestroyTexture(label);

    
}

char* GetTextForResolutionButton()
{
    switch(currentResolutionInteger)
    {
        case 0:
            return "Resolution             Default";
            break;
        case 1:
            return "Resolution             800x600";
            break;
        case 2:
            return "Resolution             1280x720";
            break;
        case 3:
            return "Resolution             1360x768";
            break;
        case 4:
            return "Resolution             1920x1080";
            break;
        case 5:
            return "Resolution             2560x1440";
            break;
        default:
            return "Resolution             Default";
            break;
    }
}

char* GetTextForRoflMode()
{
    if(isRoflMode())
    {
        return "Sad Hamster Mode   ON";
    }
    else
    {
        return "Sad Hamster Mode   OFF";
    }
}

int GetRectYCoordinate(int yCoordinateGlobal)
{
    return yCoordinateGlobal * GetScreenSizeMultiplier();
}

int GetRectWidth(int rectWidth)
{
    return rectWidth * GetScreenSizeMultiplier();
}

int GetRectHeight(int rectHeight)
{
    return rectHeight * GetScreenSizeMultiplier();
}

float GetScreenSizeMultiplier()
{
    return ((float)currentScreenHeight / 1080);
}

int GetCurrentScreenWidth()
{
    return currentScreenWidth;
}

int GetCurrentScreenHeight()
{
    return currentScreenHeight;
}

void SetupSceneChanger(CurrentScene *sceneData)
{
    sceneChangerReference = sceneData;
}

void SetupWindowReference(SDL_Window *window)
{
    windowRef = window;
}

void ToggleFullscreen()
{
    if(windowRef == NULL) return;

    bool isFullscreen = SDL_GetWindowFlags(windowRef) & SDL_WINDOW_FULLSCREEN;  
    SDL_SetWindowFullscreen(windowRef, isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN);  
    SDL_SetWindowSize(windowRef, currentScreenWidth, currentScreenHeight);
    SDL_ShowCursor(isFullscreen);
}

void OnResolutionButtonPressed()
{
    currentResolutionInteger++;
    if(currentResolutionInteger > 5) currentResolutionInteger = 0;
    ChangeResolution();
}

void ChangeResolution()
{
    if(windowRef == NULL) return;
    switch(currentResolutionInteger)
    {
        case 0:           
            if(SDL_GetDesktopDisplayMode(0, &dm) != 0)
            {
                return;
            }
            int w, h;
            w = dm.w;
            h = dm.h;
            SDL_SetWindowSize(windowRef, w, h);
            break;
        case 1:
            SDL_SetWindowSize(windowRef, 800, 600);
            break;
        case 2:
            SDL_SetWindowSize(windowRef, 1280, 720);
            break;
        case 3:
            SDL_SetWindowSize(windowRef, 1360, 768);
            break;
        case 4:
            SDL_SetWindowSize(windowRef, 1920, 1080);
            break;
        case 5:
            if(dm.w < 2560)
            {
                currentResolutionInteger = 0;
                ChangeResolution();
                return;
            }
            SDL_SetWindowSize(windowRef, 2560, 1440);
            break;
    }

    SDL_GetWindowSize(windowRef, &currentScreenWidth, &currentScreenHeight);
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

    SDL_DestroyTexture(resources->gameNameText.menuLabel);
    SDL_DestroyTexture(resources->playText.menuLabel);
    SDL_DestroyTexture(resources->settingsText.menuLabel);
    SDL_DestroyTexture(resources->developersText.menuLabel);
    SDL_DestroyTexture(resources->quitText.menuLabel);
    SDL_DestroyTexture(resources->settingsCaptionText.menuLabel);
    SDL_DestroyTexture(resources->resolutionText.menuLabel);
    SDL_DestroyTexture(resources->fullscreenText.menuLabel);
    SDL_DestroyTexture(resources->leaveSettingsText.menuLabel);
    SDL_DestroyTexture(resources->developersMenuText.menuLabel);
    SDL_DestroyTexture(resources->andreyKlText.menuLabel);
    SDL_DestroyTexture(resources->bogdanText.menuLabel);
    SDL_DestroyTexture(resources->iliaText.menuLabel);
    SDL_DestroyTexture(resources->sergeyText.menuLabel);
    SDL_DestroyTexture(resources->yuriyText.menuLabel);
    SDL_DestroyTexture(resources->andreyKuText.menuLabel);
    SDL_DestroyTexture(resources->leaveDevelopersMenuText.menuLabel);
    SDL_DestroyTexture(resources->menuBackground);

    TTF_CloseFont(resources->font);
}

void unloadGameResources(GameState *resources)
{
    if(resources->isLoaded == 0) return;

    SDL_DestroyTexture(resources->enemy);
    SDL_DestroyTexture(resources->enemyGo);
    SDL_DestroyTexture(resources->manFrames[0]);
    SDL_DestroyTexture(resources->manFrames[1]);
    SDL_DestroyTexture(resources->brick);
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
    else if(currentMenuCategory == MENU_SETTINGS)
    {
        ClearSettingsButtons();
        if(state)
        {
            selectedButtonSettingsMenu++;
        }
        else
        {
            selectedButtonSettingsMenu--;
        }
        if(selectedButtonSettingsMenu > 3) selectedButtonSettingsMenu = 0;
        if(selectedButtonSettingsMenu < 0) selectedButtonSettingsMenu = 3;

        switch(selectedButtonSettingsMenu)
        {
            case 0:
                SetElementSelected(menuButtonReferences.resolutionButton);
                break;
            case 1:
                SetElementSelected(menuButtonReferences.fullscreenButton);
                break;
            case 2:
                SetElementSelected(menuButtonReferences.toggleRoflModeButton);
                break;
            case 3:
                SetElementSelected(menuButtonReferences.leaveSettingsButton);
                break;
        }
    }
    playSound(scrollSound);
}

void ClearMainMenuButtons()
{
    menuButtonReferences.playButton->isSelected = 0;
    menuButtonReferences.settingsButton->isSelected = 0;
    menuButtonReferences.developersButton->isSelected = 0;
    menuButtonReferences.quitButton->isSelected = 0;
}

void ClearSettingsButtons()
{
    menuButtonReferences.resolutionButton->isSelected = 0;
    menuButtonReferences.fullscreenButton->isSelected = 0;
    menuButtonReferences.toggleRoflModeButton->isSelected = 0;
    menuButtonReferences.leaveSettingsButton->isSelected = 0;
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
            selectedButtonSettingsMenu = 3;
            currentMenuCategory = MENU_SETTINGS;
            SetElementSelected(menuButtonReferences.leaveSettingsButton);
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
        case MENUBUTTONPURPOSE_CLOSESETTINGS:
            currentMenuCategory = MENU_MAINMENU;
            SetElementSelected(menuButtonReferences.settingsButton);
            break;
        case MENUBUTTONPURPOSE_TOGGLERESOLUTION:
            OnResolutionButtonPressed();
            break;
        case MENUBUTTONPURPOSE_TOGGLEFULLSCREEN:
            ToggleFullscreen();
            break;
        case MENUBUTTONPURPOSE_TOGGLEROFLMODE:
            ToggleRoflMode();
            break;
    }
     playSound(clickSound);
}

//======================================================================

char* GetGameName()
{
    return gameName;
}

void ToggleRoflMode()
{
    if(roflMode == 1){
        roflMode = 0;
        playMusic(menuMusic);
    }
    else{
        roflMode = 1;
        playMusic(menuRoflMusic);
    }
}

int isRoflMode()
{
    return roflMode;
}
