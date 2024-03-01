#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//void AssignTexture(SDL_Texture *holder, char* folder, char* filename, SDL_Renderer *renderer);
char* CombineString(char* arrayHolder, const char* a, const char* b);
SDL_Surface* LoadImage(char* pathToFile, SDL_Surface* surface);


void AssignTexture(SDL_Texture **holder, const char* folder, const char* filename, SDL_Renderer *renderer)
{
    SDL_Surface *surface = NULL;

    char *imagePath = (char *)malloc(100 * sizeof(char));
    CombineString(imagePath, folder, filename);

    *holder = SDL_CreateTextureFromSurface(renderer, LoadImage(imagePath, surface));
    SDL_FreeSurface(surface);
    free(imagePath);
}

char* CombineString(char* arrayHolder, const char* a, const char* b)
{
    strcpy(arrayHolder, a);
    strcat(arrayHolder, b);   
}

SDL_Surface* LoadImage(char* pathToFile, SDL_Surface* surface)
{
    surface = IMG_Load(pathToFile);
    if (surface == NULL)
    {
        printf("cannot find %s", pathToFile);
        SDL_Quit();
        exit(1);
    }   
    return surface;
}