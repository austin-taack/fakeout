#ifndef FAKEOUT_APP
#define FAKEOUT_APP

#include <stdbool.h>
#include <SDL.h>

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

// App struct is an interface to the SDL library.
typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
    bool left;
    bool right;
} App;

void initApp(App* app);
void processInput(App* app, bool* quitGame);
void closeApp(App* app);

#endif // fakeout app

