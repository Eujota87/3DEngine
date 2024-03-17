#include <stdio.h>
#include <SDL2/SDL.h>

#include "./globals.h"
#include "./constants.h"
#include "./tad.h"
#include "./process_input.h"

void process_input() {

    SDL_Event event;
    SDL_PollEvent(&event); //reference to event

    switch (event.type) {
        case SDL_QUIT:
            game_is_running = FALSE;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE)
                game_is_running = FALSE;
            break;
    }
}