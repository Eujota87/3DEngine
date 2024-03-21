#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>

#include "import_mesh.h"
#include "constants.h"
#include "globals.h"
#include "tad.h"

Mesh* ImportMesh() {
    Mesh* STLmesh;
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

    STLmesh = CreateMesh(triangleCount);

    int lineCount = 0;
    int vectorPosition = 0;
    int triangleIndex = 0;
    int vertexIndex = 0;

    while(fgets(bufferUpdateTriangles, 255, file)) {
        switch (lineCount) {
            case 0:
                STLmesh->triangle[triangleIndex].normal.x = atof(bufferUpdateTriangles);
                lineCount++;
                break;
            case 1:
                STLmesh->triangle[triangleIndex].normal.y = atof(bufferUpdateTriangles);
                lineCount++;
                break;
            case 2:
                STLmesh->triangle[triangleIndex].normal.z = atof(bufferUpdateTriangles);
                lineCount++;
                break;
            case 3:
                STLmesh->triangle[triangleIndex].vertex[vertexIndex].x = atof(bufferUpdateTriangles);
                lineCount++;
                break;           
            case 4:
                STLmesh->triangle[triangleIndex].vertex[vertexIndex].y = atof(bufferUpdateTriangles);
                lineCount++;
                break; 
            case 5:
                STLmesh->triangle[triangleIndex].vertex[vertexIndex].z = atof(bufferUpdateTriangles);
                vertexIndex++;
                lineCount++;
                break;
            case 6:
                STLmesh->triangle[triangleIndex].vertex[vertexIndex].x = atof(bufferUpdateTriangles);
                lineCount++;
                break;           
            case 7:
                STLmesh->triangle[triangleIndex].vertex[vertexIndex].y = atof(bufferUpdateTriangles);
                lineCount++;
                break; 
            case 8:
                STLmesh->triangle[triangleIndex].vertex[vertexIndex].z = atof(bufferUpdateTriangles);
                vertexIndex++;
                lineCount++;
                break;
            case 9:
                STLmesh->triangle[triangleIndex].vertex[vertexIndex].x = atof(bufferUpdateTriangles);
                lineCount++;
                break;           
            case 10:
                STLmesh->triangle[triangleIndex].vertex[vertexIndex].y = atof(bufferUpdateTriangles);
                lineCount++;
                break; 
            case 11:
                STLmesh->triangle[triangleIndex].vertex[vertexIndex].z = atof(bufferUpdateTriangles);
                vertexIndex = 0;
                triangleIndex++;
                lineCount = 0;
                break;                                                     
        }

    }

    fclose(file);

    
    return STLmesh;
} 