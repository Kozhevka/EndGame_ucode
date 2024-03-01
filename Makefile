all:
	gcc -o mygame src/main.c src/map.c src/sounds.c src/menu.c src/status.c src/enemies.c src/interface.c src/main.h src/map.h src/sounds.h src/menu.h src/status.h src/enemies.h src/interface.h -I/SDL2 -L/SDL2/lib -lSDL2 -lSDL2_image -lSDL2_ttf
