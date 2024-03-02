#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define INITIAL_LIST_CAPACITY 10


struct LoadedTextureItem
{
    SDL_Texture *texture;
    int id;
};
struct LoadedFontItem
{
    TTF_Font *font;
    int id;
};
typedef struct 
{
    struct LoadedTextureItem* items;
    int capacity;
    int size;
}TextureList;
typedef struct 
{
    struct LoadedFontItem* items;
    int capacity;
    int size;
}FontList;

TextureList *textureList;
FontList *fontList;
int textureCount = 0;
int fontCount = 0;

char* combineString(char* arrayHolder, const char* a, const char* b);
SDL_Surface* loadImage(char* pathToFile, SDL_Surface* surface);

TextureList* createTextureList();
FontList* createFontList();
void addTextureToList(SDL_Texture *texture);
void addFontToList(TTF_Font *font);
void freeTextureList();
void freeFontList();

void InitializeResourceTool()
{
    textureList = createTextureList();
    fontList = createFontList();
}

void DisposeResourceTool()
{
    freeTextureList();
    freeFontList();
}

SDL_Texture* GetTexture(const char* folder, const char* filename, SDL_Renderer *renderer)
{
    SDL_Surface *surface = NULL;
    SDL_Texture* holder;

    char *imagePath = (char *)malloc(100 * sizeof(char));
    combineString(imagePath, folder, filename);

    holder = SDL_CreateTextureFromSurface(renderer, loadImage(imagePath, surface));
    addTextureToList(holder);
    SDL_FreeSurface(surface);
    free(imagePath);

    return holder;
}

TTF_Font* GetFont(const char* folder, const char* filename, int ptsSize)
{
    TTF_Font* holder;    

    char *fontPath = (char *)malloc(100 * sizeof(char));
    combineString(fontPath, folder, filename);

    holder = TTF_OpenFont(fontPath, ptsSize);
    if (!holder)
    {
        printf("cannot find %s", fontPath);
        SDL_Quit();
        exit(1);
    }
    addFontToList(holder);

    return holder;
}

char* combineString(char* arrayHolder, const char* a, const char* b)
{
    strcpy(arrayHolder, a);
    strcat(arrayHolder, b);   
}

SDL_Surface* loadImage(char* pathToFile, SDL_Surface* surface)
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



TextureList* createTextureList()
{
    TextureList *list = (TextureList*)malloc(sizeof(TextureList));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->items = (struct LoadedTextureItem*)malloc(INITIAL_LIST_CAPACITY * sizeof(struct LoadedTextureItem));
    if (list->items == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->capacity = INITIAL_LIST_CAPACITY;
    list->size = 0;
    return list;
}

FontList* createFontList()
{
    FontList *list = (FontList*)malloc(sizeof(FontList));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->items = (struct LoadedFontItem*)malloc(INITIAL_LIST_CAPACITY * sizeof(struct LoadedFontItem));
    if (list->items == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->capacity = INITIAL_LIST_CAPACITY;
    list->size = 0;
    return list;
}


void addTextureToList(SDL_Texture *texture)
{
    TextureList *list = textureList;

    if (list->size >= list->capacity) {
        // If the list is full, double its capacity
        list->capacity *= 2;
        list->items = (struct LoadedTextureItem*)realloc(list->items, list->capacity * sizeof(struct LoadedTextureItem));
        if (list->items == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    list->items[list->size++].texture = texture;
    list->items[list->size++].id = textureCount;
    textureCount++;
}

void addFontToList(TTF_Font *font)
{
    FontList *list = fontList;

    if (list->size >= list->capacity) {
        // If the list is full, double its capacity
        list->capacity *= 2;
        list->items = (struct LoadedFontItem*)realloc(list->items, list->capacity * sizeof(struct LoadedFontItem));
        if (list->items == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    list->items[list->size++].font = font;
    list->items[list->size++].id = textureCount;
    textureCount++;
}


void freeTextureList()
{
    for (size_t i = 0; i < textureCount; i++)
    {
        SDL_DestroyTexture(textureList->items[i].texture);
    }
    free(textureList->items);
    free(textureList);
}

void freeFontList()
{
    for (size_t i = 0; i < textureCount; i++)
    {
        TTF_CloseFont(fontList->items[i].font);
    }
    free(fontList->items);
    free(fontList);
}
