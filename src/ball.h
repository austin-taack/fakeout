#ifndef FAKEOUT_BALL
#define FAKEOUT_BALL

#include <SDL.h>

#include "app.h"
#include "hitbox.h"
#include "player.h"
#include "block.h"

// Enum for ball directions
typedef enum {
    LEFT,
    RIGHT
} XDirection;

typedef enum {
    UP,
    DOWN
} YDirection;

// Struct containing information on the ball
typedef struct {
    int x;
    int y;
    SDL_Texture* texture;

    XDirection xDirection;
    YDirection yDirection;
} Ball;

void moveBall(Ball* ball);
void checkBallCollisions(Ball* ball, Player* player, Block** blocks, int numRows, 
                         int blocksPerRow, int* blocksLeft, GameStatus* status);

#endif
