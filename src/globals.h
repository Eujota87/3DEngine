#include "./abstract_data_types.h"

extern SDL_Window* my_window;
extern SDL_Renderer* my_renderer;

extern int game_is_running;

extern Mesh* my_meshScaled;
extern Mesh* my_meshRotatedX;
extern Mesh* my_meshRotatedY;
extern Mesh* my_meshRotatedZ;
extern Mesh* my_meshTranslated;
 
extern Matrix4 projectionMatrix;

extern float zNear;
extern float zFar;
extern float fov;
extern float aspectRatio;
extern float fovRad;

extern float inputMoveX;
extern float inputMoveY;
extern float inputMoveZ;
extern float inputRotateX;
extern float inputRotateY;
extern float inputRotateZ;

