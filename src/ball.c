#include "ball.h"

#include <stdlib.h>

#include "app.h"

// Move the ball in the proper direction
void moveBall(Ball* ball) {
    if (ball->xDirection) {
	ball->x += 3;
    } else {
	ball->x -= 3;
    }

    if (ball->yDirection) {
	ball->y += 3;
    } else {
	ball->y -= 3;
    }
}

// Loops through all hitboxes to check if the ball hits anything.
void calculateBallDirection(Ball* ball, Hitbox** hitboxes, int numHitboxes) {
    int left = ball->x + 24;
    int right = ball->x + 38;
    int top = ball->y + 24;
    int bottom = ball->y + 38;
    int centerX = ball->x + 31;
    int centerY = ball->y + 31;

    // Check if the ball is hitting a boundary
    if (left <= 4) {
	ball->xDirection = true;
	return;
    } else if (right >= WINDOW_WIDTH - 5) {
	ball->xDirection = false;
	return;
    } else if (top <= 4) {
	ball->yDirection = true;
	return;
    } else if (bottom >= WINDOW_HEIGHT - 5) {
	ball->yDirection = false;
	return;
    }

    for (int i = 0; i < numHitboxes; i++) {
	Hitbox* hitbox = hitboxes[i];

    	if ((abs(left - hitbox->x0) <= 2) && (centerY >= hitbox->y0) && (centerY <= hitbox->y1)) {
	    // Left side of the ball collides with hitbox, needs to go right.
	    ball->xDirection = true;
	    return;
	} else if ((abs(right - hitbox->x1) <= 2) && (centerY >= hitbox->y0) && (centerY <= hitbox->y1)) {
	    // Right side of the ball collides with hitbox, needs to go left.
	    ball->xDirection = false;
	    return;
	} else if ((abs(top - hitbox->y0) <= 2) && (centerX >= hitbox->x0) && (centerX <= hitbox->x1)) {
	    // Top of the ball collides with hitbox, needs to go down.
	    ball->yDirection = true;
	    return;
	} else if ((abs(bottom - hitbox->y1) <= 2) && (centerX >= hitbox->x0) && (centerX <= hitbox->x1)) {
	    // Bottom of the ball collides with hitbox, needs to go up.
	    ball->yDirection = false;
	    return;
	}
    }
}

