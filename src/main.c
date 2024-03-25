#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>

#include "./constants.h"
#include "./globals.h"
#include "./abstract_data_types.h"
#include "./init_and_destroy.h"
#include "./setup.h"
#include "./process_input.h"
#include "./update.h"
#include "./render.h"

SDL_Window* my_window = NULL;
SDL_Renderer* my_renderer = NULL;

int game_is_running = FALSE;


Mesh* my_mesh = NULL;
Mesh* my_meshTranslated = NULL;
Mesh* my_meshScaled = NULL;
Mesh* my_meshRotated = NULL;
Mesh* my_meshProjected = NULL;

Matrix4 projectionMatrix;

float zNear;
float zFar;
float fov;
float aspectRatio;
float fovRad;

float inputMoveX = 0;
float inputMoveY = 0;
float inputMoveZ = 0;
float inputRotateX = 0;
float inputRotateY = 0;
float inputRotateZ = 0;



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