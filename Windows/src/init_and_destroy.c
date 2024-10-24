#include <stdio.h>
#include "./SDL2/SDL.h"

#include "./constants.h"
#include "./globals.h"
#include "./init_and_destroy.h"


int initialize_window(SDL_Window** window, SDL_Renderer** renderer) {


    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return FALSE;
    }

    *window = SDL_CreateWindow(
        "3D Engine",
        SDL_WINDOWPOS_CENTERED, //x position
        SDL_WINDOWPOS_CENTERED, //y position
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );
    if(!*window) {
        fprintf(stderr, "Error creating SDL Window.\n");
        return FALSE;
    }

    *renderer = SDL_CreateRenderer(*window, -1, 0);
    if(!*renderer) {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return FALSE;
    }

    return TRUE;
}

void destroy_window(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}