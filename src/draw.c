#include "draw.h"

#include <string.h>
#include <SDL.h>
#include <SDL_image.h>

// Fills the window with the specified color
// (set using the r, g, and b values).
void fillWindow(App* app, int r, int g, int b) {
    SDL_SetRenderDrawColor(app->renderer, r, g, b, 255);
    SDL_RenderClear(app->renderer);
}

// Loads the texture specified by textureName
// into the game.
SDL_Texture* loadTexture(App* app, const char* textureName) {
    //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", textureName);
    char filepath[40] = "../sprites/";
    strcat(filepath, textureName);
    return IMG_LoadTexture(app->renderer, filepath);
}

// Draws the given texture at the specified
// x and y coordinates on the game window.
void blitTexture(App* app, SDL_Texture* texture, int x, int y) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;

    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    dest.w *= 2;
    dest.h *= 2;

    SDL_RenderCopy(app->renderer, texture, NULL, &dest);
}

// Updates the window to display any
// changes made since the last update.
void updateWindow(App* app) {
    SDL_RenderPresent(app->renderer);
}

