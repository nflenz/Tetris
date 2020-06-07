#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_events.h>
#include <time.h>
#include <stdbool.h>

#include "tetris_types.h"
#include "colors.h"

block_t field[10][20];
piece_t gamepiece;

// Subroutine for drawing the screen
void draw_field() {
	// Draw the field
	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 10; y++)
			if (field[x][y].filled) { }
	// Draw the game piece too

}

piece_t newpiece() {
	piece_t newpiece;
	newpiece.rotation = 0;
	newpiece.type = rand() % 7;
	switch (newpiece.type) {
		case Bar:
			newpiece.color = cyan;
		case Square:
			newpiece.color = yellow;
			newpiece.x = 5;
			newpiece.y = 20;
		case T:
			newpiece.color = purple;
		case L:
			newpiece.color = orange;
		case Z:
			newpiece.color = red;
		case Reverse_L:
			newpiece.color = blue;
		case Reverse_Z:
			newpiece.color = green;
	}
	return newpiece;
}

int game_loop(SDL_Surface* screenSurface) {
	int score = 0;
	int level = 1;
	// The time in milliseconds before lowering the game piece
	int speed = 1000;
	gamepiece = newpiece();

	// Initialize the game field
	for (int x = 9; x--;) for (int y = 19; y--;) {
		field[x][y].filled = false;
		field[x][y].color  = black;
	}

	for (bool quit = false; !quit;) {
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			switch (event.type) { 
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_DOWN:  puts("Down" ); break;
						case SDLK_UP:    puts("Up"   ); break;
						case SDLK_LEFT:  puts("Left" ); break;
						case SDLK_RIGHT: puts("Right"); break;
					}
					break;
				case SDL_QUIT:
					quit = true;
					break;
			}
		}
	}

	return score;
}
