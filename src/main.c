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

#include <stdlib.h>
#include <stdbool.h>

#include "app.h"
#include "player.h"
#include "draw.h"
#include "ball.h"
#include "hitbox.h"
#include "block.h"
#include "text.h"

GameStatus runGame(App* app);
void displayWinScreen(App* app, GameStatus* status);
void displayLossScreen(App* app, GameStatus* status);

// Main loop: draw background, respond to input,
// update the window, and wait for the next frame.
int main(int argc, char* argv[]) {
    App app;
    initApp(&app);

    GameStatus status = runGame(&app);
    
    if (status == WIN) {
	displayWinScreen(&app, &status);
    } else if (status == LOSS) {
	displayLossScreen(&app, &status);
    }
    
    closeApp(&app);
    exit(0);
}

// Runs the playable portion of the game.
//
// Returns the status that the game should move
// to next: a win, a loss, or a player-requested quit.
GameStatus runGame(App* app) {
    Player player;
    player.x = 288;
    player.y = 400;
    player.texture = loadTexture(app, "player.png");

    Hitbox playerHitbox;
    playerHitbox.x0 = player.x;
    playerHitbox.x1 = player.x + 63;
    playerHitbox.y0 = player.y + 26;
    playerHitbox.y1 = player.y + 41;
    playerHitbox.type = PLAYER;
    player.hitbox = &playerHitbox;

    const int numBlocks = 60;
    const int numRows = 6;
    const int blocksPerRow = 10;

    Block* blocks[numBlocks];
    initBlockRow(app, blocks, 0, "red_block.png");
    initBlockRow(app, blocks, 1, "orange_block.png");
    initBlockRow(app, blocks, 2, "yellow_block.png");
    initBlockRow(app, blocks, 3, "green_block.png");
    initBlockRow(app, blocks, 4, "cyan_block.png");
    initBlockRow(app, blocks, 5, "blue_block.png");

    int blocksLeft = numBlocks;

    Ball ball;
    ball.x = 288;
    ball.y = 380;
    ball.texture = loadTexture(app, "ball.png");
    ball.xDirection = true;
    ball.yDirection = false;

    GameStatus status = PLAYING;

    while (status == PLAYING) {
	fillWindow(app, 0, 0, 0);

	processInput(app, &status);
	movePlayer(app, &player);

	moveBall(&ball);
	checkBallCollisions(&ball, &player, blocks, numRows, blocksPerRow, &blocksLeft, &status);

	if (blocksLeft == 0) {
	    status = WIN;
	}

	blitTexture(app, player.texture, player.x, player.y);
	blitTexture(app, ball.texture, ball.x, ball.y);

	for (int i = 0; i < numBlocks; i++) {
	    Block* block = blocks[i];
	    if (!(block->broken)) {
		blitTexture(app, block->texture, block->x, block->y);
	    }
	}

	updateWindow(app);
	SDL_Delay(16);
    }

    for (int i = 0; i < numBlocks; i++) {
	Block* block = blocks[i];
	destroyBlock(block);
    }

    return status;
}

// Displays a message letting the player
// know they won the game.
void displayWinScreen(App* app, GameStatus* status) {
    fillWindow(app, 0, 0, 0);

    SDL_Texture* textTexture = createTextTexture(app, "YOU WIN");
    blitTextureCentered(app, textTexture);

    updateWindow(app);

    while (*status == WIN) {
	processInput(app, status);
	SDL_Delay(16);
    }
}

// Displays a message letting the player know
// they lost the game.
void displayLossScreen(App* app, GameStatus* status) {
    fillWindow(app, 0, 0, 0);

    SDL_Texture* textTexture = createTextTexture(app, "YOU LOSE");
    blitTextureCentered(app, textTexture);

    updateWindow(app);

    while (*status == LOSS) {
	processInput(app, status);
	SDL_Delay(16);
    }
}

