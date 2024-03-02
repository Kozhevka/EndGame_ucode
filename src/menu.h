#ifndef sdl2_game_menu_h
#define sdl2_game_menu_h

#include "main.h"
#include <stdbool.h>

void loadMenu(MenuResources *resources);
void init_menu(MenuResources *game);
void SetTextParameters(MenuResources *resources, MenuTextElement *targetText, char* textToSet, int xPos, int yPos,  int purposeToSet);
void SetElementSelected(MenuTextElement *targetText);
int processInputInMenu(SDL_Window *window, CurrentScene *currentScene);
void renderMenu(SDL_Renderer *renderer, MenuResources *resources);
void drawText(SDL_Renderer *renderer, MenuResources *resources, MenuTextElement *textProperties);
void drawFullscreenButtonText(SDL_Renderer *renderer, MenuResources *resources, MenuTextElement *textProperties);
void drawResolutionButtonText(SDL_Renderer *renderer, MenuResources *resources, MenuTextElement *textProperties);
char* GetTextForResolutionButton();
int GetRectYCoordinate(int yCoordinateGlobal);
int GetRectWidth(int rectWidth);
int GetRectHeight(int rectHeight);
float GetScreenSizeMultiplier();
int GetCurrentScreenWidth();
int GetCurrentScreenHeight();
void initResourceManagement(MenuResources *menuResources, GameState *gameResources);
void unloadMenuResources(MenuResources *resources);
void unloadGameResources(GameState *resources);
void ChangeSelectedButton(bool state);
void ClearMainMenuButtons();
void ClearSettingsButtons();
void SetupSceneChanger(CurrentScene *sceneData);
void SetupWindowReference(SDL_Window *window);
void ToggleFullscreen();
void OnResolutionButtonPressed();
void ChangeResolution();
void OnMenuButtonPressed(MenuTextElement *menuButton);
char* GetGameName();
int isRoflMode();
int getWidth();
int getHeight();

#endif