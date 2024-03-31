#ifndef GEOMETRY_OPERTAIONS
#define GEOMETRY_OPERTAIONS

Vector3 MulMatrix4Vector3(Vector3 vecIn, Matrix4 mat4);

void TranslateObjFromPivot(Obj3D* obj);
void MeshToWorldCenter(Mesh* meshIn, Mesh* meshOut);

Triangle ProjectTriangle(Triangle triangleIn, Matrix4 matrix);
void ProjectObjMesh(Obj3D* obj, Matrix4 matrix);

void InputMoveMesh(Mesh* mesh, float delta_time);
void InputMoveObjPivot(Obj3D* obj, float delta_time);
void TranslateMesh(Mesh* meshIn, Mesh* meshOut, float distance );
void RotateObj(Obj3D* obj, float degrees, char axis);

void PrintMeshData(Mesh* mesh);

#endif