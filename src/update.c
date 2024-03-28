#include <stdio.h>
#include <SDL2/SDL.h>

#include "./constants.h"
#include "./globals.h"
#include "./abstract_data_types.h"
#include "./geometry_operations.h"
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

    //RotateMesh(my_mesh, my_meshRotatedX, theta, 'x');

    InputMoveMeshPivot(my_mesh, delta_time);
    if(errorKey != 0) { 
        fprintf(
            stderr,
            "pivot my_mesh: %f, %f, %f\n",
            my_mesh->pivot.x,
            my_mesh->pivot.y,
            my_mesh->pivot.z
            );
    }
    
    //create object struct latter
    //MeshToWorldCenter(my_mesh, my_meshWorldCentered); no need to bring to world center if it is already centered

    RotateMesh(my_mesh, my_meshRotatedX, theta, 'x');
    RotateMesh(my_meshRotatedX, my_meshRotatedY, theta/2.0F, 'y');
    RotateMesh(my_meshRotatedY, my_meshRotatedZ, theta/4.0F, 'z');
    TranslateTrianglesFromPivot(my_meshRotatedZ, my_meshTranslatedFromPivot);
    //TranslateMesh(my_meshRotatedZ, my_meshTranslatedFromPivot, 3.0F);

    ProjectMesh(my_meshTranslatedFromPivot, my_meshProjected, projectionMatrix);

}



