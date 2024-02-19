#include "block.h"

#include <stdlib.h>

#include "app.h"
#include "draw.h"

Block* createBlock(App* app, int x, int y, const char* textureName);

// Initializes one row of blocks.
void initBlockRow(App* app, Block** blocks, int rowNum, const char* textureName) {
    const char numBlocks = 10;
    for (int i = 0; i < numBlocks; i++) {
	int blockID = (rowNum * numBlocks) + i;
	int x = 64 * i;
	int y = (32 * rowNum) - 16;
	blocks[blockID] = createBlock(app, x, y, textureName);
    }
}

// Creates a single block and returns
// a pointer to the block.
Block* createBlock(App* app, int x, int y, const char* textureName) {
    Block* block = malloc(sizeof(Block));
    block->x = x;
    block->y = y;
    block->texture = loadTexture(app, textureName);
    block->broken = false;

    Hitbox* blockHitbox = malloc(sizeof(Hitbox));
    blockHitbox->x0 = block->x;
    blockHitbox->x1 = block->x + 63;
    blockHitbox->y0 = block->y + 16;
    blockHitbox->y1 = block->y + 49;
    block->hitbox = blockHitbox;
    
    return block;
}

// Remove a block from the game once it
// is hit by the ball.
void breakBlock(Block* block) {
    block->broken = true;
}

// Frees the memory given to the block.
void destroyBlock(Block* block) {
    free(block->hitbox);
    free(block);
}

