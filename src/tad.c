#include <stdio.h>
#include <SDL2/SDL.h>

#include "./tad.h"
#include "./constants.h"
#include "./globals.h"

Vector3 MulMatrix4Vector3(Vector3 vecIn, Matrix4 mat4) {
    float w;
    Vector3 vecOut;

    vecOut.x = mat4.m[0][0] * vecIn.x + mat4.m[0][1] * vecIn.y + mat4.m[0][2] * vecIn.z + mat4.m[0][3];
    vecOut.y = mat4.m[1][0] * vecIn.x + mat4.m[1][1] * vecIn.y + mat4.m[1][2] * vecIn.z + mat4.m[1][3];
    vecOut.z = mat4.m[2][0] * vecIn.x + mat4.m[2][1] * vecIn.y + mat4.m[2][2] * vecIn.z + mat4.m[2][3];
           w = mat4.m[3][0] * vecIn.x + mat4.m[3][1] * vecIn.y + mat4.m[3][2] * vecIn.z + mat4.m[3][3];

    //divide by w
    if(w != 0) {
        vecOut.x /= w;
        vecOut.y /= w;
        vecOut.z /= w;
    }

    return vecOut;
}

Mesh* CreateMesh(int triCount) {
    Mesh* m = malloc(sizeof(Mesh));
    m->triangleCount = triCount;
    m->triangle = malloc(sizeof(Triangle) * triCount);
    return m;
}

void PrintMeshData(Mesh* mesh) {
    fprintf(stderr, " MeshData:\n");
    for(int i = 0; i < mesh->triangleCount;i++) {
        for(int j = 0; j < 3; j++) {
            fprintf(
                stderr, 
                "triangle[%i].vertex[%i].x = %f\n", 
                i, 
                j,
                mesh->triangle[i].vertex[j].x);
            fprintf(
                stderr, 
                "triangle[%i].vertex[%i].y = %f\n", 
                i, 
                j,
                mesh->triangle[i].vertex[j].y);
            fprintf(
                stderr, 
                "triangle[%i].vertex[%i].z = %f\n", 
                i, 
                j,
                mesh->triangle[i].vertex[j].z);                                
        }
    }
}

/*
   //rotation x
    rotationMatrix_X.m[0][0] = 1.0f;
	rotationMatrix_X.m[1][1] = cosf(thetaX);
	rotationMatrix_X.m[1][2] = -sinf(thetaX);
	rotationMatrix_X.m[2][1] = sinf(thetaX);
	rotationMatrix_X.m[2][2] = cosf(thetaX);

    //rotation y
    rotationMatrix_Y.m[0][0] = cosf(thetaY);
	rotationMatrix_Y.m[0][2] = sinf(thetaY);
	rotationMatrix_Y.m[2][0] = -sinf(thetaY);
	rotationMatrix_Y.m[2][2] = cosf(thetaY);
	rotationMatrix_Y.m[1][1] = 1;

    //rotation z
    rotationMatrix_Z.m[0][0] = cosf(thetaX);
	rotationMatrix_Z.m[0][1] = -sinf(thetaX);
	rotationMatrix_Z.m[1][0] = sinf(thetaX);
	rotationMatrix_Z.m[1][1] = cosf(thetaX);
	rotationMatrix_Z.m[2][2] = 1;
*/