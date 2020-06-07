#include <stdbool.h>

typedef struct {
    bool filled;
    SDL_Color color;
} block_t;

typedef struct {
    int rotation;
    int x, y;
	enum { Bar, Square, T, L, Z, Reverse_L, Reverse_Z } type;
    SDL_Color color;
} piece_t;
