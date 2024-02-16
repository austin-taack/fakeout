#include "draw.h"

#include <SDL.h>

// Fills the window with the specified color
// (set using the r, g, and b values).
void fillWindow(App* app, int r, int g, int b) {
    SDL_SetRenderDrawColor(app->renderer, r, g, b, 255);
    SDL_RenderClear(app->renderer);
}

// Updates the window to display any
// changes made since the last update.
void updateWindow(App* app) {
    SDL_RenderPresent(app->renderer);
}

