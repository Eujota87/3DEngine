#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

#include "./constants.h"
#include "./globals.h"
#include "./tad.h"
#include "./setup.h"

void setup() {

    near = 0.1f;
    far = 1000.0f;
    fov = 90.0f;
    aspectRatio = (float)WINDOW_HEIGHT / (float)WINDOW_WIDTH;
    fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);

    //TESTING

    ponto1.x = -200;
    ponto1.y = 0;
    ponto1.z = 10;
    ponto2.x = 200;
    ponto2.y = 0;
    ponto2.z = 10;
    ponto3.x = 0;
    ponto3.y = 200;
    ponto3.z = 10;

    tri1.point[0] = ponto1;
    tri1.point[1] = ponto2;
    tri1.point[2] = ponto3;

    mat1.m[0][0] = aspectRatio * fovRad;
    mat1.m[1][1] = fovRad;
    mat1.m[2][2] = far / (far-near);
    mat1.m[2][3] = (-far * near) / (far-near);
    mat1.m[3][2] = 1;
    

    
}