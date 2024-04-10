#include <stdio.h>
#include <SDL2/SDL.h>

#include "./constants.h"
#include "./globals.h"
#include "./abstract_data_types.h"
#include "./geometry_operations.h"
#include "./render.h"

void RenderTriangle(Triangle triangle);
void RenderObj(Obj3D* obj);

void render() {
    
    //render black screen
    SDL_SetRenderDrawColor(my_renderer, 40 , 40, 40, 255);
    SDL_RenderClear(my_renderer);
    
    RenderObj(my_obj);

    SDL_RenderPresent(my_renderer); //swap buffer

}

void RenderTriangle(Triangle triangle) {
    Vector2 v1, v2, v3, center, normal;
    
    v1.x = triangle.vertex[0].x;
    v1.y = triangle.vertex[0].y;
    v2.x = triangle.vertex[1].x;
    v2.y = triangle.vertex[1].y;
    v3.x = triangle.vertex[2].x;
    v3.y = triangle.vertex[2].y;
    center.x = triangle.center.x;
    center.y = triangle.center.y;
    normal.x = triangle.normal.x;
    normal.y = triangle.normal.y;
    
    SDL_Point p1, p2, p3;
    
    p1.x = v1.x;
    p1.y = v1.y;
    p2.x = v2.x;
    p2.y = v2.y;
    p3.x = v3.x;
    p3.y = v3.y;
    
    SDL_Point points[4] = {p1, p2, p3, p1};
    
    int shadeColor;
    if(triangle.shadeColor < 0) {
        shadeColor = (int)(-triangle.shadeColor * 255.0F)/3;
    } 
    else shadeColor = (int)(triangle.shadeColor * 255.0F);
    SDL_Vertex vertices[3] = {
        {
            {v1.x, v1.y},
            {shadeColor, shadeColor, shadeColor, 255},
            {0.0F, 0.0F}
        },
        {
            {v2.x, v2.y},
            {shadeColor, shadeColor, shadeColor, 255},
            {0.0F, 0.0F}
        },
        {
            {v3.x, v3.y},
            {shadeColor, shadeColor, shadeColor, 255},
            {0.0F, 0.0F}
        },
    };

    //fill triangles
    SDL_RenderGeometry(my_renderer, NULL, vertices, 3 ,NULL , 0);

    if(debugKey1 > 0) {
        //draw normals
        SDL_SetRenderDrawColor(my_renderer, 255, 0, 0 ,255);
        SDL_RenderDrawLine(
            my_renderer,
            (int)center.x,
            (int)center.y,
            (int)normal.x,
            (int)normal.y
        );
    }
    if(debugKey2 > 0) {
        //draw triangle center points
        SDL_SetRenderDrawColor(my_renderer, 0, 255, 0, 255);
        SDL_RenderDrawPoint(my_renderer, center.x, center.y);

    }
    if(debugKey3 > 0) {
        //draw triangle wireframe
        SDL_SetRenderDrawColor(my_renderer, 100, 100, 100, 255);
        SDL_RenderDrawLines(
            my_renderer, 
            points,
            4
        );
    }
}

void RenderObj(Obj3D* obj) {
    for(int i = 0; i < obj->mesh2DWindowSpaceZSorted->triangleCount; i++) {
        RenderTriangle(obj->mesh2DWindowSpaceZSorted->triangle[i]);
    }
}


