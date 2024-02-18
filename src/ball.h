#ifndef FAKEOUT_BALL
#define FAKEOUT_BALL

#include <stdbool.h>
#include <SDL.h>

#include "app.h"
#include "hitbox.h"

// Struct containing information on the ball
typedef struct {
    int x;
    int y;
    SDL_Texture* texture;

    bool xDirection;
    bool yDirection;
} Ball;

void moveBall(Ball* ball);
void calculateBallDirection(Ball* ball, Hitbox** hitboxes, int numHitboxes);

#endif
