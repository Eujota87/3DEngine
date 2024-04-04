#ifndef GEOMETRY_OPERTAIONS
#define GEOMETRY_OPERTAIONS

Vector4 MulMatrix4Vector3(Vector4 vecIn, Matrix4 mat4);

void TranslateObjToPivot(Obj3D* obj);
void TranslateObjToWorldCenter(Obj3D* obj);

void InputMoveObjPivot(Obj3D* obj, float delta_time);
void RotateObj(Obj3D* obj, float degrees, char axis);

Triangle ProjectTriangle(Triangle triangleIn, Matrix4 matrix);
void ProjectObjMesh(Obj3D* obj, Matrix4 matrix);

void UpdateTriangleCenter(Obj3D* obj);

void PrintMeshData(Mesh* mesh);

#endif