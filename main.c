#include <stdio.h>
#include <SDL2/SDL.h>


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

float near;
float far;
float fov;
float aspectRatio;
float fovRad;

//------------------------------------------------------------------------------

//TESTING

Vector3 ponto1;
Vector3 ponto2;
Vector3 ponto3;

Triangle tri1;
Triangle tri2;
Triangle tri3;
Triangle tri4;

Matrix4 mat1;

Matrix4 rotationMat1;
Matrix4 rotationMat2;

int main() {
    
    game_is_running  = initialize_window(&my_window, &my_renderer);
    
    setup();

    while(game_is_running) {
        process_input();
        update();
        render();
    }

    destroy_window(my_window, my_renderer);

    return 0;
}