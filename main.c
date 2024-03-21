#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>

#include "./constants.h"
#include "./globals.h"
#include "./tad.h"
#include "./init_and_destroy.h"
#include "./setup.h"
#include "./process_input.h"
#include "./update.h"
#include "./render.h"

SDL_Window* my_window = NULL;
SDL_Renderer* my_renderer = NULL;
int game_is_running = FALSE;
Mesh* my_mesh = NULL;
Mesh* my_meshRotated = NULL;
Mesh* my_meshProjected = NULL;

float near;
float far;
float fov;
float aspectRatio;
float fovRad;

Matrix4 projectionMatrix;

Matrix4 rotationMatrix_X;
Matrix4 rotationMatrix_Y;
Matrix4 rotationMatrix_Z;

//------------------------------------------------------------------------------
//TESTING

float moveX = 0;
float moveY = 0;
float moveZ = 0;
float rotateX = 0;
float rotateY = 0;
float rotateZ = 0;

//------------------------------------------------------------------------------


int main() {
    
    game_is_running  = initialize_window(&my_window, &my_renderer);
    
    setup(&my_mesh, &my_meshProjected);

    while(game_is_running) {
        process_input();
        update(my_mesh, my_meshProjected);
        render(my_meshProjected);
    }
    
    destroy_window(my_window, my_renderer);

    return 0;
}