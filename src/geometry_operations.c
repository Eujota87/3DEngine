#include <stdio.h>
#include "C:/SDL2/include/SDL.h"
#include <stdlib.h>
#include <math.h>

#include "./abstract_data_types.h"
#include "./geometry_operations.h"
#include "./mesh_operations.h"
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

float DotProductVec2(Vector4 vec1, Vector4 vec2) {
    float scalar;
    scalar = (vec1.x * vec2.x) + (vec1.y * vec2.y);
    return scalar;
}

float DotProductVec4x3(Vector4 vec1, Vector3 vec2) {
    float scalar;
    scalar = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
    return scalar;
}

float DotProductVec4(Vector4 vec1, Vector4 vec2) {
    float scalar;
    scalar = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
    return scalar;
}

void TranslateObjToPivot(Obj3D* obj) {
    
    for(int i = 0; i < obj->triangleCount; i++) {
        for(int j = 0; j < 3; j++) {
            obj->meshBufferIn->triangle[i].vertex[j].x = obj->meshBufferOut->triangle[i].vertex[j].x + obj->pivot.x;
            obj->meshBufferIn->triangle[i].vertex[j].y = obj->meshBufferOut->triangle[i].vertex[j].y + obj->pivot.y;
            obj->meshBufferIn->triangle[i].vertex[j].z = obj->meshBufferOut->triangle[i].vertex[j].z + obj->pivot.z;
        }
        
        obj->meshBufferIn->triangle[i].center.x = obj->meshBufferOut->triangle[i].center.x + obj->pivot.x;
        obj->meshBufferIn->triangle[i].center.y = obj->meshBufferOut->triangle[i].center.y + obj->pivot.y;
        obj->meshBufferIn->triangle[i].center.z = obj->meshBufferOut->triangle[i].center.z + obj->pivot.z;


        obj->meshBufferIn->triangle[i].normal.x = (
            obj->meshBufferOut->triangle[i].normal.x + obj->meshBufferIn->triangle[i].center.x
        );
        obj->meshBufferIn->triangle[i].normal.y = (
            obj->meshBufferOut->triangle[i].normal.y + obj->meshBufferIn->triangle[i].center.y
        );
        obj->meshBufferIn->triangle[i].normal.z = (
            obj->meshBufferOut->triangle[i].normal.z + obj->meshBufferIn->triangle[i].center.z
        );
    }

    obj->meshBufferOut = obj->meshBufferIn;

}

void TranslateObjToWorldCenter(Obj3D* obj) {
    
    for(int i = 0; i < obj->triangleCount; i++) {
        for(int j = 0; j < 3; j++) {
            obj->meshBufferIn->triangle[i].vertex[j].x = obj->meshBufferOut->triangle[i].vertex[j].x - obj->pivot.x;
            obj->meshBufferIn->triangle[i].vertex[j].y = obj->meshBufferOut->triangle[i].vertex[j].y - obj->pivot.y;
            obj->meshBufferIn->triangle[i].vertex[j].z = obj->meshBufferOut->triangle[i].vertex[j].z - obj->pivot.z;
        }
    }
    
    //see later if I'll need to translate triangle centers and normals to world center as well
    obj->meshBufferOut = obj->meshBufferIn;

}

Vector4 GetVector4(Vector4 vecStart, Vector4 vecEnd) {
    Vector4 vecOut;

    vecOut.x = vecEnd.x - vecStart.x;
    vecOut.y = vecEnd.y - vecStart.y;
    vecOut.z = vecEnd.z - vecStart.z;

    return vecOut;
}

Vector4 GetVector4Normalized(Vector4 vecStart, Vector4 vecEnd) {
    return NormalizeVector4(GetVector4(vecStart, vecEnd));
}


float GetVector4Length(Vector4 vecIn) {
    float length = sqrtf((vecIn.x * vecIn.x) + (vecIn.y * vecIn.y) + (vecIn.z * vecIn.z));
    return length;
}

float GetVector3Length(Vector3 vecIn) {
    float length = sqrtf((vecIn.x * vecIn.x) + (vecIn.y * vecIn.y) + (vecIn.z * vecIn.z));
    return length;
}

Vector3 NormalizeVector3(Vector3 vecIn) {
    Vector3 vecOut;

    vecOut.x = vecIn.x / GetVector3Length(vecIn);
    vecOut.y = vecIn.y / GetVector3Length(vecIn);
    vecOut.z = vecIn.z / GetVector3Length(vecIn);

    return vecOut;
}


Vector4 NormalizeVector4(Vector4 vecIn) {
    Vector4 vecOut;

    vecOut.x = vecIn.x / GetVector4Length(vecIn);
    vecOut.y = vecIn.y / GetVector4Length(vecIn);
    vecOut.z = vecIn.z / GetVector4Length(vecIn);

    return vecOut;
}


Vector4 NormalToWorldCenter(Obj3D* obj, int triangle_index) {
    
    Vector4 centered_normal;
    
    centered_normal.x = (
        obj->meshBufferOut->triangle[triangle_index].normal.x - obj->meshBufferOut->triangle[triangle_index].center.x
    );
    centered_normal.y = (
        obj->meshBufferOut->triangle[triangle_index].normal.y - obj->meshBufferOut->triangle[triangle_index].center.y
    );
    centered_normal.z = (
        obj->meshBufferOut->triangle[triangle_index].normal.z - obj->meshBufferOut->triangle[triangle_index].center.z
    );
    
    //normalize normal
    centered_normal = NormalizeVector4(centered_normal);

    return centered_normal;

};

void InputMoveObjPivot(Obj3D* obj, float delta_time) {
    
    obj->pivot.x += 1.0 * inputMoveX * delta_time;
    obj->pivot.y += 1.0 * inputMoveY * delta_time;
    obj->pivot.z += 1.0 * inputMoveZ * delta_time;
    
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
        obj->meshBufferIn->triangle[i].normal = MulMatrix4Vector3(obj->meshBufferOut->triangle[i].normal, rotationMatrix);
    }
    obj->meshBufferOut = obj->meshBufferIn;
}

void UpdateVertexNormal(Obj3D* obj) {
for(int i = 0; i < obj->meshImported->triangleCount; i ++) {
        for( int j = 0; j < 3; j++) {
            for(int a = 0; a < obj->meshImported->triangle[i].vertex[j].sharedTrianglesCount; a++) {
                Vector4 faceNormal = NormalToWorldCenter(obj, obj->meshImported->triangle[i].vertex[j].sharedTrianglesIndex[a]);
                obj->meshImported->triangle[i].vertex[j].normal.x += 
                faceNormal.x;
                obj->meshImported->triangle[i].vertex[j].normal.y += 
                faceNormal.y;
                obj->meshImported->triangle[i].vertex[j].normal.z += 
                faceNormal.z;
            }
            
            obj->meshImported->triangle[i].vertex[j].normal = NormalizeVector3(obj->meshImported->triangle[i].vertex[j].normal);
            
        }
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