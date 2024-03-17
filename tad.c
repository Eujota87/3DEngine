#include <stdio.h>
#include <SDL2/SDL.h>

#include "./tad.h"
#include "./constants.h"
#include "./globals.h"

Vector3 MulMatrix4Vector3(Vector3 vecIn, Matrix4 mat4) {
    float w;
    Vector3 vecOut;

    vecOut.x = mat4.m[0][0] * vecIn.x + mat4.m[0][1] * vecIn.y, mat4.m[0][2] * vecIn.z + mat4.m[0][3];
    vecOut.y = mat4.m[1][0] * vecIn.x + mat4.m[1][1] * vecIn.y, mat4.m[1][2] * vecIn.z + mat4.m[1][3];
    vecOut.z = mat4.m[2][0] * vecIn.x + mat4.m[2][1] * vecIn.y, mat4.m[2][2] * vecIn.z + mat4.m[2][3];
           w = mat4.m[3][0] * vecIn.x + mat4.m[3][1] * vecIn.y, mat4.m[3][2] * vecIn.z + mat4.m[3][3];

    //divide by w
    if(w != 0) {
        vecOut.x /= w;
        vecOut.y /= w;
        vecOut.z /= w;
    }

    return vecOut;
}
