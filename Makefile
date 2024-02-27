LIBS_PATH = resourse/libs

CC = gcc
CFLAGS = -Wall -I$(LIBS_PATH)/SDL/include -I$(LIBS_PATH)/SDL_image/include -I$(LIBS_PATH)/SDL_ttf
LDFLAGS = -L$(LIBS_PATH)/SDL/build/.libs/ -L$(LIBS_PATH)/SDL_image/.libs -L$(LIBS_PATH)/SDL_ttf/.libs
LDLIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

SRC = src/main.c src/status.c src/menu.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = mygame

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)

