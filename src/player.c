#include "player.h"

// Moves the player character when prompted.
void movePlayer(App* app, Player* player) {
    if (app->left && !app->right && player->x > 4) {
	player->x -= 4;
    } else if (app->right && !app->left && player->x < 572) {
	player->x += 4;
    }
}

