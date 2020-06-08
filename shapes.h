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
	uint8_t type;
	uint8_t rotation;
	uint32_t color;
	struct { 
		uint8_t x, y; 
	} position[4];
} piece_t;

// These are the values used when a new piece is spawned
const piece_t newPiece[SHAPE_COUNT] = {
	BAR,       0, CYAN   , 3, 0, 4, 0, 5, 0, 6, 0,
	SQUARE,    0, YELLOW , 4, 0, 5, 0, 4, 1, 5, 1,
	T,         0, PURPLE , 4, 0, 5, 0, 5, 1, 6, 0,
	L,         0, ORANGE , 4, 0, 4, 1, 5, 0, 6, 0,
	Z,         0, RED    , 4, 0, 5, 0, 5, 1, 6, 1,
	REVERSE_L, 0, BLUE   , 4, 0, 5, 0, 6, 0, 6, 1,
	REVERSE_Z, 0, GREEN  , 4, 1, 5, 1, 5, 0, 6, 0
};
