#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>

#include "./import_mesh.h"
#include "./constants.h"
#include "./globals.h"
#include "./abstract_data_types.h"
#include "./geometry_operations.h"

Mesh* ImportMesh() {
    Mesh* stl_mesh;
    FILE *file;

    int triangleCount = 0;
    char bufferCountTriangles[255];
    char bufferUpdateTriangles[255];


    file = fopen("./assets/STLoutput.txt", "r");
    
    if(file == NULL) {
        fprintf(stderr, "ERROR, the file was not opened\n");
        exit(-1);
    }

    while(fgets(bufferCountTriangles, 255, file)) {
        triangleCount++;
    }

    triangleCount /= 12;

    fclose(file);
    
    file = fopen("./assets/STLoutput.txt", "r");

    stl_mesh = CreateMesh(triangleCount);

    int lineCount = 0;
    int vectorPosition = 0;
    int triangleIndex = 0;
    int vertexIndex = 0;

    while(fgets(bufferUpdateTriangles, 255, file)) {
        switch (lineCount) {
            case 0:
                stl_mesh->triangle[triangleIndex].normal.x = atof(bufferUpdateTriangles);
                lineCount++;
                break;
            case 1:
                stl_mesh->triangle[triangleIndex].normal.y = atof(bufferUpdateTriangles);
                lineCount++;
                break;
            case 2:
                stl_mesh->triangle[triangleIndex].normal.z = atof(bufferUpdateTriangles);
                lineCount++;
                break;
            case 3:
                stl_mesh->triangle[triangleIndex].vertex[vertexIndex].x = atof(bufferUpdateTriangles);
                lineCount++;
                break;           
            case 4:
                stl_mesh->triangle[triangleIndex].vertex[vertexIndex].y = atof(bufferUpdateTriangles);
                lineCount++;
                break; 
            case 5:
                stl_mesh->triangle[triangleIndex].vertex[vertexIndex].z = atof(bufferUpdateTriangles);
                vertexIndex++;
                lineCount++;
                break;
            case 6:
                stl_mesh->triangle[triangleIndex].vertex[vertexIndex].x = atof(bufferUpdateTriangles);
                lineCount++;
                break;           
            case 7:
                stl_mesh->triangle[triangleIndex].vertex[vertexIndex].y = atof(bufferUpdateTriangles);
                lineCount++;
                break; 
            case 8:
                stl_mesh->triangle[triangleIndex].vertex[vertexIndex].z = atof(bufferUpdateTriangles);
                vertexIndex++;
                lineCount++;
                break;
            case 9:
                stl_mesh->triangle[triangleIndex].vertex[vertexIndex].x = atof(bufferUpdateTriangles);
                lineCount++;
                break;           
            case 10:
                stl_mesh->triangle[triangleIndex].vertex[vertexIndex].y = atof(bufferUpdateTriangles);
                lineCount++;
                break; 
            case 11:
                stl_mesh->triangle[triangleIndex].vertex[vertexIndex].z = atof(bufferUpdateTriangles);
                vertexIndex = 0;
                triangleIndex++;
                lineCount = 0;
                break;                                                     
        }

    }

    stl_mesh->pivot = vector4Null;

    fclose(file);

    //Assign shared triangles index and shared triangle count to each vertex
    for(int i = 0; i < stl_mesh->triangleCount; i++) {
        stl_mesh->triangle[i].vertex[0].sharedTrianglesCount = 0;
        stl_mesh->triangle[i].vertex[1].sharedTrianglesCount = 0;
        stl_mesh->triangle[i].vertex[2].sharedTrianglesCount = 0;
    }

    for(int i = 0; i < stl_mesh->triangleCount; i++) {
        for(int j = 0; j < 3; j++) {
            for(int a = 0; a < stl_mesh->triangleCount; a++) {
                for(int b = 0; b < 3; b++) {
                    if(
                        stl_mesh->triangle[i].vertex[j].x == stl_mesh->triangle[a].vertex[b].x &&
                        stl_mesh->triangle[i].vertex[j].y == stl_mesh->triangle[a].vertex[b].y &&
                        stl_mesh->triangle[i].vertex[j].z == stl_mesh->triangle[a].vertex[b].z
                        ) {
                            stl_mesh->triangle[i].vertex[j].sharedTrianglesIndex[ 
                                stl_mesh->triangle[i].vertex[j].sharedTrianglesCount] = a;
                            
                            stl_mesh->triangle[i].vertex[j].sharedTrianglesCount++;
                        }
                }
            }
        }
    }

    return stl_mesh;
} 