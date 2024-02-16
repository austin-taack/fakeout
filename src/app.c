#include "app.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

// Initialize the game window and renderer.
void initApp(App* app) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	printf("Error initializing SDL: %s\n", SDL_GetError());
	exit(1);
    }

    app->window = SDL_CreateWindow("Fakeout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!app->window) {
	printf("Error creating window: %s\n", SDL_GetError());
    }

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
    if (!app->renderer) {
	printf("Error creating renderer: %s\n", SDL_GetError());
    }
}

// Poll SDL for what event (if any) has occured
// and update the game accordingly.
//
// Changes quitGame to true if the player wants to quit,
// false otherwise.
void processInput(bool* quitGame) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
	switch (event.type) {
	    // Quit the game
	    case SDL_QUIT:
		*quitGame = true;
		break;

	    // Do nothing
	    default:
		break;
	}
    }
}

// Destroy the renderer, the window, and
// all SDL processes still running.
void closeApp(App* app) {
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();

    app->renderer = NULL;
    app->window = NULL;
}

