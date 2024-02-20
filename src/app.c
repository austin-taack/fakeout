#include "app.h"

#include <SDL_image.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

// Initialize the SDL sytem, game window, and renderer.
void initApp(App* app) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	printf("Error initializing SDL: %s\n", SDL_GetError());
	exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
	printf("Error initializing IMG: %s\n", IMG_GetError());
    }

    if (TTF_Init() < 0) {
	printf("Error initializing TTF: %s\n", TTF_GetError());
    }

    app->font = TTF_OpenFont("../fonts/PressStart2P-vaV7.ttf", 15);
    if (app->font == NULL) {
	printf("Error loading font: %s\n", TTF_GetError());
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

void processKeyDown(App* app, SDL_KeyboardEvent *event);
void processKeyUp(App* app, SDL_KeyboardEvent *event);

// Poll SDL for what event (if any) has occured
// and update the game accordingly.
//
// Changes gameStatus to QUIT if the player wants to quit.
void processInput(App* app, GameStatus* gameStatus) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
	switch (event.type) {
	    // Quit the game
	    case SDL_QUIT:
		*gameStatus = QUIT;
		break;

	    // Key has been pressed down
	    case SDL_KEYDOWN:
		processKeyDown(app, &event.key);
		break;

	    // Key has been released
	    case SDL_KEYUP:
		processKeyUp(app, &event.key);
		break;

	    // Do nothing
	    default:
		break;
	}
    }
}

// Processes key presses.
void processKeyDown(App* app, SDL_KeyboardEvent *event) {
    if (!event->repeat) {
	switch (event->keysym.scancode) {
	    case SDL_SCANCODE_LEFT:
		app->left = true;
		break;

	    case SDL_SCANCODE_RIGHT:
		app->right = true;
		break;

	    default:
		break;
	}
    }
}

// Processes key releases.
void processKeyUp(App* app, SDL_KeyboardEvent *event) {
    if (!event->repeat) {
	switch (event->keysym.scancode) {
	    case SDL_SCANCODE_LEFT:
		app->left = false;
		break;

	    case SDL_SCANCODE_RIGHT:
		app->right = false;
		break;

	    default:
		break;
	}
    }
}

// Destroy the renderer, the window, and
// all SDL processes still running.
void closeApp(App* app) {
    TTF_CloseFont(app->font);
    app->font = NULL;

    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    app->renderer = NULL;
    app->window = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

