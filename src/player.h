#ifndef FAKEOUT_PLAYER
#define FAKEOUT_PLAYER

#include <SDL.h>

#include "app.h"
#include "hitbox.h"

typedef struct {
    int x;
    int y;
    SDL_Texture* texture;
    Hitbox* hitbox;
} Player;

void movePlayer(App* app, Player* player);

#endif // fakeout player

