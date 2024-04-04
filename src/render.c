#include <stdio.h>
#include <SDL2/SDL.h>

#include "./constants.h"
#include "./globals.h"
#include "./abstract_data_types.h"
#include "./geometry_operations.h"
#include "./render.h"

void RenderTriangleWireframe(Triangle triangle);
void RenderObjWireframe(Obj3D* obj);

void render() {
    
    //render black screen
    SDL_SetRenderDrawColor(my_renderer, 50, 50, 50, 255);
    SDL_RenderClear(my_renderer);
    
    RenderObjWireframe(my_obj);

    SDL_RenderPresent(my_renderer); //swap buffer

}

void RenderTriangleWireframe(Triangle triangle) {
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

    //scale points    
    v1.x += 1.0F;
    v1.y += 1.0F;
    v2.x += 1.0F;
    v2.y += 1.0F;
    v3.x += 1.0F;
    v3.y += 1.0F;
    center.x += 1.0F;
    center.y += 1.0F;
    normal.x += 1.0F;
    normal.y += 1.0F;

    //move points to screen center
    v1.x *= 0.5F * (float)WINDOW_WIDTH;
    v1.y *= 0.5F * (float)WINDOW_HEIGHT;
    v2.x *= 0.5F * (float)WINDOW_WIDTH;
    v2.y *= 0.5F * (float)WINDOW_HEIGHT;
    v3.x *= 0.5F * (float)WINDOW_WIDTH;
    v3.y *= 0.5F * (float)WINDOW_HEIGHT;
    center.x *= 0.5F * (float)WINDOW_WIDTH;
    center.y *= 0.5F * (float)WINDOW_HEIGHT;
    normal.x *= 0.5F * (float)WINDOW_WIDTH;
    normal.y *= 0.5F * (float)WINDOW_HEIGHT;

    SDL_Point p1, p2, p3;
    
    p1.x = v1.x;
    p1.y = v1.y;
    p2.x = v2.x;
    p2.y = v2.y;
    p3.x = v3.x;
    p3.y = v3.y;
    
    SDL_Point points_vertex[4] = {p1, p2, p3, p1};

    if(errorKey < 0) {
        //draw normals
        SDL_SetRenderDrawColor(my_renderer, 255, 255, 0 ,20);
        SDL_RenderDrawLine(
            my_renderer,
            (int)center.x,
            (int)center.y,
            (int)normal.x,
            (int)normal.y
        );
    }

    //draw triangle center points
    SDL_SetRenderDrawColor(my_renderer, 255, 0, 0, 255);
    SDL_RenderDrawPoint(my_renderer, center.x, center.y);

    //draw triangle wireframe
    SDL_SetRenderDrawColor(my_renderer, 0, 255, 0, 155);
    SDL_RenderDrawLines(
        my_renderer, 
        points_vertex,
        4
    );
}

void RenderObjWireframe(Obj3D* obj) {
    for(int i = 0; i < obj->triangleCount; i++) {
        //back face culling (as normals are world centered, display negative dot prod. angles)
        if(DotProductVec3(vector4DirectionZ, NormalToWorldCenter(obj, i)) < 0.0F) {
            RenderTriangleWireframe(obj->meshProjected->triangle[i]);
        }
    }
}



