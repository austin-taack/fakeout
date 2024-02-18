#ifndef FAKEOUT_BALL
#define FAKEOUT_BALL

#include <SDL.h>

#include "app.h"
#include "hitbox.h"

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
void calculateBallDirection(Ball* ball, Hitbox** hitboxes, int numHitboxes);

#endif
