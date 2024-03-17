#include <stdio.h>
#include <SDL2/SDL.h>

#include "./constants.h"
#include "./globals.h"
#include "./tad.h"
#include "./update.h"

int last_frame_time = 0;
float theta;


void update() {
    
    //caping frame rate
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    //delta time in seconds
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    last_frame_time = SDL_GetTicks();

//-------------------------------------------------------------------------------------
    
    //TESTING

    theta += 1.0f * delta_time;

    //rotation y
    rotationMat1.m[0][0] = cosf(theta);
	rotationMat1.m[0][2] = sinf(theta);
	rotationMat1.m[2][0] = -sinf(theta);
	rotationMat1.m[2][2] = cosf(theta);
	rotationMat1.m[1][1] = 1;

    //rotation z
    rotationMat2.m[0][0] = cosf(theta/2);
	rotationMat2.m[0][1] = -sinf(theta/2);
	rotationMat2.m[1][0] = sinf(theta/2);
	rotationMat2.m[1][1] = cosf(theta/2);
	rotationMat2.m[2][2] = 1;

    tri2.point[0] = MulMatrix4Vector3(tri1.point[0], rotationMat1);
    tri2.point[1] = MulMatrix4Vector3(tri1.point[1], rotationMat1);
    tri2.point[2] = MulMatrix4Vector3(tri1.point[2], rotationMat1);
    
    tri3.point[0] = MulMatrix4Vector3(tri2.point[0], rotationMat2);
    tri3.point[1] = MulMatrix4Vector3(tri2.point[1], rotationMat2);
    tri3.point[2] = MulMatrix4Vector3(tri2.point[2], rotationMat2);
    
    tri4.point[0] = MulMatrix4Vector3(tri3.point[0], mat1);
    tri4.point[1] = MulMatrix4Vector3(tri3.point[1], mat1);
    tri4.point[2] = MulMatrix4Vector3(tri3.point[2], mat1);

}