#ifndef GEOMETRY_OPERTAIONS
#define GEOMETRY_OPERTAIONS

Vector4 MulMatrix4Vector3(Vector4 vecIn, Matrix4 mat4);

//fix this mess
float DotProductVec2(Vector4 vec1, Vector4 vec2);
float DotProductVec3(Vector4 vec1, Vector3 vec2);
float DotProductVec4(Vector4 vec1, Vector4 vec2);

void TranslateObjToPivot(Obj3D* obj);
void TranslateObjToWorldCenter(Obj3D* obj);

float GetVector3Length(Vector3 vecIn);
Vector3 NormalizeVector3(Vector3 vecIn);

Vector4 GetVector4(Vector4 vecStart, Vector4 vecEnd);
Vector4 GetVector4Normalized(Vector4 vecStart, Vector4 vecEnd);
float GetVector4Length(Vector4 vecIn);
Vector4 NormalizeVector4(Vector4 vecIn);

Vector4 NormalToWorldCenter(Obj3D* obj, int triangle_index);

void InputMoveObjPivot(Obj3D* obj, float delta_time);
void RotateObj(Obj3D* obj, float degrees, char axis);

void UpdateVertexNormal(Obj3D* obj);

Triangle ProjectTriangle(Triangle triangleIn, Matrix4 matrix);
void ProjectObjMesh(Obj3D* obj, Matrix4 matrix);

void UpdateTriangleCenter(Obj3D* obj);

void LightingCalculation(Obj3D* obj);

void BackfaceCullingMesh2D(Obj3D* obj);
void ResizeMesh2D(Obj3D* obj);
void ZSortMesh2D(Obj3D* obj);
void PrintMeshData(Mesh* mesh);

#endif