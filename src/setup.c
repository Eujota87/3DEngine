#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "./constants.h"
#include "import_mesh.h"
#include "./globals.h"
#include "./abstract_data_types.h"
#include "./setup.h"



void setup(Mesh** my_mesh, Mesh** my_meshProjected) {

    zNear = 0.1f;
    zFar = 1000.0f;
    fov = 90.0f;
    aspectRatio = (float)WINDOW_HEIGHT / (float)WINDOW_WIDTH;
    fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);

    projectionMatrix.m[0][0] = aspectRatio * fovRad;
    projectionMatrix.m[1][1] = fovRad;
    projectionMatrix.m[2][2] = zFar / (zFar-zNear);
    projectionMatrix.m[2][3] = (-zFar * zNear) / (zFar-zNear);
    projectionMatrix.m[3][2] = 1.0f;
    projectionMatrix.m[3][3] = 0;

    
    //-----------------------------------------------------------------
    
    *my_mesh = ImportMesh();
    
    my_meshScaled = CreateMesh((*my_mesh)->triangleCount);
    my_meshRotatedX = CreateMesh((*my_mesh)->triangleCount);
    my_meshRotatedY = CreateMesh((*my_mesh)->triangleCount);
    my_meshRotatedZ = CreateMesh((*my_mesh)->triangleCount);
    my_meshTranslated = CreateMesh((*my_mesh)->triangleCount);
    *my_meshProjected = CreateMesh((*my_mesh)->triangleCount);

}

