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
						case SDLK_DOWN:  moveGamePiece( 0, 1); break;
						case SDLK_UP:    moveGamePiece( 0,-1); break;
						case SDLK_LEFT:  moveGamePiece(-1, 0); break;
						case SDLK_RIGHT: moveGamePiece( 1, 0); break;
					}
					break;
				case SDL_QUIT:
					quit = true;
					break;
			}
		}
		drawField();
		drawGamePiece();
		SDL_UpdateWindowSurface (window);
	}

	return score;
}
