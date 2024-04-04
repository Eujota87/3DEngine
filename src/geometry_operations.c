
#include <stdio.h>
#include <SDL2/SDL.h>

#include "./abstract_data_types.h"
#include "./geometry_operations.h"
#include "./constants.h"
#include "./globals.h"

Vector4 MulMatrix4Vector3(Vector4 vecIn, Matrix4 mat4) {
    
    float w;
    Vector4 vecOut;

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
    vecOut.w = w;
    return vecOut;
}

void TranslateObjToPivot(Obj3D* obj) {
    
    for(int i = 0; i < obj->triangleCount; i++) {
        for(int j = 0; j < 3; j++) {
            obj->meshBufferIn->triangle[i].vertex[j].y = obj->meshBufferOut->triangle[i].vertex[j].y + obj->pivot.y;
            obj->meshBufferIn->triangle[i].vertex[j].z = obj->meshBufferOut->triangle[i].vertex[j].z + obj->pivot.z;
            obj->meshBufferIn->triangle[i].vertex[j].x = obj->meshBufferOut->triangle[i].vertex[j].x + obj->pivot.x;
        }
    }
    obj->meshBufferOut = obj->meshBufferIn;
}

void TranslateObjToWorldCenter(Obj3D* obj) {
    
    for(int i = 0; i < obj->triangleCount; i++) {
        for(int j = 0; j < 3; j++) {
            obj->meshBufferIn->triangle[i].vertex[j].y = obj->meshBufferOut->triangle[i].vertex[j].y - obj->pivot.y;
            obj->meshBufferIn->triangle[i].vertex[j].z = obj->meshBufferOut->triangle[i].vertex[j].z - obj->pivot.z;
            obj->meshBufferIn->triangle[i].vertex[j].x = obj->meshBufferOut->triangle[i].vertex[j].x - obj->pivot.x;
        }
    }
    obj->meshBufferOut = obj->meshBufferIn;
}

void InputMoveObjPivot(Obj3D* obj, float delta_time) {
    
    obj->pivot.x += 3.0 * inputMoveX * delta_time;
    obj->pivot.y += 3.0 * inputMoveY * delta_time;
    obj->pivot.z += 3.0 * inputMoveZ * delta_time;
    
}

void RotateObj(Obj3D* obj, float degrees, char axis) {
    
    Matrix4 rotationMatrix;
    
    //temp
    //meshOut->pivot = meshIn->pivot;

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
    
    for(int i = 0; i < obj->triangleCount; i++) {
        for(int j = 0; j < 3; j++) {
            obj->meshBufferIn->triangle[i].vertex[j] = MulMatrix4Vector3(obj->meshBufferOut->triangle[i].vertex[j], rotationMatrix);
        }
    }
    obj->meshBufferOut = obj->meshBufferIn;
}

Triangle ProjectTriangle(Triangle triangleIn, Matrix4 matrix) {
    Triangle triangleOut;
    for(int i = 0; i < 3; i++) {
        triangleOut.vertex[i] = MulMatrix4Vector3(triangleIn.vertex[i], matrix);
    }
    triangleOut.center = MulMatrix4Vector3(triangleIn.center, matrix);
    
    return triangleOut;
}

void ProjectObjMesh(Obj3D* obj, Matrix4 matrix) {
    for(int i = 0; i < obj->triangleCount; i++) {
        obj->meshProjected->triangle[i] = ProjectTriangle(obj->meshBufferOut->triangle[i], matrix);
    }
}

void UpdateTriangleCenter(Obj3D* obj) {
    for(int i = 0; i < obj->triangleCount; i++) {
        obj->meshBufferOut->triangle[i].center.x = (
            obj->meshBufferOut->triangle[i].vertex[0].x +
            obj->meshBufferOut->triangle[i].vertex[1].x +
            obj->meshBufferOut->triangle[i].vertex[2].x
        ) / 3;
        obj->meshBufferOut->triangle[i].center.y = (
            obj->meshBufferOut->triangle[i].vertex[0].y +
            obj->meshBufferOut->triangle[i].vertex[1].y +
            obj->meshBufferOut->triangle[i].vertex[2].y
        ) / 3;
        obj->meshBufferOut->triangle[i].center.z = (
            obj->meshBufferOut->triangle[i].vertex[0].z +
            obj->meshBufferOut->triangle[i].vertex[1].z +
            obj->meshBufferOut->triangle[i].vertex[2].z
        ) / 3;
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
