#include "ball.h"

#include <stdbool.h>

#include "app.h"
#include "block.h"

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

bool checkCollisionWithHitbox(Ball* ball, Hitbox* hitbox, int left, int right, int top, int bottom, int centerX, int centerY);

// Loops through all hitboxes to check if the ball hits anything.
void checkBallCollisions(Ball* ball, Player* player, Block** blocks, int numRows, int blocksPerRow, int* blocksLeft, GameStatus* status) {
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
	*status = LOSS;
	return;
    }

    if (checkCollisionWithHitbox(ball, player->hitbox, left, right, top, bottom, centerX, centerY)) {
	return;
    }

    for (int i = 0; i < numRows; i++) {
	// Check to see which row the ball is in
	int startOfRow = blocksPerRow * i;
	if (!(top <= blocks[startOfRow]->hitbox->y0 + 4) && !(bottom >= blocks[startOfRow]->hitbox->y1 - 4)) continue;

	// Check each individual block in the row
	for (int j = startOfRow; j < startOfRow + blocksPerRow; j++) {
	    Block* block = blocks[j];
	    if (!block->broken) {
		if (checkCollisionWithHitbox(ball, block->hitbox, left, right, top, bottom, centerX, centerY)) {
		    breakBlock(block);
		    *blocksLeft = *blocksLeft - 1;
		    return;
		}
	    }
	}
    }
}

// Checks to see whether the ball collided with the given hitbox
// and processes the result if necessary. Returns true if the
// ball collided with the given hitbox, false otherwise.
bool checkCollisionWithHitbox(Ball* ball, Hitbox* hitbox, int left, int right, int top, int bottom, int centerX, int centerY) {
    if ((centerX >= hitbox->x0) && (centerX <= hitbox->x1)) {
	if ((bottom >= hitbox->y0) && (bottom <= hitbox->y1)) {
	    // Bottom of the ball collides with hitbox, needs to go up.
	    if (hitbox->type == PLAYER) {
		int playerMidpoint = (hitbox->x0 + hitbox->x1) / 2;
		if (right < playerMidpoint) {
		    ball->xDirection = LEFT;
		} else if (left > playerMidpoint) {
		    ball->xDirection = RIGHT;
		}
	    }

	    ball->yDirection = UP;
	    return true;
	} else if ((top >= hitbox->y0) && (top <= hitbox->y1)) {
	    // Top of the ball collides with hibtox, needs to go down.
	    ball->yDirection = DOWN;
	    return true;
	}
    } else if ((centerY >= hitbox->y0) && (centerY <= hitbox->y1)) {
	if ((right >= hitbox->x0) && (right <= hitbox->x1)) {
	    // Right side of the ball collides with hitbox, needs to go left.
	    ball->xDirection = LEFT;
	    return true;
	} else if ((left >= hitbox->x0) && (left <= hitbox->x1)) {
	    // Left side of the ball collides with hibtox, needs to go right.
	    ball->xDirection = RIGHT;
	    return true;
	}
    }

    return false;
}

