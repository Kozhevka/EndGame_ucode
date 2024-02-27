all:
	gcc -o mygame src/main.c src/menu.c src/status.c src/main.h src/menu.h src/status.h -I/SDL2 -L/SDL2/lib -lSDL2 -lSDL2_image -lSDL2_ttf