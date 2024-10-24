#include <stdio.h>
#include "./SDL2/SDL.h"
#include <stdlib.h>
#include <string.h>

#include "./constants.h"
#include "./globals.h"
#include "./abstract_data_types.h"
#include "./geometry_operations.h"
#include "./init_and_destroy.h"
#include "./setup.h"
#include "./process_input.h"
#include "./update.h"
#include "./render.h"

SDL_Window* my_window = NULL;
SDL_Renderer* my_renderer = NULL;

int game_is_running = FALSE;

Mesh* my_mesh = NULL;
Obj3D* my_obj = NULL; 

Matrix4 projectionMatrix;
Vector4 vector4Null;
Vector4 vector4DirectionZ;
Vector4 lightDirection;

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
int debugKey1 = -1;
int debugKey2 = -1;
int debugKey3 = -1;
int debugKey4 = -1;
int slider1 = 0;
int slider2 = 0;
int slider3 = 0;

float renderSpecAmount = 0;
float renderSpecLowLimit = 0;
float renderShadowLowLimit = 0;


int main(int argc, char *argv[]) {
    
    game_is_running = initialize_window(&my_window, &my_renderer);
    
    setup();

    while(game_is_running) {
        process_input();
        update();
        render();
    }
    
    destroy_window(my_window, my_renderer);

    return 0;
}