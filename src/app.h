#ifndef FAKEOUT_APP
#define FAKEOUT_APP

#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

// GameStatus struct keeps track of what stage of
// the game the player is currently in.
typedef enum {
    TITLE,
    PLAYING,
    WIN,
    LOSS,
    QUIT,
} GameStatus;

// App struct is an interface to the SDL library.
// It controls rendering to the window and tracks
// key presses.
typedef struct {
    GameStatus status;
    SDL_Renderer* renderer;
    SDL_Window* window;
    TTF_Font* font;
    bool left;
    bool right;
    bool space;
    bool r;
} App;

void initApp(App* app);
void processInput(App* app);
void closeApp(App* app);

#endif // fakeout app

