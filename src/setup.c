#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "./constants.h"
#include "import_mesh.h"
#include "./globals.h"
#include "./abstract_data_types.h"
#include "./geometry_operations.h"
#include "./setup.h"


void setup(Mesh** my_mesh) {

    zNear = 0.1f;
    zFar = 1000.0f;
    fov = 65.0f;
    aspectRatio = (float)WINDOW_HEIGHT / (float)WINDOW_WIDTH;
    fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);

    projectionMatrix.m[0][0] = aspectRatio * fovRad;
    projectionMatrix.m[1][1] = fovRad;
    projectionMatrix.m[2][2] = zFar / (zFar-zNear);
    projectionMatrix.m[2][3] = (-zFar * zNear) / (zFar-zNear);
    projectionMatrix.m[3][2] = 1.0f;
    projectionMatrix.m[3][3] = 0;

    vector4Null.x = 0.0F;
    vector4Null.y = 0.0F;
    vector4Null.z = 0.0F;
    vector4Null.w = 0.0F;
    
    vector4DirectionZ.x = 0.0F;
    vector4DirectionZ.y = 0.0F;
    vector4DirectionZ.z = -1.0F;
    vector4DirectionZ.w = 0.0F;

    lightDirection.x = 1.0F;
    lightDirection.y = -1.0F; //final image is fliped vertically
    lightDirection.z = -1.0F;
    
    //-----------------------------------------------------------------

    *my_mesh = ImportMesh();
    (*my_mesh)->pivot = vector4Null; //create function to calculate mesh center

    my_obj = CreateObj3D(*my_mesh);

    my_obj->pivot.z += 6.0F;

}

