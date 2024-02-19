#ifndef FAKEOUT_BLOCK
#define FAKEOUT_BLOCK

#include <stdbool.h>
#include <SDL.h>

#include "app.h"
#include "hitbox.h"

typedef struct {
    int x;
    int y;
    SDL_Texture* texture;
    Hitbox* hitbox;
    bool broken;
} Block;

void initBlockRow(App* app, Block** blocks, int rowNum, const char* textureName);
void freeBlock(Block* block);
void breakBlock(Block* block);

#endif // fakeout block

