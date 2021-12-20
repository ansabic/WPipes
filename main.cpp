#include "SDL2/SDL.h"
#include "view/View.h"
#include "common/Constants.h"

View initView() {
    Game game = Game();
    Controller controller = Controller(game);
    return View(controller);
}

int main(int, char **) {
    SDL_Window *window = nullptr;
    SDL_Surface *screenSurface = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        window = SDL_CreateWindow("WPipes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr)
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        else {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
        }
    }
    View view = initView();
    view.loop();
    return 0;
}
