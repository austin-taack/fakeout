#include "block.h"

void breakBlock(Block* block) {
    block->broken = true;
    block->hitbox = NULL;
}

