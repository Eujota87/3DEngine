#include <stdio.h>
#include "C:\SDL2\x86_64-w64-mingw32\include\SDL2\SDL.h"
#include "./constants.h"
#include "./globals.h"
#include "./abstract_data_types.h"
#include "./geometry_operations.h"
#include "./mesh_operations.h"
#include "./render.h"

void render() {
    
    //render black screen
    SDL_SetRenderDrawColor(my_renderer, 30 , 30, 30, 255);
    SDL_RenderClear(my_renderer);
    
    RenderObj(my_obj);

    SDL_RenderPresent(my_renderer); //swap buffer

}

void RenderTriangle(Triangle triangle) {
    
    Vector3 finalColor[3];
    Vector3 baseColor;
    baseColor.x = 0.8F;
    baseColor.y = 0.2F;
    baseColor.z = 0.4F;
    float SpecularAmount = 100.0F + renderSpecularAmount*255.0F;
    float SpecularLowLimit = 0.0F + renderSpecularLowLimit;
    float shadowLowLimit = 0.1F + renderShadowLowLimit; 

    if(SpecularAmount < 0) SpecularAmount = 0;
    if(SpecularLowLimit < 0) SpecularLowLimit = 0;
    if(shadowLowLimit < 0) shadowLowLimit = 0;   
    
    Vector4 v[3];
    Vector2 center, normal;
    
    v[0].x = triangle.vertex[0].x;
    v[0].y = triangle.vertex[0].y;
    v[1].x = triangle.vertex[1].x;
    v[1].y = triangle.vertex[1].y;
    v[2].x = triangle.vertex[2].x;
    v[2].y = triangle.vertex[2].y;
    center.x = triangle.center.x;
    center.y = triangle.center.y;
    normal.x = triangle.normal.x;
    normal.y = triangle.normal.y;
    v[0].SpecularularColor = 0.0F;
    v[1].SpecularularColor = 0.0F;
    v[2].SpecularularColor = 0.0F;

    
    SDL_Point p1, p2, p3;
    
    p1.x = v[0].x;
    p1.y = v[0].y;
    p2.x = v[1].x;
    p2.y = v[1].y;
    p3.x = v[2].x;
    p3.y = v[2].y;
    
    SDL_Point points[4] = {p1, p2, p3, p1};
    
    for(int i = 0; i < 3; i++) {
        triangle.vertex[i].shadeColor = (triangle.vertex[i].shadeColor + shadowLowLimit) / (1+shadowLowLimit);
    }


    if(triangle.vertex[0].shadeColor < 0) {
        v[0].shadeColor = (int)(-triangle.vertex[0].shadeColor * 255.0F);
    } 
    else v[0].shadeColor = (int)(triangle.vertex[0].shadeColor * 255.0F);
    
    if(triangle.vertex[1].shadeColor < 0) {
        v[1].shadeColor = (int)(-triangle.vertex[1].shadeColor * 255.0F);
    } 
    else v[1].shadeColor = (int)(triangle.vertex[1].shadeColor * 255.0F);

    if(triangle.vertex[2].shadeColor < 0) {
        v[2].shadeColor = (int)(-triangle.vertex[2].shadeColor * 255.0F);
    } 
    else v[2].shadeColor = (int)(triangle.vertex[2].shadeColor * 255.0F);


    if(triangle.vertex[0].SpecularularColor > SpecularLowLimit) {
        v[0].SpecularularColor = (int)(triangle.vertex[0].SpecularularColor * SpecularAmount);
    }
    if(triangle.vertex[1].SpecularularColor > SpecularLowLimit) {
        v[1].SpecularularColor = (int)(triangle.vertex[1].SpecularularColor * SpecularAmount);
    }
    if(triangle.vertex[2].SpecularularColor > SpecularLowLimit) {
        v[2].SpecularularColor = (int)(triangle.vertex[2].SpecularularColor * SpecularAmount);
    }

    for(int i = 0; i < 3; i++) {
        finalColor[i].x = (v[i].shadeColor * baseColor.x) + v[i].SpecularularColor;
        if(finalColor[i].x >= 255.0F) finalColor[i].x = 255.0F;
        finalColor[i].y = (v[i].shadeColor * baseColor.y) + v[i].SpecularularColor;
        if(finalColor[i].y >= 255.0F) finalColor[i].y = 255.0F;
        finalColor[i].z = (v[i].shadeColor * baseColor.z) + v[i].SpecularularColor;
        if(finalColor[i].z >= 255.0F) finalColor[i].z = 255.0F;
    }

    //triangle rendering
    int shadeColor;
    if(triangle.shadeColor < 0) {
        shadeColor = (int)(-triangle.shadeColor * 255.0F)/3;
    } 
    else shadeColor = (int)(triangle.shadeColor * 255.0F);

    SDL_Vertex vertices[3] = {
        {
            {v[0].x, v[0].y},
            {finalColor[0].x, finalColor[0].y, finalColor[0].z, 255},
            {0.0F, 0.0F}
        },
        {
            {v[1].x, v[1].y},
            {finalColor[1].x, finalColor[1].y, finalColor[1].z, 255},
            {0.0F, 0.0F}
        },
        {
            {v[2].x, v[2].y},
            {finalColor[2].x, finalColor[2].y, finalColor[2].z, 255},
            {0.0F, 0.0F}
        },
    };

    if(debugKey4 > 0) {
        for(int i = 0; i < 3; i++) {
            vertices[i].color.r = shadeColor * baseColor.x;
            vertices[i].color.g = shadeColor * baseColor.y;
            vertices[i].color.b = shadeColor * baseColor.z;
            vertices[i].color.a = 255;
        }
    }

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
        SDL_SetRenderDrawColor(my_renderer, 210, 210, 210, 255);
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


void LightingCalculation(Obj3D* obj) {
    
    //triangle shade color
    for(int i = 0; i < obj->triangleCount; i++) {
        for(int j = 0; j < 3; j++) {
            obj->meshProjected->triangle[i].vertex[j].shadeColor = (
                DotProductVec4x3(NormalizeVector4(lightDirection), 
                NormalizeVector3(obj->meshImported->triangle[i].vertex[j].normal))
            );
        }
    }
    for(int i = 0; i < obj->triangleCount; i++) {
        for(int j = 0; j < 3; j++) {
            Vector4 reflection;
            Vector4 projectLightToNormal;
            float dotLightToNormal = 0;
            dotLightToNormal = DotProductVec4x3(
                NormalizeVector4(lightDirection),
                NormalizeVector3(obj->meshImported->triangle[i].vertex[j].normal)
            ); 
            projectLightToNormal.x = 
            obj->meshImported->triangle[i].vertex[j].normal.x * dotLightToNormal;
            projectLightToNormal.y = 
            obj->meshImported->triangle[i].vertex[j].normal.y * dotLightToNormal;
            projectLightToNormal.z = 
            obj->meshImported->triangle[i].vertex[j].normal.z * dotLightToNormal;

            reflection.x =
            -lightDirection.x + 2*(projectLightToNormal.x);
            reflection.y =
            -lightDirection.y + 2*(projectLightToNormal.y);
            reflection.z =
            -lightDirection.z + 2*(projectLightToNormal.z);
            
            Vector4 viewVector;
            viewVector.x = -obj->meshBufferOut->triangle[i].center.x;
            viewVector.y = -obj->meshBufferOut->triangle[i].center.y;
            viewVector.z = -obj->meshBufferOut->triangle[i].center.z;

            obj->meshProjected->triangle[i].vertex[j].SpecularularColor =
            DotProductVec4(
                NormalizeVector4(viewVector),
                NormalizeVector4(reflection)
            );
        }
    }
    
    /*
    //triangle shade color
     for(int i = 0; i < obj->triangleCount; i++) {
        obj->meshProjected->triangle[i].shadeColor = (
            DotProductVec4(NormalizeVector4(lightDirection), NormalizeVector4(NormalToWorldCenter(obj, i)))
        );
     }

    //vertex shade color
     for(int i = 0; i < obj->triangleCount; i++) {
        for(int j = 0; j < 3; j++) {
            
            float shadeColorSum = 0;
            int sharedTriangleCount = obj->meshImported->triangle[i].vertex[j].sharedTrianglesCount;
            
            for(int k = 0; k < sharedTriangleCount; k++) {
                shadeColorSum += 
                obj->meshProjected->triangle[
                    obj->meshImported->triangle[i].vertex[j].sharedTrianglesIndex[k]].shadeColor;
            }

            obj->meshProjected->triangle[i].vertex[j].shadeColor = 
            shadeColorSum / obj->meshImported->triangle[i].vertex[j].sharedTrianglesCount;
        }
     }*/

}