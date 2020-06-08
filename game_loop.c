#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_events.h>
#include <time.h>
#include <stdbool.h>
#include "types.h"
#include "shapes.h"

// A section of the field is considered to be empty if it is black.
uint32_t field[10][20] = {BLACK};
piece_t gamePiece;
SDL_Surface* surface;

static void rotate() {
	piece_t save = gamePiece;
	switch (gamePiece.type) {
		case SQUARE:
			// There's no need to rotate a square
			// Checkmate, geometry.
			break;
		case BAR:
			if (gamePiece.rotation == 0) {
				gamePiece.rotation = 1;
				gamePiece.position[0].x += 2;
				gamePiece.position[0].y -= 2;
				gamePiece.position[1].x += 1;
				gamePiece.position[1].y -= 1;
				gamePiece.position[3].x -= 1;
				gamePiece.position[3].y += 1;
			}
			else {
				gamePiece.rotation = 0;
				gamePiece.position[0].x -= 2;
				gamePiece.position[0].y += 2;
				gamePiece.position[1].x -= 1;
				gamePiece.position[1].y += 1;
				gamePiece.position[3].x += 1;
				gamePiece.position[3].y -= 1;
			}
			break;
	}
}

static int removeLines() {
	int score = 0;
	int lines = 0; 

	for (int y = 19; y > 0; y--) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			if (!field[x][y])
				break;
			if (x == 9)
				lines++;
		}
		if (y - lines >= 0) {
			field[0][y] = field[0][y-lines];
			field[1][y] = field[1][y-lines];
			field[2][y] = field[2][y-lines];
			field[3][y] = field[3][y-lines];
			field[4][y] = field[4][y-lines];
			field[5][y] = field[5][y-lines];
			field[6][y] = field[6][y-lines];
			field[7][y] = field[7][y-lines];
			field[8][y] = field[8][y-lines];
			field[9][y] = field[9][y-lines];
		}
		else {
			field[0][y] = BLACK;
			field[1][y] = BLACK;
			field[2][y] = BLACK;
			field[3][y] = BLACK;
			field[4][y] = BLACK;
			field[5][y] = BLACK;
			field[6][y] = BLACK;
			field[7][y] = BLACK;
			field[8][y] = BLACK;
			field[9][y] = BLACK;
		}
	}

	return score;
}

static void drawField() {
	SDL_Rect rect;
	rect.h = BLOCK_SIZE;
	rect.w = BLOCK_SIZE;

	for (int x = 0; x < 10; x++) for (int y = 0; y < 20; y++) {
		rect.x = x * BLOCK_SIZE;
		rect.y = y * BLOCK_SIZE;
		SDL_FillRect(surface, &rect, field[x][y]);
	}
}

static void drawGamePiece() {
	static piece_t oldPosition;
	SDL_Rect rect;
	rect.h = BLOCK_SIZE;
	rect.w = BLOCK_SIZE;

	for (int i = 0; i < 4; i++) {
		rect.x = gamePiece.position[i].x * BLOCK_SIZE;
		rect.y = gamePiece.position[i].y * BLOCK_SIZE;
		SDL_FillRect(surface, &rect, gamePiece.color);
	}
}

static void moveGamePiece(uint8_t xShift, uint8_t yShift) {
	piece_t save = gamePiece;
	gamePiece.position[0].x += xShift;
	gamePiece.position[1].x += xShift;
	gamePiece.position[2].x += xShift;
	gamePiece.position[3].x += xShift;
	gamePiece.position[0].y += yShift;
	gamePiece.position[1].y += yShift;
	gamePiece.position[2].y += yShift;
	gamePiece.position[3].y += yShift;

	// Prevent the movement if moving sideways
	if (xShift) {
		for (int i = 0; i < 4; i++) {
			uint8_t x = gamePiece.position[i].x;
			uint8_t y = gamePiece.position[i].y;
			if (x > 9 || field[x][y]) {
				gamePiece = save;
				return;
			}
		}
	}

	// Spawn a new piece if we hit the bottom
	else if (yShift) {
		for (int i = 0; i < 4; i++) {
			uint8_t x = gamePiece.position[i].x;
			uint8_t y = gamePiece.position[i].y;
			if (y > 19 || field[x][y]) {
				field[save.position[0].x][save.position[0].y] = save.color;
				field[save.position[1].x][save.position[1].y] = save.color;
				field[save.position[2].x][save.position[2].y] = save.color;
				field[save.position[3].x][save.position[3].y] = save.color;
				gamePiece = newPiece[rand() % SHAPE_COUNT];
				break;
			}
		}
	}
}

int game_loop(SDL_Window* window, SDL_Surface* screenSurface) {
	surface = screenSurface;
	int score = 0;
	int level = 1;
	// The time in milliseconds before lowering the game piece
	int speed = 1000;
	gamePiece = newPiece[rand() % SHAPE_COUNT];

	for (bool quit = false; !quit;) {
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			switch (event.type) { 
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_UP:    rotate();             break;
						case SDLK_DOWN:  moveGamePiece( 0, 1); break;
						case SDLK_LEFT:  moveGamePiece(-1, 0); break;
						case SDLK_RIGHT: moveGamePiece( 1, 0); break;
					}
					break;
				case SDL_QUIT: quit = true; break;
			}
		}
		score += removeLines();
		drawField();
		drawGamePiece();
		SDL_UpdateWindowSurface (window);
	}

	return score;
}
