#include <stdio.h>
#include <SDL2/SDL.h>

#include "./constants.h"
#include "./globals.h"
#include "./tad.h"
#include "./render.h"

void RenderTriangle(Triangle tri);

void render() {
    
    //render black screen
    SDL_SetRenderDrawColor(my_renderer, 50, 50, 50, 255);
    SDL_RenderClear(my_renderer);

    SDL_SetRenderDrawColor(my_renderer, 255, 50, 50, 255);
    
    //TESTING

    /*SDL_RenderDrawPoint(my_renderer, ponto1.x, ponto1.y);
    SDL_RenderDrawPoint(my_renderer, ponto2.x, ponto2.y);
    SDL_RenderDrawPoint(my_renderer, ponto3.x, ponto3.y);*/

    RenderTriangle(tri4);
   
    SDL_RenderPresent(my_renderer); //swap buffer

}

void RenderTriangle(Triangle tri) {
    SDL_Point p1, p2, p3;
    
    p1.x = tri.point[0].x + WINDOW_WIDTH/2;
    p1.y = tri.point[0].y + WINDOW_HEIGHT/2 - 2*tri.point[0].y;
    p2.x = tri.point[1].x + WINDOW_WIDTH/2;
    p2.y = tri.point[1].y + WINDOW_HEIGHT/2 - 2*tri.point[1].y;
    p3.x = tri.point[2].x + WINDOW_WIDTH/2;
    p3.y = tri.point[2].y + WINDOW_HEIGHT/2 - 2*tri.point[2].y;

    SDL_Point points[4] = {p1, p2, p3, p1};

    SDL_RenderDrawLines(
        my_renderer, 
        points,
        4
    );
}

