#include <SDL2/SDL_Rect.h>
#include <SDL2/SDL_pixels.h>
#include <time.h>
#include "colors.h"

typedef enum { down, left, right } direction;
typedef enum { Bar, Square, T, L, Z, Reverse_L, Reverse_Z } piece_type;

// The Tetris game field
struct {
	int filled;
	SDL_Color color;
} tetris_field[10][20];

// The Tetris game piece
struct piece {
	int rotation;
	piece_type type;
	SDL_Color color;
	// positions for the 4 blocks
	// a is treated as the center
	// except when it is a square
	SDL_Rect a, b, c, d;
} piece;

// Subroutine for drawing the screen
void draw_field() {
	// Draw the field
	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 10; y++)
			if (tetris_field[x][y].filled) { }
	// Draw the piece too

}

struct piece new_piece() {
	struct piece newpiece;
	piece_type type = rand() % 7;
	newpiece.type = type;
	switch (type) {
		case Bar:
				newpiece.color = cyan;
		case Square:
				newpiece.color = yellow;
		case T:
				newpiece.color = purple;
		case L:
				newpiece.color = orange;
		case Z:
				newpiece.color = red;
		case Reverse_L:
				newpiece.color = blue;
		case Reverse_Z:
				newpiece.color = red;
	}
	return newpiece;
}

int game_loop() {
	int score = 0;
	int level = 1;
	// The time in milliseconds before lowering the game piece
	int speed = 1000;

	// Initialize the game field
	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 10; y++)
			tetris_field[x][y] = {0, black};

	while (true) {

	}

	return score;
}
