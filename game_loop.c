#include <SDL2/SDL.h>
//#include <SDL2/SDL_pixels.h>
//#include <SDL2/SDL_events.h>
//#include <SDL2/SDL_timer.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include "window.h"
#include "colors.h"
#include "shapes.h"

// A section of the field is considered to be empty if it is black.
uint32_t field[10][20] = {BLACK};
piece_t gamePiece;
piece_t dropPiece;
SDL_Surface* surface;

static void moveDropPiece(void);

static void rotate(int key) {
	if (key != SDLK_UP) return;
	piece_t save = gamePiece;
	gamePiece.position[0].x += gamePiece.change[gamePiece.rotation][0];
	gamePiece.position[0].y += gamePiece.change[gamePiece.rotation][1];
	gamePiece.position[1].x += gamePiece.change[gamePiece.rotation][2];
	gamePiece.position[1].y += gamePiece.change[gamePiece.rotation][3];
	gamePiece.position[2].x += gamePiece.change[gamePiece.rotation][4];
	gamePiece.position[2].y += gamePiece.change[gamePiece.rotation][5];
	gamePiece.position[3].x += gamePiece.change[gamePiece.rotation][6];
	gamePiece.position[3].y += gamePiece.change[gamePiece.rotation][7];
	gamePiece.rotation = (gamePiece.rotation + 1) % 4;

	for (int i = 0; i < 4; i++) {
		int x = gamePiece.position[i].x;
		int y = gamePiece.position[i].y;
		if (field[x][y] || y < 0 || x < 0 || y >= SCREEN_HEIGHT || x >= SCREEN_WIDTH) {
			gamePiece = save;
			return;
		}
	}
	moveDropPiece();
}

static int removeLines() {
	int points[5] = { 0, 40, 100, 300, 1200 };
	int lines = 0; 
	int y;
	// Only up to 4 lines will ever be removed
	// so we loop 4 times
	for (int loops = 3; loops--;) {
		for (y = 19; y > 0; y--) {
			// Check to see if the row is filled
			// with a whole lotta nots
			bool filled = ! (
			!field[0][y] + !field[1][y] +
			!field[2][y] + !field[3][y] +
			!field[4][y] + !field[5][y] +
			!field[6][y] + !field[7][y] +
			!field[8][y] + !field[9][y]);

			if (filled) {
				lines++;
				break;
			}
		}
		for (;y > 0; y--) {
			field[0][y] = field[0][y-1];
			field[1][y] = field[1][y-1];
			field[2][y] = field[2][y-1];
			field[3][y] = field[3][y-1];
			field[4][y] = field[4][y-1];
			field[5][y] = field[5][y-1];
			field[6][y] = field[6][y-1];
			field[7][y] = field[7][y-1];
			field[8][y] = field[8][y-1];
			field[9][y] = field[9][y-1];
		}
	}
	moveDropPiece();
	return points[lines];
}

static void drawField() {
	SDL_Rect rect;
	rect.h = BLOCK_SIZE;
	rect.w = BLOCK_SIZE;
	for (int x = 0; x < 10; x++) 
	for (int y = 0; y < 20; y++) {
		rect.x = x * BLOCK_SIZE;
		rect.y = y * BLOCK_SIZE;
		SDL_FillRect(surface, &rect, field[x][y]);
	}
}

static void drawGamePiece(piece_t drawTarget) {
	SDL_Rect rect;
	rect.h = BLOCK_SIZE;
	rect.w = BLOCK_SIZE;
	for (int i = 0; i < 4; i++) {
		rect.x = drawTarget.position[i].x * BLOCK_SIZE;
		rect.y = drawTarget.position[i].y * BLOCK_SIZE;
		SDL_FillRect(surface, &rect, drawTarget.color);
	}
}

static void moveDropPiece() {
	piece_t save;
	dropPiece = gamePiece;
	dropPiece.color = WHITE;

	while (true) {
		save = dropPiece;
		dropPiece.position[0].y++;
		dropPiece.position[1].y++;
		dropPiece.position[2].y++;
		dropPiece.position[3].y++;
		for (int i = 0; i < 4; i++) {
			int x = dropPiece.position[i].x;
			int y = dropPiece.position[i].y;
			if (field[x][y]) {
				dropPiece = save;
				return;
			}
			if (y == 19)
				return;
		}
	}
}

static void moveGamePiece(int key) {
	piece_t save = gamePiece;
	int xShift = 0;
	int yShift = 0;
	if (key == SDLK_DOWN ) yShift++;
	if (key == SDLK_LEFT ) xShift--;
	if (key == SDLK_RIGHT) xShift++;

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
			int x = gamePiece.position[i].x;
			int y = gamePiece.position[i].y;
			if (x > 9 || x < 0 || field[x][y]) {
				gamePiece = save;
				return;
			}
		}
		moveDropPiece();
	}
	// Spawn a new piece if we hit the bottom
	else if (yShift) {
		for (int i = 0; i < 4; i++) {
			int x = gamePiece.position[i].x;
			int y = gamePiece.position[i].y;
			if (y > 19 || field[x][y]) {
				field[save.position[0].x][save.position[0].y] = save.color;
				field[save.position[1].x][save.position[1].y] = save.color;
				field[save.position[2].x][save.position[2].y] = save.color;
				field[save.position[3].x][save.position[3].y] = save.color;
				gamePiece = newPiece[rand() % SHAPE_COUNT];
				moveDropPiece();
				break;
			}
		}
	}
}


int game_loop(SDL_Window* window, SDL_Surface* screenSurface) {
	surface = screenSurface;
	int score = 0;
	int level = 1;

	int speed = 1000000;
	struct timeval now;
	struct timeval start;
	gettimeofday(&start, NULL);

	gamePiece = newPiece[rand() % SHAPE_COUNT];
	moveDropPiece();

	for (bool quit = false; !quit;) {
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) { 
				moveGamePiece(event.key.keysym.sym);
				rotate(event.key.keysym.sym);
			}
			else if (event.type == SDL_QUIT)
				quit = true;
		}
		gettimeofday(&now, NULL);
		int64_t diff = (now.tv_sec * 1000000 + now.tv_usec) 
				- (start.tv_sec * 1000000 + start.tv_usec);
		if (diff > speed) {
				moveGamePiece(SDLK_DOWN); 
				gettimeofday(&start, NULL);
		}
		//speed = (speed * 9) / 10;

		score += removeLines();
		drawField();
		drawGamePiece(dropPiece);
		drawGamePiece(gamePiece);
		SDL_UpdateWindowSurface (window);
	}

	return score;
}
