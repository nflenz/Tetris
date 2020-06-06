#include <SDL2/SDL.h>
//#include <SDL2/SDL_video.h>
//#include <SDL2/SDL_error.h>
//#include <SDL2/SDL_timer.h>
#include <stdlib.h>
#include "colors.h"

int main(int argc, char* argv[]) {
	// Screen size
	const int BLOCK_SIZE    = 40;
	const int SCREEN_WIDTH  = 10 * BLOCK_SIZE;
	const int SCREEN_HEIGHT = 20 * BLOCK_SIZE;

	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
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
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format,black.r,black.g,black.b));

	// Update the surface
	SDL_UpdateWindowSurface(window);

	// Wait two seconds
	SDL_Delay(2000);

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
