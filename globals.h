#include "./tad.h"

extern SDL_Window* my_window;
extern SDL_Renderer* my_renderer;

extern int game_is_running;

extern float near;
extern float far;
extern float fov;
extern float aspectRatio;
extern float fovRad;

extern Mesh* my_meshRotated;
 

extern Matrix4 projectionMatrix;
extern Matrix4 rotationMatrix_X;
extern Matrix4 rotationMatrix_Y;
extern Matrix4 rotationMatrix_Z;

//------------------------------------------------------------------------------
//TESTING

extern float moveX;
extern float moveY;
extern float moveZ;
extern float rotateX;
extern float rotateY;
extern float rotateZ;

//------------------------------------------------------------------------------

