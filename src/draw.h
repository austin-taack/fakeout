#ifndef FAKEOUT_DRAW
#define FAKEOUT_DRAW

#include "app.h"

void fillWindow(App* app, int r, int g, int b);
SDL_Texture* loadTexture(App* app, const char* textureName);
void blitTexture(App* app, SDL_Texture* texture, int x, int y);
void updateWindow(App* app);

#endif // fakeout draw

