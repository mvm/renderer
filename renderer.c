#include <stdio.h>
#include <SDL.h>

int main() {
    SDL_Window *window;
    SDL_Surface *render_surface;
    SDL_Renderer *renderer;

    int err = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
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
    renderer = SDL_GetRenderer(window);

    Uint64 start_time = SDL_GetTicks64();
    unsigned int quit = 0;

    do {
        Uint64 now = SDL_GetTicks64();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderDrawLine(renderer, -50, 720, 1000, 526);
        SDL_RenderDrawLine(renderer, 200, 200, 600, 600);

        if((now - start_time > 5*1000)) break;
        SDL_RenderPresent(renderer);
    } while(1);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
