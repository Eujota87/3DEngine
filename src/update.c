#include <stdio.h>
#include <SDL2/SDL.h>

#include "./constants.h"
#include "./globals.h"
#include "./tad.h"
#include "./update.h"

int last_frame_time = 0;

//-----------------------------------------------------------------------------
//TESTING
float thetaX;
float thetaY;
//-----------------------------------------------------------------------------

Triangle ProjectTriangle(Triangle triangleIn, Matrix4 matrix);
void ProjectMesh(Mesh* meshIn, Mesh* meshOut, Matrix4 matrix);

void MoveMesh(Mesh* mesh, float delta_time);
void RotateMesh(Mesh* mesh);

void update(Mesh* my_mesh, Mesh* my_meshProjected) {
    
    //caping frame rate
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    //delta time in seconds
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    last_frame_time = SDL_GetTicks();

    //-------------------------------------------------------------------------------------
    //TESTING

    thetaY += 0.4*delta_time;
    //rotation y
    rotationMatrix_Y.m[0][0] = cosf(thetaY);
	rotationMatrix_Y.m[0][2] = sinf(thetaY);
	rotationMatrix_Y.m[2][0] = -sinf(thetaY);
	rotationMatrix_Y.m[2][2] = cosf(thetaY);
	rotationMatrix_Y.m[1][1] = 1;

    //RotateMesh(my_mesh);

    MoveMesh(my_mesh, delta_time);
    
    ProjectMesh(my_mesh, my_meshProjected,projectionMatrix);

    if(rotateX != 0) PrintMeshData(my_mesh);
    if(rotateY != 0) PrintMeshData(my_meshProjected);

    //-----------------------------------------------------------------------------
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

void MoveMesh(Mesh* mesh, float delta_time) {
    for(int i = 0; i < mesh->triangleCount; i++) {
        mesh->triangle[i].vertex[0].x += 0.5 * moveX * delta_time;
        mesh->triangle[i].vertex[0].y += 0.5 * moveY * delta_time;
        mesh->triangle[i].vertex[0].z += 0.5 * moveZ * delta_time;
        mesh->triangle[i].vertex[1].x += 0.5 * moveX * delta_time;
        mesh->triangle[i].vertex[1].y += 0.5 * moveY * delta_time;
        mesh->triangle[i].vertex[1].z += 0.5 * moveZ * delta_time;
        mesh->triangle[i].vertex[2].x += 0.5 * moveX * delta_time;
        mesh->triangle[i].vertex[2].y += 0.5 * moveY * delta_time;
        mesh->triangle[i].vertex[2].z += 0.5 * moveZ * delta_time;
    }
}

void RotateMesh(Mesh* mesh) {
    for(int i = 0; i < mesh->triangleCount; i++) {
        for(int j = 0; j < 3; j++) {
            my_meshRotated->triangle[i].vertex[j] = MulMatrix4Vector3(mesh->triangle[i].vertex[j], rotationMatrix_Y);
        }
    }
}

