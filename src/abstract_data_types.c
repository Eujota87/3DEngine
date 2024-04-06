#include <stdio.h>
#include <SDL2/SDL.h>

#include "./abstract_data_types.h"
#include "./geometry_operations.h"
#include "./constants.h"
#include "./globals.h"


Mesh* CreateMesh(int triCount) {
    Mesh* mesh = malloc(sizeof(Mesh));
    mesh->triangleCount = triCount;
    mesh->triangle = malloc(sizeof(Triangle) * triCount);
    return mesh;
}

Obj3D* CreateObj3D(Mesh* mesh) {
    Obj3D* obj = malloc(sizeof(Obj3D));
    
    obj->meshImported = mesh;
    obj->meshBufferIn = CreateMesh(mesh->triangleCount);
    obj->meshBufferOut = CreateMesh(mesh->triangleCount);
    obj->meshProjected = CreateMesh(mesh->triangleCount);
    obj->mesh2DWindowSpace = CreateMesh(mesh->triangleCount);
    obj->mesh2DWindowSpaceZSorted = CreateMesh(mesh->triangleCount);
    
    obj->pivot = vector4Null; //change this for a function calculating center of mass
    obj->triangleCount = mesh->triangleCount;
    
    obj->meshBufferOut = obj->meshImported;
    return obj;
}
