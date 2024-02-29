all:
	gcc -o mygame src/main.c src/status.c src/sounds/sounds.c src/sounds/sounds.h src/main.h src/status.h -I/SDL2 -L/SDL2/lib -lSDL2 -lSDL2_image -lSDL2_ttf