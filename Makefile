tetris: main.o game_loop.o
	gcc -lSDL2 main.o game_loop.o -o tetris

main.o: main.c game_loop.h window.h
	gcc -g -c main.c

game_loop.o: game_loop.c window.h shapes.h colors.h
	gcc -g -c game_loop.c

clean:
	rm -f tetris main.o game_loop.o tags

tags:
	ctags /usr/include/SDL2/* *.c *.h
