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

// Main loop: draw background, respond to input,
// update the window, and wait for the next frame.
int main(int argc, char* argv[]) {
    App app;
    initApp(&app);

    Player player;
    player.x = 288;
    player.y = 400;
    player.texture = loadTexture(&app, "player.png");

    bool quitGame = false;

    while (!quitGame) {
	fillWindow(&app, 0, 0, 0);
	processInput(&app, &quitGame);
	movePlayer(&app, &player);
	blitTexture(&app, player.texture, player.x, player.y);
	updateWindow(&app);
	SDL_Delay(16);
    }

    closeApp(&app);
    exit(0);
}
