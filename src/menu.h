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
void initResourceManagement(MenuResources *menuResources, GameState *gameResources);
void unloadMenuResources(MenuResources *resources);
void unloadGameResources(GameState *resources);
void ChangeSelectedButton(bool state);
void ClearMainMenuButtons();
void SetupSceneChanger(CurrentScene *sceneData);
void OnMenuButtonPressed(MenuTextElement *menuButton);

#endif