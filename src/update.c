#include <stdio.h>
#include <SDL2/SDL.h>

#include "./constants.h"
#include "./globals.h"
#include "./abstract_data_types.h"
#include "./update.h"

int last_frame_time = 0;

float theta = 0;

void update(Mesh* my_mesh, Mesh* my_meshProjected) {
    
    //caping frame rate
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    //delta time in seconds
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    last_frame_time = SDL_GetTicks();

    //-----------------------------------------------------------------

    theta += 0.7F *delta_time;

    RotateMesh(my_mesh, my_meshRotated, theta, 'z');

    InputMoveMesh(my_mesh, delta_time);
    
    ProjectMesh(my_meshRotated, my_meshProjected, projectionMatrix);

}



