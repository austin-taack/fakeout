#ifndef FAKEOUT_APP
#define FAKEOUT_APP

#include <stdbool.h>
#include <SDL.h>

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

// App struct contains pointers to the
// SDL renderer and window.
typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
} App;

void initApp(App* app);
void processInput(bool* quitGame);
void closeApp(App* app);

#endif // fakeout app

