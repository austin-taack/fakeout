#include "ball.h"

#include "app.h"

// Move the ball in the proper direction
void moveBall(Ball* ball) {
    if (ball->xDirection == RIGHT) {
	ball->x += 3;
    } else {
	ball->x -= 3;
    }

    if (ball->yDirection == DOWN) {
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
	ball->xDirection = RIGHT;
	return;
    } else if (right >= WINDOW_WIDTH - 5) {
	ball->xDirection = LEFT;
	return;
    } else if (top <= 4) {
	ball->yDirection = DOWN;
	return;
    } else if (bottom >= WINDOW_HEIGHT - 5) {
	ball->yDirection = UP;
	return;
    }

    for (int i = 0; i < numHitboxes; i++) {
	Hitbox* hitbox = hitboxes[i];
	
	if ((centerX >= hitbox->x0) && (centerX <= hitbox->x1)) {
	    if ((bottom >= hitbox->y0) && (top <= hitbox->y0)) {
		// Ball collides with the top of the hitbox, needs to go up.
		ball->yDirection = UP;
		return;
	    }
	} else if ((centerY >= hitbox->y0) && (centerY <= hitbox->y1)) {
	    if ((right >= hitbox->x0) && (right <= hitbox->x1)) {
		// Ball collides with the left side of the hitbox, needs to go left.
		ball->xDirection = LEFT;
		return;
	    } else if ((left >= hitbox->x0) && (left <= hitbox->x1)) {
		// Ball collides with the right side of the hitbox, needs to go right.
		ball->xDirection = RIGHT;
		return;
	    }
	}
    }
}

