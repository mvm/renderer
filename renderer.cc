#include <iostream>
#include <cstdio>
#include <cmath>
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

void draw_line(SDL_Renderer *renderer, Uint32 color, int x1, int y1, int x2, int y2) {
    float slope;
    bool flip_axis = false;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    if(x2 == x1) {
        flip_axis = true;
    } else {
        float tmpslope = (y2 - y1) / (float)(x2 - x1);
        if(tmpslope > 0.5) {
            flip_axis = true;
        }
    }

    if(flip_axis == false) {
        slope = (y2 - y1) / (float)(x2 - x1);
    } else {
        slope = (x2 - x1) / (float)(y2 - y1);
    }
    
    if(flip_axis) {
        if(y1 > y2) {
            int t = y2;
            y2 = y1;
            y1 = t;
        }
        for(int y = y1; y < y2; y++) {
            int x = (int)SDL_floorf(slope*y) + x1;
            SDL_RenderDrawPoint(renderer, x, y);
        }
    } else {
        if(x1 > x2) {
            int t = x2;
            x2 = x1;
            x1 = t;
        }
        for(int x = x1; x < x2; x++) {
            int y = (int)SDL_floorf(slope*x) + y1;
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, int nCmdShow)
#else
int main()
#endif
{
    SDL_Window *window;

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

    SDL_Surface *screen_sfc = SDL_GetWindowSurface(window);
    SDL_Renderer *renderer = SDL_GetRenderer(window);

    Uint64 ticks = SDL_GetTicks64();
    SDL_Event event;

    while(!quit) {

        while(SDL_PollEvent(&event)) {
            handle_events(&event);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        draw_line(renderer, -1, 0, 0, WIDTH, HEIGHT);
        draw_line(renderer, -1, 0, HEIGHT, WIDTH, 0);
        draw_line(renderer, -1, WIDTH/2, 0, WIDTH/2, HEIGHT);
        draw_line(renderer, -1, 0, HEIGHT/2, WIDTH, HEIGHT/2);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
