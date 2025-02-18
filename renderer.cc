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

void draw_line(SDL_Renderer *renderer, Uint32 color, int _x1, int _y1, int _x2, int _y2) {
    float slope;
    bool flip_axis = false;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    int x1, x2, y1, y2;
    x1 = _x1;
    x2 = _x2;
    y1 = _y1;
    y2 = _y2;

    if(x2 == x1) {
        flip_axis = true;
    } else {
        float tmpslope = (y2 - y1) / (float)(x2 - x1);
        if(abs(tmpslope) > 1) {
            flip_axis = true;
        }
    }

    if(flip_axis == false) {
        if(x1 > x2) {
            x1 = _x2;
            y1 = _y2;

            x2 = _x1;
            y2 = _y1;
        }
        slope = (y2 - y1) / (float)(x2 - x1);
    } else {
        if(y1 > y2) {
            y1 = _y2;
            x1 = _x2;

            y2 = _y1;
            x2 = _x1;
        }
        slope = (x2 - x1) / (float)(y2 - y1);
    }
    
    if(flip_axis) {
        SDL_assert(y1 < y2);
        for(int y = y1; y < y2; y++) {
            int x = (int)SDL_floorf(slope*y) + x1;
            SDL_RenderDrawPoint(renderer, x, y);
        }
    } else {
        SDL_assert(x1 < x2);
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

        draw_line(renderer, -1, WIDTH/2 + 30, 0, WIDTH/2 - 30, HEIGHT);
        draw_line(renderer, -1, WIDTH/2 - 30, 0, WIDTH/2 + 30, HEIGHT);
        
        draw_line(renderer, -1, 0, HEIGHT/2 - 30, WIDTH, HEIGHT/2 + 30);
        draw_line(renderer, -1, WIDTH, HEIGHT/2 - 30, 0, HEIGHT/2 + 30);
        
        draw_line(renderer, -1, WIDTH/2, -50, WIDTH/2, HEIGHT + 50);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
