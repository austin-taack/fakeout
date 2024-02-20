#include "text.h"

#include <SDL_ttf.h>

// Create a texture with the given text written on it.
SDL_Texture* createTextTexture(App* app, const char* text) {
    SDL_Color white = {0xFF, 0xFF, 0xFF};
    SDL_Surface* textSurface = TTF_RenderText_Solid(app->font, text, white);
    if (textSurface == NULL) {
	printf("Error loading text surface: %s\n", TTF_GetError());
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(app->renderer, textSurface);
    if (textTexture == NULL) {
	printf("Error creating text texture after loading surface: %s\n", SDL_GetError());
    }

    SDL_FreeSurface(textSurface);

    return textTexture;
}
