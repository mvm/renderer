#include <iostream>
#include <cstdio>
#include <SDL.h>
#ifdef WIN32
#include <windows.h>
#endif

#define WIDTH 1280
#define HEIGHT 720

bool quit = false;

void handle_events(SDL_Event *event) {
    if(event->type == SDL_QUIT)
        quit = true;
}

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, int nCmdShow)
#else
int main()
#endif
{
    SDL_Window *window;
    SDL_Surface *render_surface;
    SDL_Renderer *renderer;

    int err = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    if(err < 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Renderer", 0, 0, WIDTH, HEIGHT, 0);
    if(window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "can't create a window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface *sfc = SDL_GetWindowSurface(window);

    Uint64 ticks = SDL_GetTicks64();
    SDL_Event event;

    while(!quit) {

        while(SDL_PollEvent(&event)) {
            handle_events(&event);
        }
        
        SDL_UpdateWindowSurface(window);

    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
