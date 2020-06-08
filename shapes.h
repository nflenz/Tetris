// Tetris has seven different shapes
#define SHAPE_COUNT 7

// Shapes
#define BAR       0
#define SQUARE    1
#define T         2
#define L         3
#define Z         4
#define REVERSE_L 5
#define REVERSE_Z 6

// This type stores values for the game piece
typedef struct {
    int8_t type;
    int8_t rotation;
    uint32_t color;
    struct { int8_t x, y; } position[4];
	int8_t change[4][8];
} piece_t;

// These are the values used when a new piece is spawned
// The rotations are specified here too

const piece_t newPiece[SHAPE_COUNT] = {

	BAR, 0, CYAN,
	 3,  0,  4,  0,  5,  0,  6,  0,
	 2, -2,  1, -1,  0,  0, -1,  1,
	-2,  2, -1,  1,  0,  0,  1, -1,
	 2, -2,  1, -1,  0,  0, -1,  1,
	-2,  2, -1,  1,  0,  0,  1, -1,

	// Squares don't rotate, so you get a bunch of zeros
	// Checkmate, geometry
	// Such a majestic shape
	SQUARE, 0, YELLOW, 
	 4,  0,  5,  0,  4,  1,  5,  1, 
	 0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,

	T, 0, PURPLE, 
	 4,  0,  5,  0,  5,  1,  6,  0,
	 1, -1,  0,  0, -1, -1, -1,  1,
	 1,  1,  0,  0,  1, -1, -1, -1,
	-1,  1,  0,  0,  1,  1,  1, -1,
	-1, -1,  0,  0, -1,  1,  1,  1,

	L, 0, ORANGE, 
	 4,  0,  4,  1,  5,  0,  6,  0,
	 1, -1,  0, -2,  0,  0, -1,  1,
	 1,  1,  2,  0,  0,  0, -1, -1,
	-1,  1,  0,  2,  0,  0,  1, -1,
	-1, -1, -2,  0,  0,  0,  1,  1,

	Z, 0, RED, 
	 4,  0,  5,  0,  5,  1,  6,  1,
	 1, -1,  0,  0, -1, -1, -2,  0,
	-1,  1,  0,  0,  1,  1,  2,  0,
	 1, -1,  0,  0, -1, -1, -2,  0,
	-1,  1,  0,  0,  1,  1,  2,  0,

	REVERSE_L, 0, BLUE, 
	 4,  0,  5,  0,  6,  0,  6,  1,
	 1, -1,  0,  0, -1,  1, -2,  0,
	 1,  1,  0,  0, -1, -1,  0, -2,
	-1,  1,  0,  0,  1, -1,  2,  0,
	-1, -1,  0,  0,  1,  1,  0,  2,

	REVERSE_Z, 0, GREEN, 
	 4,  1,  5,  1,  5,  0,  6,  0,
	 1,  0,  0, -1, -1,  0, -2, -1,
	-1,  0,  0,  1,  1,  0,  2,  1,
	 1,  0,  0, -1, -1,  0, -2, -1,
	-1,  0,  0,  1,  1,  0,  2,  1

};
