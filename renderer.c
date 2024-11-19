#include <stdio.h>
#include <SDL.h>

int main() {
    SDL_Window *window;
    SDL_Surface *render_surface;

    int err = SDL_Init(SDL_INIT_VIDEO);
    if(err < 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Renderer", 0, 0, 1280, 720, 0);
    if(window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "can't create a window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    render_surface = SDL_GetWindowSurface(window);

    Uint64 start_time = SDL_GetTicks64();
    unsigned int quit = 0;

    do {
        Uint64 now = SDL_GetTicks64();

        if((now - start_time > 5*1000)) break;
        SDL_UpdateWindowSurface(window);
    } while(1);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
