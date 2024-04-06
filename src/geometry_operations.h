#ifndef GEOMETRY_OPERTAIONS
#define GEOMETRY_OPERTAIONS

Vector4 MulMatrix4Vector3(Vector4 vecIn, Matrix4 mat4);

float DotProductVec2(Vector4 vec1, Vector4 vec2);
float DotProductVec3(Vector4 vec1, Vector4 vec2);

void TranslateObjToPivot(Obj3D* obj);
void TranslateObjToWorldCenter(Obj3D* obj);

Vector4 GetVector4(Vector4 vecStart, Vector4 vecEnd);
Vector4 GetVector4Normalized(Vector4 vecStart, Vector4 vecEnd);
float GetVector4Length(Vector4 vecIn);
Vector4 NormalizeVector4(Vector4 vecIn);

Vector4 NormalToWorldCenter(Obj3D* obj, int triangle_index);

void InputMoveObjPivot(Obj3D* obj, float delta_time);
void RotateObj(Obj3D* obj, float degrees, char axis);

Triangle ProjectTriangle(Triangle triangleIn, Matrix4 matrix);
void ProjectObjMesh(Obj3D* obj, Matrix4 matrix);

void UpdateTriangleCenter(Obj3D* obj);

void PrintMeshData(Mesh* mesh);

#endif