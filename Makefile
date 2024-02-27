# Directories
SDL_DIR := resource/libs/SDL
SDL_IMAGE_DIR := resource/libs/SDL_image
SDL_TTF_DIR := resource/libs/SDL_ttf

# Compiler
CC := gcc
CFLAGS := -I$(SDL_DIR)/include -I$(SDL_IMAGE_DIR)/include -I$(SDL_TTF_DIR) -Wall -Wextra -pedantic -O2

# Linker
LDFLAGS := -L$(SDL_DIR)/build -L$(SDL_IMAGE_DIR)/.libs -L$(SDL_TTF_DIR)/.libs
LDLIBS := -lSDL2 -lSDL2_image -lSDL2_ttf

# Targets
EXECUTABLE := mygame
SRCDIR := src
SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(SRC:.c=.o)

# Build rules
$(EXECUTABLE): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) $(EXECUTABLE)