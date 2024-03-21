#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "./constants.h"
#include "import_mesh.h"
#include "./globals.h"
#include "./tad.h"
#include "./setup.h"



void setup(Mesh** my_mesh, Mesh** my_meshProjected) {

    near = 0.1f;
    far = 1000.0f;
    fov = 90.0f;
    aspectRatio = (float)WINDOW_HEIGHT / (float)WINDOW_WIDTH;
    fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);

    projectionMatrix.m[0][0] = aspectRatio * fovRad;
    projectionMatrix.m[1][1] = fovRad;
    projectionMatrix.m[2][2] = far / (far-near);
    projectionMatrix.m[2][3] = (-far * near) / (far-near);
    projectionMatrix.m[3][2] = 1.0f;
    projectionMatrix.m[3][3] = 0;

    
    //-----------------------------------------------------------------------------
    //TESTING
    
    *my_mesh = ImportMesh();
    //PrintMeshData(*my_mesh);
    
    *my_meshProjected = CreateMesh((*my_mesh)->triangleCount);
    my_meshRotated = CreateMesh((*my_mesh)->triangleCount);


    
    fprintf(
        stderr, 
        "%f, triCount: %i\n", 
        (*my_mesh)->triangle[0].vertex[0].x, 
        (*my_mesh)->triangleCount
    );
    //-----------------------------------------------------------------------------
}

