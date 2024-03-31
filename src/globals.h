#include "./abstract_data_types.h"
#include "./geometry_operations.h"

extern SDL_Window* my_window;
extern SDL_Renderer* my_renderer;

extern int game_is_running;

extern Vector3 vector3Null;

extern Obj3D* testObj;

extern Mesh* my_meshScaled;

extern Mesh* my_meshWorldCentered;
extern Mesh* my_meshRotatedX;
extern Mesh* my_meshRotatedY;
extern Mesh* my_meshRotatedZ;
extern Mesh* my_meshTranslatedFromPivot;
extern Mesh* my_meshScaled;
 
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
extern int errorKey;
