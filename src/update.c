#include <stdio.h>
#include <SDL2/SDL.h>

#include "./constants.h"
#include "./globals.h"
#include "./abstract_data_types.h"
#include "./geometry_operations.h"
#include "./update.h"

int last_frame_time = 0;

float theta = 0;

void update() {
    
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

    //clear mesh buffer everyframe
    my_obj->meshBufferOut = my_obj->meshImported;
    
    InputMoveObjPivot(my_obj, delta_time);

    RotateObj(my_obj, theta, 'x');
    RotateObj(my_obj, theta/2.0F, 'y');
    RotateObj(my_obj, theta/4.0F, 'z');
    
    UpdateTriangleCenter(my_obj);

    TranslateObjToPivot(my_obj);

    ProjectObjMesh(my_obj, projectionMatrix);

}



