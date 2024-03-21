#include <stdio.h>
#include <SDL2/SDL.h>

#include "./constants.h"
#include "./globals.h"
#include "./tad.h"
#include "./render.h"

void RenderTriangle(Triangle triangle);
void RenderMesh(Mesh* mesh);

void render(Mesh* my_meshProjected) {
    
    //render black screen
    SDL_SetRenderDrawColor(my_renderer, 50, 50, 50, 255);
    SDL_RenderClear(my_renderer);

    SDL_SetRenderDrawColor(my_renderer, 255, 50, 50, 255);
    
    RenderMesh(my_meshProjected);
   
    SDL_RenderPresent(my_renderer); //swap buffer

}

void RenderTriangle(Triangle triangle) {
    Vector2 v1, v2, v3;
    
    v1.x = triangle.vertex[0].x;
    v1.y = triangle.vertex[0].y;
    v2.x = triangle.vertex[1].x;
    v2.y = triangle.vertex[1].y;
    v3.x = triangle.vertex[2].x;
    v3.y = triangle.vertex[2].y;
    
    v1.x += 1.0f;
    v1.y += 1.0f;
    v2.x += 1.0f;
    v2.y += 1.0f;
    v3.x += 1.0f;
    v3.y += 1.0f;

    v1.x *= 0.5f * (float)WINDOW_WIDTH;
    v1.y *= 0.5f * (float)WINDOW_HEIGHT;
    v2.x *= 0.5f * (float)WINDOW_WIDTH;
    v2.y *= 0.5f * (float)WINDOW_HEIGHT;
    v3.x *= 0.5f * (float)WINDOW_WIDTH;
    v3.y *= 0.5f * (float)WINDOW_HEIGHT; 

    SDL_Point p1, p2, p3;
    
    p1.x = v1.x;
    p1.y = v1.y;
    p2.x = v2.x;
    p2.y = v2.y;
    p3.x = v3.x;
    p3.y = v3.y;



    SDL_Point points[4] = {p1, p2, p3, p1};

    SDL_RenderDrawLines(
        my_renderer, 
        points,
        4
    );
}

void RenderMesh(Mesh* mesh) {
    int triangleCount = mesh->triangleCount; 
    for(int i = 0; i < triangleCount; i++) {
        RenderTriangle(mesh->triangle[i]);
    }
}



