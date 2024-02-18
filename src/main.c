/*
* A basic video game modeled after Atari Breakout.
* Hit the ball towards the colored blocks to break them.
*
* Created by Austin Taack on February 15, 2024.
*
* Special thanks to Parallel Realities for their tutorial
* over SDL2 on which this game is based.
*
* Reference: https://www.parallelrealities.co.uk/tutorials/#shooter
*/

#include <stdbool.h>

#include "app.h"
#include "player.h"
#include "draw.h"
#include "ball.h"
#include "hitbox.h"

// Main loop: draw background, respond to input,
// update the window, and wait for the next frame.
int main(int argc, char* argv[]) {
    App app;
    initApp(&app);

    Player player;
    player.x = 288;
    player.y = 400;
    player.texture = loadTexture(&app, "player.png");

    Hitbox playerHitbox;
    playerHitbox.x0 = player.x;
    playerHitbox.x1 = player.x + 63;
    playerHitbox.y0 = player.y + 26;
    playerHitbox.y1 = player.y + 40;
    player.hitbox = &playerHitbox;

    Hitbox* hitboxes[] = {player.hitbox};

    Ball ball;
    ball.x = 288;
    ball.y = 380;
    ball.texture = loadTexture(&app, "ball.png");
    ball.xDirection = true;
    ball.yDirection = false;

    bool quitGame = false;

    while (!quitGame) {
	fillWindow(&app, 0, 0, 0);
	processInput(&app, &quitGame);
	movePlayer(&app, &player);
	moveBall(&ball);
	calculateBallDirection(&ball, hitboxes, 1);
	blitTexture(&app, player.texture, player.x, player.y);
	blitTexture(&app, ball.texture, ball.x, ball.y);
	updateWindow(&app);
	SDL_Delay(16);
    }

    closeApp(&app);
    exit(0);
}
