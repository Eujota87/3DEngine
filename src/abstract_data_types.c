#include <stdio.h>
#include <SDL2/SDL.h>

#include "./abstract_data_types.h"
#include "./geometry_operations.h"
#include "./constants.h"
#include "./globals.h"


Mesh* CreateMesh(int triCount) {
    Mesh* m = malloc(sizeof(Mesh));
    m->triangleCount = triCount;
    m->triangle = malloc(sizeof(Triangle) * triCount);
    return m;
}