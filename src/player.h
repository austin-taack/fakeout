#ifndef FAKEOUT_PLAYER
#define FAKEOUT_PLAYER

#include "app.h"

typedef struct {
    int x;
    int y;
    SDL_Texture* texture;
} Player;

void movePlayer(App* app, Player* player);

#endif // fakeout player

