#include <SDL2/SDL.h>
#include <stdlib.h>
#include "window.h"
#include "game_loop.h"

int main(int argc, char* argv[]) {

	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		exit(0);
	}

	// Create window
	window = SDL_CreateWindow( "Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( window == NULL )
	{
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		exit(0);
	}

	// Get window surface
	screenSurface = SDL_GetWindowSurface(window);

	// Fill the surface black
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format,0,0,0));

	// Update the surface
	SDL_UpdateWindowSurface(window);

	// Run the main game loop
	int score = game_loop(window, screenSurface);

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
