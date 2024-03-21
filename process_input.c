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

            if(event.key.keysym.sym == SDLK_UP)
                moveY = -1;
            if(event.key.keysym.sym == SDLK_DOWN)
                moveY = 1;
            if(event.key.keysym.sym == SDLK_LEFT)
                moveX = -1;
            if(event.key.keysym.sym == SDLK_RIGHT)
                moveX = 1;

            if(event.key.keysym.sym == SDLK_e)
                moveZ = 1;
            if(event.key.keysym.sym == SDLK_q)
                moveZ = -1;

            if(event.key.keysym.sym == SDLK_a)
                rotateY = -1;
            if(event.key.keysym.sym == SDLK_d)
                rotateY = 1;
            if(event.key.keysym.sym == SDLK_w)
                rotateX = 1;
            if(event.key.keysym.sym == SDLK_s)
                rotateX = -1;
            
            break;
        case SDL_KEYUP:
            moveX = 0;
            moveY = 0;
            moveZ = 0;
            rotateX = 0;
            rotateY = 0;
            rotateZ = 0;
    }
}