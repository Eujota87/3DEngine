#include <stdio.h>
#include <SDL2/SDL.h>

#include "./abstract_data_types.h"
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

Triangle ProjectTriangle(Triangle triangleIn, Matrix4 matrix) {
    Triangle triangleOut;
    for(int i = 0; i < 3; i++) {
        triangleOut.vertex[i] = MulMatrix4Vector3(triangleIn.vertex[i], matrix);
    }
    return triangleOut;
}

void ProjectMesh(Mesh* meshIn, Mesh* meshOut, Matrix4 matrix) {
    for(int i = 0; i < meshIn->triangleCount; i++) {
        meshOut->triangle[i] = ProjectTriangle(meshIn->triangle[i], matrix);
    }
}

void InputMoveMesh(Mesh* meshIn, float delta_time) {
    for(int i = 0; i < meshIn->triangleCount; i++) {
        meshIn->triangle[i].vertex[0].x += 1.5 * inputMoveX * delta_time;
        meshIn->triangle[i].vertex[0].y += 1.5 * inputMoveY * delta_time;
        meshIn->triangle[i].vertex[0].z += 1.5 * inputMoveZ * delta_time;
        meshIn->triangle[i].vertex[1].x += 1.5 * inputMoveX * delta_time;
        meshIn->triangle[i].vertex[1].y += 1.5 * inputMoveY * delta_time;
        meshIn->triangle[i].vertex[1].z += 1.5 * inputMoveZ * delta_time;
        meshIn->triangle[i].vertex[2].x += 1.5 * inputMoveX * delta_time;
        meshIn->triangle[i].vertex[2].y += 1.5 * inputMoveY * delta_time;
        meshIn->triangle[i].vertex[2].z += 1.5 * inputMoveZ * delta_time;
    }
}

void RotateMesh(Mesh* meshIn, Mesh* meshOut, float degrees, char axis) {
    
    Matrix4 rotationMatrix;
    
    switch(axis) {
        case 'x':
            //rotation x
            rotationMatrix.m[0][0] = 1.0F;
            rotationMatrix.m[0][1] = 0.0F;
            rotationMatrix.m[0][2] = 0.0F;
            rotationMatrix.m[0][3] = 0.0F;
	        rotationMatrix.m[1][0] = 0.0F;
	        rotationMatrix.m[1][1] = cosf(degrees);
	        rotationMatrix.m[1][2] = -sinf(degrees);
	        rotationMatrix.m[1][3] = 0.0F;
	        rotationMatrix.m[2][0] = 0.0F;
	        rotationMatrix.m[2][1] = sinf(degrees);
	        rotationMatrix.m[2][2] = cosf(degrees);
	        rotationMatrix.m[2][3] = 0.0F;
            rotationMatrix.m[3][0] = 0.0F;
	        rotationMatrix.m[3][1] = 0.0F;
	        rotationMatrix.m[3][2] = 0.0F;
	        rotationMatrix.m[3][3] = 0.0F;
            break;
        case 'y':
            //rotation y
            rotationMatrix.m[0][0] = cosf(degrees);
            rotationMatrix.m[0][1] = 0.0F;
	        rotationMatrix.m[0][2] = sinf(degrees);
            rotationMatrix.m[0][3] = 0.0F;
	        rotationMatrix.m[1][0] = 0.0F;
	        rotationMatrix.m[1][1] = 1.0F;
	        rotationMatrix.m[1][2] = 0.0F;
	        rotationMatrix.m[1][3] = 0.0F;
	        rotationMatrix.m[2][0] = -sinf(degrees);
	        rotationMatrix.m[2][1] = 0.0F;
	        rotationMatrix.m[2][2] = cosf(degrees);
	        rotationMatrix.m[2][3] = 0.0F;
            rotationMatrix.m[3][0] = 0.0F;
	        rotationMatrix.m[3][1] = 0.0F;
	        rotationMatrix.m[3][2] = 0.0F;
	        rotationMatrix.m[3][3] = 0.0F;
            break;
        case 'z':
            //rotation z
            rotationMatrix.m[0][0] = cosf(degrees);
	        rotationMatrix.m[0][1] = -sinf(degrees);
	        rotationMatrix.m[0][2] = 0.0F;
	        rotationMatrix.m[0][3] = 0.0F;
	        rotationMatrix.m[1][0] = sinf(degrees);
	        rotationMatrix.m[1][1] = cosf(degrees);
	        rotationMatrix.m[1][2] = 0.0F;
	        rotationMatrix.m[1][3] = 0.0F;
	        rotationMatrix.m[2][0] = 0.0F;
	        rotationMatrix.m[2][1] = 0.0F;
	        rotationMatrix.m[2][2] = 1.0F;
	        rotationMatrix.m[2][3] = 0.0F;
	        rotationMatrix.m[3][0] = 0.0F;
	        rotationMatrix.m[3][1] = 0.0F;
	        rotationMatrix.m[3][2] = 0.0F;
	        rotationMatrix.m[3][3] = 0.0F;
            break;
    }
    
    for(int i = 0; i < meshIn->triangleCount; i++) {
        for(int j = 0; j < 3; j++) {
            meshOut->triangle[i].vertex[j] = MulMatrix4Vector3(meshIn->triangle[i].vertex[j], rotationMatrix);
        }
    }
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