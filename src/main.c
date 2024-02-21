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

void displayTitleScreen(App* app);
void runGame(App* app);
void displayWinScreen(App* app);
void displayLossScreen(App* app); 

// Main loop: draw background, respond to input,
// update the window, and wait for the next frame.
int main(int argc, char* argv[]) {
    App app;
    initApp(&app);

    displayTitleScreen(&app);

    while (app.status != QUIT) {
	switch (app.status) {
	    case PLAYING:
		runGame(&app);
		break;

	    case WIN:
		displayWinScreen(&app);
		break;

	    case LOSS:
		displayLossScreen(&app);
		break;

	    default:
		printf("Error changing game status.");
		app.status = QUIT;
		break;
	}
    }
    
    closeApp(&app);
    exit(0);
}

// Runs the playable portion of the game.
//
// Returns the status that the game should move
// to next: a win, a loss, or a player-requested quit.
void runGame(App* app) {
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

    while (app->status == PLAYING) {
	fillWindow(app, 0, 0, 0);

	processInput(app);
	movePlayer(app, &player);

	moveBall(&ball);
	checkBallCollisions(app, &ball, &player, blocks, numRows, blocksPerRow, &blocksLeft);

	if (blocksLeft == 0) {
	    app->status = WIN;
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
}

void setUpTextScreen(App* app, const GameStatus status, bool* newGame, const char* message1, const char* message2);

// Displays the title screen prompting
// the player to start.
void displayTitleScreen(App* app) {
    setUpTextScreen(app, TITLE, &app->space, "FAKEOUT", "PRESS SPACE");
}

// Displays a screen telling the player they won.
void displayWinScreen(App* app) {
    setUpTextScreen(app, WIN, &app->r, "YOU WIN", "PRESS R TO RESTART");
}

// Displays a screen telling the player they lost.
void displayLossScreen(App* app) {
    setUpTextScreen(app, LOSS, &app->r, "YOU LOSE", "PRESS R TO RETRY");
}

// Displays a screen with two messages to the
// player, given by message1 and message2.
void setUpTextScreen(App* app, const GameStatus status, bool* newGame, const char* message1, const char* message2) {
    fillWindow(app, 0, 0, 0);

    SDL_Texture* texture1 = createTextTexture(app, message1);
    blitTextureCentered(app, texture1, 150);

    SDL_Texture* texture2 = createTextTexture(app, message2);
    blitTextureCentered(app, texture2, 300);

    updateWindow(app); 

    while (app->status == status) {
	processInput(app);

	if (*newGame) {
	    app->status = PLAYING;
	}

	SDL_Delay(16);
    }
}

