#ifndef FAKEOUT_HITBOX
#define FAKEOUT_HITBOX

typedef enum {
    PLAYER,
    BLOCK
} HitboxType;


typedef struct {
    HitboxType type; 
    int x0;
    int x1;
    int y0;
    int y1;
} Hitbox;

#endif // Fakeout hitbox

