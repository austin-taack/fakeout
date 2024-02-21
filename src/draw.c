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
    char filepath[50] = "../sprites/";
    strcat(filepath, textureName);

    SDL_Texture* imgTexture = IMG_LoadTexture(app->renderer, filepath);
    if (imgTexture == NULL) {
	printf("Error loading image: %s\n", IMG_GetError());
    }

    return imgTexture;
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

    if (SDL_RenderCopy(app->renderer, texture, NULL, &dest) < 0) {
	printf("Error blitting image to screen: %s\n", SDL_GetError());
    }
}

// Draws the given texture at the specified
// y-value, centered along the x-axis.
void blitTextureCentered(App* app, SDL_Texture* texture, int y) {
    SDL_Rect dest;

    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    dest.w *= 2;
    dest.h *= 2;
    dest.x = (WINDOW_WIDTH - dest.w) / 2;
    dest.y = y;

    if (SDL_RenderCopy(app->renderer, texture, NULL, &dest) < 0) {
	printf("Error blitting image to screen: %s\n", SDL_GetError());
    }
}

// Updates the window to display any
// changes made since the last update.
void updateWindow(App* app) {
    SDL_RenderPresent(app->renderer);
}

