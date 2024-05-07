#include <stdio.h>
#include <SDL2/SDL.h>

#include "./globals.h"
#include "./constants.h"
#include "./abstract_data_types.h"
#include "./geometry_operations.h"
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
                inputMoveY = -1;
            if(event.key.keysym.sym == SDLK_DOWN)
                inputMoveY = 1;
            if(event.key.keysym.sym == SDLK_LEFT)
                inputMoveX = -1;
            if(event.key.keysym.sym == SDLK_RIGHT)
                inputMoveX = 1;

            if(event.key.keysym.sym == SDLK_e)
                inputMoveZ = 1;
            if(event.key.keysym.sym == SDLK_q)
                inputMoveZ = -1;

            if(event.key.keysym.sym == SDLK_a)
                inputRotateY = -1;
            if(event.key.keysym.sym == SDLK_d)
                inputRotateY = 1;
            if(event.key.keysym.sym == SDLK_w)
                inputRotateX = -1;
            if(event.key.keysym.sym == SDLK_s)
                inputRotateX = 1;
            if(event.key.keysym.sym == SDLK_1)
                debugKey1 *= -1;
            if(event.key.keysym.sym == SDLK_2)
                debugKey2 *= -1;
            if(event.key.keysym.sym == SDLK_3)
                debugKey3 *= -1;
            if(event.key.keysym.sym == SDLK_4)
                debugKey4 *= -1;
            
            break;
        case SDL_KEYUP:
            inputMoveX = 0;
            inputMoveY = 0;
            inputMoveZ = 0;
            inputRotateX = 0;
            inputRotateY = 0;
            inputRotateZ = 0;
            debugKey1 = debugKey1;
            debugKey2 = debugKey2;
            debugKey3 = debugKey3;
            debugKey4 = debugKey4;
    }
}