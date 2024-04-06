
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <math.h>

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

float DotProductVec2(Vector4 vec1, Vector4 vec2) {
    float scalar;
    scalar = (vec1.x * vec2.x) + (vec1.y * vec2.y);
    return scalar;
}

float DotProductVec3(Vector4 vec1, Vector4 vec2) {
    float scalar;
    scalar = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
    return scalar;
}

void TranslateObjToPivot(Obj3D* obj) {
    
    for(int i = 0; i < obj->triangleCount; i++) {
        for(int j = 0; j < 3; j++) {
            obj->meshBufferIn->triangle[i].vertex[j].y = obj->meshBufferOut->triangle[i].vertex[j].y + obj->pivot.y;
            obj->meshBufferIn->triangle[i].vertex[j].z = obj->meshBufferOut->triangle[i].vertex[j].z + obj->pivot.z;
            obj->meshBufferIn->triangle[i].vertex[j].x = obj->meshBufferOut->triangle[i].vertex[j].x + obj->pivot.x;
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
            obj->meshBufferIn->triangle[i].vertex[j].y = obj->meshBufferOut->triangle[i].vertex[j].y - obj->pivot.y;
            obj->meshBufferIn->triangle[i].vertex[j].z = obj->meshBufferOut->triangle[i].vertex[j].z - obj->pivot.z;
            obj->meshBufferIn->triangle[i].vertex[j].x = obj->meshBufferOut->triangle[i].vertex[j].x - obj->pivot.x;
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
        obj->meshBufferIn->triangle[i].normal = MulMatrix4Vector3(obj->meshBufferOut->triangle[i].normal, rotationMatrix);
    }
    obj->meshBufferOut = obj->meshBufferIn;
}

Triangle ProjectTriangle(Triangle triangleIn, Matrix4 matrix) {
    Triangle triangleOut;
    for(int i = 0; i < 3; i++) {
        triangleOut.vertex[i] = MulMatrix4Vector3(triangleIn.vertex[i], matrix);
    }
    triangleOut.center = MulMatrix4Vector3(triangleIn.center, matrix);
    triangleOut.normal = MulMatrix4Vector3(triangleIn.normal, matrix);
    
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

void UpdateObjMesh2D(Obj3D* obj) {
    int meshTriCount = 0;

    //backface culling
    for(int i = 0; i < obj->triangleCount; i++) {
        if(DotProductVec3(GetVector4Normalized(obj->meshBufferOut->triangle[i].center, vector4Null), NormalToWorldCenter(obj, i)) > 0.0F) {
            obj->mesh2DWindowSpace->triangle[meshTriCount] = obj->meshProjected->triangle[i];
            
            //lighting calculation
            obj->mesh2DWindowSpace->triangle[meshTriCount].shadeColor = (
                DotProductVec3(NormalizeVector4(lightDirection), NormalToWorldCenter(obj, i))
            );
            
            meshTriCount++;
        }
    }
    
    obj->mesh2DWindowSpace->triangleCount = meshTriCount;

    //translate and scale 2D coordinates
    for(int i = 0; i < meshTriCount; i++) {
        //translate points from (-1,1) range to (0,2) range
        obj->mesh2DWindowSpace->triangle[i].vertex[0].x += 1.0F;
        obj->mesh2DWindowSpace->triangle[i].vertex[0].y += 1.0F;
        obj->mesh2DWindowSpace->triangle[i].vertex[1].x += 1.0F;
        obj->mesh2DWindowSpace->triangle[i].vertex[1].y += 1.0F;
        obj->mesh2DWindowSpace->triangle[i].vertex[2].x += 1.0F;
        obj->mesh2DWindowSpace->triangle[i].vertex[2].y += 1.0F;
        obj->mesh2DWindowSpace->triangle[i].center.x += 1.0F;
        obj->mesh2DWindowSpace->triangle[i].center.y += 1.0F;
        obj->mesh2DWindowSpace->triangle[i].normal.x += 1.0F;
        obj->mesh2DWindowSpace->triangle[i].normal.y += 1.0F;


        //scale points based on windows size (divided by two as points range from 0 to 2)
        obj->mesh2DWindowSpace->triangle[i].vertex[0].x *= 0.5F * (float)WINDOW_WIDTH;
        obj->mesh2DWindowSpace->triangle[i].vertex[0].y *= 0.5F * (float)WINDOW_HEIGHT;
        obj->mesh2DWindowSpace->triangle[i].vertex[1].x *= 0.5F * (float)WINDOW_WIDTH;
        obj->mesh2DWindowSpace->triangle[i].vertex[1].y *= 0.5F * (float)WINDOW_HEIGHT;
        obj->mesh2DWindowSpace->triangle[i].vertex[2].x *= 0.5F * (float)WINDOW_WIDTH;
        obj->mesh2DWindowSpace->triangle[i].vertex[2].y *= 0.5F * (float)WINDOW_HEIGHT;
        obj->mesh2DWindowSpace->triangle[i].center.x *= 0.5F * (float)WINDOW_WIDTH;
        obj->mesh2DWindowSpace->triangle[i].center.y *= 0.5F * (float)WINDOW_HEIGHT;
        obj->mesh2DWindowSpace->triangle[i].normal.x *= 0.5F * (float)WINDOW_WIDTH;
        obj->mesh2DWindowSpace->triangle[i].normal.y *= 0.5F * (float)WINDOW_HEIGHT;
    }
}

void UpdateObjMesh2DZsorted(Obj3D* obj) {
    
    obj->mesh2DWindowSpaceZSorted->triangleCount = obj->mesh2DWindowSpace->triangleCount;

    for(int i = 0; i < obj->mesh2DWindowSpace->triangleCount; i++) {
        obj->mesh2DWindowSpaceZSorted->triangle[i] = obj->mesh2DWindowSpace->triangle[i];
    }

    //selection sort
    int size = obj->mesh2DWindowSpaceZSorted->triangleCount;
    int i, j, min;
    Triangle store;
    
    for(i = 0; i < size - 1; i++) {
        min = i;
        for(j = i+1; j < size; j++) {
            if(obj->mesh2DWindowSpaceZSorted->triangle[j].center.z > obj->mesh2DWindowSpaceZSorted->triangle[min].center.z) {
                min = j;
            }
        }

        if(min != i) { //swap
            store = obj->mesh2DWindowSpaceZSorted->triangle[i];
            obj->mesh2DWindowSpaceZSorted->triangle[i] = obj->mesh2DWindowSpaceZSorted->triangle[min];
            obj->mesh2DWindowSpaceZSorted->triangle[min] = store;
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
