#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


void InitializeResourceTool();
void DisposeResourceTool();
SDL_Texture* GetTexture(const char* folder, const char* filename, SDL_Renderer *renderer);
TTF_Font* GetFont(const char* folder, const char* filename, int ptsSize);




