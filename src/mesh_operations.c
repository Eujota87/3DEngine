#include <stdio.h>
#include "C:\SDL2\x86_64-w64-mingw32\include\SDL2\SDL.h"
#include <stdlib.h>
#include <math.h>

#include "./abstract_data_types.h"
#include "./geometry_operations.h"
#include "./mesh_operations.h"
#include "./constants.h"
#include "./globals.h"

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

void BackfaceCullingMesh2D(Obj3D* obj) {
    int meshTriCount = 0;

    //backface culling
    for(int i = 0; i < obj->triangleCount; i++) {
        if(DotProductVec4(GetVector4Normalized(obj->meshBufferOut->triangle[i].center, vector4Null), NormalToWorldCenter(obj, i)) > 0.0F) {
            obj->mesh2DWindowSpace->triangle[meshTriCount] = obj->meshProjected->triangle[i];
            
            meshTriCount++;
        }
    }
    
    obj->mesh2DWindowSpace->triangleCount = meshTriCount;
}

void ResizeMesh2D(Obj3D* obj) {
    //translate and scale 2D coordinates
    for(int i = 0; i < obj->mesh2DWindowSpace->triangleCount; i++) {
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

void ZSortMesh2D(Obj3D* obj) {

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