#ifndef RENDER
#define RENDER

void render();

void RenderTriangle(Triangle triangle);
void RenderObj(Obj3D* obj);
void LightingCalculation(Obj3D* obj);

#endif